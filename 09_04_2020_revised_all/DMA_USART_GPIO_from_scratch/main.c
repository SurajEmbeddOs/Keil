

#include <stdint.h>
#include <string.h>
#include "stm32f446xx.h"

/*start include preprocessor directories */

/*start prototype of private function */
static void Cfg_gpio_init(void);
static void Cfg_usart_init(void);
static void Cfg_dma_init(void);

/* start prototype of helper functions */
void full_transfer_callback();
void half_transfer_callback();

void printmsg(char *msg);
/*start private variable initializations */
char *usr_msg=" hello this is DMA scratch demo code running \n\r";

char send_data[]=" hello this is DMA1 scratch demo code running \n\r";

GPIO_TypeDef        *pGpio;
USART_TypeDef       *pUsart;
SYSCFG_TypeDef      *pSyscfg=SYSCFG; 
RCC_TypeDef         *pRcc=RCC;
EXTI_TypeDef        *pExti=EXTI;
DMA_TypeDef         *pDma=DMA1;
DMA_Stream_TypeDef  *pDMA_Stream=DMA1_Stream6;


int main()
{
	
	Cfg_gpio_init();
	Cfg_usart_init();
	Cfg_dma_init();
	//sprintf(usr_msg,"hello this is DMA scratch demo code running \n\r");
//	printmsg(usr_msg);
	while(1);
	

}	

static void Cfg_gpio_init(void)
{
	//Button is conneccted PC13
	pGpio=GPIOC;
	/* enable pherepheral clock */
	pRcc->AHB1ENR |=(1<<2);
	
	/* configure gpio pin 13 port c as input */
	pGpio->MODER &=~(0x3<<(13*2)); 
	
	
	/* enable SYSCFG pherepheral clock */
	pRcc->APB2ENR |=(1<<14);
	/*configure SYSCFG EXTI line */
	pSyscfg->EXTICR[3] |= (0x2<<4);
	
	/*Enable Exti line as falling edge detections */
	pExti->FTSR |=(1<<13);
	/*unmasked Exti 13 line */
	pExti->IMR  |=(1<<13);
	
	NVIC_SetPriority(EXTI15_10_IRQn,0);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
}

static void Cfg_usart_init(void)
{
	pUsart=USART2;
	
	/* USART2 PA2 =TX ,PA3=RX ,Altenate functionality AF7 */
	/* Enable Pheripheral Clock */
	pRcc->APB1ENR |=(1<<17);
	pRcc->AHB1ENR |=(1<<0); /*port A clock enable */
	
	
	/* set baud rate 115200 */
	pUsart->BRR = 0x8B;
	
	/*configure GPIO pin as USART mode */
	
	pGpio=GPIOA;

	/*PA2 TX mode and PA3 Rx */
	pGpio->MODER  |=(0x2<<(2*2));
	pGpio->MODER  |=(0x2<<(3*2));
	
	/* PUll up register */
	pGpio->PUPDR  |=(1<<(2*2));
	pGpio->PUPDR  |=(1<<(2*3));
	
	/*Alternate functionality register */
	pGpio->AFR[0]  |=(0x7<<(4*2));
	pGpio->AFR[0]  |=(0x7<<(4*3));
	
	/*Enable TE and RE in CR1 bit*/
	pUsart->CR1 |=(1<<3);
	
	/*enable uart */
	pUsart->CR1  |=(1<<13);

}
static void Cfg_dma_init(void)
{
	/*channel 4 stream 6 */
	/* channel 4 */
	pRcc->AHB1ENR |=(1<<21);
	
	pDMA_Stream->CR |=(0x4<<25);
	
	// congig mem data size ,phe data size, mem inc,phe inc,,directions,
	pDMA_Stream->CR |=(1<<10); /*mem auto inc*/
	
	pDMA_Stream->CR |=(1<<6);   /* mem to pheripheral*/
	
	/* pheripheral address */
	
	pDMA_Stream->PAR |= (uint32_t)&USART2->DR;
	
	pDMA_Stream->M0AR =(uint32_t)send_data;
	
	uint32_t len =sizeof(send_data);
	pDMA_Stream->NDTR =len;
	
	pDMA_Stream->FCR |=(1<<2);
	pDMA_Stream->FCR |=(0x3<<0);
	
	/*enable interrupt*/
	pDMA_Stream->CR |=(0xf<<1);
	
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	/*Enable dma stream */
	pDMA_Stream->CR |=(1<<0);
}
void printmsg(char *msg)
{
	for(uint32_t i=0;i<strlen(msg);i++)
	{
	while(!(pUsart->SR & (1<<7))) {}
		pUsart->DR =msg[i];
	}
}


void full_transfer_callback()
{
			/* stop request  DMA1 mode */
	pUsart->CR3 &=~(1<<7);
	
	/* again enable stream request */
		pDMA_Stream->CR |=(1<<0);
	
	/*reload NDTR register */
		uint32_t len =sizeof(send_data);
  	pDMA_Stream->NDTR =len;
}
void half_transfer_callback()
{

	
}