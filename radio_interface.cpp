#include <iostream> 
#include <thread>
#include <termios.h>
#include "serial.h"
const speed_t RADIO_BAUD  = B57600; 



int main(int argc, char** argv){
        int fd = serial_setup::open_device_file(serial_setup::get_device_path(argv, argc)); 
        struct termios termios_config; 
        serial_setup::configure_termios(&termios_config,fd, RADIO_BAUD, RADIO_BAUD);
        std::thread read_thread(serial_setup::read_device, fd); 
        std::thread write_thread(serial_setup::write_device, fd); 
        read_thread.join(); 
        write_thread.join(); 
        close(fd);
}
