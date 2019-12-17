#include "interrupt_vector.h"
#include "EERTOS.h"
#include "uart.h"
#include "command.h"
#include "ADC.h"
#include "count.h"
#include "gsm.h"
#include "string_.h"
char strrr[]="123";
UART_Settings UART0;
UART_Settings UART_GPS;
UART_Settings UART_GSM;
UART_Settings UART3;
void Blink(void);
void UART0_RX_Callback(char ch);
void UART_GPS_RX_Callback(char ch);
void UART_GSM_RX_Callback(char ch);
void UART3_RX_Callback(char ch);
void GSM_TX1(void);
void Uart0_TX(void);
void GPS_TX(void);
void GPS_RX(void);
void Pulse(void);
void GSM_Recv_Parser(void);
char GSM_Recv[40];

void GSM_TX1 (void)
{
    char ch=0;
    int i=0;
    for (i=0;i<40;i++)
    {
        GSM_Recv[i]=0;
    }
    i=0;
    while(UART_Recv(&UART_GSM,&ch))
    {
        GSM_Recv[i]=ch;
        i++;
        UART_Send(&UART0,ch);
        if(ch==10) {break;}
    }
    GSM_Recv[i]=0;
    SetTask(GSM_Recv_Parser);
}

void Uart0_TX(void)
{
   char ch;

   while(UART_Recv(&UART0,&ch))
   {
    UART_Send(&UART_GSM,ch);
   }

}

void GPS_TX(void)
{
    char ch;
  //  GPS_HL=ON;
    while(UART_Recv(&UART0,&ch))
    {
     UART_Send(&UART_GPS,ch);
    }
 //   GPS_HL=OFF;
}

void GPS_RX(void)
{
    char ch;
GSM_HL=ON;
    while(UART_Recv(&UART_GPS,&ch))
    {
     UART_Send(&UART0,ch);
    }
GSM_HL=OFF;
}

void UART3_TX(void)
{
    char ch[10];
    u08 len;
    u16 hs;
 //   GPS_HL=ON;
    len=UART_Recv_String(&UART0,ch,sizeof(ch));
    UART_Send_String(&UART3,ch);
    UART_Send(&UART3,len);
    hs =hash(ch);

    UART_Send(&UART3,(u08)((hs>>8)&0xFF));
    UART_Send(&UART3,(u08)(hs&0xFF));



   // GPS_HL=OFF;
}

void Blink(void)
{
//    u16 Count=0;
    u16 a=0;
    u16 b=0;
    u16 Cnt;

    Cnt=Count_Read();
    UART_Send(&UART0,(Cnt/1000)+0x30);
    a=Cnt%1000;
    UART_Send(&UART0,(a/100)+0x30);
    b=a%100;
    UART_Send(&UART0,(b/10)+0x30);
    UART_Send(&UART0,(b%10)+0x30);
    UART_Send(&UART0,32);

    UART_Send(&UART0,13);

   SetTimerTask(Blink,1000);
   ADC_Start();
   if(GSM_HL)
   {
       GSM_HL=OFF;
   }
   else
   {
       GSM_HL=ON;
   }
}

void Pulse(void)
{
    R1^=1;
   // GPS_HL^=1;
    SetTimerTask(Pulse,50);
}

void main (void)
{
    InitAll();
//    Init_ADC();
//    Count_Init();
    __set_il(7); // Set interrupt level of entire system to 7 (lowest)

    UART0.port=0;
    UART0.Baud_Rate=_19200;
    UART0.Data_Length=_8bit;
    UART0.Stop_Bit=_1;
    UART0.Parity=none;
    UART0.RX_Callback=UART0_RX_Callback;
    UART_INIT(&UART0);

    UART_GPS.port=2;
    UART_GPS.Baud_Rate=_4800;
    UART_GPS.Data_Length=_8bit;
    UART_GPS.Stop_Bit=_1;
    UART_GPS.Parity=none;
    UART_GPS.RX_Callback=UART_GPS_RX_Callback;
    UART_INIT(&UART_GPS);

    UART_GSM.port=1;
    UART_GSM.Baud_Rate=_19200;
    UART_GSM.Data_Length=_8bit;
    UART_GSM.Stop_Bit=_1;
    UART_GSM.Parity=none;
    UART_GSM.RX_Callback=UART_GSM_RX_Callback;
    UART_INIT(&UART_GSM);

    UART3.port=3;
    UART3.Baud_Rate=_19200;
    UART3.Data_Length=_8bit;
    UART3.Stop_Bit=_1;
    UART3.Parity=none;
    UART3.RX_Callback=UART3_RX_Callback;
    UART_INIT(&UART3);

    InitRTOS();			// Инициализация RTOS
    RunRTOS();			// Старт RTOS
    // Фоновые задачи
   // SetTask(Blink);
  //  SetTask(Pulse);
   // GPS_PWR=ON;
   // SetTimerTask(GSM_Start,1000);


   // while (1)
    for(;;)
    {
        TaskManager();	// Вызов диспетчера
    }
}

void UART0_RX_Callback(char ch)
{

    if (ch==13)
    {
        //SetTimerTask(Uart0_TX,100);

        UART_Send_String(&UART0,strrr);

    }
}

void UART_GPS_RX_Callback(char ch)
{
    if (ch==10)
    {
      //  SetTimerTask(GPS_RX,10);
    }

}

void UART_GSM_RX_Callback(char ch)
{
    if (ch==10)
    {
        SetTask(GSM_TX1);
    }

}

void UART3_RX_Callback(char ch)
{

    if (ch==13)
    {
     SetTimerTask(GSM_Stop,100);
   }
}

void GSM_Recv_Parser(void)
{
    char str[13]={0};
    char str1[13]={0};
    int i=0;
    int j=0;
    int res=0;
    str[0]='+';
    str[1]='7';
    str[2]='9';
    str[3]='6';
    str[4]='1';
    str[5]='3';
    str[6]='5';
    str[7]='0';
    str[8]='7';
    str[9]='8';
    str[10]='4';
    str[11]='8';
    str[12]='\0';
    while (GSM_Recv[i]!=0)
    {
        if(i>=8&i<=19)
        {
            str1[j]=GSM_Recv[i];
            j++;
        }

        i++;
    }
    str1[j]=0;

    res=strcmp(str1,str);

   if (res==0)
   {
       GPS_HL^=1;
   }

   // UART_Send_String(&UART0,str1);
//    UART_Send(&UART0,13);
//    UART_Send(&UART0,10);
//    UART_Send(&UART0,res);
//    UART_Send(&UART0,13);
//    UART_Send(&UART0,10);
}
