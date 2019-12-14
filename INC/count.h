#ifndef COUNT_H
#define COUNT_H
#include "HAL.h"
void Count_Init(void);
u16 Count_Read(void);
__interrupt void Count_Capture(void);

#endif // COUNT_H
