#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "serial.h"

serial_t serial_init(char *pathname) {
	serial_t serial = fopen(pathname, "r+");

	struct termios tty;
	if (tcgetattr(fileno(serial), &tty)) {
		puts("Failed to initialize the serial port");
		exit(-1);
	}

	cfsetospeed(&tty, BAUD_RATE);
	cfsetispeed(&tty, BAUD_RATE);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
	tty.c_iflag &= ~IGNBRK;
	tty.c_lflag = 0;
	tty.c_cc[VMIN] = 0;
	tty.c_cc[VTIME] = 5;
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~(PARENB | PARODD);
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr(fileno(serial), TCSANOW, &tty)) {
		puts("Failed to initialize the serial port");
		exit(-1);
	}

	return serial;
}

int serial_write(serial_t serial, char *str) {
	return fprintf(serial, "%s", str); 
}

char *serial_read(serial_t serial, char *buf, int count) {
	return fgets(buf, count, serial);
}

