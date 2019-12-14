#include "uart.h"
#include "HAL.h"

UART_Buffer* pUART_TX_Buffer[5];
UART_Buffer* pUART_RX_Buffer[5];
Callback RX_Callback[5];

void UART_INIT(UART_Settings *u)
{
    pUART_TX_Buffer[u->port]=&u->TX_Buffer;
    pUART_RX_Buffer[u->port]=&u->RX_Buffer;
    u->RX_Buffer.begin=0;
    u->RX_Buffer.end=0;
    u->RX_Buffer.count=0;
    u->TX_Buffer.begin=0;
    u->TX_Buffer.end=0;
    u->TX_Buffer.count=0;
    RX_Callback[u->port]=u->RX_Callback;
    if (u->port==0)
    {
        IO_ICR12.bit.IL=0x00;                           // Приоритет прерываний
        IO_UART0.SCR0.bit.TXE=1;                        // Разрешение передачи
        IO_UART0.SCR0.bit.RXE=1;                        // Разрешение приема

        if(u->Data_Length==_7bit)                       // Длина данных
        {  IO_UART0.SCR0.bit.CL=0;}
        else {  IO_UART0.SCR0.bit.CL=1;}

        if(u->Stop_Bit==_1)                             // Число стоповых бит
        {  IO_UART0.SCR0.bit.SBL=0;}
        else {  IO_UART0.SCR0.bit.SBL=1;}

        switch (u->Parity)
        {
        case none: IO_UART0.SCR0.bit.PEN=0;   break;    // Паритет
        case even: IO_UART0.SCR0.bit.PEN=1; IO_UART0.SCR0.bit.P=0; break;
        case odd:  IO_UART0.SCR0.bit.PEN=1; IO_UART0.SCR0.bit.P=1; break;
        }
        IO_UART0.SMR0.bit.SOE=1;
        IO_UART0.SSR0.bit.RIE=1;
        IO_UART0.BGR0.word=u->Baud_Rate;
    }
    if (u->port==1)
    {
        IO_ICR13.bit.IL=0x00;                           // Приоритет прерываний
        IO_UART1.SCR1.bit.TXE=1;                        // Разрешение передачи
        IO_UART1.SCR1.bit.RXE=1;                        // Разрешение приема

        if(u->Data_Length==_7bit)                       // Длина данных
        {  IO_UART1.SCR1.bit.CL=0;}
        else {  IO_UART1.SCR1.bit.CL=1;}

        if(u->Stop_Bit==_1)                             // Число стоповых бит
        {  IO_UART1.SCR1.bit.SBL=0;}
        else {  IO_UART1.SCR1.bit.SBL=1;}

        switch (u->Parity)
        {
        case none: IO_UART1.SCR1.bit.PEN=0;   break;    // Паритет
        case even: IO_UART1.SCR1.bit.PEN=1; IO_UART0.SCR0.bit.P=0; break;
        case odd:  IO_UART1.SCR1.bit.PEN=1; IO_UART0.SCR0.bit.P=1; break;
        }
        IO_UART1.SMR1.bit.SOE=1;
        IO_UART1.SSR1.bit.RIE=1;
        IO_UART1.BGR1.word=u->Baud_Rate;
    }
    if (u->port==2)
    {
        IO_ICR14.bit.IL=0x00;                           // Приоритет прерываний
        IO_UART2.SCR2.bit.TXE=1;                        // Разрешение передачи
        IO_UART2.SCR2.bit.RXE=1;                        // Разрешение приема

        if(u->Data_Length==_7bit)                       // Длина данных
        {  IO_UART2.SCR2.bit.CL=0;}
        else {  IO_UART2.SCR2.bit.CL=1;}

        if(u->Stop_Bit==_1)                             // Число стоповых бит
        {  IO_UART2.SCR2.bit.SBL=0;}
        else {  IO_UART2.SCR2.bit.SBL=1;}

        switch (u->Parity)
        {
        case none: IO_UART2.SCR2.bit.PEN=0;   break;    // Паритет
        case even: IO_UART2.SCR2.bit.PEN=1; IO_UART2.SCR2.bit.P=0; break;
        case odd:  IO_UART2.SCR2.bit.PEN=1; IO_UART2.SCR2.bit.P=1; break;
        }
        IO_UART2.SMR2.bit.SOE=1;
        IO_UART2.SSR2.bit.RIE=1;
        IO_UART2.BGR2.word=u->Baud_Rate;
    }
    if (u->port==3)
    {
        IO_ICR13.bit.IL=0x00;                           // Приоритет прерываний
        IO_UART3.SCR3.bit.TXE=1;                        // Разрешение передачи
        IO_UART3.SCR3.bit.RXE=1;                        // Разрешение приема

        if(u->Data_Length==_7bit)                       // Длина данных
        {  IO_UART3.SCR3.bit.CL=0;}
        else {  IO_UART3.SCR3.bit.CL=1;}

        if(u->Stop_Bit==_1)                             // Число стоповых бит
        {  IO_UART3.SCR3.bit.SBL=0;}
        else {  IO_UART3.SCR3.bit.SBL=1;}

        switch (u->Parity)
        {
        case none: IO_UART3.SCR3.bit.PEN=0;   break;    // Паритет
        case even: IO_UART3.SCR3.bit.PEN=1; IO_UART3.SCR3.bit.P=0; break;
        case odd:  IO_UART3.SCR3.bit.PEN=1; IO_UART3.SCR3.bit.P=1; break;
        }
        IO_UART3.SMR3.bit.SOE=1;
        IO_UART3.SSR3.bit.RIE=1;
        IO_UART3.BGR3.word=u->Baud_Rate;
    }
    if (u->port==4)
    {
        IO_ICR14.bit.IL=0x00;                           // Приоритет прерываний
        IO_UART4.SCR4.bit.TXE=1;                        // Разрешение передачи
        IO_UART4.SCR4.bit.RXE=1;                        // Разрешение приема

        if(u->Data_Length==_7bit)                       // Длина данных
        {  IO_UART4.SCR4.bit.CL=0;}
        else {  IO_UART4.SCR4.bit.CL=1;}

        if(u->Stop_Bit==_1)                             // Число стоповых бит
        {  IO_UART4.SCR4.bit.SBL=0;}
        else {  IO_UART4.SCR4.bit.SBL=1;}

        switch (u->Parity)
        {
        case none: IO_UART4.SCR4.bit.PEN=0;   break;    // Паритет
        case even: IO_UART4.SCR4.bit.PEN=1; IO_UART4.SCR4.bit.P=0; break;
        case odd:  IO_UART4.SCR4.bit.PEN=1; IO_UART4.SCR4.bit.P=1; break;
        }
        IO_UART4.SMR4.bit.SOE=1;
        IO_UART4.SSR4.bit.RIE=1;
        IO_UART4.BGR4.word=u->Baud_Rate;
    }
}

