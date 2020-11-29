/**
  ******************************************************************************
  * @file     common.c
  * @author   �����
  * @version
  * @date     2020��9��18��
  * @brief    һЩ�����ĺ���
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "iv_in.h"
#include "iv_out.h"
#include "opto_in.h"
#include "relay_out.h"
#include "calendar.h"

#include "mem.h"
#include "piezo.h"
#include "sound.h"
#include "buzzer.h"
#include "stdio.h"


uint8_t g_control_type = CONTROL_TYPE_AUTO;
uint8_t ble_data[BLE_DATA_BUF_SIZE];
/* Ӳ���豸��ʼ�� */
void init_dev(void)
{
    eIVInStatus_t ivinStatus;
    eIVOutStatus_t ivoutStatus;
		sCalendar_t calendar_t;
    /* ��ʼ�������� */
    soundInit();

    /* ��ʼ���洢�� */
    mem_dev.init();

    /* ��ʼ��������ѹ�����豸 */
    ivinStatus = iv_in_dev.init();
    if(ivinStatus != eIVIn_Ok)
    {
        //"IV�����豸��ʼ��ʧ�ܣ�";
        while(1) osDelay(1000);
    }

#if defined(USE_I_OUT)
    /* ��ʼ��������ѹ����豸 */
    ivoutStatus = iv_out_dev.init();
    if(ivoutStatus != eIVOut_Ok)
    {
        //"IV����豸��ʼ��ʧ�ܣ�";
        while(1) osDelay(1000);
    }
#endif

    /* ��ʼ���̵�������豸 */
    relay_out_dev.init();

    /* ��ʼ�����������豸 */
    opto_in_dev.init();
    
    /* ��ʼ������ */
    calendar_dev.init();
		#ifdef SET_CURRENTTIME_INIT
		calendar_t.year = 2020;
		calendar_t.month = 9;
		calendar_t.mday = 22;
		calendar_t.hour = 14;
		calendar_t.min = 25;
		calendar_t.sec = 0;
		calendar_t.wday = 3;
		calendar_dev.set(&calendar_t);
		#endif
}

/* ���ȵ�������ת�� */
static float openingDegreeToIma(float percent)
{
    //return (float)(percent/100.0*20);   /* ������뷶Χ��0-20ma�Ŀ��Ʒ� */
    return (float)(percent/100.0*(16)+4); /* ������뷶Χ��4-20ma�Ŀ��Ʒ� */
}

/* ���ÿ��� */
void setValveActionWithOpening(float Opening)
{
#if defined(USE_I_OUT)
    iv_out_dev.i_out(openingDegreeToIma(Opening));
#endif
}

/* ���ֵ */
__weak float getTolerance(void)
{
    return 0;
}

/* ���ÿ��� */
void setValveActionWithERR(float ERR)
{
#if defined(USE_RLY_OUT)
  
    if(ERR<=getTolerance())
    {
        ERR = 0;
    }

		int action;
    if(ERR>0)
    {
        relay_out_dev.out(eRLYOut_CH1,false);
        //relay_out_dev.out(eRLYOut_CH2,false);
        osDelay(100);                                        //�����ʵ���ʱ��Ԥ���̵�����е��Ӧʱ��
        relay_out_dev.out(eRLYOut_CH2,true);
				action = VALVE_STATE_DOWN;
		}
		else if(ERR<0)
		{
        relay_out_dev.out(eRLYOut_CH2,false);
        //relay_out_dev.out(eRLYOut_CH1,false);
        osDelay(100);                                        //�����ʵ���ʱ��Ԥ���̵�����е��Ӧʱ��
        relay_out_dev.out(eRLYOut_CH1,true);
				action = VALVE_STATE_UP;
		}
		else
		{
        relay_out_dev.out(eRLYOut_CH1,false);
        relay_out_dev.out(eRLYOut_CH2,false);
				action = VALVE_STATE_KEEP;
		}
#endif
}

void manualSetValve(int Action)
{
    switch(Action){
      case VALVE_STATE_DOWN:
          setValveActionWithOpening(0);
          setValveActionWithERR(-1);
          break;
      case VALVE_STATE_UP:
          setValveActionWithOpening(100);
          setValveActionWithERR(1);
          break;
      case VALVE_STATE_KEEP:
          setValveActionWithERR(0);
          break;
      default:
          break;
    }
}
