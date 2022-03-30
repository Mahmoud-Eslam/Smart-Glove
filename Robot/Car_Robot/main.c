/*
 * main.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Elbekoo
 */

#include "USART.h"
#include <avr/delay.h>

void moveForwardward(int speed);
void moveBackward(int speed);
void moveRight(int speed);
void moveLeft(int speed);
void stop();

int main() {
	//define uart pins
	DDRD &= ~(1 << 0); //RX
	DDRD |= (1 << 1); //TX
	PORTD &= ~(1 << 0); //RX
	PORTD &= ~(1 << 1); //TX
	UART_INIT();

	//motor
	DDRD |= (1 << 5); //OCR1
	DDRC |= (1 << 5) | (1 << 6); //Motor1
	DDRC |= (1 << 3) | (1 << 4); //Motor2
	TCCR1A = (1 << WGM11) | (1 << COM1A1); // MODE 14 FAST PWM, non inverting
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11); // N = 64
	OCR1A = 500;
	ICR1 = 1000;

	while (1) {

		s8 recieved_char = UART_Recieve();
		if (recieved_char == '0') {
			stop();
		} else if (recieved_char == '1') {
			moveForwardward(500);
		} else if (recieved_char == '2') {
			moveForwardward(1000);
		} else if (recieved_char == '3') {
			moveRight(500);
		} else if (recieved_char == '4') {
			moveRight(1000);
		} else if (recieved_char == '5') {
			moveLeft(500);
		} else if (recieved_char == '6') {
			moveLeft(1000);
		} else if (recieved_char == '7') {
			moveBackward(500);
		} else if (recieved_char == '8') {
			moveBackward(1000);
		}
	}
	return 0;
}

void moveBackward(int speed) {
	OCR1A = speed;
	PORTC |= (1 << 5);
	PORTC &= ~(1 << 6);
	PORTC |= (1 << 3);
	PORTC &= ~(1 << 4);
	_delay_ms(500);
	PORTC &= ~((1 << 5) | (1 << 6) | (1 << 3) | (1 << 4));
	_delay_ms(1000);
}

void stop() {
	PORTC &= ~((1 << 5) | (1 << 6) | (1 << 3) | (1 << 4));
	_delay_ms(1000);
}

void moveForwardward(int speed) {
	OCR1A = speed;
	PORTC &= ~(1 << 5);
	PORTC |= (1 << 6);
	PORTC &= ~(1 << 3);
	PORTC |= (1 << 4);
	_delay_ms(500);
	PORTC &= ~((1 << 5) | (1 << 6) | (1 << 3) | (1 << 4));
	_delay_ms(1000);
}
void moveLeft(int speed) {
	OCR1A = speed;
	PORTC &= ~(1 << 5);
	PORTC |= (1 << 6);
	PORTC &= ~(1 << 3);
	PORTC &= ~(1 << 4);
	_delay_ms(500);
	PORTC &= ~((1 << 5) | (1 << 6) | (1 << 3) | (1 << 4));
	_delay_ms(1000);
}
void moveRight(int speed) {
	OCR1A = speed;
	PORTC &= ~(1 << 5);
	PORTC &= ~(1 << 6);
	PORTC &= ~(1 << 3);
	PORTC |= (1 << 4);
	_delay_ms(500);
	PORTC &= ~((1 << 5) | (1 << 6) | (1 << 3) | (1 << 4));
	_delay_ms(1000);
}

