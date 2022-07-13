/*
 * main.cpp
 *
 * RGB LED example. Cycles through colours of the rainbow
 *
 *  Created on: 9 Jun 2022
 *      Author: jondurrant
 */

#include "RGBLED.h"
#include <stdio.h>

#define DELAY 2000 // in microseconds

//Rainbow sequence as Red, Green, Blue tuples
uint8_t rainbow[][3]= {
	{0x94, 0x00, 0xD3},
	{0x4B, 0x00, 0x82},
	{0x00, 0x00, 0xFF},
	{0x00, 0xFF, 0x00},
	{0xFF, 0xFF, 0x00},
	{0xFF, 0x7F, 0x00},
	{0xFF, 0x00, 0x00}
};

int main(){

	stdio_init_all();

	RGBLED rgb(2, 3, 4);

	while (true){
		for (uint8_t i=0; i < 7; i++){
			rgb.setColour(rainbow[i]);
			sleep_ms(DELAY);
		}
	}
}


