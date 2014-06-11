#include <stdio.h>
#include <wiringSerial.h>
#include "main.h"

int main() {
	int fd;
	int input;
	unsigned long inColor;
	
	fd = serialOpen("/dev/ttyAMA0", 9600);
	while(1) {
		printf("Select an option:\n1) Color strip one color\n2) Color single pixel\n");
		scanf("%i", &input);
		printf("Enter RGB value in hex: ");
		scanf("%x", &inColor);
		switch(input) {
			case 1:
				setStripColor(fd, inColor);
				break;
			case 2:
				printf("Enter pixel number: ");
				scanf("%i", &input);
				setSinglePixel(fd, input, inColor);
				break;
			default:
				break;
		}
	}
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
	for(i = 2; i >= 0; i--) {
		buffer[i] = color & 0xff;
		color >>= 8;
	}
}

void setStripColor(int fd, unsigned long color) {
	char buffer[5];
	buffer[0] = 4;
	buffer[1] = 0x00;
	setRgbBuffer(buffer + 2, color);
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
