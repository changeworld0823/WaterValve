/**
  ******************************************************************************
  * @file     calendar.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "tps08u.h"
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "calendar.h"
#include "ds3231.h"

/* 初始化 */
eCalendarStatus_t calendar_init(void)
{
    uint8_t mode = 0;
    uint8_t enable = 0;

    if(ds3231_init()==0)
    {
        return eCalendar_InitFail;  /* 初始化失败 */
    }

    return eCalendar_Ok;            /* 初始化成功 */
}

/* 设置日期时间 */
eCalendarStatus_t calendar_set(const sCalendar_t *s)
{
    struct tm tmVal;
    
    tmVal.tm_year = s->year;
    tmVal.tm_mon  = s->month-1;
    tmVal.tm_mday = s->mday;
    tmVal.tm_hour = s->hour;
    tmVal.tm_min  = s->min;
    tmVal.tm_sec  = s->sec;
    tmVal.tm_wday = s->wday-1;
    
    uint8_t ret = ds3231_set_time(&tmVal);
    
    if(ret==0) return eCalendar_SetFail;
    
    return eCalendar_Ok;
}

/* 获取日期时间 */
eCalendarStatus_t calendar_get(sCalendar_t *s)
{
    struct tm tmVal;
    
    uint8_t ret = ds3231_get_time(&tmVal);
    
    if(ret==0) return eCalendar_GetFail;
    
    s->year   = tmVal.tm_year;
    s->month  = tmVal.tm_mon+1;
    s->mday   = tmVal.tm_mday;
    s->hour   = tmVal.tm_hour;
    s->min    = tmVal.tm_min;
    s->sec    = tmVal.tm_sec;
    s->wday   = tmVal.tm_wday+1;
    
    return eCalendar_Ok;
}

/* 日历设备 */
const calendar_dev_t calendar_dev =
{
   .init = calendar_init,
   .set = calendar_set,
   .get = calendar_get,
};

