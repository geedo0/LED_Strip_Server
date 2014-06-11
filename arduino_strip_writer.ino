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
	char buffer[10];
	int count = 0;
	
	int size = Serial.read();
	while(Serial.available() != size);
	while(Serial.available())
		buffer[count++] = Serial.read();
	
	switch(buffer[0]) {
		case 0x00:
			/*
			*	Set the entire strip to a single color
			*	Format:	RGB		Size: 4
			*	Where:	RGB = Color
			*/
			setAllPixels(getColorFromStream(&buffer[1]));
			//setAllPixels(buffer[1]);
			break;
		case 0x01:
			/*
			*	Set a single pixel's color
			*	Format:	N RGB		Size: 5
			*	Where:	N = Pixel number, RGB = Color
			*/
			strip.setPixelColor(buffer[1], getColorFromStream(&buffer[2]));
			break;
		default:
			break;
	}
	strip.show();
}

uint32_t getColorFromStream(char *buffer) {
	return strip.Color(buffer[0], buffer[1], buffer[2]);
}

void setAllPixels(uint32_t color) {
	for(int i = 0; i < NUM_PIXELS; i++) {
		strip.setPixelColor(i, color);
	}
}


