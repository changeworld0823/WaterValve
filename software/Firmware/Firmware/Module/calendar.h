/**
  ******************************************************************************
  * @file     calendar.h
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "timers.h"


typedef enum
{
    eCalendar_Ok,       /* 状态OK */
    eCalendar_InitFail, /* 初始化失败 */
    eCalendar_SetFail,  /* 设置失败 */
    eCalendar_GetFail,  /* 获取失败 */
} eCalendarStatus_t;

typedef struct 
{
    uint8_t hour;       /* 小时，范围：0-23 */
    uint8_t min;        /* 分钟，范围：0-59 */
    uint8_t sec;        /* 秒，范围：0-59 */
    uint16_t year;      /* 年，范围：2000-2099 */
    uint8_t  month;     /* 月，范围：1-12 */
    uint8_t  mday;      /* 日，范围：0-31 */
    uint8_t  wday;      /* 一个星期的第几天，从1开始，1代表星期日，范围：1-7 */
} sCalendar_t;

typedef struct
{
    /* 初始化 */
    eCalendarStatus_t (*init)(void);
    /* 设置时间 */
    eCalendarStatus_t (*set)(const sCalendar_t *TM);
    /* 获取时间 */
    eCalendarStatus_t (*get)(sCalendar_t *TM);
} calendar_dev_t;


extern const calendar_dev_t calendar_dev;

#endif
