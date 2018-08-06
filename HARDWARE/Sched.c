#include "header.h"	

#define SA_TASK_PRIO		10
#define SA_STK_SIZE 		256
OS_TCB SATaskTCB;
CPU_STK SA_TASK_STK[SA_STK_SIZE];
void Create_SA_task(void);

#define SB_TASK_PRIO		10
#define SB_STK_SIZE 		256
OS_TCB SBTaskTCB;
CPU_STK SB_TASK_STK[SB_STK_SIZE];
void Create_SB_task(void);

void Greate_Sched_Task(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	OS_CRITICAL_ENTER();
	 
	OSTaskCreate((OS_TCB 	* )&SATaskTCB,		
				 (CPU_CHAR	* )"Create_SA_task", 		
                 (OS_TASK_PTR )Create_SA_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )SA_TASK_PRIO,     
                 (CPU_STK   * )&SA_TASK_STK[0],	
                 (CPU_STK_SIZE)SA_STK_SIZE/10,	
                 (CPU_STK_SIZE)SA_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )10,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	

	OSTaskCreate((OS_TCB 	* )&SBTaskTCB,		
				 (CPU_CHAR	* )"Create_SB_task", 		
                 (OS_TASK_PTR )Create_SB_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )SB_TASK_PRIO,     
                 (CPU_STK   * )&SB_TASK_STK[0],	
                 (CPU_STK_SIZE)SB_STK_SIZE/10,	
                 (CPU_STK_SIZE)SB_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )10,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
			
	OS_CRITICAL_EXIT();	
}


void Create_SA_task(void)
{
		u8 i=0;
		while(1)
		{
				for(i=0;i<5;i++)
				UART_PRINTF("A:01234\r\n");
		}
}

void Create_SB_task(void)
{
		u8 i=0;
		while(1)
		{
				for(i=0;i<5;i++)
				UART_PRINTF("B:56789\r\n");
		}
}



