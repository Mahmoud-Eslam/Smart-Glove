/*
 * ADC.h
 *
 * Created: 11/13/2021 4:30:43 PM
 *  Author: user
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include "STD_Types.h"


void ADC_Init(void);
int ADC_Read(Uint8 modeID);

#endif /* ADC_H_ */