#include "EERTOSHAL.h"

//RTOS Запуск системного таймера
void RunRTOS (void)
{
    // Инициализация системного таймера
    IO_ICR07.bit.IL=0x00;       // Приоритет прерываний
    IO_TBTC.bit.TBIE=1;         // Разрешение прерываний
    Enable_Interrupt;
}

