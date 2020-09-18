#line 1 "..\\BSP\\mem_data.c"










 

#line 1 "..\\BSP\\mem_data.h"











  



#line 1 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"



























 



 



 
    






  


 



 






 

#line 78 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"



 
  
#line 91 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"



 
#line 103 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"



 



 

#line 1 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

























 




 



 
    









 


 







 



 




 

  
typedef enum
{
 
  NonMaskableInt_IRQn         = -14,     
  HardFault_IRQn              = -13,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      
  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_IRQn               = 24,      
  TIM1_UP_IRQn                = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTC_Alarm_IRQn              = 41,      
  USBWakeUp_IRQn              = 42,      
  TIM8_BRK_IRQn               = 43,      
  TIM8_UP_IRQn                = 44,      
  TIM8_TRG_COM_IRQn           = 45,      
  TIM8_CC_IRQn                = 46,      
  ADC3_IRQn                   = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_IRQn                   = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_5_IRQn        = 59,      
} IRQn_Type;



 

#line 1 "../Drivers/CMSIS/Include/core_cm3.h"
 




 
















 










#line 1 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 35 "../Drivers/CMSIS/Include/core_cm3.h"

















 




 



 

#line 1 "../Drivers/CMSIS/Include/cmsis_version.h"
 




 
















 










 
#line 64 "../Drivers/CMSIS/Include/core_cm3.h"

 









 







#line 114 "../Drivers/CMSIS/Include/core_cm3.h"

#line 1 "../Drivers/CMSIS/Include/cmsis_compiler.h"
 




 
















 




#line 29 "../Drivers/CMSIS/Include/cmsis_compiler.h"



 
#line 1 "../Drivers/CMSIS/Include/cmsis_armcc.h"
 




 
















 









 













   
   


 
#line 103 "../Drivers/CMSIS/Include/cmsis_armcc.h"

 



 





 
 






 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}









 







 







 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}






 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xFFU);
}







 
static __inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  register uint32_t __regBasePriMax      __asm("basepri_max");
  __regBasePriMax = (basePri & 0xFFU);
}






 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}






 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1U);
}









 
static __inline uint32_t __get_FPSCR(void)
{





   return(0U);

}






 
static __inline void __set_FPSCR(uint32_t fpscr)
{





  (void)fpscr;

}


 


 



 




 






 







 






 








 










 










 






                  





 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 
#line 532 "../Drivers/CMSIS/Include/cmsis_armcc.h"







 











 












 












 














 














 














 










 









 









 









 

__attribute__((section(".rrx_text"))) static __inline __asm uint32_t __RRX(uint32_t value)
{
  rrx r0, r0
  bx lr
}








 








 








 








 








 








 


#line 780 "../Drivers/CMSIS/Include/cmsis_armcc.h"

   


 



 

#line 862 "../Drivers/CMSIS/Include/cmsis_armcc.h"
 


#line 35 "../Drivers/CMSIS/Include/cmsis_compiler.h"




 
#line 263 "../Drivers/CMSIS/Include/cmsis_compiler.h"




#line 116 "../Drivers/CMSIS/Include/core_cm3.h"

















 
#line 155 "../Drivers/CMSIS/Include/core_cm3.h"

 






 
#line 171 "../Drivers/CMSIS/Include/core_cm3.h"

 




 












 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:27;               
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 


















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:1;                
    uint32_t ICI_IT_1:6;                  
    uint32_t _reserved1:8;                
    uint32_t T:1;                         
    uint32_t ICI_IT_2:2;                  
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 






























 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t _reserved1:30;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 







 



 
typedef struct
{
  volatile uint32_t ISER[8U];                
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];                
        uint32_t RSERVED1[24U];
  volatile uint32_t ISPR[8U];                
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];                
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];                
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];                
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;                    
}  NVIC_Type;

 



 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
  volatile uint32_t VTOR;                    
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
  volatile uint8_t  SHP[12U];                
  volatile uint32_t SHCSR;                   
  volatile uint32_t CFSR;                    
  volatile uint32_t HFSR;                    
  volatile uint32_t DFSR;                    
  volatile uint32_t MMFAR;                   
  volatile uint32_t BFAR;                    
  volatile uint32_t AFSR;                    
  volatile const  uint32_t PFR[2U];                 
  volatile const  uint32_t DFR;                     
  volatile const  uint32_t ADR;                     
  volatile const  uint32_t MMFR[4U];                
  volatile const  uint32_t ISAR[5U];                
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                   
} SCB_Type;

 















 






























 




#line 457 "../Drivers/CMSIS/Include/core_cm3.h"

 





















 









 


















 










































 









 















 


















 


















 









 















 







 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const  uint32_t ICTR;                    

  volatile uint32_t ACTLR;                   



} SCnSCB_Type;

 



 










 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 







 



 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                  
    volatile  uint16_t   u16;                 
    volatile  uint32_t   u32;                 
  }  PORT [32U];                          
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;                     
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;                     
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;                     
        uint32_t RESERVED3[29U];
  volatile  uint32_t IWR;                     
  volatile const  uint32_t IRR;                     
  volatile uint32_t IMCR;                    
        uint32_t RESERVED4[43U];
  volatile  uint32_t LAR;                     
  volatile const  uint32_t LSR;                     
        uint32_t RESERVED5[6U];
  volatile const  uint32_t PID4;                    
  volatile const  uint32_t PID5;                    
  volatile const  uint32_t PID6;                    
  volatile const  uint32_t PID7;                    
  volatile const  uint32_t PID0;                    
  volatile const  uint32_t PID1;                    
  volatile const  uint32_t PID2;                    
  volatile const  uint32_t PID3;                    
  volatile const  uint32_t CID0;                    
  volatile const  uint32_t CID1;                    
  volatile const  uint32_t CID2;                    
  volatile const  uint32_t CID3;                    
} ITM_Type;

 



 



























 



 



 



 









   







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t CYCCNT;                  
  volatile uint32_t CPICNT;                  
  volatile uint32_t EXCCNT;                  
  volatile uint32_t SLEEPCNT;                
  volatile uint32_t LSUCNT;                  
  volatile uint32_t FOLDCNT;                 
  volatile const  uint32_t PCSR;                    
  volatile uint32_t COMP0;                   
  volatile uint32_t MASK0;                   
  volatile uint32_t FUNCTION0;               
        uint32_t RESERVED0[1U];
  volatile uint32_t COMP1;                   
  volatile uint32_t MASK1;                   
  volatile uint32_t FUNCTION1;               
        uint32_t RESERVED1[1U];
  volatile uint32_t COMP2;                   
  volatile uint32_t MASK2;                   
  volatile uint32_t FUNCTION2;               
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP3;                   
  volatile uint32_t MASK3;                   
  volatile uint32_t FUNCTION3;               
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   







 



 
typedef struct
{
  volatile const  uint32_t SSPSR;                   
  volatile uint32_t CSPSR;                   
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;                    
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;                    
        uint32_t RESERVED2[131U];
  volatile const  uint32_t FFSR;                    
  volatile uint32_t FFCR;                    
  volatile const  uint32_t FSCR;                    
        uint32_t RESERVED3[759U];
  volatile const  uint32_t TRIGGER;                 
  volatile const  uint32_t FIFO0;                   
  volatile const  uint32_t ITATBCTR2;               
        uint32_t RESERVED4[1U];
  volatile const  uint32_t ITATBCTR0;               
  volatile const  uint32_t FIFO1;                   
  volatile uint32_t ITCTRL;                  
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;                
  volatile uint32_t CLAIMCLR;                
        uint32_t RESERVED7[8U];
  volatile const  uint32_t DEVID;                   
  volatile const  uint32_t DEVTYPE;                 
} TPI_Type;

 



 



 












 






 



 





















 






 





















 






 



 


















 






   


