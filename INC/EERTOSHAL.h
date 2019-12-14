#ifndef EERTOSHAL_H
#define EERTOSHAL_H
#include "HAL.h"

#define STATUS_REG 			SREG
#define Interrupt_Flag		SREG_I

//RTOS Config
#define	TaskQueueSize		15
#define MainTimerQueueSize	10


void RunRTOS (void);

#endif
