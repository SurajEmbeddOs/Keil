
#include"stm32f4xx.h"
#include"stm32f4xx_hal.h"
#include<string.h>

static void Mx_Gpio_Init(void);
static void Mx_Tim2_Init(void);
static void Mx_Tim3_Init(void);

TIM_HandleTypeDef htim2,htim3;


uint32_t timestamp=0;
uint32_t  first=0,last=0;
uint32_t Period=0;
float freq=0;
int main()
{
	
Mx_Gpio_Init();
Mx_Tim2_Init();
Mx_Tim3_Init();
	
HAL_TIM_OC_Start(&htim2,TIM_CHANNEL_1);
HAL_TIM_IC_Start(&htim3,TIM_CHANNEL_2);
	
	while(1)
	{
		
		  while(!(TIM3->SR & (1<<2))){}
			TIM3->SR=0;
			first=TIM3->CCR2;
			Period=first-last;
				if(last>first)
				{
					Period=0xFFFF-last+first;
				}
				last=first;
			freq=100000.0f/Period;
		   //timestamp=	__HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_2);
			
	}
	
	
}

static void Mx_Gpio_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef  GPIO_Init_type;;
	memset(&GPIO_Init_type,0,sizeof(GPIO_Init_type));
	
    GPIO_Init_type.Pin					=GPIO_PIN_5;
		GPIO_Init_type.Mode					=GPIO_MODE_AF_PP;
		GPIO_Init_type.Alternate		=GPIO_AF1_TIM2;
		GPIO_Init_type.Pull					=GPIO_NOPULL;
		GPIO_Init_type.Speed				=GPIO_SPEED_MEDIUM;
	
		HAL_GPIO_Init(GPIOA,&GPIO_Init_type);
	
		memset(&GPIO_Init_type,0,sizeof(GPIO_Init_type));
	
    GPIO_Init_type.Pin					=GPIO_PIN_7;
		GPIO_Init_type.Mode					=GPIO_MODE_AF_PP;
		GPIO_Init_type.Alternate		=GPIO_AF2_TIM3;
		GPIO_Init_type.Pull					=GPIO_NOPULL;
		GPIO_Init_type.Speed				=GPIO_SPEED_MEDIUM;
	
		HAL_GPIO_Init(GPIOA,&GPIO_Init_type);
	
}

static void Mx_Tim2_Init(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	htim2.Instance								=TIM2;
	htim2.Init.Prescaler					=1600-1; //16,000,000 /16,00=10,000
	htim2.Init.Period							=10000-1;
	htim2.Init.CounterMode				=TIM_COUNTERMODE_UP;

	
	
	
	if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    while(1);
  }
	
	
	TIM_OC_InitTypeDef ptim2;
	memset(&ptim2,0,sizeof(ptim2));
	
	ptim2.OCMode				=TIM_OCMODE_TOGGLE;
	ptim2.Pulse					=0;
	
	HAL_TIM_OC_ConfigChannel(&htim2,&ptim2,TIM_CHANNEL_1);
	
}
static void Mx_Tim3_Init(void)
{
	
		__HAL_RCC_TIM3_CLK_ENABLE();
	
	htim3.Instance								=TIM3;
	htim3.Init.Prescaler					=16000-1; //16,000,000 /16,00=10,000
	htim3.Init.Period							=0xffff;
	htim3.Init.CounterMode				=TIM_COUNTERMODE_UP;
	
	HAL_TIM_IC_Init(&htim3);
	
	TIM_IC_InitTypeDef ictime;
	memset(&ictime,0,sizeof(ictime));
	
	ictime.ICPolarity     =TIM_ICPOLARITY_RISING;
	ictime.ICSelection    =TIM_ICSELECTION_DIRECTTI;
	ictime.ICPrescaler		=TIM_ICPSC_DIV1;
	ictime.ICFilter				=0;
	
	if(HAL_TIM_IC_ConfigChannel(&htim3,&ictime,TIM_CHANNEL_2)!=HAL_OK)
	{
		
		while(1);
	}

	
}




