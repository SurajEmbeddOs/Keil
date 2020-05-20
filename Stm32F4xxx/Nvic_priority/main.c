
#include "stm32f446xx.h"

void WWDG_IRQHandler(void)
{
	NVIC_SetPendingIRQ(USART3_IRQn);
	//while(1);
	
}

void USART3_IRQHandler(void)
{
	NVIC_SetPendingIRQ(TIM2_IRQn);
	//while(1);
}

void TIM2_IRQHandler(void)
{
	//while(1);
}

int main(void)
{
	/// enable watchdog irq and usart3
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	
	// change the priority
	NVIC_SetPriority(WWDG_IRQn,5);
	NVIC_SetPriority(USART3_IRQn,4);
	NVIC_SetPriority(TIM2_IRQn,3);
	
	//pend irq
	NVIC_SetPendingIRQ(WWDG_IRQn);
	//NVIC_SetPendingIRQ(USART3_IRQn);
	
		
	
	
	while(1);
		
}