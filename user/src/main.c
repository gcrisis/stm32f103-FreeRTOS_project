/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "Usart.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
	long xColumn;
	signed char *pcMessage;
} logmsg_t;
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
QueueHandle_t xlogQueue;
/* Private functions ---------------------------------------------------------*/
void LED_Init(void)		   
{	
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;			 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Delay(vu32 nCount)	 
{
    for(; nCount != 0; nCount--);
}

void Delay_Ms(u16 time)  //延时函数
{ 
	u16 i,j;
	for(i=0;i<(time);i++)
  		for(j=0;j<10260;j++);
}

void Delay_Us(u16 time)  //延时函数
{ 
	u16 i,j;
	for(i=0;i<(time);i++)
  		for(j=0;j<9;j++);
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
static void LED1Task( void *pvParameters )
{
		logmsg_t a;
		while(1)
		{
			vTaskDelay(1000);
			GPIO_ResetBits(GPIOG, GPIO_Pin_14);
				a.pcMessage = "led1\r\n";
		xQueueSend( xlogQueue, &a, portMAX_DELAY );
			//printf("led 1\r\n");
			vTaskDelay(1000);
			GPIO_SetBits(GPIOG, GPIO_Pin_14);
		}
		
}
static void LED2Task( void *pvParameters )
{
	logmsg_t a;
		while(1)
		{
		vTaskDelay(2000);
		
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
			a.pcMessage = "led2\r\n";
		xQueueSend( xlogQueue, &a, portMAX_DELAY );
		vTaskDelay(2000);
		
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		}
}

static void LOGTASK( void *pvParameters )
{
	logmsg_t a;
			for( ;; )
	{
		/* Wait for a message to arrive that requires displaying. */
		while( xQueueReceive( xlogQueue, &a, portMAX_DELAY ) != pdPASS );

		/* Display the message.  Print each message to a different position. */
		printf( ( char const * ) a.pcMessage );
	}
}
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */    
	SystemInit();			 //系统时钟配置system_stm32f10x.c中
	LED_Init();
	Init_Usart2();
  Usart2_Configuration(115200);

  /* Add your application code here
     */
		 
//	printf("led 1\r\n");
  /* Infinite loop */
	  xlogQueue=xQueueCreate( 3, sizeof( logmsg_t ) );
	
	xTaskCreate( LED1Task, "led1", 128, NULL, 3, NULL );
	xTaskCreate( LED2Task, "led2", 128, NULL, 2, NULL );
	xTaskCreate( LOGTASK , "log" , 128, NULL, 1, NULL );
	vTaskStartScheduler();
  while (0)
  {
		Delay(0xDffff);
		GPIO_ResetBits(GPIOG, GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		printf("led 1\r\n");
		Delay(0xDffff);
		GPIO_SetBits(GPIOG, GPIO_Pin_14);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		//printf("led 2\r\n");
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
