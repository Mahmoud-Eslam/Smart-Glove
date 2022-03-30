/*
 * ADC_E25.c
 *
 * Created: 11/13/2021 4:26:58 PM
 * Author : user
 */
#include "DIO.h"
#include "LCD.h"
#include "ADC.h"
#include <stdlib.h>

int main(void) {
	//define uart pins
	DDRD &= ~(1 << 0); //RX
	DDRD |= (1 << 1); //TX
	PORTD &= ~(1 << 0); //RX
	PORTD &= ~(1 << 1); //TX
	UART_INIT();

	// flex sensor readings
	int temp[5] = { 0 };
	int done = 0;
	char string[50];

	DIO_Init();
	LCD_Init();
	ADC_Init();
	while (1) {
		temp[0] = ADC_Read(1); //read from channel 1
		temp[0] = temp[0] - 204;
		itoa(temp[0], string, 10); //convert to char
		if (temp[0] >= 0) {
			LCD_String(string);
		} else {
			LCD_String("0");
		}

		temp[1] = ADC_Read(2); //read from channel 2
		temp[1] = temp[1] - 204;
		LCD_SetPos(1, 5);
		itoa(temp[1], string, 10); //convert to char
		if (temp[1] >= 0) {
			LCD_String(string);
		} else {
			LCD_String("0");
		}

		temp[2] = ADC_Read(3); //read from channel 3
		temp[2] = temp[2] - 204;
		LCD_SetPos(1, 10);
		itoa(temp[2], string, 10); //convert to char
		if (temp[2] >= 0) {
			LCD_String(string);
		} else {
			LCD_String("0");
		}

		temp[3] = ADC_Read(4); //read from channel 4
		temp[3] = temp[3] - 204;
		LCD_SetPos(2, 3);
		itoa(temp[3], string, 10); //convert to char
		if (temp[3] >= 0) {
			LCD_String(string);
		} else {
			LCD_String("0");
		}

		temp[4] = ADC_Read(5); //read from channel 5
		temp[4] = temp[4] - 204;
		LCD_SetPos(2, 8);
		itoa(temp[4], string, 10); //convert to char
		if (temp[4] >= 0) {
			LCD_String(string);
		} else {
			LCD_String("0");
		}

		LCD_SetPos(2, 14);
		// Stop gesture
		if (temp[0] >= 0 && temp[0] <= 80) {
			if (temp[1] >= 0 && temp[1] <= 80) {
				if (temp[2] >= 0 && temp[2] <= 80) {
					if (temp[3] >= 0 && temp[3] <= 80) {
						if (temp[4] >= 0 && temp[4] <= 80) {
							UART_TransmitChar('0');
							LCD_String("0");
							done = 1;
						}
					}
				}
			}
		}
		// move forward gesture
		//if (done = 0) {
			if (temp[0] >= 150) {
				if (temp[2] >= 150) {
					if (temp[3] >= 150) {
						if (temp[4] >= 150) {
							if (temp[1] >= 0 && temp[1] <= 80) {
								UART_TransmitChar('1');
								LCD_String("1");
								done = 1;
							} else if (temp[1] >= 80) {
								UART_TransmitChar('2');
								LCD_String("2");
								done = 1;
							}
						}
					}
				}
			}
		//}
		// move right gesture
		//if (done = 0) {
			if (temp[0] >= 150) {
				if (temp[3] >= 150) {
					if (temp[4] >= 150) {
						if (temp[2] >= 0 && temp[2] <= 80) {
							if (temp[1] >= 0 && temp[1] <= 80) {
								UART_TransmitChar('3');
								LCD_String("3");
								done = 1;
							} else if (temp[1] >= 80) {
								UART_TransmitChar('4');
								LCD_String("4");
								done = 1;
							}
						}
					}
				}
			}
	//	}
		// move left gesture
		//if (done = 0) {
			if (temp[0] >= 150) {
				if (temp[4] >= 150) {
					if (temp[3] >= 0 && temp[3] <= 80) {
						if (temp[2] >= 0 && temp[2] <= 80) {
							if (temp[1] >= 0 && temp[1] <= 80) {
								UART_TransmitChar('5');
								LCD_String("5");
								done = 1;
							} else if (temp[1] >= 80) {
								UART_TransmitChar('6');
								LCD_String("6");
								done = 1;
							}
						}
					}
				}
			}
		//}
		// move backward gesture
		//if (done = 0) {
			if (temp[0] >= 150) {
				if (temp[4] >= 0 && temp[4] <= 80) {
					if (temp[3] >= 0 && temp[3] <= 80) {
						if (temp[2] >= 0 && temp[2] <= 80) {
							if (temp[1] >= 0 && temp[1] <= 80) {
								UART_TransmitChar('7');
								LCD_String("7");
								done = 1;
							} else if (temp[1] >= 80) {
								UART_TransmitChar('8');
								LCD_String("8");
								done = 1;
							}
						}
					}
				}
			}
	//	}
		done = 0;
		LCD_SetPos(1, 0);
		_delay_ms(200);
		LCD_Cmd(0x01); //clear LCD
	}
}

