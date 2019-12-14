#include "ADC.h"
#include "HAL.h"
int ADC[ADC_MAX_CHANNEL]={0};
int Count_Channel=0;
void Init_ADC(void)
{
    int i;
    IO_ADER6.byte=0;
    for (i=0; i < ADC_MAX_CHANNEL; ++i)
    {
        IO_ADER6.byte|=1<<i;
    }
    IO_ICR09.bit.IL=0x00;
    IO_ADCS.bit.INT=0;
    IO_ADCS.bit.INTE=1;
    IO_ADCS.bit.MD=1;
    IO_ADSR=0;
    IO_ADSR|=0xFC00;
    IO_ADSR|=ADC_MAX_CHANNEL-1;
    Count_Channel=0;
    //IO_ADSR=36865;
    // IO_ADCS.bit.STRT=1;
}

__interrupt void ADC_int(void)
{
    if (IO_ADCS.bit.INT)
    {
        GPS_HL=ON;
        IO_ADCS.bit.INT=0;
        ADC[Count_Channel]=IO_ADCR.word&0x3FF;
        Count_Channel++;
        if (Count_Channel>=ADC_MAX_CHANNEL)
        {
            Count_Channel=0;

        }

        GPS_HL=OFF;
    }

}

int Read_ADC(int ch)
{
    int ADC_Temp=0;
    IO_ADCS.bit.INTE=0;
    ADC_Temp=ADC[ch];
    IO_ADCS.bit.INTE=1;
    return ADC_Temp;
}

 void ADC_Start()
{
    IO_ADCS.bit.STRT=1;
}
