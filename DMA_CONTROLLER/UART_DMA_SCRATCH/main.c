#include "stm32f4xx.h"                  // Device header
#include <string.h>




static void Gpio_Init(void);
static void Uart_Init(void);
static void Dma_Init(void);
void Enable_Stream(void);
void Enamble_DMA1_Interrupt(void);

void print_msg(const char * p);

void half_transfer_compt_callback(void);
void full_transfer_compt_callback(void);
void transfer_error_callback(void);
void direct_mode_error_callback(void);




const char send_data[] =" I am embedded software enginner \r\n";
const char send_data1[] =" hello i m suraj dev pandit\r\n";
extern uint8_t is_button_press;
int main()
{
	
	Gpio_Init();
	Uart_Init();
	Dma_Init();
	
	print_msg(send_data1);
	while(1)
	{
		
	}
	
}


void print_msg(const char * p)
{
	 USART_TypeDef *pUART2;
	 pUART2=USART2;
	for(uint8_t i=0;i<strlen(p);i++)
	{
		
		while(!(pUART2->SR & (1<<7))){}
			pUART2->DR=p[i];
	}
}
//Private Function definitions start here
static void Gpio_Init(void)
{
	//Button Is connected at PC13
	RCC_TypeDef *pRCC;
	pRCC=RCC;
	
	GPIO_TypeDef *pGPIOC;
	pGPIOC=GPIOC;
	
	SYSCFG_TypeDef  *pSYSCFG;
	pSYSCFG=SYSCFG;
	
	EXTI_TypeDef *pEXTI;
	pEXTI =EXTI;
	
	

	
	//1.ENABLE port C pheripheral clock
	pRCC->AHB1ENR=(1<<3);
	
	//2.configure as Input mode
	/*default mode is input */
	 pGPIOC->MODER  &=~(0x3<<(2*13));
	
	 pGPIOC->PUPDR  &=~(0x3<<(2*13)); 
	 
	 //Enable   SYSCFG  clock
   pRCC->APB2ENR |= (1<<14);	
	 pSYSCFG->EXTICR[3] |=(0x2<<4);
	 
	 //Configure EXTI LIne 
	 pEXTI->FTSR &=~(1<<13);//configure as falling edge
	 pEXTI->FTSR |=(1<<13);
	 
	 pEXTI->IMR |=(1<<13); //enable Exti line
	 
	 //Enable Nvic Engine
	 NVIC_EnableIRQ(EXTI15_10_IRQn);
	 NVIC_SetPendingIRQ(EXTI15_10_IRQn);
}
static void Uart_Init(void)
{
	// PA3 UART_Rx ,PA2 UART_Tx
	RCC_TypeDef *pRCC;
	pRCC=RCC;
	
	GPIO_TypeDef *pGPIOA;
	pGPIOA=GPIOA;
	
	
	 USART_TypeDef *pUART2;
	 pUART2=USART2;
	
	
	
   //PA3 as A rx
	
	// ENABLE port A clock
	 pRCC->AHB1ENR |=(1<<0);
	
	 pGPIOA->MODER |=(0x2<<(3*2));
	
	 pGPIOA->PUPDR  &=~(0x3<<(2*3)); 
	 pGPIOA->PUPDR  |=(1<<(2*3)); 
	
	 pGPIOA->AFR[0] |= (0x7<<(4*3));
	
	//PA2 as A rx
	 pGPIOA->MODER |=(0x2<<(2*2));
	
	 pGPIOA->PUPDR  &=~(0x3<<(2*2)); 
	 pGPIOA->PUPDR  |=(1<<(2*2)); 
	
	 pGPIOA->AFR[0] |= (0x7<<(4*2));
	 
	 //configure Uart parameter
	 
	 //Enable USART2 Pheripheral Clock
	 pRCC->APB1ENR |=(1<<17);
	 
	 //Configure Baud_rate  115200bps
	 pUART2->BRR |= 0X8B;
	 
	 // no of stop bit ,parity, data width
	 /*bydefault it is configured */
	 //transmit enable
	 pUART2->CR1 |=(1<<3);
	 
	 //uart enable
   pUART2->CR1 |=(1<<13); 
    	
	
}

static void Dma_Init(void)
{
	 USART_TypeDef *pUART2;
	 pUART2=USART2;
	
	RCC_TypeDef *pRCC;
	pRCC=RCC;
	

	
	DMA_Stream_TypeDef  *pDMA_Stream6;
	pDMA_Stream6=DMA1_Stream6;
	//1.enable the pheriphel clock for dma1
	  pRCC->AHB1ENR |=(1<<21);
	
	//2. identify the stream which is suitale for pheripheral
	//channel 4 stream 6
	
	
	//3. identify the channel numbber on which uart2 pheriphral  send dma request
	//channel 4
	
	pDMA_Stream6->CR |=(4<<25);
	//4.programm the source address
	  pDMA_Stream6->M0AR =(uint32_t)send_data;
	
	//5.programm the destinations address
	pDMA_Stream6->PAR = (uint32_t)&pUART2->DR;
	
	//6. program number of data item sends
   uint32_t  len =sizeof(send_data);
	 pDMA_Stream6->NDTR =len;
	
	
	//7. durecction of data M2M,M2P,P2M
	//M2P
	pDMA_Stream6->CR |=(1<<6);
	
	//8.program the source and destination data width
	
	// progrma memory or pheripheral increment mode
	pDMA_Stream6->CR |=(1<<10);
	
	//9.direct mode or fifo mode
		pDMA_Stream6->FCR |=(1<<2);
	
	
	//10.select the fifo theresold
	pDMA_Stream6->FCR &=~(3<<0);
	pDMA_Stream6->FCR |=(3<<0);
	
	
	//11.enable the circular or normal mode \
	
	//12.single transfer or burst transfer
	
	//13.condigure the  stream priority
	Enamble_DMA1_Interrupt();
	  Enable_Stream();
}


void Enable_Stream(void)
{
	DMA_Stream_TypeDef  *pDMA_Stream6;
	pDMA_Stream6=DMA1_Stream6;
	//Enable the stream
	pDMA_Stream6->CR |=(1<<0);
}
void Enamble_DMA1_Interrupt(void)
{
	DMA_Stream_TypeDef  *pDMA_Stream6;
	pDMA_Stream6=DMA1_Stream6;
	
	//direct mode error interrupt
	pDMA_Stream6->CR |=(1<<1);
	
	// Transfer error interrupt enable
	pDMA_Stream6->CR |=(1<<2);
	
	//Half transfer interrupt enable
	pDMA_Stream6->CR |=(1<<3);
	
	// Transfer complete interrupt enable
	pDMA_Stream6->CR |=(1<<4);
	
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	
}

void half_transfer_compt_callback(void)
{
	
}

void full_transfer_compt_callback(void)
{
	   DMA_Stream_TypeDef  *pDMA_Stream6;
	   pDMA_Stream6=DMA1_Stream6;
	
	USART_TypeDef *pUART2;
	pUART2=USART2;
	
	//first stop request
		pUART2->CR3 &=~(1<<7);
	//again enable stream 
	Enable_Stream();
	//reload NDTR register
	 uint32_t  len =sizeof(send_data);
	 pDMA_Stream6->NDTR =len;
	
}

void transfer_error_callback(void)
{
	while(1);
}

void direct_mode_error_callback(void)
{
	while(1);
}