#line 1242 "../Drivers/CMSIS/Include/core_cm3.h"







 



 
typedef struct
{
  volatile uint32_t DHCSR;                   
  volatile  uint32_t DCRSR;                   
  volatile uint32_t DCRDR;                   
  volatile uint32_t DEMCR;                   
} CoreDebug_Type;

 




































 






 







































 







 






 







 


 







 

 
#line 1391 "../Drivers/CMSIS/Include/core_cm3.h"

#line 1400 "../Drivers/CMSIS/Include/core_cm3.h"






 










 


 



 





 

#line 1451 "../Drivers/CMSIS/Include/core_cm3.h"

#line 1461 "../Drivers/CMSIS/Include/core_cm3.h"




 













 
static __inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);              

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));  
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U) );                
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}






 
static __inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}







 
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}









 
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);
  }
}









 
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}







 
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}









 
static __inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}










 
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}










 
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               >> (8U - 4U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4U)));
  }
}












 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}










 
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];
}





 
__declspec(noreturn) static __inline void __NVIC_SystemReset(void)
{
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = (uint32_t)((0x5FAUL << 16U)    |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U)    );          
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 

 







 





 








 
static __inline uint32_t SCB_GetFPUType(void)
{
    return 0U;            
}


 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 4U) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 



 





 

extern volatile int32_t ITM_RxBuffer;                               










 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&       
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL               ) != 0UL)   )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __nop();
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}







 
static __inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                            

  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);        
  }

  return (ch);
}







 
static __inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);                               
  }
  else
  {
    return (1);                               
  }
}

 










#line 150 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
#line 1 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/system_stm32f1xx.h"

















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           
extern const uint8_t  AHBPrescTable[16U];   
extern const uint8_t  APBPrescTable[8U];    



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 151 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
#line 152 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;

typedef struct
{
  volatile uint32_t SR;                
  volatile uint32_t CR1;               
  volatile uint32_t CR2;               
  uint32_t  RESERVED[16];
  volatile uint32_t DR;                
} ADC_Common_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint32_t DR1;
  volatile uint32_t DR2;
  volatile uint32_t DR3;
  volatile uint32_t DR4;
  volatile uint32_t DR5;
  volatile uint32_t DR6;
  volatile uint32_t DR7;
  volatile uint32_t DR8;
  volatile uint32_t DR9;
  volatile uint32_t DR10;
  volatile uint32_t RTCCR;
  volatile uint32_t CR;
  volatile uint32_t CSR;
  uint32_t  RESERVED13[2];
  volatile uint32_t DR11;
  volatile uint32_t DR12;
  volatile uint32_t DR13;
  volatile uint32_t DR14;
  volatile uint32_t DR15;
  volatile uint32_t DR16;
  volatile uint32_t DR17;
  volatile uint32_t DR18;
  volatile uint32_t DR19;
  volatile uint32_t DR20;
  volatile uint32_t DR21;
  volatile uint32_t DR22;
  volatile uint32_t DR23;
  volatile uint32_t DR24;
  volatile uint32_t DR25;
  volatile uint32_t DR26;
  volatile uint32_t DR27;
  volatile uint32_t DR28;
  volatile uint32_t DR29;
  volatile uint32_t DR30;
  volatile uint32_t DR31;
  volatile uint32_t DR32;
  volatile uint32_t DR33;
  volatile uint32_t DR34;
  volatile uint32_t DR35;
  volatile uint32_t DR36;
  volatile uint32_t DR37;
  volatile uint32_t DR38;
  volatile uint32_t DR39;
  volatile uint32_t DR40;
  volatile uint32_t DR41;
  volatile uint32_t DR42;
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[14];
} CAN_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;            
  volatile uint8_t  IDR;           
  uint8_t       RESERVED0;     
  uint16_t      RESERVED1;       
  volatile uint32_t CR;             
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;
} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;





 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;        
  volatile uint32_t SR2;         
  volatile uint32_t PMEM2;       
  volatile uint32_t PATT2;       
  uint32_t      RESERVED0;   
  volatile uint32_t ECCR2;       
  uint32_t      RESERVED1;   
  uint32_t      RESERVED2;   
  volatile uint32_t PCR3;        
  volatile uint32_t SR3;         
  volatile uint32_t PMEM3;       
  volatile uint32_t PATT3;       
  uint32_t      RESERVED3;   
  volatile uint32_t ECCR3;       
} FSMC_Bank2_3_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t OAR1;
  volatile uint32_t OAR2;
  volatile uint32_t DR;
  volatile uint32_t SR1;
  volatile uint32_t SR2;
  volatile uint32_t CCR;
  volatile uint32_t TRISE;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;            
  volatile uint32_t PR;            
  volatile uint32_t RLR;           
  volatile uint32_t SR;            
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;


} RCC_TypeDef;



 

typedef struct
{
  volatile uint32_t CRH;
  volatile uint32_t CRL;
  volatile uint32_t PRLH;
  volatile uint32_t PRLL;
  volatile uint32_t DIVH;
  volatile uint32_t DIVL;
  volatile uint32_t CNTH;
  volatile uint32_t CNTL;
  volatile uint32_t ALRH;
  volatile uint32_t ALRL;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t CRCPR;
  volatile uint32_t RXCRCR;
  volatile uint32_t TXCRCR;
  volatile uint32_t I2SCFGR;
  volatile uint32_t I2SPR;
} SPI_TypeDef;



 
typedef struct
{
  volatile uint32_t CR1;              
  volatile uint32_t CR2;              
  volatile uint32_t SMCR;             
  volatile uint32_t DIER;             
  volatile uint32_t SR;               
  volatile uint32_t EGR;              
  volatile uint32_t CCMR1;            
  volatile uint32_t CCMR2;            
  volatile uint32_t CCER;             
  volatile uint32_t CNT;              
  volatile uint32_t PSC;              
  volatile uint32_t ARR;              
  volatile uint32_t RCR;              
  volatile uint32_t CCR1;             
  volatile uint32_t CCR2;             
  volatile uint32_t CCR3;             
  volatile uint32_t CCR4;             
  volatile uint32_t BDTR;             
  volatile uint32_t DCR;              
  volatile uint32_t DMAR;             
  volatile uint32_t OR;               
}TIM_TypeDef;




 
 
