#include "HAL.h"

void InitAll(void)
{
    // Инициализация тактирования
    IO_CKSCR.bit.CS=2;      // PLL x3
    IO_CKSCR.bit.MCS=0;     // PLL en
    while(IO_CKSCR.bit.MCM)
    {

    }


    // Инициализация портов
    CPU_HL_DIR=ON;
    CPU_HL=OFF;

    GPS_HL_DIR=ON;
    GPS_HL=OFF;

    GSM_HL_DIR=ON;
    GSM_HL=OFF;

    GSM_VBAT_DIR=ON;
    GSM_VBAT=OFF;

    GSM_PWRKEY_DIR=ON;
    GSM_PWRKEY=OFF;

    GPS_PWR_DIR=ON;
    GPS_PWR=OFF;

    R1_DIR=ON;
    R1=OFF;

    IO_ADER5.byte=0;
    IO_ADER6.byte=0;
    IO_ADER7.byte=0;

}
