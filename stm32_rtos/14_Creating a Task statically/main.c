#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core



#define GREEN  GPIO_PIN_12
#define ORANGE GPIO_PIN_13
#define RED    GPIO_PIN_14
#define BLUE   GPIO_PIN_15

#define blueTask_STACK_SIZE 100
StaticTask_t xBlueLedControllerTaskBuffer;
StackType_t  xBlueLedControllerStack[blueTask_STACK_SIZE];

#define redTask_STACK_SIZE 100
StaticTask_t xRedLedControllerTaskBuffer;
StackType_t  xRedLedControllerStack[blueTask_STACK_SIZE];

#define orangeTask_STACK_SIZE 100
StaticTask_t xOrangeLedControllerTaskBuffer;
StackType_t  xOrangeLedControllerStack[blueTask_STACK_SIZE];

#define greenTask_STACK_SIZE 100
StaticTask_t xGreenLedControllerTaskBuffer;
StackType_t  xGreenLedControllerStack[blueTask_STACK_SIZE];

void vBlueLedControllerTask(void *pvParameters);
void vRedLedControllerTask(void *pvParameters);
void vOrangeLedControllerTask(void *pvParameters);
void vGreenLedControllerTask(void *pvParameters);


/**@note - add #define  configSUPPORT_STATIC_ALLOCATION 1 
* to FreeRTOSConfig.h file 
*vApplicationGetIdleTaskMemory callback function to main.c
*vApplicationGetTimerTaskMemory callback function to main.c
*/

void GPIO_Init(void);


int main()
{
	 GPIO_Init();
  xTaskCreateStatic(vBlueLedControllerTask,
										"Blue Led Controller",
										 blueTask_STACK_SIZE,
										 NULL,
										 1,
										 xBlueLedControllerStack,
	                   &xBlueLedControllerTaskBuffer
	);
	
	  xTaskCreateStatic(vRedLedControllerTask,
										"Red Led Controller",
										 redTask_STACK_SIZE,
										 NULL,
										 1,
										 xRedLedControllerStack,
	                   &xRedLedControllerTaskBuffer
	); 
	xTaskCreateStatic(vOrangeLedControllerTask,
										"Orange Led Controller",
										 orangeTask_STACK_SIZE,
										 NULL,
										 1,
										 xOrangeLedControllerStack,
	                   &xOrangeLedControllerTaskBuffer
	); 

xTaskCreateStatic(vGreenLedControllerTask,
										"Green Led Controller",
										 greenTask_STACK_SIZE,
										 NULL,
										 1,
										 xGreenLedControllerStack,
	                   &xGreenLedControllerTaskBuffer
	);
	
	vTaskStartScheduler();
	
	while(1){}
}


 void vBlueLedControllerTask(void *pvParameters)
 {
	  	int i;

	   while(1)
		 {
		HAL_GPIO_TogglePin(GPIOD,BLUE);
	  for(i=0;i<70000;i++){}
		 }
 } 
 
  void vRedLedControllerTask(void *pvParameters)
 {
	  	int i;

	   while(1)
		 {
		HAL_GPIO_TogglePin(GPIOD,RED);
	  for(i=0;i<70000;i++){}
		 }
 }  void vGreenLedControllerTask(void *pvParameters)
 {
	  	int i;

	   while(1)
		 {
		HAL_GPIO_TogglePin(GPIOD,GREEN);
	  for(i=0;i<70000;i++){}
		 }
 }  void vOrangeLedControllerTask(void *pvParameters)
 {
	  	int i;

	   while(1)
		 {
		HAL_GPIO_TogglePin(GPIOD,ORANGE);
	  for(i=0;i<70000;i++){}
		 }
 } 
 
  /* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
 
 void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
 {
	 /* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
	 
	 static StaticTask_t xIdleTaskTCB;
	 static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
	 
 /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
	 
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    /* Pass out the array that will be used as the Idle task's stack. */

	  *ppxIdleTaskStackBuffer = uxIdleTaskStack;
	 
	 
    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */ 
	 *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;


 }
 
 void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
	static StaticTask_t xTimerTaskTCB;
  static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];
	
	    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
	    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
     *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;


}
 
void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);	
}
