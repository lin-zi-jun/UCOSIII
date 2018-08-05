#include "header.h"	

#define HEAT_TASK_PRIO		10
#define HEAT_STK_SIZE 		256
OS_TCB HeatTaskTCB;
CPU_STK HEAT_TASK_STK[HEAT_STK_SIZE];
void heat_task(void);

void Great_Heat_Task(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	OS_CRITICAL_ENTER();	 
	OSTaskCreate((OS_TCB 	* )&HeatTaskTCB,		
				 (CPU_CHAR	* )"heat_task", 		
                 (OS_TASK_PTR )heat_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )HEAT_TASK_PRIO,     
                 (CPU_STK   * )&HEAT_TASK_STK[0],	
                 (CPU_STK_SIZE)HEAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)HEAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				
	OS_CRITICAL_EXIT();	

}

void heat_task(void)
{
		static u32 HeatTimer=0; 
		u8 TimerTemp=0;
		u8 TimerBuf[64]={0},TempBuf[32]={0};

		while(1)
		{
				HeatTimer++;
				TimerTemp=HeatTimer/(60*60);
				sprintf((char*)TimerBuf,"%.2d:",TimerTemp);
				TimerTemp=0;

				TimerTemp=HeatTimer/60%60;
				sprintf((char *)TempBuf,"%.2d:",TimerTemp);
				strcat((char*)TimerBuf,(char*)TempBuf);


				memset(TempBuf,0,32);
				TimerTemp=0;
				TimerTemp=HeatTimer%60;
				sprintf((char *)TempBuf,":%.2d",TimerTemp);
				strcat((char*)TimerBuf,(char*)TempBuf);
				memset(TempBuf,0,32);
				TimerTemp=0;

				delay_ms(1000);
				UART_PRINTF("$MCU--%s\r\n",TimerBuf);
		}
}

