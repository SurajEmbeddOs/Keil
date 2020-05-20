
#include "stm32f4xx.h"

extern void __set_FAULTMASK(uint32_t faultMask);
//We have to impleted the watchdog handler
void WWDG_IRQHandler(void)
{
	for(uint32_t i=0;i<50000;i++);
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

void generate_NMI_interrupt()
{
	SCB_Type *pSCB;
	pSCB =SCB;
	pSCB->ICSR |=SCB_ICSR_NMIPENDSET_Msk;
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
	/* let the program the premask registers 0th bit to 1 */
	
	//__set_PRIMASK(1);
	__set_FAULTMASK(1);
	//void (*JumpAddr)(void) =(void*) 0X00000002;
	//JumpAddr();
	
	generate_NMI_interrupt();
	gebnerate_interrupt();
	while(1);
	return 0;
}









