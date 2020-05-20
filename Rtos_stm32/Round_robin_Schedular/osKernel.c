

//Schedular
//TCB
//Stack

#include "osKernel.h"

void osSchedulaLaunch(void);

#define SYSPRI3             (*((volatile uint32_t *) 0xE000DE20))
#define NUM_OF_THREAD   3
#define  STACKSIZE      100

#define   BUS_FREQ      16000000
uint32_t   MILLIS_PRESCALAR;

struct tcb {
	  int32_t *stackpt;
	  struct tcb *nextpt;
};

typedef struct tcb tcbType;
tcbType tcbs[NUM_OF_THREAD];
tcbType *currentPt;

int32_t TCB_STACK[NUM_OF_THREAD][STACKSIZE];

void osKernelStackInit(int i)
{
	tcbs[i].stackpt=&TCB_STACK[i][STACKSIZE-16];
	TCB_STACK[i][STACKSIZE-1]= 0x01000000;
	
}

uint8_t osKernelAddThreads(  void(*task0)(void),
	                           void(*task1)(void),
														 void(*task2)(void)
                          )
{

	__disable_irq();
	tcbs[0].nextpt=&tcbs[1];
	tcbs[1].nextpt=&tcbs[2];
	tcbs[2].nextpt=&tcbs[0];
	osKernelStackInit(0);
	TCB_STACK[0][STACKSIZE-2]=(int32_t)(task0);
	
	osKernelStackInit(1);
	TCB_STACK[1][STACKSIZE-2]=(int32_t)(task1);
	
	osKernelStackInit(2);
	TCB_STACK[2][STACKSIZE-2]=(int32_t)(task2);
	
	currentPt=&tcbs[0];
	__enable_irq();
return 1;
	
}	

void osKernelInit(void)
{
	__disable_irq();
	
	MILLIS_PRESCALAR=BUS_FREQ/1000;
}

void osKernelLaunch(uint32_t quanta)
{
	SysTick->CTRL =0;
	SysTick->VAL =0;
	
	SYSPRI3 =(SYSPRI3 &0x00FFFFFF) | 0xE0000000; //priority 7
	SysTick->LOAD =(quanta*MILLIS_PRESCALAR)-1;
	
	SysTick->CTRL =0x00000007;
	osSchedulaLaunch();
}





