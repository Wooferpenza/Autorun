#include "gsm.h"
#include "EERTOS.h"
void GSM_Start(void)
{
    if (!GSM_VBAT)              {GSM_VBAT=ON; GSM_HL=ON; SetTimerTask(GSM_Start,1000); return;}
    if (GSM_VBAT&&!GSM_PWRKEY)  {GSM_PWRKEY=ON; GPS_HL=ON; SetTimerTask(GSM_Start,3000); return;}
    if (GSM_VBAT&&GSM_PWRKEY)   {GSM_PWRKEY=OFF; GPS_HL=OFF;  return;}

}

void GSM_Stop(void)
{
    static st=0;
    if (GSM_VBAT&&!GSM_PWRKEY&&!st)  {GSM_PWRKEY=ON; GPS_HL=ON; SetTimerTask(GSM_Stop,1500); return;}
    if (GSM_VBAT&&GSM_PWRKEY)        {GSM_PWRKEY=OFF; GPS_HL=OFF; SetTimerTask(GSM_Stop,8000);st=1; return;}
    if (GSM_VBAT)                    {GSM_VBAT=OFF; GSM_HL=OFF; st=0; return;}
}
