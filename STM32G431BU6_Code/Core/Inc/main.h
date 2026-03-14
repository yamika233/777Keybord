/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// #include "tim.h"

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
#define OLED_DC_Pin GPIO_PIN_11
#define OLED_DC_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_12
#define OLED_CS_GPIO_Port GPIOB
#define K_Z_Pin GPIO_PIN_14
#define K_Z_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_6
#define OLED_RES_GPIO_Port GPIOC
#define W25Q_HOLD_Pin GPIO_PIN_10
#define W25Q_HOLD_GPIO_Port GPIOC
#define W25Q_CS_Pin GPIO_PIN_11
#define W25Q_CS_GPIO_Port GPIOC
#define W25Q_WP_Pin GPIO_PIN_7
#define W25Q_WP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
//TIM DEFLINE
#define Encoder_Tim	&htim1
#define WS2812		&htim2
#define ADC_Tim		&htim3
#define Show_Tim	&htim4
#define OLED_TIM		&htim7
#define LED_Tim		&htim8

#define WS2812_CHNNEL 	TIM_CHANNEL_3
#define LED_CHNNEL		TIM_CHANNEL_4

#define OLED_SPI	&hspi2
#define W25Qxx_SPI	&hspi1
#define Debug_USART	&huart1

#define WS2812_Star HAL_TIM_PWM_Start_DMA//注意 HAL_TIMEx_PWMN_Start_DMA


//CONST DEFLINE

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
