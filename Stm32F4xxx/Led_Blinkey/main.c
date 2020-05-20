
#include "Board_LED.h"


void delay()
{
	for(uint32_t i=0;i<50000;i++);
}

int main(void)
{
	
	LED_Initialize();
	while(1)
	{
		LED_On(0);
		delay();
		LED_Off(0);
		delay();
		
	}
	return 0;
}


