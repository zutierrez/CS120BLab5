/*	Author: Zion Gutierrez, zguti001
 *      Partner(s) Name: none
 *	Lab Section: 023
 *	Assignment: Lab #4 Exercise #2
 *	Exercise Description: INCREMENTER AND DECREMENTER 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { WAIT , PRESS_INCREMENT, RELEASE_INCREMENT, PRESS_DECREMENT, RELEASE_DECREMENT, PRESS_RESET, RELEASE_RESET } state;

unsigned char inputA = 0x00;
unsigned char cnt = 0x00;

void SM()
{
	switch(state) {      //TRANSITIONS
	
		case WAIT:
	       		if ( inputA == 0x01 ){
				if( cnt < 9){
					state = PRESS_INCREMENT;
				}
	       		}
			else if( inputA == 0x02 ){
				if( cnt > 0 ){
					state = PRESS_DECREMENT;
				}
			}
			else if( inputA == 0x03 ){
				cnt = 0x00;
				state = PRESS_RESET;
			}
			else { state = WAIT; }
	       		break;

	    	case PRESS_INCREMENT:
			if( inputA == 0x01 ){
				state = PRESS_INCREMENT; }
			else if( inputA == 0x03 ){
				cnt = 0x00;
				state = PRESS_RESET;
			}
			else if( inputA == 0x00) {
				 state = RELEASE_INCREMENT; }
	       		break;
	    	
		case RELEASE_INCREMENT: 
			++cnt;
			state = WAIT;
			break;

	   	case PRESS_DECREMENT:
			if( inputA == 0x02 ){
				state = PRESS_DECREMENT; }
			else if( inputA == 0x03 ){
				cnt = 0x00;
				state = PRESS_RESET;
			}
			else if( inputA == 0x00) {
				 state = RELEASE_DECREMENT; }
			break;

		case RELEASE_DECREMENT:
			--cnt;
			state = WAIT;
			break;

		case PRESS_RESET:
			if( inputA == 0x03 ){
				cnt = 0x00;
				state = PRESS_RESET; }
			else if (inputA == 0x00){
				state = RELEASE_RESET; }
			break;

		case RELEASE_RESET:
			cnt = 0x00;
			state = WAIT;
			break;

		default:
	        	state = WAIT;
	       		break;	
		}	

	switch(state) {      //ACTIONS
	    
	    	case WAIT:		
			break;
	    	case PRESS_INCREMENT:
			break;
		case RELEASE_INCREMENT:
			break;
		case PRESS_DECREMENT:
			break;
		case RELEASE_DECREMENT:
			break;
		case PRESS_RESET:
			break;
		case RELEASE_RESET:
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
	
	PORTC = cnt;
	}  

	return 1;
}
