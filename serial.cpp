#include <iostream> 
#include <unistd.h> 
#include <fcntl.h>
#include <termios.h> 
#include "serial.h"


namespace serial_setup{
void configure_termios(struct termios * termios_config, int device_file_descriptor,speed_t input_baud,speed_t output_baud){

        if(tcgetattr(device_file_descriptor, termios_config)< 0){
         std::cout<< "could not get previous configuration for device\n";
         exit(0); 
        }

        cfmakeraw(termios_config); 
        if( cfsetispeed(termios_config, input_baud)< 0 ||  cfsetospeed(termios_config, output_baud)  < 0){
          std::cout<< "failed to set input/output baud rate\n"; 
          exit(0);  
        }
        tcsetattr(device_file_descriptor,TCSANOW, termios_config); 
}

int open_device_file(char * device_path){
        int fd = open(device_path, O_RDWR|O_NDELAY); 
        if(fd < 0){
                std::cout<<"could not open device\n";
               exit(0); 
        }
        return fd; 
}


void read_device(int fd, char * buffer, size_t buffer_size) {
    while (true) {
        ssize_t bytes_read = read(fd, buffer, buffer_size-1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate to make it a string
        }
    }
}

void write_device(int fd, std::string message) {
    while (true) {
        ssize_t bytes_written = write(fd, message.c_str(), message.size());
        if (bytes_written < 0) {
            std::cout << "Failed to write to device\n";
        }
        usleep(1000000); // Sleep 1 second between writes
    }
}

char* get_device_path(char ** argv, int argc){
    return argv[1]; 
}
}