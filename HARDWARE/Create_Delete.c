#include "header.h"	

#define CREATE_TASK_PRIO		10
#define CREATE_STK_SIZE 		256
OS_TCB CreateTaskTCB;
CPU_STK CREATE_TASK_STK[CREATE_STK_SIZE];
void Create_Create_task(void);

#define DELETE_TASK_PRIO		10
#define DELETE_STK_SIZE 		256
OS_TCB DeleteTaskTCB;
CPU_STK DELETE_TASK_STK[DELETE_STK_SIZE];
void Create_Delete_task(void);

void Greate_Create_Delete_Task(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	OS_CRITICAL_ENTER();
	 
	OSTaskCreate((OS_TCB 	* )&CreateTaskTCB,		
				 (CPU_CHAR	* )"Create_Create_task", 		
                 (OS_TASK_PTR )Create_Create_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )CREATE_TASK_PRIO,     
                 (CPU_STK   * )&CREATE_TASK_STK[0],	
                 (CPU_STK_SIZE)CREATE_STK_SIZE/10,	
                 (CPU_STK_SIZE)CREATE_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	

	OSTaskCreate((OS_TCB 	* )&DeleteTaskTCB,		
				 (CPU_CHAR	* )"Create_Delete_task", 		
                 (OS_TASK_PTR )Create_Delete_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )DELETE_TASK_PRIO,     
                 (CPU_STK   * )&DELETE_TASK_STK[0],	
                 (CPU_STK_SIZE)DELETE_STK_SIZE/10,	
                 (CPU_STK_SIZE)DELETE_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
			
	OS_CRITICAL_EXIT();	
}


void Create_Create_task(void)
{
		static u8 Timer=0;
		OS_ERR err;
		while(1)
		{
				Timer++;
				delay_ms(1000);
				UART_PRINTF("$MCU2--%d\r\n",Timer);

			if(Timer==15)
			{
					UART_PRINTF("Delete MCU1--%d\r\n",Timer);
					OSTaskDel(&DeleteTaskTCB,&err);
			}

			if(Timer==30)
			{
					UART_PRINTF("Delete MCU2--%d\r\n",Timer);
					OSTaskDel(&CreateTaskTCB,&err);
			}
		}
}

void Create_Delete_task(void)
{
		static u8 Timer=0;
		while(1)
		{
				Timer++;
				delay_ms(1000);
				UART_PRINTF("$MCU1--%d\r\n",Timer);
		}
}



