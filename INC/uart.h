#ifndef UART_H
#define UART_H

#include "HAL.h"

#define TX_BUFFER_SIZE 255
#define RX_BUFFER_SIZE 255
enum Baud_Rate_Type {_2400=F_CPU/2400U-1, _4800=F_CPU/4800U-1, _9600=F_CPU/9600U-1, _19200=F_CPU/19200U-1, _38400=F_CPU/38400U-1, _115200=F_CPU/115200UL-1};
enum Data_Length_Type {_7bit,_8bit};
enum Stop_Bit_Type {_1, _2};
enum Parity_Type {none,odd,even};
typedef void (*Callback)(char);
typedef struct
{
    u08 count;              // число элементов в буфере
    u08 begin;				// начало буфера
    u08 end;				// конец буфера
    char Buffer[TX_BUFFER_SIZE];    // буфер
}UART_Buffer;
typedef struct
{
    int port;                            //Номер порта
    enum Baud_Rate_Type Baud_Rate;       //битрейт
    enum Data_Length_Type Data_Length;   //Длина данных
    enum Stop_Bit_Type Stop_Bit;         // Стоповые биты
    enum Parity_Type Parity;             // Паритет
    UART_Buffer RX_Buffer;
    UART_Buffer TX_Buffer;
    Callback RX_Callback;
}UART_Settings;

void UART_INIT(UART_Settings* u);
u08 UART_Send(UART_Settings* u, char ch); // отправка символа
u08 UART_Send_String(UART_Settings* u,char *str); //отправка строки
u08 UART_Recv (UART_Settings* u, char *ch); //прием символа
u08 UART_Recv_String (UART_Settings* u, char *str, u08 len ); //прием строки
__interrupt void uart0_rx_int(void);
__interrupt void uart0_tx_int(void);
__interrupt void uart1_3_rx_int(void);
__interrupt void uart1_3_tx_int(void);
__interrupt void uart2_4_rx_int(void);
__interrupt void uart2_4_tx_int(void);

#endif // UART_H
