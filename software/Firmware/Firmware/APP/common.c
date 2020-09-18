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

/* Ӳ���豸��ʼ�� */
void init_dev(void)
{
    eIVInStatus_t ivinStatus;
    eIVOutStatus_t ivoutStatus;
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
    
    /* ��ʼ��������ѹ����豸 */
    ivoutStatus = iv_out_dev.init();
    if(ivoutStatus != eIVOut_Ok)
    {
        //"IV����豸��ʼ��ʧ�ܣ�";
        while(1) osDelay(1000);
    }
    
    /* ��ʼ���̵�������豸 */
    relay_out_dev.init();

    /* ��ʼ�����������豸 */
    opto_in_dev.init();
    
    /* ��ʼ������ */
    calendar_dev.init();
}
