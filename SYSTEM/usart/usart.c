#include "sys.h"
#include "usart.h"	  
#include "includes.h"				 

	
void USART1_INIT(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;   

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
		USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}
// 主串口的硬件管脚配置，串口配置以及初始化

void USART1_IRQHandler(void){
    if(((USART1->SR)&(USART_FLAG_RXNE)) != 0)    
    {

    }
}
// 主串口的中断处理程序



void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data) {  
    USART_SendData(USARTx, Data);  
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}  
} 
//发送一个字节 

void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str)  {    
    while (0 != *str)    
    {    
        UART_PutChar(USARTx, *str);    
        str++;    
    }    
}
//发送一串字符

char UART_BUF[512]={0};
void UART_PRINTF(char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char *)UART_BUF,fmt,ap);  
		UART_PutStr (USART1,(u8 *)UART_BUF);
    va_end(ap);
}


//参数化发送

