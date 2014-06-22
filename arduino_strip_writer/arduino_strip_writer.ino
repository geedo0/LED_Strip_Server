#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS	29
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, 6, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(9600);
	strip.begin();
	strip.show();
}

void loop() {
}

void serialEvent() {
	char buffer[20];
	int index;
	long color;
	
	//Obtain Transmission length
	while(Serial.available() < 2);
	buffer[0] = Serial.read();
	buffer[1] = Serial.read();
	buffer[2] = 0x00;
	int size = strtoul(buffer, NULL, 16);
	Serial.readBytes(buffer, size);
	
	switch(buffer[0]) {
		case 'a':
			/*
			*	Set the entire strip to a single color
			*	Format:	RGB		Size: 7
			*	Where:	RGB = Color
			*/
			buffer[7] = 0x00;
			color = strtoul(buffer + 1, NULL, 16);
			setAllPixels(color);
			break;
		case 'b':
			/*
			*	Set a single pixel's color
			*	Format:	N RGB		Size: 9
			*	Where:	N = Pixel number, RGB = Color
			*/
			buffer[9] = 0x00;
			color = strtoul(buffer + 3, NULL, 16);
			buffer[3] = 0x00;
			index = strtoul(buffer + 1, NULL, 16);
			strip.setPixelColor(index, color);
			break;
		default:
			break;
	}
	strip.show();
}

void setAllPixels(uint32_t color) {
	for(int i = 0; i < NUM_PIXELS; i++) {
		strip.setPixelColor(i, color);
	}
}


