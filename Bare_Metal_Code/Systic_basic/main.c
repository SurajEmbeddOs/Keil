
#include"stm32f4xx.h"

void Mx_Gpio_Init();
void Mx_SysTic_Config();

int main()
{
	Mx_Gpio_Init();
	Mx_SysTic_Config();
	
	while(1)
	{
		if(SysTick->CTRL & (1<<16))
		{
			GPIOA->ODR ^=(1<<5);


		}
	}
	
}


void Mx_Gpio_Init()
{
	RCC->AHB1ENR |=(1<<0);
	GPIOA->MODER |=(1<<10);
}

void Mx_SysTic_Config()
{
	SysTick->CTRL = 0x7; //101
	SysTick->LOAD =3200000-1;
	SysTick->VAL =0;
	
}
void SysTick_Handler()
{
	
}

