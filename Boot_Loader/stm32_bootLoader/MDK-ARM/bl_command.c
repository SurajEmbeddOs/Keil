
#include "stm32f4xx.h"                  // Device header
#include "main.h"


uint8_t SUPPORTED_CMD[] = {
	BL_GET_VER,
	BL_GET_HELP,
	BL_GET_CID,
	BL_GET_RDP_STATUS,
	BL_GO_TO_ADDR,
	BL_FLASH_ERASE,
	BL_MEM_WRITE,
	BL_EN_R_W_PROTECT,
	BL_MEM_READ,
	BL_READ_SECTOR_STATUS,
	BL_OTP_READ,
	BL_DIS_R_W_PROTECT
};

void bootloader_send_ack(uint8_t command_code, uint8_t follow_len)
{
	// here we send two bytes 
	// 1 bytes is ack and 2 bytes is len value
	uint8_t ack_buff[2];
	ack_buff[0]=BL_ACK;
	ack_buff[1]=follow_len;
	HAL_UART_Transmit(C_UART,ack_buff,2,HAL_MAX_DELAY);
	
}
void bootloader_send_nack(void)
{
  uint8_t nack=BL_NACK;
	HAL_UART_Transmit(C_UART,&nack,1,HAL_MAX_DELAY);
}

uint8_t bootloader_verify_crc(uint8_t *pData,uint32_t len ,uint32_t crc_host)
{
	uint32_t uwCRCvalue=0xff;
	
   for(uint32_t i=0;i<len;i++)
	{
		uint32_t i_data=pData[i];
		uwCRCvalue=HAL_CRC_Accumulate(&hcrc,&i_data,1);
	}
	if(uwCRCvalue==crc_host)
	{
		return VERIFY_CRC_SUCCESS;
	}
	
	return VERIFY_CRC_FAIL;
	
}
	

/************implementation of  bootloder handle function  ************/

void bootloader_handle_get_ver(uint8_t *pBuffer)
{
	uint8_t bl_version;
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle get ver \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=  *((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],2);
		bl_version=get_bootloader_version();
		printmsg("BL_DEBUG_MSG:BL_ver : %d %x\n\r",bl_version,bl_version);
		
		bootloader_uart_write_data(&bl_version,sizeof(bl_version));
		
		
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
}
void bootloader_handle_get_help(uint8_t *pBuffer)
{
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle get help  \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=  *((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],sizeof(SUPPORTED_CMD));
		bootloader_uart_write_data(SUPPORTED_CMD,sizeof(SUPPORTED_CMD));
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
}
void bootloader_handle_get_cid(uint8_t *pBuffer)
{
		uint16_t bl_Cid_num;
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle get ver \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=  *((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],2);
		bl_Cid_num=get_bootloader_cid_num();
		printmsg("BL_DEBUG_MSG:BL_ver : %d %x\n\r",bl_Cid_num,bl_Cid_num);
		
		uint8_t send_len=sizeof(bl_Cid_num);
		bootloader_uart_write_data((uint8_t *)&bl_Cid_num,send_len);
		
		
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
}
void bootloader_handle_get_rdp_status(uint8_t *pBuffer)
{
	uint8_t RDP_Status;
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle RDP Status \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=  *((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],1);
		RDP_Status=get_bootloader_RDP_status();
		printmsg("BL_DEBUG_MSG:RDP STAtus : %d %x\n\r",RDP_Status,RDP_Status);
		
		bootloader_uart_write_data(&RDP_Status,sizeof(RDP_Status));
		
		
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
}
void bootloader_handle_go_to_addr(uint8_t *pBuffer)
{
		uint32_t goto_add;
	 uint8_t Valid_add=VALID_ADD;
	uint8_t InValid_add=INVALID_ADD;
	
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle RDP Status \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=  *((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],1);
		// extract the address to jump
		goto_add= *((uint32_t*)&pBuffer[2]);
		
		if(is_valid_add(goto_add)==Valid_add)
		{
			//tell the host is add is fine
			bootloader_uart_write_data(&Valid_add,sizeof(Valid_add));
			
			goto_add+=1; // make T bit 1;
			
			void (*lest_jump)(void)= (void *)goto_add;
			printmsg("BL_DEBUG_MSG:jumping to the address \n\r");
			
			lest_jump();
		}
		else
		{
			printmsg("BL_DEBUG_MSG:address is invalid \n\r");
			//tell the host is add is not fine
			bootloader_uart_write_data(&InValid_add,sizeof(InValid_add));
		}
		
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
	
}
void bootloader_handle_flash_erase(uint8_t *pBuffer)
{
		uint8_t flash_erase_Status;
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle flash erase Status \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=  *((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],1);
		printmsg("BL_DEBUG_MSG:sector and no of sector \
            		: %d %d\n\r",pBuffer[2],pBuffer[3]);
		flash_erase_Status=get_bootloader_flash_erase(pBuffer[2],pBuffer[3]);	
		printmsg("BL_DEBUG_MSG:flash erase status \
            		: %d %x\n\r",flash_erase_Status,flash_erase_Status);
		
		bootloader_uart_write_data(&flash_erase_Status,sizeof(flash_erase_Status));
		
		
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
}
void bootloader_handle_mem_write(uint8_t *pBuffer)
{
	uint8_t write_status=0x00;;
	 uint8_t Valid_add=VALID_ADD;
	uint8_t InValid_add=INVALID_ADD;
	uint8_t check_sum=0,len=0;
	 len=pBuffer[0];
	uint8_t payload_len=pBuffer[6];
	
	uint32_t mem_add= *((uint32_t*)(&pBuffer[2]));
	
	check_sum=pBuffer[len];
	//1. verfiy the checkum
	printmsg("BL_DEBUG_MSG:bootloader handle memory write \n\r");
	
	//2.commond packet lenght
	uint32_t command_packet_len =pBuffer[0]+1;
	
	//extract the crc32 sent by the host
	uint32_t crc_host=*((uint32_t *)(pBuffer+command_packet_len-4));
	
	if(!bootloader_verify_crc(&pBuffer[0],command_packet_len-4,crc_host))
	{
		printmsg("BL_DEBUG_MSG:checksum succes \n\r");
		//checksum is correct
		bootloader_send_ack(pBuffer[0],1);
		// extract the address to jump
		printmsg("BL_DEBUG_MSG: memory write address %d \n\r",mem_add);
		
		if(is_valid_add(mem_add)==Valid_add)
		{
			printmsg("BL_DEBUG_MSG: valid address \n\r");
			
			write_status=execute_mem_write(&pBuffer[7],mem_add,payload_len);
			//tell the host is add is fine
			bootloader_uart_write_data(&write_status,sizeof(write_status));
			
		
		}
		else
		{
			printmsg("BL_DEBUG_MSG:address is invalid \n\r");
			//tell the host is add is not fine
			bootloader_uart_write_data(&InValid_add,sizeof(InValid_add));
		}
		
	}
	else
	{
		printmsg("BL_DEBUG_MSG:check_sum fail \n\r");
		bootloader_send_nack();
	}
}
void bootloader_handle_en_r_w_protect(uint8_t *pBuffer)
{
	
}
void bootloader_handle_mem_read(uint8_t *pBuffer)
{
	
}
void bootloader_handle_read_sector_status(uint8_t *pBuffer)
{
	
}
void bootloader_handle_otp_read(uint8_t *pBuffer)
{
	
}
void bootloader_handle_dis_r_w_protect(uint8_t *pBuffer)
{
	
}

