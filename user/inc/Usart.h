
#ifndef _UART1_H_
#define _UART1_H_
#include<stdio.h>
#include<stdarg.h>


//º¯ÊıÉùÃ÷

void Init_Usart1(void);
void Usart1_Configuration(uint32_t BaudRate); 



void Init_Usart2(void);
void Usart2_Configuration(uint32_t BaudRate); 
void printf2(char * fmt,...);

#endif