u08 UART_Send(UART_Settings *u, char ch)
{
    Disable_Interrupt;
    if (u->TX_Buffer.count<TX_BUFFER_SIZE)  // если буфер не переполнен
    {
        u->TX_Buffer.Buffer[u->TX_Buffer.end]=ch;
        u->TX_Buffer.count++;
        u->TX_Buffer.end++;
        if (u->TX_Buffer.end==TX_BUFFER_SIZE)
        {
            u->TX_Buffer.end=0;
        }
        switch (u->port)
        {
        case 0: IO_UART0.SSR0.bit.TIE=1; break;
        case 1: IO_UART1.SSR1.bit.TIE=1; break;
        case 2: IO_UART2.SSR2.bit.TIE=1; break;
        case 3: IO_UART3.SSR3.bit.TIE=1; break;
        case 4: IO_UART4.SSR4.bit.TIE=1; break;
        }
        Enable_Interrupt;
        return 1;
    }
    else {Enable_Interrupt; return 0;}
}

u08 UART_Send_String(UART_Settings *u, char *data)
{
    char s=0;
    u08 count=0;      // число отправленных символов
    while (*data)
    {
        s=*data++;
        if (UART_Send(u,s)){count++;}
        else {break;}
    }
    return count;
}

u08 UART_Recv (UART_Settings *u, char *ch)
{
    Disable_Interrupt;
    if (u->RX_Buffer.count) // Если буфер не пустой
    {
        *ch=u->RX_Buffer.Buffer[u->RX_Buffer.begin];
        u->RX_Buffer.count--;
        u->RX_Buffer.begin++;
        if (u->RX_Buffer.begin==RX_BUFFER_SIZE)
        {
            u->RX_Buffer.begin=0;
        }
       Enable_Interrupt;
        return 1;
    }
    else
    {
        u->RX_Buffer.begin=0;
        u->RX_Buffer.end=0;
       Enable_Interrupt;
        return 0;
    }
}

