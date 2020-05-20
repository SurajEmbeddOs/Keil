
#include"stm32f446xx.h"
#include "Board_Buttons.h"
#include "Board_LED.h"


extern void __set_BASEPRI(uint32_t basePri);

int main(void)
{
	// led initializations
	LED_Initialize();
	
	//Button initializations
	Buttons_Initialize();
	NVIC->IP[EXTI15_10_IRQn]=0x00;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	#if 0
	
	__set_PRIMASK(1);
	#endif
	
	#if 1
	
	__set_BASEPRI(0x80);
	#endif
	
	while(1);
	return 0;
}
uint8_t temp=1;
void EXTI15_10_IRQHandler(void)
{
	if(temp){
		LED_On(0);
		temp=!temp;
	}
	else
	{
		LED_Off(0);
		temp=!temp;
	}
	   if((EXTI->PR & 0x01))
		 {
			 EXTI->PR |=0x01;
		 }
	
}