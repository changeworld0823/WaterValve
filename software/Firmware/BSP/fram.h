/**
  ******************************************************************************
  * @file     fram.h
  * @author   李柏文
  * @version  
  * @date     2020年8月02日
  * @brief
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#ifndef __FRAM_H__
#define __FRAM_H__

#include "stm32f1xx.h"
#include "stdbool.h"

uint8_t framWrite(uint8_t *p, uint16_t addr, uint16_t len);
uint8_t framRead(uint8_t *p, uint16_t addr, uint16_t len);
void framInit(void);

#endif
