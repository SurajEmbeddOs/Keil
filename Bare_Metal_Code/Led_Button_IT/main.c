#include"stm32f4xx.h"

void Mx_Gpio_Init();


int main()
{
	Mx_Gpio_Init();

	
	while(1)
	{

	}
	
}


void Mx_Gpio_Init()
{
	//gpio pa 5 led and pc13 button
	RCC->AHB1ENR |=(1<<0);
	GPIOA->MODER |=(0x1<<(5*2));
	
__disable_irq();
	RCC->AHB1ENR |=(1<<2);
	RCC->APB2ENR |=(1<<14);
	
	SYSCFG->EXTICR[3]=(0x2<<(1*4));
	EXTI->FTSR  |=(1<<13);
	EXTI->IMR   |=(1<<13);
	

	NVIC_EnableIRQ(EXTI15_10_IRQn);
		__enable_irq();

}


void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & (1<<13))
	{
		EXTI->PR |=(1<<13);
	}
	GPIOA->ODR ^=(1<<5);
	
}




