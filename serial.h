#ifndef SERIAL.H
#define SERIAL.H


#include <termios.h>
#include <iostream>

namespace Serial_Setup{
void configure_termios(struct termios * termios_config, int device_file_descriptor,speed_t input_baud,speed_t output_baud); 

int open_device_file(char * device_path); 

void read_device(int fd, char * buffer, size_t buffer_size)

void write_device(int fd, std::string message) {

char* get_device_path(char ** argv, int argc); 

}; 


#endif