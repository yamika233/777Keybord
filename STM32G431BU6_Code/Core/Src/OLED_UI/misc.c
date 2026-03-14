/*
 * misc.c
 *
 *    Created on: Nov 23, 2024
 *            Author: tonny
 */
//#include "misc.h"
//#include "main.h"
//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_pwr_ex.h"
//#include "stm32f4xx_hal_pwr.h"
//#include "main.h"


//BTN_stat_t BTN_stat;

//void BTN_init()
//{
//    BTN_stat.isPressing = 0;
//    BTN_stat.isLongPressing = 0;
//    BTN_stat.isDebouncedPressing = 0;
//    BTN_stat.pressEvent = 0;
//    BTN_stat.longPressEvent = 0;
//    BTN_stat.pressStartTick = 0;
//    //BTN_stat.pressEndTick = 0;
//}



//void BtnTask()
//{
//    //============================    按钮管理    ============================
//	uint8_t BTNpin;
//	BTNpin = !HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);
//	//读取GPIO
//	if (BTNpin && !BTN_stat.isPressing)	//按下瞬间
//	{
//		BTN_stat.pressStartTick = HAL_GetTick();	//记录当前tick
//		BTN_stat.isPressing = 1;
//	}
//	if (!BTNpin && BTN_stat.isPressing) //松开瞬间
//	{
//		BTN_stat.isPressing = 0;
//		BTN_stat.isLongPressing = 0;
//		BTN_stat.isDebouncedPressing = 0;
//		BTN_stat.pressEvent = 0;
//		BTN_stat.longPressEvent = 0;
//	}

//	// 短按检测（按下时长超过消抖时间）
//	if (BTN_stat.isPressing && !BTN_stat.isDebouncedPressing && HAL_GetTick() > BTN_stat.pressStartTick + BTN_DEBOUNCE_MS)
//	{
//		BTN_stat.isDebouncedPressing = 1;
//		BTN_stat.pressEvent = 1;
//	}

//    // 长按检测（按下时长超过长按时间）
//    if (BTN_stat.isPressing && !BTN_stat.isLongPressing && HAL_GetTick() > BTN_stat.pressStartTick + BTN_LONG_PRESS_MS)
//    {
//        BTN_stat.isLongPressing = 1;
//        BTN_stat.longPressEvent = 1;
//    }
//}
