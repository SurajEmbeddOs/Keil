

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include <string.h>

static void  gpio_and_button_init(void);
static void  usart2_init(void);
static void  Dma1_init(void);

USART_HandleTypeDef huart2;
DMA_HandleTypeDef   hdma1;

int main()
{
	HAL_Init();
	gpio_and_button_init();
	
	while(1)
	{
		
	}
	

	
}

static void  gpio_and_button_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	//led configurations
	GPIO_InitTypeDef gpio;
	
	memset(&gpio,0,sizeof(gpio));
	
	gpio.Pin =GPIO_PIN_5;
	gpio.Mode =GPIO_MODE_OUTPUT_PP;
	gpio.Pull =GPIO_NOPULL;
	gpio.Speed =GPIO_SPEED_MEDIUM;
	
	 HAL_GPIO_Init(GPIOA,&gpio);
	
	gpio.Pin =GPIO_PIN_13;
	gpio.Mode =GPIO_MODE_IT_FALLING;
	gpio.Pull =GPIO_NOPULL;
	gpio.Speed =GPIO_SPEED_MEDIUM;
	
	 HAL_GPIO_Init(GPIOA,&gpio);
	
	 NVIC_EnableIRQ(EXTI15_10_IRQn);
	 
		
}
static void  usart2_init(void)
{
	
}
static void  Dma1_init(void)
{
	
}

 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	

}

