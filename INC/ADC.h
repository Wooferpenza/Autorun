#ifndef ADC_H
#define ADC_H
#include "HAL.h"

#define ADC_MAX_CHANNEL 6

void Init_ADC(void);
void ADC_Start(void);
int Read_ADC(int ch);
__interrupt void ADC_int(void);
#endif // ADC_H
