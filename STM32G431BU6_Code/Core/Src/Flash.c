/*
 * Flash.c
 *
 *  Created on: Apr 6, 2025
 *      Author: admin
 */


#include "Flash.h"
#include <stdio.h>

 /**********************************************************************************
  * 函数功能: 模块初始化
*/
uint8_t BSP_W25Q_Init(void)
{
	uint8_t cmd[2] = {RESET_ENABLE_CMD,RESET_MEMORY_CMD};
	W25Q_HOLD_Clr();
	W25Q_WP_Set();
	HAL_Delay(1);
	W25Q_CS_Set();
	/* Send the reset command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 2, W25Q_TIMEOUT_VALUE);
	W25Q_CS_Clr();
	return BSP_W25Q_GetStatus();
}

/**********************************************************************************
 * 函数功能: 获取设备状态
 */
uint8_t BSP_W25Q_GetStatus(void)
{
	uint8_t cmd[] = {READ_STATUS_REG1_CMD};
	uint8_t status=0;

	W25Q_CS_Set();
	/* Send the read status command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 1, W25Q_TIMEOUT_VALUE);
	/* Reception of the data */
	HAL_SPI_Receive(SPI_W25Q_POT,&status, 1, W25Q_TIMEOUT_VALUE);
	W25Q_CS_Clr();

	/* Check the value of the register */
 if((status & W25Q_FSR_BUSY) != 0)
 {
   return W25Q_BUSY;
 }
	else
	{
		return W25Q_OK;
	}
}

/**********************************************************************************
 * 函数功能: 写使能
 */
uint8_t BSP_W25Q_WriteEnable(void)
{
	uint8_t cmd[] = {WRITE_ENABLE_CMD};
	uint32_t tickstart = HAL_GetTick();

	/*Select the FLASH: Chip Select low */
	W25Q_CS_Set();
	/* Send the read ID command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 1, W25Q_TIMEOUT_VALUE);
	/*Deselect the FLASH: Chip Select high */
	W25Q_CS_Clr();

	/* Wait the end of Flash writing */
	while(BSP_W25Q_GetStatus() == W25Q_BUSY)
	{
		/* Check for the Timeout */
		if((HAL_GetTick() - tickstart) > W25Q_TIMEOUT_VALUE)
		{
				return W25Q_TIMEOUT;
		}
	}

	return W25Q_OK;
}

/**********************************************************************************
 * 函数功能: 获取设备ID
 */
void BSP_W25Q_Read_ID(uint8_t *ID)
{
	uint8_t cmd[4] = {READ_ID_CMD,0x00,0x00,0x00};

	W25Q_CS_Set();
	/* Send the read ID command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 4, W25Q_TIMEOUT_VALUE);
	/* Reception of the data */
	HAL_SPI_Receive(SPI_W25Q_POT,ID, 2, W25Q_TIMEOUT_VALUE);
	W25Q_CS_Clr();

}

/**********************************************************************************
 * 函数功能: 读数据
 * 输入参数: 缓存数组指针、读地址、字节数
 */
uint8_t BSP_W25Q_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
	uint8_t cmd[4];
//	uint8_t St=BSP_W25Q_GetStatus();
	/* Configure the command */
	cmd[0] = READ_CMD;
	cmd[1] = (uint8_t)(ReadAddr >> 16);
	cmd[2] = (uint8_t)(ReadAddr >> 8);
	cmd[3] = (uint8_t)(ReadAddr);
	uint8_t j = BSP_W25Q_GetStatus();
	W25Q_CS_Set();
	/* Send the read ID command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 4, W25Q_TIMEOUT_VALUE);
	/* Reception of the data */
	HAL_Delay(Size);
	uint8_t s = HAL_SPI_Receive(SPI_W25Q_POT, pData,Size,W25Q_TIMEOUT_VALUE);
	if ( s != HAL_OK)
 {
   return W25Q_ERROR;
 }
	W25Q_CS_Clr();
	return W25Q_OK;
}

/**********************************************************************************
 * 函数功能: 写数据
 * 输入参数: 缓存数组指针、写地址、字节数
 */