typedef struct
{
  volatile uint32_t SR;          
  volatile uint32_t DR;          
  volatile uint32_t BRR;         
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t CR3;         
  volatile uint32_t GTPR;        
} USART_TypeDef;



 
  
typedef struct
{
  volatile uint16_t EP0R;                   
  volatile uint16_t RESERVED0;                  
  volatile uint16_t EP1R;                  
  volatile uint16_t RESERVED1;                    
  volatile uint16_t EP2R;                  
  volatile uint16_t RESERVED2;                    
  volatile uint16_t EP3R;                   
  volatile uint16_t RESERVED3;                    
  volatile uint16_t EP4R;                  
  volatile uint16_t RESERVED4;                    
  volatile uint16_t EP5R;                  
  volatile uint16_t RESERVED5;                    
  volatile uint16_t EP6R;                  
  volatile uint16_t RESERVED6;                    
  volatile uint16_t EP7R;                  
  volatile uint16_t RESERVED7[17];              
  volatile uint16_t CNTR;                  
  volatile uint16_t RESERVED8;                    
  volatile uint16_t ISTR;                  
  volatile uint16_t RESERVED9;                    
  volatile uint16_t FNR;                   
  volatile uint16_t RESERVEDA;                    
  volatile uint16_t DADDR;                 
  volatile uint16_t RESERVEDB;                    
  volatile uint16_t BTABLE;                
  volatile uint16_t RESERVEDC;                    
} USB_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CFR;   
  volatile uint32_t SR;    
} WWDG_TypeDef;



 
  


 













 




#line 778 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



#line 797 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
























 






 
  


   

#line 898 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"




 



 
  
  

 
    
 
 
 

 
 
 
 
 

 




 




 




 
 
 
 
 

 
#line 959 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 966 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 976 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 986 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"






 
#line 1005 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 

 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 






 
#line 1237 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 1245 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 1262 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 

 
#line 1300 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


 
 










 










 
#line 1333 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 1343 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 1351 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 1365 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 



















 
#line 1400 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"




#line 1450 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 1458 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







  
#line 1475 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 1528 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


 
#line 1549 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1563 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"






#line 1581 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 
#line 1600 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1611 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 1624 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1647 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"








 
#line 1668 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1679 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


 
#line 1700 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1714 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"






#line 1732 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 
#line 1751 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1762 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 1775 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 1798 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"








 
#line 1816 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 





#line 1835 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

   
#line 1864 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


 
 
 
 
 
 

 








































































































 








































































































 
#line 2132 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2182 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2232 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 2281 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2331 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2384 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 

 
#line 2395 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2443 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 2450 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2465 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 
#line 2483 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 2498 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 2513 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 2531 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 2546 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"











 
#line 2565 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 2584 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2592 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 2603 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


 
#line 2618 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2639 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2660 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

   
#line 2681 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2702 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2716 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2737 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2758 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

   
#line 2779 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2800 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2814 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2835 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2856 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

   
#line 2877 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2898 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2912 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2933 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2954 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

   
#line 2975 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 2996 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 






 
 
 
 
 

 
#line 3068 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3090 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
 
 
#line 3149 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3170 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3229 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3250 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3309 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3330 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3389 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3410 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3469 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3490 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 

 
#line 3582 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3668 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3694 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"























 




 




 




 
 
 
 
 



 


 
#line 3759 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 



 
#line 3773 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3798 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3805 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3813 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3820 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 



 
#line 3844 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3851 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 3862 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3875 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3883 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3890 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3897 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3904 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3911 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3918 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3925 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3932 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 3940 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3947 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3954 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3961 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3968 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3975 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3982 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3989 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 3996 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4003 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 




 




 




 




 
#line 4043 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4052 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4061 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4070 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4078 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4088 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4097 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4106 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4115 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4124 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4133 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4143 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4152 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4161 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4170 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4179 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4188 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4198 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4207 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4216 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4225 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 




 




 




 




 
#line 4259 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
 
 
 
 
 

 
#line 4275 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4282 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 4296 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4309 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4316 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 4330 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"






 
#line 4343 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 




 




 




 




 
#line 4381 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4389 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4397 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 






 
 
 
 
 
 
#line 4431 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















 
#line 4458 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4465 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4490 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4498 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4505 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 4517 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 4530 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4577 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4615 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4641 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 






#line 4655 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4662 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"











#line 4679 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4686 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 







#line 4706 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 4720 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 






#line 4734 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4741 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"











#line 4758 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4765 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 







#line 4785 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 4799 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4843 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 




 




 




 




 




 




 
#line 4896 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 4921 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4931 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 4940 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
 
 
 
 

 
#line 4962 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 4982 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 




 




 




 




 




 




 
 
 
 
 

 




 
#line 5041 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
#line 5054 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 

 
#line 5072 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5081 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 
#line 5097 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5106 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 







 




 
 
 
 
 

 
#line 5139 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"













#line 5182 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5191 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5199 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5211 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5219 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5227 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5235 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 5250 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5258 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5270 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5278 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







 
#line 5295 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"











#line 5313 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5321 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5328 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5351 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5364 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5376 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5388 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5400 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5413 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5425 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5437 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5449 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5462 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5474 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5486 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5498 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 
 
 
 
 

 






 
#line 5535 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 5548 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 










#line 5586 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 




 




 




 




 




 




 
#line 5640 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5648 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 5661 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
#line 5740 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5781 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 5855 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 
 
 
 
 

 
#line 5881 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

  
#line 5913 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 

                                                                            
#line 5925 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


                                                                                
#line 5935 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
                                                                                
#line 5943 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 5964 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
                                                                           
















#line 5987 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 



                                                                          






#line 6008 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"










                                                                           






#line 6031 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 6052 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















#line 6075 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 6096 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















#line 6119 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 6140 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















#line 6163 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 6184 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















#line 6207 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 6228 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















#line 6251 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 










#line 6272 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

















#line 6295 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
#line 6337 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 6369 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 6386 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 6412 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





     




 
 




 




 




 




 




 




 




 




 

 




 




 




 




 




 




 




 




 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 




 




 




 




 




 




 




 




 

 




#line 6612 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6630 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6648 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6666 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6684 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6702 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6720 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 




#line 6738 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 

 


#line 6754 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6766 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6778 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6790 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6802 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6814 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6826 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6838 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6850 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6862 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6874 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6886 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6898 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6910 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6922 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


#line 6934 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 
 
 
 
 

 
 
