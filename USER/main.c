#include "header.h"	

int i=0;


#define START_TASK_PRIO		3
#define START_STK_SIZE 		128
OS_TCB StartTaskTCB;
CPU_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *p_arg);



int main(void)
{

	OS_ERR err;
	CPU_SR_ALLOC();

	OSInit(&err);	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组配置
	USART1_INIT();  
	   
	OS_CRITICAL_ENTER();	 
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		
				 (CPU_CHAR	* )"start task", 		
                 (OS_TASK_PTR )start_task, 		
                 (void		* )0,					
                 (OS_PRIO	  )START_TASK_PRIO,     
                 (CPU_STK   * )&START_TASK_STK[0],	
                 (CPU_STK_SIZE)START_STK_SIZE/10,	
                 (CPU_STK_SIZE)START_STK_SIZE,		
                 (OS_MSG_QTY  )0,				
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				
	OS_CRITICAL_EXIT();	
	OSStart(&err);   

}

//开始任务任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	


	OS_CRITICAL_ENTER();	//进入临界区

	Great_Heat_Task();


	OS_CRITICAL_EXIT();	//退出临界区
	OSTaskDel((OS_TCB*)0,&err);	//删除start_task任务自身
}