u08 UART_Recv_String (UART_Settings* u, char *str, u08 len )
{
    u08 i=0;
    len=len-1;
    for (i=0;i<len;i++)
    {
        if (!UART_Recv(u,(str+i))) {break;}

    }
    *(str+i)=0;
    return i;
}

__interrupt void uart0_tx_int(void)
{

    if (pUART_TX_Buffer[0]->count)           // если в буфере есть элементы
    {
        IO_UART0.RDR0=pUART_TX_Buffer[0]->Buffer[pUART_TX_Buffer[0]->begin];
        pUART_TX_Buffer[0]->count--;
        pUART_TX_Buffer[0]->begin++;
        if (pUART_TX_Buffer[0]->begin==TX_BUFFER_SIZE)
        {
            pUART_TX_Buffer[0]->begin=0;
        }
    }
    if (!pUART_TX_Buffer[0]->count)
    {
        pUART_TX_Buffer[0]->begin=0;
        pUART_TX_Buffer[0]->end=0;
        IO_UART0.SSR0.bit.TIE=0;
    }
    return;
}

__interrupt void uart0_rx_int(void)
{
    if (pUART_RX_Buffer[0]->count<RX_BUFFER_SIZE) // Если буфер не переполнен
    {
        char ch=IO_UART0.RDR0;
        pUART_RX_Buffer[0]->Buffer[pUART_RX_Buffer[0]->end]=ch;
        pUART_RX_Buffer[0]->count++;
        pUART_RX_Buffer[0]->end++;
        if (pUART_RX_Buffer[0]->end==RX_BUFFER_SIZE)
        {
            pUART_RX_Buffer[0]->end=0;
        }
        if (RX_Callback[0]) {RX_Callback[0](ch);}
    }
    if(IO_UART0.SSR0.bit.FRE||IO_UART0.SSR0.bit.ORE||IO_UART0.SSR0.bit.PE)  {IO_UART0.SCR0.bit.CRE=1;}
    return;
}

__interrupt void uart1_3_tx_int(void)
{
    if(IO_UART1.SSR1.bit.TDRE)
    {
        if (pUART_TX_Buffer[1]->count)           // если в буфере есть элементы
        {
            IO_UART1.RDR1=pUART_TX_Buffer[1]->Buffer[pUART_TX_Buffer[1]->begin];
            pUART_TX_Buffer[1]->count--;
            pUART_TX_Buffer[1]->begin++;
            if (pUART_TX_Buffer[1]->begin==TX_BUFFER_SIZE)
            {
                pUART_TX_Buffer[1]->begin=0;
            }
        }
        if (!pUART_TX_Buffer[1]->count)
        {
            pUART_TX_Buffer[1]->begin=0;
            pUART_TX_Buffer[1]->end=0;
            IO_UART1.SSR1.bit.TIE=0;
        }
    }
    if (IO_UART3.SSR3.bit.TDRE)
    {
        if (pUART_TX_Buffer[3]->count)           // если в буфере есть элементы
        {
            IO_UART3.RDR3=pUART_TX_Buffer[3]->Buffer[pUART_TX_Buffer[3]->begin];
            pUART_TX_Buffer[3]->count--;
            pUART_TX_Buffer[3]->begin++;
            if (pUART_TX_Buffer[3]->begin==TX_BUFFER_SIZE)
            {
                pUART_TX_Buffer[3]->begin=0;
            }
        }
        if (!pUART_TX_Buffer[3]->count)
        {
            pUART_TX_Buffer[3]->begin=0;
            pUART_TX_Buffer[3]->end=0;
            IO_UART3.SSR3.bit.TIE=0;
        }
    }
    return;
}