#line 6975 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7004 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7054 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 7067 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 7080 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7094 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7108 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7152 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7163 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 7170 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 7177 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7206 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
#line 7224 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7235 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7249 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7263 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7280 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7291 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7305 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7319 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7336 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

   
#line 7347 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7361 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7375 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7389 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7400 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7414 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7428 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7442 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7453 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7467 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7481 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
#line 7490 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7537 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7584 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7631 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7678 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7776 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7874 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 7972 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8070 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8168 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8266 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8364 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8462 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8560 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8658 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8756 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8854 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 8952 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9050 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9148 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9246 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9344 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9442 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9540 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9638 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9736 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9834 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 9932 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10030 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10128 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10226 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10324 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10422 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 


 



 
#line 10444 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 10451 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 10482 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10502 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10528 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 




 




 




 






























#line 10586 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10597 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 

 
#line 10647 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10658 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 10674 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 



#line 10709 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 
#line 10721 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
#line 10770 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10796 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10807 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
 
 
 
 

 
#line 10850 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
#line 10863 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10907 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10930 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"











 
#line 10975 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 10988 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 
 
 
 
 

 




#line 11023 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11037 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"







#line 11083 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
 
 
 
 
 
#line 11096 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11106 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




#line 11121 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 







 
#line 11143 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11175 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 
#line 11188 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11207 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 




 

 
#line 11222 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11230 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11238 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11246 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11254 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11262 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11270 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 
#line 11278 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





 



  



 

 



                                       







     


 


 


 
#line 11327 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
  
 
#line 11336 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

 


 


 



 


 



 


 


 




 
 
#line 11376 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 11388 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11396 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11404 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11412 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11420 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11428 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11436 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11444 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11452 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11460 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11468 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11478 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11486 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



#line 11496 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 11537 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11548 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11556 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"





#line 11568 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11578 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
    
#line 11586 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"
    




#line 11597 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"

#line 11604 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"



 


                                            




 






 






 






                                     




 




 






 






 





 


 


 











  
 
 
 
 
  
 
 

 
#line 11718 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"


 
#line 11745 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xe.h"




 



 





  

  
  
  
   
#line 134 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"
#line 143 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"



 



   
typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;


typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;



 




 



















 

#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"


















 

 







 
#line 1 "../Core/Inc/stm32f1xx_hal_conf.h"
















 

 







 
 

 


 



 
 
 
 
 
 
 
 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 

#line 78 "../Core/Inc/stm32f1xx_hal_conf.h"

 




 












 






 









 









 

 


 





#line 158 "../Core/Inc/stm32f1xx_hal_conf.h"

 



 
 

 

 

 
#line 177 "../Core/Inc/stm32f1xx_hal_conf.h"

 





 

 

 

 





 




#line 211 "../Core/Inc/stm32f1xx_hal_conf.h"





 





 




 



 


 

#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

















 

 







 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"


















 

 







 
#line 1 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"



























 



 



 
    
#line 209 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"


 



 
  



 
#line 31 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"
#line 1 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"
 






 

 
 
 





 





#line 34 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"




  typedef signed int ptrdiff_t;



  



    typedef unsigned int size_t;    
#line 57 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



   



      typedef unsigned short wchar_t;  
#line 82 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



    




   




  typedef long double max_align_t;









#line 114 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



 

#line 35 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"

 



 
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;



 
typedef enum
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;

 



























 


#line 104 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"







#line 119 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"


 
#line 141 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"




 









 


#line 174 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"



 



 


#line 191 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h"







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"




 



 

 



 



 
typedef struct
{
  uint32_t PLLState;      
 

  uint32_t PLLSource;     
 

  uint32_t PLLMUL;        
 
} RCC_PLLInitTypeDef;



 
typedef struct
{
  uint32_t ClockType;             
 

  uint32_t SYSCLKSource;          
 

  uint32_t AHBCLKDivider;         
 

  uint32_t APB1CLKDivider;        
 

  uint32_t APB2CLKDivider;        
 
} RCC_ClkInitTypeDef;



 

 


 



 






 



 







 



 





 



 






 



 







 



 





 



 






 



 







 



 






 



 






 



 
#line 214 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 



 








 



 






 




 





 



 




 



 
#line 272 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"


 









 
 




 
#line 298 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

 




 



 

 



 







 
#line 330 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 338 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 346 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 354 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"








 







 

#line 380 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 







 
#line 399 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 407 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 415 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 423 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 431 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 439 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 447 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"












 







 

#line 483 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 







 
#line 502 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 510 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 518 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 526 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 534 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 542 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 550 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 558 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 566 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 573 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"







 







 

#line 608 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 




 
#line 623 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"




#line 633 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"






 




 
#line 652 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"





#line 664 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"







 



 










 









 





 



 





 






 




 



 






















 
#line 774 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 



 

















 
#line 822 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 



 






 




 































 








 




 



 








 









 




 



 

#line 939 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"











 








 



 






















 








 




 




 





 



 




 




 
















 

















 


















 



















 





 
























 






 



 

 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 



 



 

#line 56 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"






 



 






#line 87 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 109 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"










#line 158 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"





#line 169 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"


#line 186 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"










 

 



 

#line 224 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 
typedef struct
{
  uint32_t OscillatorType;       
 






  uint32_t HSEState;              
 

  uint32_t HSEPredivValue;       
 

  uint32_t LSEState;              
 

  uint32_t HSIState;              
 

  uint32_t HSICalibrationValue;   
 

  uint32_t LSIState;              
 

  RCC_PLLInitTypeDef PLL;          




} RCC_OscInitTypeDef;

#line 279 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 
typedef struct
{
  uint32_t PeriphClockSelection;      
 

  uint32_t RTCClockSelection;         
 

  uint32_t AdcClockSelection;         
 



  uint32_t I2s2ClockSelection;         
 

  uint32_t I2s3ClockSelection;         
 

#line 308 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




  uint32_t UsbClockSelection;         
 


} RCC_PeriphCLKInitTypeDef;



 

 



 



 
#line 343 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 



 







 





 







 



 







 








 





 




#line 433 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 446 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 



#line 473 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 

#line 534 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 

#line 561 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 



 
#line 580 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"


 

#line 608 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 

 


 







 

#line 636 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




#line 649 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




#line 661 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"





#line 678 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 726 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 







 

#line 766 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 







 

#line 788 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




#line 803 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 811 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 819 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 827 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"







#line 843 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




#line 856 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 864 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 872 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 880 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 888 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 896 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 904 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 913 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 952 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1018 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1030 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1060 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 







 

#line 1151 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 







 

#line 1174 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




#line 1207 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1219 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




#line 1232 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1240 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"





#line 1253 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1261 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"





#line 1286 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1316 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 







 

#line 1377 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 

#line 1403 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




 








#line 1424 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"













#line 1446 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1455 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1467 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1485 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"







#line 1501 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 




 









#line 1528 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



























#line 1562 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"

#line 1572 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 



 

#line 1593 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"







 





#line 1614 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"


 






 

#line 1667 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"




 








 







 




#line 1712 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"








 









 




 

