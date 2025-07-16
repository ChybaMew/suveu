#include <stdio.h>
#include <termios.h>

#define BAUD_RATE B9600

typedef FILE * serial_t;

serial_t serial_init(char *);
int serial_write(serial_t, char *);
char *serial_read(serial_t, char *, int);

