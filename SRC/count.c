#include "count.h"
 //TODO: учитывать переполнение
u32 Curr_Count=0;
u32 Prev_Count=0;

void Count_Init(void)
{
    IO_TCCS0.bit.CLK=7;
    IO_ICS23.bit.EG2=1;
    IO_ICS23.bit.ICE2=1;
    IO_ICR11.bit.IL=0x00;
}

u16 Count_Read(void)
{
    u16 value;
    IO_ICS23.bit.ICE2=0;
    if (Curr_Count>Prev_Count)
    {
        value=187500UL/(Curr_Count-Prev_Count);
    }
    else
    {
        if (Curr_Count==Prev_Count)
        {
            value=0;
        }
        else
        {
           value=187500UL/(65535U+Curr_Count-Prev_Count);
        }
    }
IO_ICS23.bit.ICE2=1;
return value;
}

__interrupt void Count_Capture(void)
{
    if(IO_ICS23.bit.ICP2)
    {
        IO_ICS23.bit.ICP2=0;
        Prev_Count=Curr_Count;
        Curr_Count=IO_IPCP.IPCP2;
    }

}
