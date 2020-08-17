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
#ifndef __TPIC6B595_H__
#define __TPIC6B595_H__

#include "main.h"
#include "stdbool.h"

#define  JPHC595_DS_H()  HAL_GPIO_WritePin(TPIC_DATA_GPIO_Port, TPIC_DATA_Pin, GPIO_PIN_SET);
#define  JPHC595_DS_L()  HAL_GPIO_WritePin(TPIC_DATA_GPIO_Port, TPIC_DATA_Pin, GPIO_PIN_RESET);
#define  JPHC595_SRCLR_H()  HAL_GPIO_WritePin(TPIC_SRCLR_GPIO_Port, TPIC_SRCLR_Pin, GPIO_PIN_SET);
#define  JPHC595_SRCLR_L()  HAL_GPIO_WritePin(TPIC_SRCLR_GPIO_Port, TPIC_SRCLR_Pin, GPIO_PIN_RESET);
#define  JPHC595_SHCP_H()  HAL_GPIO_WritePin(TPIC_SRCK_GPIO_Port, TPIC_SRCK_Pin, GPIO_PIN_SET);
#define  JPHC595_SHCP_L()  HAL_GPIO_WritePin(TPIC_SRCK_GPIO_Port, TPIC_SRCK_Pin, GPIO_PIN_RESET);
#define  JPHC595_STCP_H()  HAL_GPIO_WritePin(TPIC_RCK_GPIO_Port, TPIC_RCK_Pin, GPIO_PIN_SET);
#define  JPHC595_STCP_L()  HAL_GPIO_WritePin(TPIC_RCK_GPIO_Port, TPIC_RCK_Pin, GPIO_PIN_RESET);    

void tpic6b595Action(uint16_t sel, bool val);

#endif /*__TW_TPIC6B595_H__*/