__interrupt void uart1_3_rx_int(void)
{

    if(IO_UART1.SSR1.bit.RDRF)
    {

        if (pUART_RX_Buffer[1]->count<RX_BUFFER_SIZE) // Если буфер не переполнен
        {
            char ch=IO_UART1.RDR1;
            pUART_RX_Buffer[1]->Buffer[pUART_RX_Buffer[1]->end]=ch;
            pUART_RX_Buffer[1]->count++;
            pUART_RX_Buffer[1]->end++;
            if (pUART_RX_Buffer[1]->end==RX_BUFFER_SIZE)
            {
                pUART_RX_Buffer[1]->end=0;
            }
            if (RX_Callback[1]) {RX_Callback[1](ch);}
        }

    }
    if (IO_UART3.SSR3.bit.RDRF)
    {
        if (pUART_RX_Buffer[3]->count<RX_BUFFER_SIZE) // Если буфер не переполнен
        {
            char ch=IO_UART3.RDR3;
            pUART_RX_Buffer[3]->Buffer[pUART_RX_Buffer[3]->end]=ch;
            pUART_RX_Buffer[3]->count++;
            pUART_RX_Buffer[3]->end++;
            if (pUART_RX_Buffer[3]->end==RX_BUFFER_SIZE)
            {
                pUART_RX_Buffer[3]->end=0;
            }
            if (RX_Callback[3]) {RX_Callback[3](ch);}
        }
    }
if(IO_UART1.SSR1.bit.FRE||IO_UART1.SSR1.bit.ORE||IO_UART1.SSR1.bit.PE)  {IO_UART1.SCR1.bit.CRE=1;}
if(IO_UART3.SSR3.bit.FRE||IO_UART3.SSR3.bit.ORE||IO_UART3.SSR3.bit.PE)  {IO_UART3.SCR3.bit.CRE=1;}

return;
}

__interrupt void uart2_4_tx_int(void)
{
    if(IO_UART2.SSR2.bit.TDRE)
    {
        if (pUART_TX_Buffer[2]->count)           // если в буфере есть элементы
        {
            IO_UART2.RDR2=pUART_TX_Buffer[2]->Buffer[pUART_TX_Buffer[2]->begin];
            pUART_TX_Buffer[2]->count--;
            pUART_TX_Buffer[2]->begin++;
            if (pUART_TX_Buffer[2]->begin==TX_BUFFER_SIZE)
            {
                pUART_TX_Buffer[2]->begin=0;
            }
        }
        if (!pUART_TX_Buffer[2]->count)
        {
            pUART_TX_Buffer[2]->begin=0;
            pUART_TX_Buffer[2]->end=0;
            IO_UART2.SSR2.bit.TIE=0;
        }
    }

        if (IO_UART4.SSR4.bit.TDRE)
        {
            if (pUART_TX_Buffer[4]->count)           // если в буфере есть элементы
            {
                IO_UART4.RDR4=pUART_TX_Buffer[4]->Buffer[pUART_TX_Buffer[4]->begin];
                pUART_TX_Buffer[4]->count--;
                pUART_TX_Buffer[4]->begin++;
                if (pUART_TX_Buffer[4]->begin==TX_BUFFER_SIZE)
                {
                    pUART_TX_Buffer[4]->begin=0;
                }
            }
            if (!pUART_TX_Buffer[4]->count)
            {
                pUART_TX_Buffer[4]->begin=0;
                pUART_TX_Buffer[4]->end=0;
                IO_UART4.SSR4.bit.TIE=0;
            }
        }
return;
}

__interrupt void uart2_4_rx_int(void)
{

    if(IO_UART2.SSR2.bit.RDRF)
    {
        if (pUART_RX_Buffer[2]->count<RX_BUFFER_SIZE) // Если буфер не переполнен
        {
            char ch=IO_UART2.RDR2;
            pUART_RX_Buffer[2]->Buffer[pUART_RX_Buffer[2]->end]=ch;
            pUART_RX_Buffer[2]->count++;
            pUART_RX_Buffer[2]->end++;
            if (pUART_RX_Buffer[2]->end==RX_BUFFER_SIZE)
            {
                pUART_RX_Buffer[2]->end=0;
            }
            if (RX_Callback[2]) {RX_Callback[2](ch);}
        }
    }
        if (IO_UART4.SSR4.bit.RDRF)
        {
            if (pUART_RX_Buffer[4]->count<RX_BUFFER_SIZE) // Если буфер не переполнен
            {
                char ch=IO_UART4.RDR4;
                pUART_RX_Buffer[4]->Buffer[pUART_RX_Buffer[4]->end]=ch;
                pUART_RX_Buffer[4]->count++;
                pUART_RX_Buffer[4]->end++;
                if (pUART_RX_Buffer[4]->end==RX_BUFFER_SIZE)
                {
                    pUART_RX_Buffer[4]->end=0;
                }
                if (RX_Callback[4]) {RX_Callback[4](ch);}
            }
        }
    if(IO_UART2.SSR2.bit.FRE||IO_UART2.SSR2.bit.ORE||IO_UART2.SSR2.bit.PE)  {IO_UART2.SCR2.bit.CRE=1;}
     if(IO_UART4.SSR4.bit.FRE||IO_UART4.SSR4.bit.ORE||IO_UART4.SSR4.bit.PE)  {IO_UART4.SCR4.bit.CRE=1;}

    return;
}
