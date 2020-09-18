/**
  ******************************************************************************
  * @file     input.h
  * @author   李柏文
  * @version  
  * @date     2020年8月02日
  * @brief
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#ifndef __INPUT_H__
#define __INPUT_H__

#include "stm32f1xx.h"
#include "stdbool.h"
#include "main.h"

typedef enum {
  D_IN_NoAction,
  D_IN_FaillingEdge,
  D_IN_RisingEdge,
  D_IN_Pressed,
  D_IN_Released
} eD_IN_STATUS;


//polarity configuration constant
#define POS 1
#define NEG 0

//Hardware configuration                                                              
#define D_IN_POL     NEG

#define D_IN_NUM     D_IN_LAST


typedef enum {D_IN_1 = 0, 
              D_IN_2,
              D_IN_3,
              D_IN_4,
              D_IN_5,
              D_IN_6,
              D_IN_7,
              D_IN_8,
              D_IN_LAST
} d_in_t;

void inputInit(void);

eD_IN_STATUS inputGetDInEdgeStatus(d_in_t sr);
eD_IN_STATUS inputGetDInHoldStatus(d_in_t sr);

#endif
