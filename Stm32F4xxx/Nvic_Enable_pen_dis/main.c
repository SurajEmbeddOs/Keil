
#include "stm32f446xx.h"

/* Enable and pend USART3 Pheripheral */

#define  USART3_IRQ        39

void USART3_IRQHandler(void)
{
	while(1);
}
	

int main(void)
{
	
	//Enable USART3 /Usart3 IRQ no.
	NVIC_Type *pNVIC;
	pNVIC = NVIC;
	
	//enable the usart3 interrupt 
	pNVIC->ISER[1] |= (1<<(39-32));
	// pend the interrupt
	pNVIC->ISPR[1] |= (1<<(39-32));
	
	
	while(1);
	
	return 0;
}