#line 1846 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"


 

 


 



 

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);



 

#line 1888 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h"



 



 



 







 

#line 1145 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

 


 



 

 
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency);



 



 

 
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
void              HAL_RCC_DisableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency);

 
void              HAL_RCC_NMI_IRQHandler(void);

 
void              HAL_RCC_CSSCallback(void);



 



 



 



 

 

 
#line 1210 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 



 
#line 1224 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 




 






 
 


 


 


 



 
 



 



 
 



 



 



 





 

 


 


 


 








 



 


 






 

#line 1333 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"

#line 1358 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h"



 



 



 







 

#line 238 "../Core/Inc/stm32f1xx_hal_conf.h"


#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h"



 



 

 


 



 
typedef struct
{
  uint32_t Pin;       
 

  uint32_t Mode;      
 

  uint32_t Pull;      
 

  uint32_t Speed;     
 
} GPIO_InitTypeDef;



 
typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;


 

 



 



 
#line 100 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h"




 










 
#line 122 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h"













 




 






 




 





 



 

 


 






 







 







 







 







 



 

 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"



 



 
 
 



 




 



 

#line 70 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 87 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"


 



 














 



 




 





 






 






 






 






 






 






 






 






 






 






 






 






 






 






 






 






 






 







 







 







 







 







 








 






 






 











 









 








 







 



#line 365 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 384 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 402 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"





 






 






 






 








 






 









 






 







 






 






 







 


#line 512 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 531 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 550 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 567 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 584 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 600 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 617 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 634 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"







 






 



#line 668 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 685 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 702 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 719 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 736 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 753 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 772 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"

#line 799 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"



 



 



 
#line 828 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"













#line 847 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h"









 

 
 



 



 
void HAL_GPIOEx_ConfigEventout(uint32_t GPIO_PortSource, uint32_t GPIO_PinSource);
void HAL_GPIOEx_EnableEventout(void);
void HAL_GPIOEx_DisableEventout(void);



 



 



 



 







 
#line 214 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h"

 


 



 
 
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);


 



 
 
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



 



 
 
 
 


 



 

 


 
#line 281 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h"


 

 


 



 



 



 







 
#line 242 "../Core/Inc/stm32f1xx_hal_conf.h"


#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h"



 




 

 



 



 
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U
} EXTI_CallbackIDTypeDef;



 
typedef struct
{
  uint32_t Line;                     
  void (* PendingCallback)(void);    
} EXTI_HandleTypeDef;



 
typedef struct
{
  uint32_t Line;      
 
  uint32_t Mode;      
 
  uint32_t Trigger;   
 
  uint32_t GPIOSel;   

 
} EXTI_ConfigTypeDef;



 

 


 



 
#line 115 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h"



 



 





 



 






 




 
#line 158 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h"


 



 

 


 



 

 


 


 







 




 




 




 
#line 212 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h"


 

 


 














#line 261 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h"





 

 



 




 
 
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);


 




 
 
void              HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti);



 



 



 



 







 
#line 246 "../Core/Inc/stm32f1xx_hal_conf.h"


#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma.h"



 



 

 



 



 
typedef struct
{
  uint32_t Direction;                 

 

  uint32_t PeriphInc;                 
 

  uint32_t MemInc;                    
 

  uint32_t PeriphDataAlignment;       
 

  uint32_t MemDataAlignment;          
 

  uint32_t Mode;                      


 

  uint32_t Priority;                  
 
} DMA_InitTypeDef;



 
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,   
  HAL_DMA_STATE_READY             = 0x01U,   
  HAL_DMA_STATE_BUSY              = 0x02U,   
  HAL_DMA_STATE_TIMEOUT           = 0x03U    
}HAL_DMA_StateTypeDef;



 
typedef enum
{
  HAL_DMA_FULL_TRANSFER           = 0x00U,     
  HAL_DMA_HALF_TRANSFER           = 0x01U      
}HAL_DMA_LevelCompleteTypeDef;



 
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID          = 0x00U,     
  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,     
  HAL_DMA_XFER_ERROR_CB_ID         = 0x02U,      
  HAL_DMA_XFER_ABORT_CB_ID         = 0x03U,      
  HAL_DMA_XFER_ALL_CB_ID           = 0x04U       
    
}HAL_DMA_CallbackIDTypeDef;



 
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef   *Instance;                        
  
  DMA_InitTypeDef       Init;                              
  
  HAL_LockTypeDef       Lock;                               
  
  HAL_DMA_StateTypeDef  State;                            
  
  void                  *Parent;                                                         
  
  void                  (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);      
  
  void                  (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);  
  
  void                  (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);     

  void                  (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);       
  
  volatile uint32_t         ErrorCode;                                                     

  DMA_TypeDef            *DmaBaseAddress;                                              
  
  uint32_t               ChannelIndex;                                                   

} DMA_HandleTypeDef;    


 

 



 



 







 



 






 



 




 



 




 



 





 



 





 



 




 



 






 




 





 



 
#line 271 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma.h"


 



 


 


 




 






 






 



 










 











 











 






 




 

 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"



 



 

  
 
 


 
 




 





 
#line 70 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"





       
#line 89 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"





 
#line 108 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"





 
#line 127 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"
   










 














 






 

#line 257 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h"
  


 



 



 




        



 
#line 357 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma.h"

 


 



 
 
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit (DMA_HandleTypeDef *hdma);


 



 
 
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, uint32_t CompleteLevel, uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)( DMA_HandleTypeDef * _hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);



 



 
 
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t HAL_DMA_GetError(DMA_HandleTypeDef *hdma);


 



 

 


 































  

 



 



 







 
#line 250 "../Core/Inc/stm32f1xx_hal_conf.h"


















#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h"



 



  
 


 

#line 76 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h"



 

 



 



 
#line 100 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h"


 



 





 

#line 245 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h"



 


 

 


 
  


 
 
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);


 



 
 
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);








 



 

 
 
 
 


 















#line 388 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h"



 

 



  



 
  





 

 
#line 270 "../Core/Inc/stm32f1xx_hal_conf.h"


#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


















 

 







 
#line 31 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


 



  

  


 








 
typedef struct
{
  uint32_t DataAlign;                        

 
  uint32_t ScanConvMode;                     









 
  FunctionalState ContinuousConvMode;         

 
  uint32_t NbrOfConversion;                  

 
  FunctionalState  DiscontinuousConvMode;    


 
  uint32_t NbrOfDiscConversion;              

 
  uint32_t ExternalTrigConv;                 


 
}ADC_InitTypeDef;





  
typedef struct 
{
  uint32_t Channel;                





 
  uint32_t Rank;                   

 
  uint32_t SamplingTime;           







 
}ADC_ChannelConfTypeDef;





 
typedef struct
{
  uint32_t WatchdogMode;      
 
  uint32_t Channel;           

 
  FunctionalState  ITMode;    
 
  uint32_t HighThreshold;     
 
  uint32_t LowThreshold;      
 
  uint32_t WatchdogNumber;     
}ADC_AnalogWDGConfTypeDef;



  
 





 




 






 





 




 





  
typedef struct __ADC_HandleTypeDef
{
  ADC_TypeDef                   *Instance;               

  ADC_InitTypeDef               Init;                    

  DMA_HandleTypeDef             *DMA_Handle;             

  HAL_LockTypeDef               Lock;                    
  
  volatile uint32_t                 State;                   

  volatile uint32_t                 ErrorCode;               

#line 198 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"
}ADC_HandleTypeDef;


