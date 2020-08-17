/**
  ******************************************************************************
  * @file     TPIC6B595.c
  * @author   李柏文
  * @version  
  * @date     2013.4.18
  * @brief
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "TPIC6B595.h"
#include "stdbool.h"

uint16_t sel_rec = 0;
void tpic6b595Action(uint16_t sel, bool val)
{
    uint16_t temp_dat = 0;
    uint8_t i;
  
    if ( val == false )
    {
        sel_rec &= ~sel;
    }
    else
    {
        sel_rec |= sel;
    }
    
    if ( sel_rec == 0 )
    {
        JPHC595_SRCLR_L(); 
        for(int i=0;i<30;i++)
        {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
    }
    else
    {
        JPHC595_SRCLR_H(); 
        for(int i=0;i<30;i++)
        {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
    }
    
    temp_dat = sel_rec;
    
    //置位
    JPHC595_STCP_L();//与上取反则为0输出,或上原值为1输出

    for(int i=0;i<30;i++)
    {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
    for(i=0;i<8;i++)
    {
        JPHC595_SHCP_L();	//拉低
        
        for(int i=0;i<30;i++)
        {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
        if(((temp_dat&0x80)!=0?1:0))
        {
          JPHC595_DS_H();
        }
        else
        {
          JPHC595_DS_L();
        }
        temp_dat <<= 1;

        for(int i=0;i<30;i++)
        {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
        JPHC595_SHCP_H();	//拉高

        for(int i=0;i<30;i++)
        {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
    }
    JPHC595_STCP_H();

    for(int i=0;i<30;i++)
    {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
}
