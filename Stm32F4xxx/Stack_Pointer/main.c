#include "stm32f446xx.h"
#include "Board_LED.h"

extern void __set_MSP(uint32_t topOfMainStack);
void delay(void)
{
	for(int i=0;i<50000;i++);
}

void WWDG_IRQHandler(void)
{
	for(int i=0;i<5000;i++);
}
void generate_interrupt(void)
{
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
	
}


int main(void)
{
	/* let Move the top of the stac to end of SRM1 */
	/* Lets program 0x2001_BFFF+1 in to msp */
	
	__set_MSP(0x2001BFFF+1);
	
	/* let change current pointer to PSP */
	uint32_t value =__get_CONTROL();
	value |= 0x2;
	
	__set_CONTROL(value);
	
	/*Let Intialisze PSP before using fisrt */
	
	__set_PSP(0x2001BFFF+1);
	
	generate_interrupt();
	
	LED_Initialize();
	LED_On(0);
	delay();
	LED_Off(0);
	delay();
	while(1);
	return 0;
}


