#ifndef HAL_H
#define HAL_H

#include "_ffmc16.h"
#include "avrlibtypes.h"
#define Disable_Interrupt	__DI();
#define Enable_Interrupt	__EI();

//Clock Config
#define F_CPU 24000000UL

#define ON 1
#define OFF 0

//PORT Defines
#define GSM_VBAT                IO_PDR0.bit.P05     // Выход
#define GSM_VBAT_DIR            IO_DDR0.bit.D05

#define AKB_DISCHARGE           IO_PDR0.bit.P06     // Выход
#define AKB_DISCHARGE_DIR       IO_DDR0.bit.D06

#define AMP_PWR                 IO_PDR0.bit.P07     // Выход
#define AMP_PWR_DIR             IO_DDR0.bit.D07

#define R1                      IO_PDR1.bit.P14     // Выход
#define R1_DIR                  IO_DDR1.bit.D14

#define R2                      IO_PDR1.bit.P15     // Выход
#define R2_DIR                  IO_DDR1.bit.D15

#define R3                      IO_PDR1.bit.P16     // Выход
#define R3_DIR                  IO_DDR1.bit.D16

#define WDI                     IO_PDR2.bit.P20     // Выход
#define WDI_DIR                 IO_DDR2.bit.D20

#define Count           IO_PDR2.bit.P26
#define Count_DIR       IO_DDR2.bit.D26

#define GPS_PWR                 IO_PDR3.bit.P30     // Выход
#define GPS_PWR_DIR             IO_DDR3.bit.D30

#define CPU_HL                  IO_PDR3.bit.P31     // Выход
#define CPU_HL_DIR              IO_DDR3.bit.D31

#define GSM_PWRKEY              IO_PDR3.bit.P32     // Выход
#define GSM_PWRKEY_DIR          IO_DDR3.bit.D32

#define COM3_PULL_DOWN_RX       IO_PDR3.bit.P33     // Выход
#define COM3_PULL_DOWN_RX_DIR   IO_DDR3.bit.D33

#define COM3_PULL_DOWN_TX       IO_PDR3.bit.P34     // Выход
#define COM3_PULL_DOWN_TX_DIR   IO_DDR3.bit.D34

#define GSM_HL                  IO_PDR3.bit.P35     // Выход
#define GSM_HL_DIR              IO_DDR3.bit.D35

#define GPS_HL                  IO_PDR3.bit.P36     // Выход
#define GPS_HL_DIR              IO_DDR3.bit.D36

#define X1                      IO_PDR7.bit.P70     // Дискретный вход 1
#define X1_DIR                  IO_DDR7.bit.D70     // Вход

#define X2                      IO_PDR7.bit.P71     // Дискретный вход 2
#define X2_DIR                  IO_DDR7.bit.D71     // Вход

#define X3                      IO_PDR7.bit.P72     // Дискретный вход 3
#define X3_DIR                  IO_DDR7.bit.D72     // Вход

#define X4                      IO_PDR7.bit.P73     // Дискретный вход 4
#define X4_DIR                  IO_DDR7.bit.D73     // Вход

#define GSM_Ring                IO_PDR7.bit.P74     // Сигнал вызов c GSM модуля
#define GSM_Ring_DIR            IO_DDR7.bit.D74     // Вход

#define GSM_TX                  IO_PDR7.bit.P75     // Синал TX GSM модуля
#define GSM_TX_DIR              IO_DDR7.bit.D75     // Вход

void InitAll(void);

#endif
