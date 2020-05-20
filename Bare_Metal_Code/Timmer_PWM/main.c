#include"stm32f4xx.h"

void Mx_Gpio_Init();
void TIM2_Conf();

uint32_t period=0;
float	frequency=0;
uint32_t last_value=0;
uint32_t current_value=0;

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
	GPIOA->MODER |=(0x2<<(5*2));
	GPIOA->AFR[0] =	(0x1<<(5*4));
	

}

void TIM2_Conf()
{
	RCC->APB1ENR |=(1<<0);
	TIM2->PSC     =10-1; //16,000,000 divide 10 give 16,00,000hz
	TIM2->ARR			=266670-1; // 16,00,000 divide 26667 give 1hz
	TIM2->CCMR1  |=(0x6<<4);
	TIM2->CCR1    =266680/3-1;
	TIM2->CCER  |=1;
	TIM2->CNT			=0;  //CLEAR_BIT timer counter

	TIM2->CR1    |= (1<<0) ;
	


}



