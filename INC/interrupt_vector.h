#ifndef INTERRUPT_VECTOR_H
#define INTERRUPT_VECTOR_H

#pragma	intvect	_start 8 0
#pragma	intvect timer_int 25
#pragma	intvect ADC_int 29
#pragma	intvect Count_Capture 33
#pragma	intvect uart0_rx_int 35
#pragma	intvect uart0_tx_int 36
#pragma	intvect uart1_3_rx_int 37
#pragma	intvect uart1_3_tx_int 38
#pragma	intvect uart2_4_rx_int 39
#pragma	intvect uart2_4_tx_int 40
extern __interrupt void _start(void);

#endif // INTERRUPT_VECTOR_H