#line 222 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"



 



 



 



 











 




 




 



 
 
 
 




 



 




 



 
 
 
#line 305 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"





 



 
#line 323 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


 



 
#line 346 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


 



 
#line 360 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


 



 





 



 





 



 





 



 







 




  

 



 



 
 
 
 
#line 431 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


 



 
#line 445 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 453 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 461 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 470 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 479 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"


 

 




 


 



 
 
     









 


    




 


    








 


    








 











 













 


    










 






 
#line 598 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"



 

 



 
 
 





 









 








 









 






 







 








 








 








 








 








 







 












 







 







 







 
 
 
















    
#line 783 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"










#line 811 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 820 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 837 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

#line 845 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"











 



 



 



 



 



 
      


 
    
 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"



 



  

  


 











 
typedef struct 
{
  uint32_t InjectedChannel;                       





 
  uint32_t InjectedRank;                          

 
  uint32_t InjectedSamplingTime;                  







 
  uint32_t InjectedOffset;                        


 
  uint32_t InjectedNbrOfConversion;               



 
  FunctionalState InjectedDiscontinuousConvMode;  





 
  FunctionalState AutoInjectedConv;               






 
  uint32_t ExternalTrigInjecConv;                 






 
}ADC_InjectionConfTypeDef;






 
typedef struct
{
  uint32_t Mode;              







 

  
}ADC_MultiModeTypeDef;                                                          




 


 
   


 



 






 



 




 
    


 
 
 

 
#line 176 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"


 
#line 185 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"

 



 
 
 
 
 
 

 
 
 






 



 
 
 

 







 






 




 
 
 
 
 
 

 
 
 






 




 
#line 266 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"


 




 


 



 



 
 
 
 

 
#line 297 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"
 
 




 
#line 311 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"

 




 



 
 
 
 

 
#line 333 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"
 
 




 
#line 346 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"

 





 



 


 

 



 
 
 

    









 
#line 398 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"










 
#line 426 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"






 
#line 445 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"





 
#line 463 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"





 
#line 481 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"







 










 


       












 



 

#line 565 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"

#line 613 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"

#line 626 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h"



       
   
    

    
    
   
 


 

 


 

 
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc);

 
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

 
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc);


 
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc); 


 
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank);

uint32_t                HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);


 
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc);


 


 


 
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc,ADC_InjectionConfTypeDef* sConfigInjected);

HAL_StatusTypeDef       HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);



 




 




  



 
  







 
#line 884 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h"

 


 



 


 
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);









 

 



 


 
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);

 
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

 
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

 
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);

 
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);


 


 


 
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);


 


 


 
uint32_t                HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t                HAL_ADC_GetError(ADC_HandleTypeDef *hadc);


 




 


 


 
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc);
void              ADC_StabilizationTime(uint32_t DelayUs);
void              ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void              ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
void              ADC_DMAError(DMA_HandleTypeDef *hdma);


  




  



 








 
#line 274 "../Core/Inc/stm32f1xx_hal_conf.h"










#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash.h"
   


 



 
  


 



 



 















   

  


   



 
typedef enum 
{
  FLASH_PROC_NONE              = 0U, 
  FLASH_PROC_PAGEERASE         = 1U,
  FLASH_PROC_MASSERASE         = 2U,
  FLASH_PROC_PROGRAMHALFWORD   = 3U,
  FLASH_PROC_PROGRAMWORD       = 4U,
  FLASH_PROC_PROGRAMDOUBLEWORD = 5U
} FLASH_ProcedureTypeDef;



 
typedef struct
{
  volatile FLASH_ProcedureTypeDef ProcedureOnGoing;  
  
  volatile uint32_t               DataRemaining;     

  volatile uint32_t               Address;           

  volatile uint64_t               Data;              

  HAL_LockTypeDef             Lock;              

  volatile uint32_t               ErrorCode;        
 
} FLASH_ProcessTypeDef;



 

 


   



 








 



  






 




 






 

#line 160 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash.h"


   
  
 




 
 



 






 







 




 





  
  





  







  




 





    



  





 




 
  


  

 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"



 



  



 







   



 





















 





 
#line 88 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"

 






 





 








#line 118 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"

 






 
#line 134 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"

 







 






 
#line 157 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"



   

  


   



 
typedef struct
{
  uint32_t TypeErase;   
 
  
  uint32_t Banks;       
     
  
  uint32_t PageAddress; 

 
  
  uint32_t NbPages;     
 
                                                          
} FLASH_EraseInitTypeDef;



 
typedef struct
{
  uint32_t OptionType;  
 

  uint32_t WRPState;    
 

  uint32_t WRPPage;     
 

  uint32_t Banks;        
  
    
  uint8_t RDPLevel;     
 

#line 213 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"
  uint8_t USERConfig;   


 


  uint32_t DATAAddress; 
 
  
  uint8_t DATAData;     
 
} FLASH_OBProgramInitTypeDef;



 

 


   



  



  



        




         
        



 



  





 



 
#line 278 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"


 



 



  



 







 



  





 



 
 
#line 328 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"
        
       
 
#line 357 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"


 
#line 398 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"
         
        


 
 




 
#line 415 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"
       
 
#line 423 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"

 
#line 431 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"
      
 
#line 439 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"



 



 




 
  


  




 



  




  



  




 

#line 490 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"



 




 



 



  




 
#line 529 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"










 
  



 
#line 556 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"







   



 
  



 

 


 




  

#line 675 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"







  









  












 












 
#line 730 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h"





 



 

 


 



 
 
HAL_StatusTypeDef  HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef  HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);



 



 
 
HAL_StatusTypeDef  HAL_FLASHEx_OBErase(void);
HAL_StatusTypeDef  HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void               HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
uint32_t           HAL_FLASHEx_OBGetUserData(uint32_t DATAAdress);


 



 



 



 






 
#line 249 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash.h"

 


 
  


 
 
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

 
void       HAL_FLASH_IRQHandler(void);
  
void       HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void       HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);



 



 
 
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
void HAL_FLASH_OB_Launch(void);



 



 
 
uint32_t HAL_FLASH_GetError(void);



 



 

 


 
HAL_StatusTypeDef       FLASH_WaitForLastOperation(uint32_t Timeout);






 



 



 







 

#line 286 "../Core/Inc/stm32f1xx_hal_conf.h"










