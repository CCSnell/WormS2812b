/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "ws2812_config.h"
#include "light_ws2812.h"

#define MAX_LEDS 150
void stressShit(void) {
    struct cRGB ledarray[MAX_LEDS];
    memset(ledarray, 0, MAX_LEDS*sizeof(struct cRGB));
	struct cRGB dut;
	struct cRGB no_dot;
	memset(&no_dot, 0, sizeof(struct cRGB));
	memset(&dut, 0, sizeof(struct cRGB));
	dut.g=20;

	uint16_t i;
	int16_t step = 1;
	uint8_t max_speed = 20;
	uint8_t accel = 60;
	uint8_t faster = 1;

	for(i=1;;) {
		if(i%accel == 0) {
			if (step < 0) {
				dut.b = -10*step;
				if (faster) {
					step--;
				} else {
					step++;
				}
			} else {
				dut.b = 10*step;
				if (faster) {
					step++;
				} else {
					step--;
				}
			}
		}
		if (step < 0) {
			if (-step >= max_speed) {
				faster = 0;
			}
		} else if (step > 0){
			if (step >= max_speed) {
				faster = 0;
			}
		} else {
			faster = 1;
		}
	
		ledarray[i] = dut;
		ledarray[(i+1)%MAX_LEDS] = dut;
		ws2812_setleds(ledarray, MAX_LEDS);
		ledarray[i] = no_dot;
		ledarray[(i+1)%MAX_LEDS] = no_dot;
		_delay_ms(30);
	
		i+=step;
		if (i>=MAX_LEDS | i<0) {
			step = -step;
			i+=step;
		}
	}
}

/**
 * Erzeugt chillige Würmer, was sonst??!
 */
void chillWorm(void) {
    struct cRGB ledarray[MAX_LEDS];
    memset(ledarray, 0, MAX_LEDS*sizeof(struct cRGB));
    
    ws2812_setleds(ledarray, MAX_LEDS);
    
    struct cRGB no_dot;
	memset(&no_dot, 0, sizeof(struct cRGB));
	
	// Wieviele dots willste?!
	int8_t num_dots = 5;
	
	// wie schnell dimmen?
	int8_t dimmfactor = 2;
	
	// welche farbe??
	struct cRGB dot1;
	dot1.r = 10;
	dot1.g = 30;
	dot1.b = 5;
	
	struct cRGB dot2;
	dot2.r = 50;
	dot2.g = 30;
	dot2.b = 5;
	
	struct cRGB dot3;
	dot3.r = 20;
	dot3.g = 20;
	dot3.b = 12;
	
	struct cRGB dot4;
	dot4.r = 10;
	dot4.g = 40;
	dot4.b = 20;
	
	struct cRGB dot5;
	dot5.r = 20;
	dot5.g = 12;
	dot5.b = 12;
	
	// will doch nur eine farbe..
	
	struct cRGB dots[num_dots];
	uint8_t index[num_dots];
	int8_t step[num_dots];
	
	dots[0] = dot2;
	dots[1] = dot2;
	dots[2] = dot2;
	dots[3] = dot2;
	dots[4] = dot2;
	
	// an welchen stellen??
	index[0] = 0;
	index[1] = 50;
	index[2] = 100;
	index[3] = 25;
	index[4] = 125;
	
	// welche Bewegungsrichtung, speed??
	step[0] = 1;
	step[1] = -1;
	step[2] = 1;
	step[3] = -1;
	step[4] = 1;
	
	uint8_t i;
	uint8_t a = 0;
	
	for (;;) {
		//ledarray[j] = dot;
		// Bei jedem schritt einmal dimmen
		for (i=0; i<MAX_LEDS; i++) {
			if (ledarray[i].r >= dimmfactor) {
				ledarray[i].r-=dimmfactor;
			} else {
				ledarray[i].r=0;
			}
			if (ledarray[i].g >= dimmfactor) {
				ledarray[i].g-=dimmfactor;
			} else {
				ledarray[i].g=0;
			}
			if (ledarray[i].b >= dimmfactor) {
				ledarray[i].b-=dimmfactor;
			} else {
				ledarray[i].b=0;
			}
		}
		// dots eintragen:
		for (a=0; a<num_dots; a++) {
			// clipping
			// r
			if (ledarray[index[a]].r+dots[a].r > 255) {
				ledarray[index[a]].r=255-dimmfactor;
			} else {
				ledarray[index[a]].r+=dots[a].r;
			}
			// g
			if (ledarray[index[a]].g+dots[a].g > 255) {
				ledarray[index[a]].g=255-dimmfactor;
			} else {
				ledarray[index[a]].g+=dots[a].g;
			}
			// b
			if (ledarray[index[a]].b+dots[a].b > 255) {
				ledarray[index[a]].b=255-dimmfactor;
			} else {
				ledarray[index[a]].b+=dots[a].b;
			}
			// am rand umdrehen
			if ((index[a]==MAX_LEDS-1)|((index[a] == 0)&(step[a] == -1))) {
				step[a] = -step[a];
			}
			index[a]+=step[a];
		}
		ws2812_setleds(ledarray, MAX_LEDS);
		_delay_ms(30);
	}
}

/**
 * Helligkeit zwischen 0 und 100
 */
void chillFarbe(uint8_t brightness) {
    struct cRGB ledarray[MAX_LEDS];
    memset(ledarray, 0, MAX_LEDS*sizeof(struct cRGB));
	struct cRGB dot2;
	dot2.r = 2.5*brightness;
	dot2.g = 1.5*brightness;
	dot2.b = 0.3*brightness;
	uint8_t i;
	for (i=0; i<MAX_LEDS; i++) {
		ledarray[i]=dot2;
		ws2812_setleds(ledarray, MAX_LEDS);
		_delay_ms(40);
	}
}

/**
 * Momentan noch Baustelle
 */
void chillFarbe2(uint8_t brightness) {
    struct cRGB ledarray[MAX_LEDS];
    memset(ledarray, 0, MAX_LEDS*sizeof(struct cRGB));
	struct cRGB dot2;
	dot2.r = 2.5*brightness;
	dot2.g = 1.5*brightness;
	dot2.b = 0.3*brightness;
	int16_t i;
	double fact;
	for (i=0; i<MAX_LEDS; i++) {
		fact = ((i%12)/12.0); // fliesskomma, biatch!
		ledarray[i].r= fact*255;
		//ledarray[i].g= 1.3*brightness*(((i%12)-6)/6);
		//ledarray[i].b= 0.3*brightness*(((i%12)-6)/6);
		ws2812_setleds(ledarray, MAX_LEDS);
		_delay_ms(40);
	}
}

int main(void)
{
    
    cli();
    
    
	// Init PIN 2 of PORTB as Output
	DDRB |= _BV(DDB2);
	// Switch LED's off by setting Outputs to LOW (GND)
	PORTB &= ~(_BV(PORTB2));
    
    /* Ab hier gehts los mit den spielchen :) */
    
    
	//chillWorm();
	chillFarbe(15);
	//chillFarbe2(15);
    //stressShit();
	
    sei();
    
    return 0;
}
