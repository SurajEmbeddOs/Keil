

#include "stm32f446xx.h"

void NMI_Handler (void)
{
	
}

 void HardFault_Handler (void)
{
	 
}

void MemManage_Handler(void)
{
	
}

void BusFault_Handler (void)
{
	
}

void UsageFault_Handler (void)
{
	
}

void 	SVC_Handler (void)
{
	
}

void DebugMon_Handler(void)
{
	
}

void PendSV_Handler(void)
{
	
}

void SysTick_Handler (void)
{
	
}
 int DvideByZero(int x,int y)
 {
	 return x/y;
 }

int main()
{
	void (*Fun_Ptr ) (void);
	Fun_Ptr = 0x00000000;

	
	// 1. Enable Exception : MemMange ,BusFault, UsageFault,SVC, Pendsv 
	
	SCB_Type *pSCB;
	pSCB=SCB;
	pSCB->SHCSR |=(1<<16)|(1<<17)|(1<<18); 
	//pSCB->CCR  |= (1<<3);
	
	//Devide by zero
	int val = DvideByZero(4,0);
	
	// Unalignment  data access
	
	uint32_t volatile *p = (uint32_t*)0x20000001;
	
	uint32_t volatile var =*p;
	var++;
	
	while(1);
	
	return 0;
}