//helper function definitions
uint8_t get_bootloader_version(void)
{
	return (uint8_t)BL_VERSION;
}

uint16_t get_bootloader_cid_num(void)
{
	 uint16_t _temp_cid_num=0;
	_temp_cid_num=(uint16_t)(DBGMCU->IDCODE);
	 return _temp_cid_num;
}

uint8_t get_bootloader_RDP_status(void)
{
	uint8_t RDP_Status=0;
	#if (0)
   FLASH_OBProgramInitTypeDef OB_Handler;
	 HAL_FLASHEx_OBGetConfig(&OB_Handler);
	 RDP_Status = (uint8_t)OB_Handler.RDPLevel;
	 return RDP_Status;
	#else
	volatile uint32_t *get_rdp = (uint32_t *)0x1FFFC000;
	RDP_Status= (uint8_t)(*get_rdp>>8);
	return RDP_Status;
	#endif
}

uint8_t is_valid_add(uint32_t go_add)	
{
	//so what is the valid address so we can jump
	//can we jump system memory ? yes
	//can we jump SRM1 memory ? yes
	//can we jump SRM2 memory ? yes
	//can we jump Back up SRM memory ? yes
	//can we jump external memory ? yes
	//can we jump pheriphera memory ? its possible but dont allowed : No
	
	if(go_add>=SRAM1_BASE && go_add <=SRAM1_END)
	{
		return VALID_ADD;
	}
	else if(go_add>=SRAM2_BASE && go_add <=SRAM2_END)
	{
		return VALID_ADD;
	}
	else if(go_add>=BKPSRAM_BASE && go_add <=BACKUP_SRAM_END)
	{
		return VALID_ADD;
	}
	else if(go_add>=FLASH_BASE && go_add<=FLASH_END)
	{
		return VALID_ADD;
	}
	else
	{
		return INVALID_ADD;
	}
	
}


uint8_t get_bootloader_flash_erase(uint32_t sector_no,uint32_t no_of_sector)
{
	FLASH_EraseInitTypeDef Flash_erase_init;
	HAL_StatusTypeDef status;
	uint32_t SectorError;
		if(sector_no>8)
		{
			return VALID_STATUS;
		}

		
	if(sector_no==0xff ||sector_no<8 )
	{
		if(sector_no==0xff)
		{
			Flash_erase_init.TypeErase=FLASH_TYPEERASE_MASSERASE;
		}
		else
		{
			uint8_t remaing_sector=8- no_of_sector;
			if(no_of_sector>remaing_sector)
			{
				no_of_sector=remaing_sector;
			}
		
		
		Flash_erase_init.TypeErase=FLASH_TYPEERASE_SECTORS;
	  Flash_erase_init.Sector=sector_no;
    Flash_erase_init.NbSectors=no_of_sector;
	  Flash_erase_init.VoltageRange=FLASH_VOLTAGE_RANGE_3;
	  }
	  Flash_erase_init.Banks=FLASH_BANK_1;
		
		HAL_FLASH_Unlock();
		
	  status=(uint8_t)HAL_FLASHEx_Erase(&Flash_erase_init,&SectorError);
		
		HAL_FLASH_Lock();
		
		return status;
	
	}
	return INVALID_STATUS;
}

uint8_t execute_mem_write(uint8_t *pBuffer ,uint8_t mem_add,uint8_t payload_len)
{
	uint8_t status=HAL_OK;
	HAL_FLASH_Unlock();
	
	for(uint32_t i=0;i<payload_len;i++)
	{
		status=HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,mem_add+i,pBuffer[i]);
	}
	HAL_FLASH_Lock();
	return status;
}

void bootloader_uart_write_data(uint8_t *pBuffer,uint8_t len)
{
	HAL_UART_Transmit(C_UART,pBuffer,len,HAL_MAX_DELAY);
}


