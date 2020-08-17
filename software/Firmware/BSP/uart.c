#include "stdio.h"
#include "cmsis_os.h"
#include "main.h"

//#define debug_printf sprintf


//int debug_printf(void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)

extern UART_HandleTypeDef huart2;

int fputc(int ch,FILE *p) //?????,???printf???????
{
    uint8_t outch = ch;
    HAL_UART_Transmit(&huart2,&outch,1,10);
    return ch;
}
