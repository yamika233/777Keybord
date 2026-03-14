/*
 * Flash.h
 *
 *  Created on: Apr 6, 2025
 *      Author: admin
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#ifndef _FLASH_H_
#define _FLASH_H_
#include "main.h"
#include "stm32g4xx_hal.h"
#include "spi.h"

#define SPI_W25Q_POT W25Qxx_SPI

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define W25Q_HOLD_Clr() (HAL_GPIO_WritePin(W25Q_HOLD_GPIO_Port, W25Q_HOLD_Pin, 1))//HOLD为高电平时才能使用该芯片
#define W25Q_HOLD_Set() (HAL_GPIO_WritePin(W25Q_HOLD_GPIO_Port, W25Q_HOLD_Pin, 0))

#define W25Q_CS_Clr() (HAL_GPIO_WritePin(W25Q_CS_GPIO_Port, W25Q_CS_Pin, 1))//低电平选中
#define W25Q_CS_Set() (HAL_GPIO_WritePin(W25Q_CS_GPIO_Port, W25Q_CS_Pin, 0))

#define W25Q_WP_Clr() (HAL_GPIO_WritePin(W25Q_WP_GPIO_Port, W25Q_WP_Pin, 1))//不可写
#define W25Q_WP_Set() (HAL_GPIO_WritePin(W25Q_WP_GPIO_Port, W25Q_WP_Pin, 0))//低有效

//#define FLASH_SECTOR_0_BASE_ADDR 0x08000000UL /*!< Sector Number 0   */
//#define FLASH_SECTOR_1_BASE_ADDR 0x08004000UL /*!< Sector Number 1   */
//#define FLASH_SECTOR_2_BASE_ADDR 0x08008000UL /*!< Sector Number 2   */
//#define FLASH_SECTOR_3_BASE_ADDR 0x0800C000UL /*!< Sector Number 3   */
//#define FLASH_SECTOR_4_BASE_ADDR 0x08010000UL /*!< Sector Number 4   */
//#define FLASH_SECTOR_5_BASE_ADDR 0x08020000UL /*!< Sector Number 5   */




uint8_t BSP_W25Q_Init(void);
void	BSP_W25Q_Reset(void);
uint8_t BSP_W25Q_GetStatus(void);
uint8_t BSP_W25Q_WriteEnable(void);
void BSP_W25Q_Read_ID(uint8_t *ID);
uint8_t BSP_W25Q_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t BSP_W25Q_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_W25Q_Erase_Block(uint32_t Address);
uint8_t BSP_W25Q_Erase_Chip(void);


#define W25Q_FLASH_SIZE                  0x1000000 /* 128 MBits => 16MBytes */
#define W25Q_SECTOR_SIZE                 0x10000   /* 256 sectors of 64KBytes */
#define W25Q_SUBSECTOR_SIZE              0x1000    /* 4096 subsectors of 4kBytes */
#define W25Q_PAGE_SIZE                   0x100     /* 65536 pages of 256 bytes */

#define W25Q_DUMMY_CYCLES_READ           4
#define W25Q_DUMMY_CYCLES_READ_QUAD      10

#define W25Q_BULK_ERASE_MAX_TIME         250000
#define W25Q_SECTOR_ERASE_MAX_TIME       3000
#define W25Q_SUBSECTOR_ERASE_MAX_TIME    1000
#define W25Q_TIMEOUT_VALUE               1000

/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

#define ENTER_QPI_MODE_CMD                   0x38
#define EXIT_QPI_MODE_CMD                    0xFF

/* Identification Operations */
#define READ_ID_CMD                          0x90
#define DUAL_READ_ID_CMD                     0x92
#define QUAD_READ_ID_CMD                     0x94
#define READ_JEDEC_ID_CMD                    0x9F

/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15

#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31
#define WRITE_STATUS_REG3_CMD                 0x11


/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_INPUT_PAGE_PROG_CMD             0x32


/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20
#define CHIP_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75


/* Flag Status Register */
#define W25Q_FSR_BUSY                    ((uint8_t)0x01)    /*!< busy */
#define W25Q_FSR_WREN                    ((uint8_t)0x02)    /*!< write enable */
#define W25Q_FSR_QE                      ((uint8_t)0x02)    /*!< quad enable */
#endif



#define W25Q_OK            ((uint8_t)0x00)
#define W25Q_ERROR         ((uint8_t)0x01)
#define W25Q_BUSY          ((uint8_t)0x02)
#define W25Q_TIMEOUT		((uint8_t)0x03)


#endif /* INC_FLASH_H_ */
