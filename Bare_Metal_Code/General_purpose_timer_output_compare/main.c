#include"stm32f4xx.h"

void Mx_Gpio_Init();
void TIM2_Conf();

int main()
{
	Mx_Gpio_Init();
	TIM2_Conf();
	
	while(1)
	{

			
	}
	
}


void Mx_Gpio_Init()
{
	RCC->AHB1ENR |=(1<<0);
	GPIOA->MODER |=(0x2<<10);
	GPIOA->AFR[0] =	(0x1<<(5*4));
}

void TIM2_Conf()
{
	RCC->APB1ENR |=(1<<0);
	TIM2->PSC     =1600-1; //16000000 divide 1600 give 100000hz
	TIM2->ARR			=10000-1; // 10000 divide 10000 give 1hz
	TIM2->CCMR1  |=(0x3<<4);
	TIM2->CCR1  =0;
	TIM2->CCER  |=1;
	TIM2->CNT			=0;  //CLEAR_BIT timer counter

	TIM2->CR1    |= (1<<0) ;
	
	
	//NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler()
{
	//GPIOA->ODR ^=(1<<5);
}


