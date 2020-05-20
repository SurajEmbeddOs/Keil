
#include "stm32f4xx.h"
#include "stm32f446xx.h"
extern DMA_TypeDef         *pDma;

#define  IS_DIRECT_MODE_ERROR()           pDma->HISR & (1<<18)
#define  IS_TRANSFER_ERROR()              pDma->HISR & (1<<19)
#define  IS_HALFTRANSFER_CPLT()           pDma->HISR & (1<<20)
#define  IS_FULLTRANSFER_CPLT()           pDma->HISR & (1<<21)

extern void full_transfer_callback();
extern void half_transfer_callback();

extern EXTI_TypeDef        *pExti;
void EXTI15_10_IRQHandler(void)
{
	USART_TypeDef       *pUsart;
	pUsart =USART2;
		/* enable DMA1 mode */
	pUsart->CR3 |=(1<<7);
	
	if(pExti->PR &(1<<13))
	{
		pExti->PR |=(1<<13);
	}
	
}

void DMA1_Stream6_IRQHandler(void)
{
	
	if(IS_HALFTRANSFER_CPLT())
	{
		 pDma->HIFCR |=(1<<20);
		half_transfer_callback();
	}
	else if(IS_FULLTRANSFER_CPLT())
	{
		 pDma->HIFCR |=(1<<21);
		full_transfer_callback();
	}
	else if(IS_TRANSFER_ERROR())
	{
		 pDma->HIFCR |=(1<<19);
		while(1);
	}
	else if(IS_DIRECT_MODE_ERROR())
	{
		 pDma->HIFCR |=(1<<18);
		while(1);
	}
	
}