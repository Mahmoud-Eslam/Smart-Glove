/*
 * ADC.c
 *
 * Created: 11/13/2021 4:30:28 PM
 *  Author: user
 */ 

#include "ADC.h"

void ADC_Init(void){
	ADMUX = (1<<REFS0);//INTERNAL V_REF
	ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);//ENABLE ADC & F_CPU/128
}
int ADC_Read(Uint8 modeID){
	long temp = 0;
	ADMUX = (ADMUX & 0xE0)|(modeID & 0x1F);//SET THE ADC MODE
	ADCSRA |= (1<<ADSC);//START CONVERSION
	while (!(ADCSRA & (1<<ADIF)));//WAITING THE FLAG TO BE SET 
	ADCSRA |= (1<<ADIF);//CLEAR THE FLAG
	temp = ADCL;
	temp |= (ADCH << 8);
	return temp;
}
