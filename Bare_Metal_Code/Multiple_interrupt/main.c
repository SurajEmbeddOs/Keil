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
	__disable_irq();
	//gpio pa 5 led and pc13 button
	RCC->AHB1ENR |=0x7;
	RCC->APB2ENR |=(1<<14);
	
	
	GPIOA->MODER |=(0x1<<(5*2));
	

	
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




