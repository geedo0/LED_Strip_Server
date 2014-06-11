#ifndef MAIN_H
#define MAIN_H

void putBuffer(int fd, char* buffer, int length);
void setSinglePixel(int fd, int pixel, unsigned long color);
void setStripColor(int fd, unsigned long color);
unsigned long getColor(unsigned char r, unsigned char g, unsigned char b);
void setRgbBuffer(char* buffer, unsigned long color);

#endif
