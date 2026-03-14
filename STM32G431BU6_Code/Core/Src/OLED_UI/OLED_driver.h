#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "stm32g4xx.h"
#include "stm32g4xx_hal.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>
#include "stdio.h"
#include "main.h"

// 主控型号选择
#define SSD1306
// #define SH1106

// 是否使用硬件SPI（注释该项则直接控制GPIO）
#define OLED_UI_USE_HW_SPI

// 使用硬件SPI
#ifdef OLED_UI_USE_HW_SPI
#define OLED_UI_SPI_USE_DMA         // 使用DMA
//#define OLED_UI_SPI_NSS_HARD_OUTPUT // 硬件CS（注释该项则/使用软件控制OLED的CS pin）

#define OLED_DC_Clr()   (HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 0))  // 复位 DC (将DC引脚拉低)
#define OLED_DC_Set()   (HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 1))  // 置位 DC (将DC引脚拉高)

#define OLED_CS_Clr()   (HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 0))  // 复位 DC (将DC引脚拉低)
#define OLED_CS_Set()   (HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 1))  // 置位 DC (将DC引脚拉高)

#define OLED_RES_Clr()  (HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, 0))  // 复位 DC (将DC引脚拉低)
#define OLED_RES_Set()  (HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, 1))  // 置位 DC (将DC引脚拉高)


// 不使用硬件SPI
#else

// 使用宏定义，速度更快（寄存器方式）
#define OLED_SCL_Clr() (OLED_CLK_GPIO_Port->BRR = OLED_CLK_Pin)  // 复位 SCL (将 GPIOB 的 8 号引脚拉低)
#define OLED_SCL_Set() (OLED_CLK_GPIO_Port->BSRR = OLED_CLK_Pin) // 置位 SCL (将 GPIOB 的 8 号引脚拉高)

#define OLED_SDA_Clr() (OLED_MOSI_GPIO_Port->BRR = OLED_MOSI_Pin)  // 复位 SDA (将 GPIOB 的 9 号引脚拉低)
#define OLED_SDA_Set() (OLED_MOSI_GPIO_Port->BSRR = OLED_MOSI_Pin) // 置位 SDA (将 GPIOB 的 9 号引脚拉高)

#define OLED_RES_Clr() (OLED_RST_GPIO_Port->BRR = OLED_RST_Pin)  // 复位 RES (将 GPIOB 的 5 号引脚拉低)
#define OLED_RES_Set() (OLED_RST_GPIO_Port->BSRR = OLED_RST_Pin) // 置位 RES (将 GPIOB 的 5 号引脚拉高)

#define OLED_DC_Clr() (OLED_DC_GPIO_Port->BRR = OLED_DC_Pin)  // 复位 DC (将 GPIOB 的 6 号引脚拉低)
#define OLED_DC_Set() (OLED_DC_GPIO_Port->BSRR = OLED_DC_Pin) // 置位 DC (将 GPIOB 的 6 号引脚拉高)

#define OLED_CS_Clr() (OLED_CS_GPIO_Port->BRR = OLED_CS_Pin)  // 复位 CS (将 GPIOB 的 7 号引脚拉低)
#define OLED_CS_Set() (OLED_CS_GPIO_Port->BSRR = OLED_CS_Pin) // 置位 CS (将 GPIOB 的 7 号引脚拉高)

#endif

#define OLED_CMD 0  // 写命令
#define OLED_DATA 1 // 写数据

//	oled初始化函数
void OLED_Init(void);
//	oled全局刷新函数
void OLED_Update(void);
//	oled局部刷新函数
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
// 设置颜色模式
void OLED_SetColorMode(bool colormode);
// OLED 设置亮度函数
void OLED_Brightness(int16_t Brightness);

#endif
