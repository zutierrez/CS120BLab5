/*	Author: Zion Gutierrez, zguti001
 *      Partner(s) Name: none
 *	Lab Section: 023
 *	Assignment: Lab #4 Exercise #3
 *	Exercise Description: FESTIVE LIGHTS CHALLENGE 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { WAIT , PRESS_SEQ1, RELEASE_SEQ1 } state;

unsigned char inputA = 0x00;
int i = 0;
const unsigned char SEQ_ARRAY[3] = {0xAA, 0x55, 0x99};

void SM()
{
	switch(state) {      //TRANSITIONS
	
		case WAIT:
	       		if ( inputA == 0x01 ){
				state = PRESS_SEQ1;
				}
			else { state = WAIT; }
	       		break;

	    	case PRESS_SEQ1:
			if( inputA == 0x01 ){
				state = PRESS_SEQ1; }
			else if( inputA == 0x00) {
				 state = RELEASE_SEQ1; }
	       		break;
	    	
		case RELEASE_SEQ1: 
			PORTC = SEQ_ARRAY[i];
			if( i < 2){
				++i;}
			else if( i == 2){
				i = 0;}
			state = WAIT;
			break;

		default:
	        	state = WAIT;
	       		break;	
		}	

	switch(state) {      //ACTIONS
	    
	    	case WAIT:		
			break;
	    	case PRESS_SEQ1:
			break;
		case RELEASE_SEQ1:
			break;		
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port C's 8 pins as inputs, initialize to 0s
     	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 7 most significant pins as outputs and PB0 as input
	enum States state = WAIT;
        
	while(1){ 
	//INPUT:
	inputA = PINA;
	inputA = ~inputA;
	
	SM();
	}  

	return 1;
}
