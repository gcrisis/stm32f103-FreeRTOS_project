#include "stm32f10x.h"
#include "Usart.h"

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#define GETCHAR_PROTOTYPE int __io_getchar(FILE *f)
#else
	#define	PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define	GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif
//private var

/***********start1**��׼��ʹ��printf��Ҫ��֧�ֺ���****************/
/***********����Ҳ������������ѡ��use MicroLIBʵ��ͬ���Ĺ���****************/	
#pragma import(__use_no_semihosting)
_sys_exit(int x)
{
	x = x;
}
	
struct __FILE
{
	int handle;
};
FILE __stdout;

/*****************end1**************************/


void Init_Usart1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����һ��GPIO�ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);	
															//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 				//���ô��ڽ��ն˿ڹҽӵ�9�˿�
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		//���ù��������©
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//���ö˿��ٶ�Ϊ50M
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOA�Ĵ���	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������(��λ״̬);	   				
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOA�Ĵ���	
}
void Usart1_Configuration(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;							    	//����һ�����ڽṹ��

	USART_InitStructure.USART_BaudRate            =BaudRate ;	  			//������115200
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 	//���������ʹ��8λ����
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;	 	//��֡��β����1λֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No ;	 	//��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ����ʧ��
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //���պͷ���ģʽ
	USART_Init(USART1, &USART_InitStructure);								//���ݲ�����ʼ�����ڼĴ���
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);							//ʹ�ܴ����жϽ���
	USART_Cmd(USART1, ENABLE);   											 //ʹ�ܴ�������
	USART_ClearFlag(USART1,USART_FLAG_TC);  								//���TC��־��ԭ��TCĬ��Ϊ�ߣ����¸տ�ʼ�������ݻᶪʧ��ǰ������ݡ�			

}

PUTCHAR_PROTOTYPE
{
	 USART_SendData(USART2,(uint8_t) ch);
     while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	 return ch;	 
}
GETCHAR_PROTOTYPE
{
	while(!(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)));
	return USART_ReceiveData(USART2);
}
/*************************************

   printf2 use usart2 to send messages
   
   
 *********************************  */
void Init_Usart2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����һ��GPIO�ṹ�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	
															//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 				//���ô��ڽ��ն˿ڹҽӵ�9�˿�
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		//���ù��������©
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//���ö˿��ٶ�Ϊ50M
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOA�Ĵ���	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������(��λ״̬);	   				
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOA�Ĵ���	
}
void Usart2_Configuration(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;							    	//����һ�����ڽṹ��

	USART_InitStructure.USART_BaudRate            =BaudRate ;	  			//������115200
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 	//���������ʹ��8λ����
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;	 	//��֡��β����1λֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No ;	 	//��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ����ʧ��
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //���պͷ���ģʽ
	USART_Init(USART2, &USART_InitStructure);								//���ݲ�����ʼ�����ڼĴ���

	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);							//ʹ�ܴ����жϽ���
	USART_Cmd(USART2, ENABLE);     											//ʹ�ܴ�������
	USART_GetFlagStatus(USART2,USART_FLAG_TC); 
}
void printf2(char * fmt,...)
{
	char buffer[100];
	u16 i=0;
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	vsnprintf(buffer,100,fmt,arg_ptr);
		
	while(i<99&&buffer[i])
	{
		
		USART_SendData(USART1,(uint8_t) buffer[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		i++;
	}
	va_end(arg_ptr);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
