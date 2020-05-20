
#include "stm32f4xx.h"                  // Device header


#define IS_HALF_TRNSFER()      DMA1->HISR & (1<<20)
#define IS_FULL_TRANSFER()     DMA1->HISR & (1<<21)
#define IS_TRANSFER_ERROR()    DMA1->HISR & (1<<19)
#define IS_DIRECT_MODE_ERROR() DMA1->HISR & (1<<18)

extern void half_transfer_compt_callback(void);
extern void full_transfer_compt_callback(void);
extern void transfer_error_callback(void);
extern void direct_mode_error_callback(void);

uint8_t is_button_press=0;


void EXTI15_10_IRQHandler(void)
{
	 USART_TypeDef *pUART2;
	 pUART2=USART2;
	is_button_press=1;
	//ENABLE USART2 TO TX
	pUART2->CR3 |=(1<<7);
	
	EXTI_TypeDef *pEXTI;
	pEXTI =EXTI;
	if(pEXTI->PR & (1<<13))
	{
		pEXTI->PR |=(1<<13);
	}
	
}

void DMA1_Stream6_IRQHandler(void)
{
	if(IS_HALF_TRNSFER())
	{
		DMA1->HIFCR |= (1<<20);
		half_transfer_compt_callback();
	}
	else if(IS_FULL_TRANSFER())
	{
		DMA1->HIFCR |= (1<<21);
		full_transfer_compt_callback();
	}
	else if(IS_TRANSFER_ERROR())
	{
		DMA1->HIFCR |= (1<<19);
		transfer_error_callback();
	}
	else if(IS_DIRECT_MODE_ERROR())
	{
		DMA1->HIFCR |= (1<<18);
		direct_mode_error_callback();
	}
	
}


