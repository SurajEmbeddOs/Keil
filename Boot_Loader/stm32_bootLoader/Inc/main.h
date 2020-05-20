/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern CRC_HandleTypeDef hcrc;

#define BL_ACK         0xA5
#define BL_NACK        0x7F
#define BL_VERSION     0xAA

#define D_UART  &huart2
#define C_UART  &huart3

#define VERIFY_CRC_SUCCESS  0
#define VERIFY_CRC_FAIL     1

#define VALID_ADD       0
#define INVALID_ADD     1

#define VALID_STATUS       0
#define INVALID_STATUS     1


#define SRAM1_SIZE   112*1024 //112 kb
#define SRAM1_END     (SRAM1_BASE + SRAM1_SIZE)
#define SRAM2_SIZE   16*1024 //16 kb
#define SRAM2_END     (SRAM2_BASE + SRAM2_SIZE)
#define BACKUP_SRAM_SIZE   4*1024 //4 kb
#define BACKUP_SRAM_END     (BKPSRAM_BASE + SRAM2_SIZE)
#define FLASH_SIZE   512*1024 //512 kb
//#define FLASH_END   (FLASH_BASE + FLASH_SIZE);






/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

typedef enum
{
	//This command is used to read the bootloader version from the MCU
	BL_GET_VER = 0x51,
	//This command is used to know what are the commands supported by the bootloader
	BL_GET_HELP=0x52,
	//This command is used to read the MCU chip identification number
	BL_GET_CID=0x53,
	//This command is used to read the FLASH Read Protection level.
	BL_GET_RDP_STATUS=0x54,
	//This command is used to jump bootloader to specified address.
	BL_GO_TO_ADDR=0x55,
	//This command is used to mass erase or sector erase of the user flash
	BL_FLASH_ERASE=0x56,
	//This command is used to write data in to different memories of the MCU
	BL_MEM_WRITE=0x57,
	//This command is used to enable read/write protect on different sectors of the user flash .
	BL_EN_R_W_PROTECT=0x58,
	//This command is used to read data from different memories of the microcontroller.
	BL_MEM_READ=0x59,
	//This command is used to read all the sector protection status.
	BL_READ_SECTOR_STATUS=0x5A,
	//This command is used to read the OTP contents.
	BL_OTP_READ=0x5B,
	//This command is used to disable read/write protection on different sectors of the user flash . This 
    //command takes the protection status to default state.
	BL_DIS_R_W_PROTECT=0x5C
}BL_COMMAND_LIST_t;



//main function prototype
void printmsg( char *format, ...);
void bootloader_uart_read_data(void);
void bootloader_jump_to_user_app(void);


//bootloader handle functions prototype 
void bootloader_handle_get_ver(uint8_t *pBuffer);
void bootloader_handle_get_help(uint8_t *pBuffer);
void bootloader_handle_get_cid(uint8_t *pBuffer);
void bootloader_handle_get_rdp_status(uint8_t *pBuffer);
void bootloader_handle_go_to_addr(uint8_t *pBuffer);
void bootloader_handle_flash_erase(uint8_t *pBuffer);
void bootloader_handle_mem_write(uint8_t *pBuffer);
void bootloader_handle_en_r_w_protect(uint8_t *pBuffer);
void bootloader_handle_mem_read(uint8_t *pBuffer);
void bootloader_handle_read_sector_status(uint8_t *pBuffer);
void bootloader_handle_otp_read(uint8_t *pBuffer);
void bootloader_handle_dis_r_w_protect(uint8_t *pBuffer);

void bootloader_send_ack(uint8_t command_code, uint8_t follow_len);
void bootloader_send_nack(void);	


//helper function prototype
uint8_t get_bootloader_version(void);
uint16_t get_bootloader_cid_num(void);
uint8_t get_bootloader_RDP_status(void);
uint8_t is_valid_add(uint32_t go_add);
uint8_t get_bootloader_flash_erase(uint32_t sector_no,uint32_t no_of_sector);
uint8_t execute_mem_write(uint8_t *pBuffer ,uint8_t mem_add,uint8_t payload_len);
void bootloader_uart_write_data(uint8_t *pBuffer,uint8_t len);



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
