
#if 0
    ivoutStatus = iv_out_dev.i_out(curSet);
    if(ivoutStatus!=eIVOut_Ok)
    {
        printf("IVOut device set output fail! %d\r\n",ivoutStatus);
    }
    float ima = 0;
    ivinStatus = iv_in_dev.i_in(eIVInCH4,&ima);
    if(ivinStatus==eIVIn_Ok)
    {
        printf("Current = %f\r\n",ima);
    }
    else
    {
        printf("IVIn device get input fail! %d\r\n",ivinStatus);
    }
    
    
    eCalendarStatus_t cldStatu = calendar_dev.get(&cld);
    if(cldStatu==eCalendar_Ok)
    {
        printf("Date: %04d-%02d-%02d week-%d\r\n",cld.year,cld.month,cld.mday,cld.wday);
        printf("Time: %02d:%02d:%02d\r\n",cld.hour,cld.min,cld.sec);
    }
    else
    {
        printf("Calendar get fail!\r\n");
    }
    if(cldSet)
    {
        if(calendar_dev.set(&cld)==eCalendar_Ok)
        {
            printf("Calendar Set Success!\r\n");
        }
        else
        {
            printf("Calendar Set Fail!\r\n");
        }
        cldSet = 0;
    }
#endif