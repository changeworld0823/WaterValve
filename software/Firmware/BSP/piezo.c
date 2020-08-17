/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2012 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * piezo.c - Piezo/Buzzer driver
 *
 * This code mainly interfacing the PWM peripheral lib of ST.
 */

#include <stdbool.h>

/* ST includes */
#include "stm32f1xx.h"

#include "piezo.h"

//FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

static bool isInit = false;

/* Public functions */

void piezoInit()
{
  if (isInit)
    return;
  
  if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK)
  {
    /* PWM Generation Error */
  }

  isInit = true;
}

bool piezoTest(void)
{
  return isInit;
}

void TIM3_CH1_FREQ_DUTY(uint16_t freq, uint8_t duty)
{
    uint16_t TIM_Prescaler,TIM_Period;
    uint32_t utemp;
    
    if (freq==0)
    {
        TIM3->ARR = 65535;
        TIM3->CCR1 = 0;
        return;
    }
    
    utemp = SystemCoreClock/(uint32_t)freq;
    
    TIM_Prescaler = utemp/65536;
    ++TIM_Prescaler;                       // 注意这句话，一定要++
    
    utemp =SystemCoreClock/TIM_Prescaler;  // 分频后的定时器输入频率
    TIM_Period = utemp/freq;               // 周期常数
    
    /* Set the Autoreload value */
    TIM3->ARR = TIM_Period-1;
     
    /* Set the Prescaler value */
    TIM3->PSC = TIM_Prescaler-1;
        
    TIM3->CCR1 = (uint16_t)((duty/100.0)*(TIM3->ARR+1));
    //TIM3->EGR  = TIM_PSCReloadMode_Update;               // 定时器开始运行
}
extern TIM_HandleTypeDef htim3;
void piezoSetRatio(uint8_t ratio)
{
  //return;
  htim3.Instance->CCR1 = ratio/100.0*TIM3->ARR;
}

void piezoSetFreq(uint16_t freq)
{
    //return;
    TIM3_CH1_FREQ_DUTY(freq,30);
    //TIM3->PSC = (PIEZO_BASE_FREQ/freq)-1;
}
