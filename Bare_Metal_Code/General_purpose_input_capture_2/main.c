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
  
		//Wait until capture
		  while(!(TIM3->SR & 0x2)){}
			current_value=TIM3->CCR1;
			period=current_value-last_value;
			last_value=current_value;
			frequency=1000.0f/period;
			
			
			
	}
	
}


void Mx_Gpio_Init()
{
	RCC->AHB1ENR |=(1<<0);
	GPIOA->MODER |=(0x2<<(5*2));
	GPIOA->AFR[0] =	(0x1<<(5*4));
	
	RCC->AHB1ENR |=  (1<<0);
	GPIOA->MODER |= (0x2<<(6*2));
	GPIOA->AFR[0] |=	(0x2<<(6*4));
	
}

void TIM2_Conf()
{
	RCC->APB1ENR |=(1<<0);
	TIM2->PSC     =1600-1; //16000000 divide 1600 give 100000hz
	TIM2->ARR			=100-1; // 10000 divide 10000 give 1hz
	TIM2->CCMR1  |=(0x3<<4);
	TIM2->CCR1    =0;
	TIM2->CCER  |=1;
	TIM2->CNT			=0;  //CLEAR_BIT timer counter

	TIM2->CR1    |= (1<<0) ;
	
	RCC->APB1ENR |=(1<<1);
	TIM3->PSC     =16000-1; 
	TIM3->CCMR1  |=0x41;
	TIM3->CCER  = 0x0B;
	TIM3->CR1    |= (1<<0) ;
	

}



