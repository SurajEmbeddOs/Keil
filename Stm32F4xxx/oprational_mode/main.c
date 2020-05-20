
#include "stm32f4xx.h"


//We have to impleted the watchdog handler
void WWDG_IRQHandler(void)
{
	uint32_t value=__get_CONTROL();
	 value &=0x1;
	__set_CONTROL(value);
}
void gebnerate_interrupt(void)
{
	//lets simulate the watch dog interrupt
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
}

void call_applictios_task(void)
{
	/* move to privilage acess level */
	
	gebnerate_interrupt();
}

void Rtos_Init(void)
{
	/* does of Low level init */
uint32_t value=__get_CONTROL();
	
	 value |=0x1;
	__set_CONTROL(value);
	
	/* before calling application task,change the acess level
	to unprivilage*/
	call_applictios_task();
}

int main(void)
{
//	Rtos_Init();
	
	void (*JumpAddr) (void) = (void*)(0x08000380+1);//&gebnerate_interrupt;
	JumpAddr();
	
	while(1);
	return 0;
}


