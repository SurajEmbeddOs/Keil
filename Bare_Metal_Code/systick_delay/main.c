
#include"stm32f4xx.h"

void Mx_Gpio_Init();
void Mx_SysTic_Config();
int get_tick(void);
void delay(int ms);
int __tick;
int main()
{
	Mx_Gpio_Init();
	Mx_SysTic_Config();
	
	while(1)
	{
		 GPIOA->ODR ^=(1<<5);
     delay(1000);
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
	SysTick->LOAD =16000-1;
	SysTick->VAL =0;
}
void SysTick_Handler()
{
	__tick++;
	
	
}
int get_tick()
{
	return __tick;
}
void delay(int ms)
{
	 int get_count= get_tick();
	 while((get_count+ms>=get_tick()));
	
}
