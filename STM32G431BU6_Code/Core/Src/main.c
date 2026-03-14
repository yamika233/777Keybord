/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// 包含例程菜单数据头文
#include "OLED_UI/OLED_UI_MenuData.h"
// 包含OLED_UI.h头文
#include "OLED_UI/OLED.h"

#include <stdio.h>
#include "User_Key.h"
#include "Flash.h"
#include "OLED_UI/OLED_UI.h"
#include "usbd_customhid.h"
#include "ws2812.h"


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

/* USER CODE BEGIN PV */
//char TTL_Str[TTL_Long]={0};
int Key_Status;

extern int Key_Status;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){	//定时器中断函
		static uint8_t i=0;
		static uint32_t d =0;

	if(htim==ADC_Tim){//启动ADC转换

		HAL_ADC_Start_DMA(&hadc2,&ADC_To_DMA_2, 3);
		HAL_ADC_Start_DMA(&hadc1,&ADC_To_DMA, 4);

	}
	if(htim==Show_Tim){
		extern int Key_Status;
		Key_Status=Key_GetStatus();
		OLED_UI_InterruptHandler();
		if(i>=106){
//			rainbow_effect(1);
			i=0;
		}
		i++;
//		rainbow_effect(1);
	}
	if(htim==OLED_TIM){
	}


	  UNUSED(htim);

}

uint8_t RxBuff=0;








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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USB_Device_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
//for(int i =0;i<1000;i++){
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
//}
	BSP_W25Q_Init();
	Keyboard_Init();
	OLED_UI_Init(&MainMenuPage);
	HAL_TIM_Base_Start_IT(ADC_Tim);
	HAL_TIM_Base_Start_IT(Show_Tim);
	HAL_TIM_Base_Start(Encoder_Tim);
//	HAL_TIM_Base_Start_IT(WS2812);
	//HAL_TIM_Base_Start_IT(&htim8);
	//HAL_TIM_Base_Start_IT(OLED_TIM);

	HAL_TIMEx_PWMN_Start(LED_Tim,LED_CHNNEL);
//	HAL_TIM_PWM_Start(LED_Tim,LED_CHNNEL);
	__HAL_TIM_SetCompare(LED_Tim,LED_CHNNEL,90);

//	HAL_TIM_PWM_Start(WS2812, WS2812_CHNNEL);
//

    HAL_UART_Receive_IT(Debug_USART, &RxBuff, 1);
//    rainbow_effect(1);
//    HAL_TIM_PWM_Start(WS2812, WS2812_CHNNEL);
//    __HAL_TIM_SetCompare(WS2812, WS2812_CHNNEL,50);
    //先发送1byte 的report ID，然后1byte的功能按键，然后1byte的LED，15byte的普通按键。
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 1);
	  OLED_UI_MainLoop();
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0);

		  USB_report();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 18;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)
{
    if(UartHandle==Debug_USART) {
        const char absk[] = "absk";
        const char save[] = "save";
        const char rest_Config[] = "CFG reset";
        static uint32_t RxLine = 0;
        RxLine++;//每接收到一个数据，进入回调数据长度加1
        static uint8_t DataBuff[20] = {0};
        DataBuff[RxLine - 1] = RxBuff;  //把每次接收到的数据保存到缓存数组

        if (RxBuff == '/')   //接收结束标志位，这个数据可以自定义，根据实际需求
        {
            int i=0;
//            if (!strncmp((char *) DataBuff, absk, sizeof (absk)-2)) {
//                HAL_UART_Transmit(Debug_USART, "开始校准...", sizeof("开始校准..."), 999);
//                Fadjusting_Window();
//            }
            if (!strncmp((char *) DataBuff, save, sizeof(save)-2)) {
                HAL_UART_Transmit(Debug_USART, "保存...", sizeof("保存..."), 999);
                Save_Keyboard_Config();

            }
            if (!strncmp((char *) DataBuff, rest_Config, sizeof(rest_Config)-2)) {
                HAL_UART_Transmit(Debug_USART, "重置键盘设置", sizeof("重置键盘设置"), 999);
                Keyboard_Config_reset();

            }
            memset(DataBuff, 0, sizeof(DataBuff));  //清空缓存数组
            RxLine = 0;  //清空接收长度

        }

        RxBuff = 0;
        HAL_UART_Receive_IT(Debug_USART, &RxBuff, 1);
        //每接收一个数据，就打开一次串口中断接收，否则只会接收一个数据就停止接收
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
