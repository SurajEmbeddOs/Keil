#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

#define  LED1   GPIO_PIN_5
#define  LED2   GPIO_PIN_6
#define  LED3   GPIO_PIN_7
#define  LED4   GPIO_PIN_8

uint32_t count1,count2,count3,count4;
void vLED1_Controller(void *ptr);
void vLED2_Controller(void *ptr);
void vLED3_Controller(void *ptr);
void vLED4_Controller(void *ptr);

void Gpio_Init(void);
int main(void)
{
	
	Gpio_Init();
	xTaskCreate(vLED1_Controller,
	             "led1 controller",
	            100,0,
               1,
               0	
              );
	xTaskCreate(vLED2_Controller, 
							"led2 controller",
	            100,0,
               1,
               0	
              );
	xTaskCreate(vLED3_Controller,
							"led3 controller",
	            100,0,
               1,
               0	
              );
	xTaskCreate(vLED4_Controller,
							"led4 controller",
	            100,0,
               1,
               0	
              );	
vTaskStartScheduler();
while(1);

}


void vLED1_Controller(void *ptr)
{
	
	while(1){
		GPIOA->ODR ^= GPIO_PIN_5;
	for(int i=0;i<700000;i++){}
		count4++;
	}
}

void vLED2_Controller(void *ptr)
{
	
	while(1){
		GPIOA->ODR ^= GPIO_PIN_6;
	for(int i=0;i<700000;i++){}
		count3++;
	}
}

void vLED3_Controller(void *ptr)
{
	
	while(1){
		GPIOA->ODR ^= GPIO_PIN_7;
	for(int i=0;i<700000;i++){}
		count2++;
	}
}

void vLED4_Controller(void *ptr)
{
	
	while(1){
		GPIOA->ODR ^= GPIO_PIN_8;
	for(int i=0;i<700000;i++){}
		count1++;
	}
}

void Gpio_Init(void)
{
	/* enable pheripheral clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef Gpio_InitStructure;
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8,GPIO_PIN_RESET);
	
	Gpio_InitStructure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
	Gpio_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	Gpio_InitStructure.Pull=GPIO_NOPULL;
	Gpio_InitStructure.Speed=GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(GPIOA,&Gpio_InitStructure);
	
}