uint8_t BSP_W25Q_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
	uint8_t cmd[4];
	uint32_t end_addr, current_size, current_addr;
	uint32_t tickstart = HAL_GetTick();

	/* Calculation of the size between the write address and the end of the page */
 current_addr = 0;

 while (current_addr <= WriteAddr)
 {
   current_addr += W25Q_PAGE_SIZE;
 }
 current_size = current_addr - WriteAddr;

 /* Check if the size of the data is less than the remaining place in the page */
 if (current_size > Size)
 {
   current_size = Size;
 }

 /* Initialize the adress variables */
 current_addr = WriteAddr;
 end_addr = WriteAddr + Size;

 /* Perform the write page by page */
 do
 {
		/* Configure the command */
		cmd[0] = PAGE_PROG_CMD;
		cmd[1] = (uint8_t)(current_addr >> 16);
		cmd[2] = (uint8_t)(current_addr >> 8);
		cmd[3] = (uint8_t)(current_addr);

		/* Enable write operations */
		BSP_W25Q_WriteEnable();

		W25Q_CS_Set();
   /* Send the command */
   if (HAL_SPI_Transmit(SPI_W25Q_POT,cmd, 4, W25Q_TIMEOUT_VALUE) != HAL_OK)
   {
     return W25Q_ERROR;
   }

   /* Transmission of the data */
   if (HAL_SPI_Transmit(SPI_W25Q_POT, pData,current_size, W25Q_TIMEOUT_VALUE) != HAL_OK)
   {
     return W25Q_ERROR;
   }
			W25Q_CS_Clr();
   	/* Wait the end of Flash writing */
		while(BSP_W25Q_GetStatus() == W25Q_BUSY)
		{
			/* Check for the Timeout */
			if((HAL_GetTick() - tickstart) > W25Q_TIMEOUT_VALUE)
			{
				return W25Q_TIMEOUT;
			}
		}

   /* Update the address and size variables for next page programming */
   current_addr += current_size;
   pData += current_size;
   current_size = ((current_addr + W25Q_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : W25Q_PAGE_SIZE;
 } while (current_addr < end_addr);


	return W25Q_OK;
}

/**********************************************************************************
 * 函数功能: 扇区擦除
 * 输入参数: 地址
 */
uint8_t BSP_W25Q_Erase_Block(uint32_t Address)
{
	uint8_t cmd[4];
	uint32_t tickstart = HAL_GetTick();
	cmd[0] = SECTOR_ERASE_CMD;
	cmd[1] = (uint8_t)(Address >> 16);
	cmd[2] = (uint8_t)(Address >> 8);
	cmd[3] = (uint8_t)(Address);

	/* Enable write operations */
	BSP_W25Q_WriteEnable();

	/*Select the FLASH: Chip Select low */
	W25Q_CS_Set();
	/* Send the read ID command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 4, W25Q_TIMEOUT_VALUE);
	/*Deselect the FLASH: Chip Select high */
	W25Q_CS_Clr();

	/* Wait the end of Flash writing */
	while(BSP_W25Q_GetStatus() == W25Q_BUSY)
	{
		/* Check for the Timeout */
   if((HAL_GetTick() - tickstart) > W25Q_SECTOR_ERASE_MAX_TIME)
   {
			return W25Q_TIMEOUT;
   }
	}
	return W25Q_OK;
}

/**********************************************************************************
 * 函数功能: 芯片擦除
 */
uint8_t BSP_W25Q_Erase_Chip(void)
{
	uint8_t cmd[4];
	uint32_t tickstart = HAL_GetTick();
	cmd[0] = CHIP_ERASE_CMD;

	/* Enable write operations */
	BSP_W25Q_WriteEnable();

	/*Select the FLASH: Chip Select low */
	W25Q_CS_Set();
	/* Send the read ID command */
	HAL_SPI_Transmit(SPI_W25Q_POT, cmd, 1, W25Q_TIMEOUT_VALUE);
	/*Deselect the FLASH: Chip Select high */
	W25Q_CS_Clr();

	/* Wait the end of Flash writing */
	while(BSP_W25Q_GetStatus() != W25Q_BUSY)
	{
		/* Check for the Timeout */
   if((HAL_GetTick() - tickstart) > W25Q_BULK_ERASE_MAX_TIME)
   {
			return W25Q_TIMEOUT;
   }
	}
	return W25Q_OK;
}