#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"



 



 

 


 




 
typedef struct
{
  uint32_t ClockSpeed;       
 

  uint32_t DutyCycle;        
 

  uint32_t OwnAddress1;      
 

  uint32_t AddressingMode;   
 

  uint32_t DualAddressMode;  
 

  uint32_t OwnAddress2;      
 

  uint32_t GeneralCallMode;  
 

  uint32_t NoStretchMode;    
 

} I2C_InitTypeDef;



 



























 
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,    
  HAL_I2C_STATE_READY             = 0x20U,    
  HAL_I2C_STATE_BUSY              = 0x24U,    
  HAL_I2C_STATE_BUSY_TX           = 0x21U,    
  HAL_I2C_STATE_BUSY_RX           = 0x22U,    
  HAL_I2C_STATE_LISTEN            = 0x28U,    
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   
 
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   
 
  HAL_I2C_STATE_ABORT             = 0x60U,    
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,    
  HAL_I2C_STATE_ERROR             = 0xE0U     

} HAL_I2C_StateTypeDef;



 


















 
typedef enum
{
  HAL_I2C_MODE_NONE               = 0x00U,    
  HAL_I2C_MODE_MASTER             = 0x10U,    
  HAL_I2C_MODE_SLAVE              = 0x20U,    
  HAL_I2C_MODE_MEM                = 0x40U     

} HAL_I2C_ModeTypeDef;



 




 
#line 176 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"


 




 
typedef struct __I2C_HandleTypeDef
{
  I2C_TypeDef                *Instance;       

  I2C_InitTypeDef            Init;            

  uint8_t                    *pBuffPtr;       

  uint16_t                   XferSize;        

  volatile uint16_t              XferCount;       

  volatile uint32_t              XferOptions;     

  volatile uint32_t              PreviousState;  
 

  DMA_HandleTypeDef          *hdmatx;         

  DMA_HandleTypeDef          *hdmarx;         

  HAL_LockTypeDef            Lock;            

  volatile HAL_I2C_StateTypeDef  State;           

  volatile HAL_I2C_ModeTypeDef   Mode;            

  volatile uint32_t              ErrorCode;       

  volatile uint32_t              Devaddress;      

  volatile uint32_t              Memaddress;      

  volatile uint32_t              MemaddSize;      

  volatile uint32_t              EventCount;      


#line 239 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"
} I2C_HandleTypeDef;

#line 269 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"


 



 
 



 



 




 



 




 



 




 



 




 



 




 



 




 



 




 



 
#line 354 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"



 




 






 





 



 

#line 397 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"


 



 

 



 




 
#line 424 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"









 











 
























 













 






 
#line 499 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"




 
#line 511 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"




 





 




 

 


 



 
 
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

 
#line 550 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"


 



 
 
 
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);

 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);


 



 
 
void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c);


 



 
 
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c);
uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);



 



 
 
 
 


 





 

 


 

#line 661 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"













 
#line 697 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h"








 



 

 


 



 



 



 








 
#line 298 "../Core/Inc/stm32f1xx_hal_conf.h"










#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pwr.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pwr.h"



 



 

 



  



 
typedef struct
{
  uint32_t PVDLevel;   
 

  uint32_t Mode;      
 
}PWR_PVDTypeDef;




 


 



  





 

 
 



  



 
#line 93 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pwr.h"
                                                          


 



 
#line 108 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pwr.h"



 




 





 



 





 



 





 



 





 



 







 



 

 


 















 







 





 





 





 





 






 






 






 






 





 






 







 





 





 



 

 


 






















 



 



 
  


 

 
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);



 



 

 
void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
 
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);

 
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

 
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);



void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);


 



 



 



 








 
#line 310 "../Core/Inc/stm32f1xx_hal_conf.h"






















#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"



 



 

 


 



 
typedef struct
{
  uint32_t Prescaler;         
 

  uint32_t CounterMode;       
 

  uint32_t Period;            

 

  uint32_t ClockDivision;     
 

  uint32_t RepetitionCounter;  






 

  uint32_t AutoReloadPreload;  
 
} TIM_Base_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCFastMode;    

 


  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 
} TIM_OC_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 

  uint32_t ICPolarity;    
 

  uint32_t ICSelection;   
 

  uint32_t ICFilter;      
 
} TIM_OnePulse_InitTypeDef;



 
typedef struct
{
  uint32_t  ICPolarity;  
 

  uint32_t ICSelection;  
 

  uint32_t ICPrescaler;  
 

  uint32_t ICFilter;     
 
} TIM_IC_InitTypeDef;



 
typedef struct
{
  uint32_t EncoderMode;   
 

  uint32_t IC1Polarity;   
 

  uint32_t IC1Selection;  
 

  uint32_t IC1Prescaler;  
 

  uint32_t IC1Filter;     
 

  uint32_t IC2Polarity;   
 

  uint32_t IC2Selection;  
 

  uint32_t IC2Prescaler;  
 

  uint32_t IC2Filter;     
 
} TIM_Encoder_InitTypeDef;



 
typedef struct
{
  uint32_t ClockSource;     
 
  uint32_t ClockPolarity;   
 
  uint32_t ClockPrescaler;  
 
  uint32_t ClockFilter;     
 
} TIM_ClockConfigTypeDef;



 
typedef struct
{
  uint32_t ClearInputState;      
 
  uint32_t ClearInputSource;     
 
  uint32_t ClearInputPolarity;   
 
  uint32_t ClearInputPrescaler;  
 
  uint32_t ClearInputFilter;     
 
} TIM_ClearInputConfigTypeDef;



 
typedef struct
{
  uint32_t  MasterOutputTrigger;   
 
  uint32_t  MasterSlaveMode;       





 
} TIM_MasterConfigTypeDef;



 
typedef struct
{
  uint32_t  SlaveMode;         
 
  uint32_t  InputTrigger;      
 
  uint32_t  TriggerPolarity;   
 
  uint32_t  TriggerPrescaler;  
 
  uint32_t  TriggerFilter;     
 

} TIM_SlaveConfigTypeDef;





 
typedef struct
{
  uint32_t OffStateRunMode;      
 
  uint32_t OffStateIDLEMode;     
 
  uint32_t LockLevel;            
 
  uint32_t DeadTime;             
 
  uint32_t BreakState;           
 
  uint32_t BreakPolarity;        
 
  uint32_t BreakFilter;          
 
  uint32_t AutomaticOutput;      
 
} TIM_BreakDeadTimeConfigTypeDef;



 
typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,     
  HAL_TIM_STATE_READY             = 0x01U,     
  HAL_TIM_STATE_BUSY              = 0x02U,     
  HAL_TIM_STATE_TIMEOUT           = 0x03U,     
  HAL_TIM_STATE_ERROR             = 0x04U      
} HAL_TIM_StateTypeDef;



 
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,     
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,     
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,     
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,     
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U      
} HAL_TIM_ActiveChannel;



 



