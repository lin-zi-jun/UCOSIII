#include "header.h"	

#define A_TASK_PRIO		10
#define A_STK_SIZE 		256
OS_TCB ATaskTCB;
CPU_STK A_TASK_STK[A_STK_SIZE];
void Create_A_task(void);

#define B_TASK_PRIO		10
#define B_STK_SIZE 		256
OS_TCB BTaskTCB;
CPU_STK B_TASK_STK[B_STK_SIZE];
void Create_B_task(void);

void Greate_Suspend_Task(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	OS_CRITICAL_ENTER();
	 
	OSTaskCreate((OS_TCB 	* )&ATaskTCB,		
				 (CPU_CHAR	* )"Create_A_task", 		
                 (OS_TASK_PTR )Create_A_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )A_TASK_PRIO,     
                 (CPU_STK   * )&A_TASK_STK[0],	
                 (CPU_STK_SIZE)A_STK_SIZE/10,	
                 (CPU_STK_SIZE)A_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	

	OSTaskCreate((OS_TCB 	* )&BTaskTCB,		
				 (CPU_CHAR	* )"Create_B_task", 		
                 (OS_TASK_PTR )Create_B_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )B_TASK_PRIO,     
                 (CPU_STK   * )&B_TASK_STK[0],	
                 (CPU_STK_SIZE)B_STK_SIZE/10,	
                 (CPU_STK_SIZE)B_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
			
	OS_CRITICAL_EXIT();	
}


void Create_A_task(void)
{
		static u8 Timer=0;
		OS_ERR err;
		while(1)
		{
				Timer++;
				delay_ms(5000);
				UART_PRINTF("$MCU2--%d\r\n",Timer);

			if(Timer%2==0)
			{
					UART_PRINTF("A:Suspend->B--%d\r\n",Timer);
					 OSTaskSuspend (&BTaskTCB,&err);
					
			}else
			{
					UART_PRINTF("A:Resume->B--%d\r\n",Timer);
					OSTaskResume (&BTaskTCB,&err);
			}
		}
}

void Create_B_task(void)
{
		static u8 Timer=0;
		while(1)
		{
				Timer++;
				delay_ms(1000);
				UART_PRINTF("$B--%d\t",Timer);
		}
}



