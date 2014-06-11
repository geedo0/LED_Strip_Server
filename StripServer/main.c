#include <stdio.h>
#include <wiringSerial.h>
#include "main.h"

//Test sending command to color lights blue
char sendBuffer[] = {0x04, 0x00, 0x00, 0x00, 0xff};

int main() {
	int fd;
	
	fd = serialOpen("/dev/ttyAMA0", 9600);
	putBuffer(fd, sendBuffer, 5); 
	serialClose(fd);	
	
	return 0;
}

void putBuffer(int fd, char* buffer, int length) {
	int i;
	for(i = 0; i < length; i++) {
		serialPutchar(fd, buffer[i]);
	}
}

void setSinglePixel(int fd, int pixel, unsigned long color) {
	char buffer[6];
	buffer[0] = 5;
	buffer[1] = 0x01;
	buffer[2] = pixel;
	setRgbBuffer(buffer + 3, color);
	putBuffer(fd, buffer, 6);
}

void setRgbBuffer(char* buffer, unsigned long color) {
	int i;
	for(i = 0; i < 3; i++) {
		buffer[i] = color & 0xff;
		color >>= 8;
	}
}

void setStripColor(int fd, unsigned long color) {
	char buffer[5];
	buffer[0] = 4;
	buffer[1] = 0x00;
	setRgbBuffer(buffer, color);
	putBuffer(fd, buffer, 5);
}

unsigned long getColor(unsigned char r, unsigned char g, unsigned char b) {
	long out = 0;
	out |= b;
	out <<= 8;
	out |= g;
	out <<= 8;
	out |= r;
	
	return out;
}