typedef struct

{
  TIM_TypeDef                 *Instance;      
  TIM_Base_InitTypeDef        Init;           
  HAL_TIM_ActiveChannel       Channel;        
  DMA_HandleTypeDef           *hdma[7];      
 
  HAL_LockTypeDef             Lock;           
  volatile HAL_TIM_StateTypeDef   State;          

#line 355 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"
} TIM_HandleTypeDef;

#line 399 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"



 
 

 


 



 




 



 
#line 442 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 
#line 457 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 





 



 




 



 






 



 







 



 





 



 




 



 





 



 




 



 




 



 




 



 




 



 




 



 




 



 





 



 







 



 






 



 




 



 





 



 
#line 649 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 




 



 
#line 672 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 
#line 691 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 







 



 
#line 720 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 







 



 






 



 




 



 






 



 




 



 




 


 






 



 




 



 




 



 





 



 
#line 834 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 




 



 







 



 
#line 870 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 
#line 886 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 







 



 






 



 




 



 
#line 943 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 
#line 957 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


 



 






 



 
 

 


 




 
#line 1007 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"





 






 






 
#line 1037 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"






 
#line 1054 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"






 















 















 














 














 



















 



















 
















 
















 








 







 







 






 







 










 











 
#line 1266 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"








 


















 




















 

















 
















 
















 
















 




















 




















 













 












 
















 








 
 

 


 

 




 
 

 


 



#line 1519 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"


































































#line 1595 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"















































#line 1650 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"













#line 1669 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"

#line 1678 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"























#line 1719 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"

































 
 

 
#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim_ex.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim_ex.h"



 



 

 


 



 

typedef struct
{
  uint32_t IC1Polarity;         
 

  uint32_t IC1Prescaler;        
 

  uint32_t IC1Filter;           
 

  uint32_t Commutation_Delay;   
 
} TIM_HallSensor_InitTypeDef;


 
 

 


 



 


 



 
 

 


 



 
 

 


 



 
 

 


 




 
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);


 




 
 
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);


 




 
 
HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(TIM_HandleTypeDef *htim);


 



 
 

 


 
void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);


 
 



 



 








 
#line 1757 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h"

 


 




 
 
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim,  TIM_Encoder_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_IC_InitTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim, TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

 








 




 
 
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(TIM_HandleTypeDef *htim);


 



 
 

 


 
void TIM_Base_SetConfig(TIM_TypeDef *TIMx, TIM_Base_InitTypeDef *Structure);
void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter);
void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config);
void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);

void TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma);
void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState);







 
 



 



 







 
#line 334 "../Core/Inc/stm32f1xx_hal_conf.h"


#line 1 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"

















 

 







 
#line 30 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"



 



 

 


 



 
typedef struct
{
  uint32_t BaudRate;                  


 

  uint32_t WordLength;                
 

  uint32_t StopBits;                  
 

  uint32_t Parity;                    




 

  uint32_t Mode;                      
 

  uint32_t HwFlowCtl;                 
 

  uint32_t OverSampling;              

 
} UART_InitTypeDef;







































 
typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,    
 
  HAL_UART_STATE_READY             = 0x20U,    
 
  HAL_UART_STATE_BUSY              = 0x24U,    
 
  HAL_UART_STATE_BUSY_TX           = 0x21U,    
 
  HAL_UART_STATE_BUSY_RX           = 0x22U,    
 
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    

 
  HAL_UART_STATE_TIMEOUT           = 0xA0U,    
 
  HAL_UART_STATE_ERROR             = 0xE0U     
 
} HAL_UART_StateTypeDef;



 
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef                 *Instance;         

  UART_InitTypeDef              Init;              

  uint8_t                       *pTxBuffPtr;       

  uint16_t                      TxXferSize;        

  volatile uint16_t                 TxXferCount;       

  uint8_t                       *pRxBuffPtr;       

  uint16_t                      RxXferSize;        

  volatile uint16_t                 RxXferCount;       

  DMA_HandleTypeDef             *hdmatx;           

  DMA_HandleTypeDef             *hdmarx;           

  HAL_LockTypeDef               Lock;              

  volatile HAL_UART_StateTypeDef    gState;           

 

  volatile HAL_UART_StateTypeDef    RxState;          
 

  volatile uint32_t                 ErrorCode;         

#line 188 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"

} UART_HandleTypeDef;

#line 218 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"



 

 


 



 
#line 240 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"


 



 




 



 




 



 





 



 






 



 





 



 




 



 






 



 




 



 




 





 
#line 346 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"


 









 













 



 

 


 






 
#line 402 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"





 



















 























 







 
#line 467 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"






 







 







 







 

















 



















 


















 
















 



















 



















 



















 
#line 651 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"




 





 



 

 


 



 

 
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

 







 



 

 
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
 
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);



 



 
 
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);


 



 
 
HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
uint32_t              HAL_UART_GetError(UART_HandleTypeDef *huart);


 



 
 
 
 


 


 







 

 


 
#line 806 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h"





 








 






 

 


 



 



 



 







 
#line 338 "../Core/Inc/stm32f1xx_hal_conf.h"






























 
#line 384 "../Core/Inc/stm32f1xx_hal_conf.h"







 
#line 31 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"



 



 

 



 



 
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;


 
 
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;



 
 


 











 

 


 





 






 







 







 







 




#line 135 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

#line 143 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

#line 151 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"



 





 





 






 







 




#line 193 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

 



 







 




#line 218 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

#line 226 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

#line 234 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"


#line 243 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

#line 251 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

#line 259 "../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"



 



 





 

 


 


 
 
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);


 



 
 
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);


 



 



 
 
 


 


 
 


 


 
 
 


 



 







 
#line 201 "../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h"










 



 
  



 
#line 17 "..\\BSP\\mem_data.h"
#line 1 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdbool.h"
 






 





#line 25 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdbool.h"



#line 18 "..\\BSP\\mem_data.h"
  

_Bool framWrite(uint8_t *p, uint16_t addr, uint16_t len);
_Bool framRead(uint8_t *p, uint16_t addr, uint16_t len);


#line 14 "..\\BSP\\mem_data.c"
#line 15 "..\\BSP\\mem_data.c"
#line 16 "..\\BSP\\mem_data.c"

extern I2C_HandleTypeDef hi2c2;

_Bool framWrite(uint8_t *p, uint16_t addr, uint16_t len)
{
  
  HAL_I2C_Mem_Write(&hi2c2, 0xa0|((addr>>7)&0x0e), addr&0x00ff, 0x00000001U, p, len, 100);

  return 1;
}

_Bool framRead(uint8_t *p, uint16_t addr, uint16_t len)
{
  
  HAL_I2C_Mem_Read(&hi2c2, 0xa1|((addr>>7)&0x0e), addr&0x00ff, 0x00000001U, p, len, 100);
  
  return 1;
}

