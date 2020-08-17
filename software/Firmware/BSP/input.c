/**
  ******************************************************************************
  * @file     input.c
  * @author   李柏文
  * @version
  * @date     2020年8月02日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "input.h"
#include "FreeRtos.h"
#include "timers.h"

static GPIO_TypeDef* port[] =
{
  [D_IN_1] = MCU_D8_IN_GPIO_Port,
  [D_IN_2] = MCU_D7_IN_GPIO_Port,
  [D_IN_3] = MCU_D6_IN_GPIO_Port,
  [D_IN_4] = MCU_D5_IN_GPIO_Port,
  [D_IN_5] = MCU_D4_IN_GPIO_Port,
  [D_IN_6] = MCU_D3_IN_GPIO_Port,
  [D_IN_7] = MCU_D2_IN_GPIO_Port,
  [D_IN_8] = MCU_D1_IN_GPIO_Port,
};
static unsigned int pin[] =
{
  [D_IN_1] = MCU_D8_IN_Pin,
  [D_IN_2] = MCU_D7_IN_Pin,
  [D_IN_3] = MCU_D6_IN_Pin,
  [D_IN_4] = MCU_D5_IN_Pin,
  [D_IN_5] = MCU_D4_IN_Pin,
  [D_IN_6] = MCU_D3_IN_Pin,
  [D_IN_7] = MCU_D2_IN_Pin,
  [D_IN_8] = MCU_D1_IN_Pin,
};
static int polarity[] =
{
  [D_IN_1] = D_IN_POL,
  [D_IN_2] = D_IN_POL,
  [D_IN_3] = D_IN_POL,
  [D_IN_4] = D_IN_POL,
  [D_IN_5] = D_IN_POL,
  [D_IN_6] = D_IN_POL,
  [D_IN_7] = D_IN_POL,
  [D_IN_8] = D_IN_POL,
};

void inputInit(void)
{
  //IO的初始化由CubeMX生成代码了，这里不做什么
}

GPIO_PinState pinState;
static bool dInSR_GetStatus(d_in_t sr)
{
  bool value;

  if (sr>D_IN_LAST)
    return false;
  
  pinState = GPIO_PIN_SET;
  pinState = HAL_GPIO_ReadPin(port[sr], pin[sr]);

  if( pinState == GPIO_PIN_RESET )
  {
    if (polarity[sr]==NEG)
      value = true;
    else
      value = false;
  }
  else
  {
    if (polarity[sr]==NEG)
      value = false;
    else
      value = true;
  }
  
  return value;
}

eD_IN_STATUS inputGetDInHoldStatus(d_in_t sr)
{
  if(sr>D_IN_LAST) return D_IN_NoAction;

  static uint8_t state = 0;
  uint8_t retval;
  bool now_read = false;
  static bool last_read[D_IN_LAST] = {false};
  static bool unchange[D_IN_LAST] = {false};
  static TickType_t last_time[D_IN_LAST];
  static eD_IN_STATUS val[D_IN_LAST] = {D_IN_NoAction};
  
  TickType_t now_time = xTaskGetTickCount();
  
  now_read = dInSR_GetStatus(sr);
  
  if( now_read != last_read[sr] ) {
    last_time[sr] = now_time;
    unchange[sr] = false;
  }
  if( !unchange[sr] && ((now_time-last_time[sr])>30) )
  {
    if(now_read==true)
    {
      //按下去的
      val[sr] = D_IN_Pressed;
    }
    else
    {
      //松开的
      val[sr] = D_IN_Released;
    }
    unchange[sr] = true;
  }
  last_read[sr] = now_read;
  
  return val[sr];
}

eD_IN_STATUS inputGetDInEdgeStatus(d_in_t sr)
{
  if(sr>D_IN_LAST) return D_IN_NoAction;

  static uint8_t state = 0;
  uint8_t retval;
  bool now_read = false;
  static bool last_read[D_IN_LAST] = {false};
  static bool unchange[D_IN_LAST] = {false};
  static TickType_t last_time[D_IN_LAST];
  eD_IN_STATUS val = D_IN_NoAction;
  static eD_IN_STATUS lastVal[D_IN_LAST] = {D_IN_NoAction};
  
  TickType_t now_time = xTaskGetTickCount();
  
  now_read = dInSR_GetStatus(sr);
  
  if( now_read != last_read[sr] ) {
    last_time[sr] = now_time;
    unchange[sr] = false;
  }
  if( !unchange[sr] && ((now_time-last_time[sr])>30) )
  {
    if(now_read==true)
    {
      //按下去了
      if(lastVal[sr]!=D_IN_FaillingEdge)
      {
        val = D_IN_FaillingEdge;
        lastVal[sr] = D_IN_FaillingEdge;
      }
    }
    else
    {
      //松开了
      if(lastVal[sr]!=D_IN_RisingEdge)
      {
        val = D_IN_RisingEdge;
        lastVal[sr] = D_IN_RisingEdge;
      }
    }
    unchange[sr] = true;
  }
  last_read[sr] = now_read;
  
  return val;
}
