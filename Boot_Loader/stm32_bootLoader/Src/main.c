/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
  #include <string.h>
	#include <stdarg.h>
	
  #define BL_DEBUG_MSG_EN
	#define FLASH_SECTOR_2_BASE_ADD   0x08008000U
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
	
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */

extern int vsprintf( char *restrict buffer, const char *restrict format,
              va_list vlist );


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
		char temp_data[]= "Hello this is testing uart\r\n";
    uint8_t BL_COMMAND_RCV_buffer[200];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
			//pc11 =rx
			//pc10 =tx,
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
					 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==RESET)
						 {
								 printmsg("BL_DEBUG_MSG:Button is Pressed...going to Bl mode\n\r");
								 //we should go continue in bootloader 
								 bootloader_uart_read_data();
						 }
					 else
							{
									printmsg("BL_DEBUG_MSG:Button is not Pressed...executing user appv\n\r");		 
								 //we should go jump to user app 
									bootloader_jump_to_user_app();
							}
		  					
  /* USER CODE END 3 */
}

uint8_t rcv_len;
void bootloader_uart_read_data(void)
	{
   uint8_t rcv_len;
		printmsg("wellcome to command line \n\r");
		
		while(1)
		{
		//read first the number of byte need to read
		HAL_UART_Receive(C_UART,(uint8_t*)&BL_COMMAND_RCV_buffer[0],1,HAL_MAX_DELAY);
		
		rcv_len= BL_COMMAND_RCV_buffer[0];
		//read rest of the bytes
		HAL_UART_Receive(C_UART,(uint8_t*)&BL_COMMAND_RCV_buffer[1],rcv_len,HAL_MAX_DELAY);
		
		switch(BL_COMMAND_RCV_buffer[1])
		{
			case BL_GET_VER:
			{

				bootloader_handle_get_ver(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_GET_HELP:
			{
				bootloader_handle_get_help(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_GET_CID:
			{
				bootloader_handle_get_cid(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_GET_RDP_STATUS:
			{
				bootloader_handle_get_rdp_status(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_GO_TO_ADDR:
			{
				bootloader_handle_go_to_addr(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_FLASH_ERASE:
			{
				bootloader_handle_flash_erase(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_MEM_WRITE:
			{
				bootloader_handle_mem_write(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_EN_R_W_PROTECT:
			{
				bootloader_handle_en_r_w_protect(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_MEM_READ:
			{
				//TODO
				bootloader_handle_mem_read(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_READ_SECTOR_STATUS:
			{
				bootloader_handle_read_sector_status(BL_COMMAND_RCV_buffer);
				break;
			}
			case BL_OTP_READ:
			{
				//TODO
				bootloader_handle_otp_read(BL_COMMAND_RCV_buffer);
				break;
				
			}
			case BL_DIS_R_W_PROTECT:
			{
				bootloader_handle_dis_r_w_protect(BL_COMMAND_RCV_buffer);
				break;
			}
			default:
			{
				printmsg("Invalid command code recived from host\n\r");
				break;
			}
		}
		
	}
			
			
	}
void bootloader_jump_to_user_app(void)
		{
    // just a function hold the address of reset handler
			
			void (*app_reset_handler)(void);
			
			printmsg("BL_DEBUG_MSG:bootLoader jump to  user appv\n\r");
			
			//configure the msp by reading from base address of sector 2
			uint32_t msp_value = *(volatile uint32_t *)FLASH_SECTOR_2_BASE_ADD;
			
			printmsg("BL_DEBUG_MSG:msb value : %x\n\r",msp_value);
			
			//set msp register
			
			__set_MSP(msp_value);
			
		//	SCB->VTOR =FLASH_SECTOR_2_BASE_ADD;
			
			uint32_t resethandler_address = *(volatile uint32_t *)(FLASH_SECTOR_2_BASE_ADD
				+4);
			
			app_reset_handler= (void*)resethandler_address;
			
			printmsg("BL_DEBUG_MSG:resethandler_address : %x\n\r",resethandler_address);
			
			// jump the reset handler of the applications
			
			app_reset_handler();
			
		}
/* print formated string to the consol uart */
 void printmsg( char *format, ...)
{
	
		#ifdef BL_DEBUG_MSG_EN
		  char str[80];
		  //Extract the Va argument list using VA apis 
		  va_list args;
		  va_start(args,format);
			vsprintf(str,format,args);
			HAL_UART_Transmit(D_UART,(uint8_t*)str,strlen(str),HAL_MAX_DELAY);
		  va_end(args);
		#endif
	
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
