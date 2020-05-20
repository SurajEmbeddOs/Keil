

//
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include <string.h>

void Mx_Usart_Init(void);
void Usart_write(char *ptr);
uint8_t Usart_recieved(void);

char msg[]= "hello world \n\r";
char rcvd_data[250];
uint8_t count=0;
int main()
{
	Mx_Usart_Init();
	Usart_write(msg);
	
	while(1)
	{
		rcvd_data[count++]=Usart_recieved();
		if(rcvd_data[count-1]=='\r')
		{
			rcvd_data[count++]='\n';
			rcvd_data[count++]='\r';
			Usart_write(rcvd_data);
			count=0;
		}
	}
	
}

void Mx_Usart_Init(void)
{
	//pa2=tx,pa3=rx
	RCC->AHB1ENR |=(1<<0);
	RCC->APB1ENR |=(1<<17);
	
	GPIOA->MODER |=(0x2<<(2*2));
	GPIOA->MODER |=(0x2<<(3*2));
	
	GPIOA->PUPDR |=(0x1<<(3*2));
	GPIOA->PUPDR |=(0x2<<(2*2));
	
	GPIOA->AFR[0] |=(0x7<<(3*4));
	GPIOA->AFR[0] |=(0x7<<(2*4));
	
	
	
	USART2->CR1 |=(1<<13);
	USART2->BRR	=0x8B;
	USART2->CR1 |=(0x3<<2);
	
}

void Usart_write(char *ptr)
{
	uint32_t len=strlen(ptr);
	for(uint32_t i=0;i<len;i++)
	{
	   while(!(USART2->SR & (1<<7))){}
	   USART2->DR =(ptr[i]&0xFF);
	}
}

uint8_t Usart_recieved(void)
{
	  while(!(USART2->SR & (1<<5))){}
		return (USART2->DR & 0xFF);
}
