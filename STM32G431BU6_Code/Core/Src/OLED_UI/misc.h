/*
 * misc.h
 *
 *  Created on: Nov 24, 2024
 *      Author: tonny
 */

#ifndef MISC_H_
#define MISC_H_

#include "main.h"

#define BTN_LONG_PRESS_MS 1000
#define BTN_DEBOUNCE_MS 50	//消抖时间ms

typedef struct{
	uint8_t isPressing;				//按钮状态
	uint8_t isDebouncedPressing;	//消抖后的状态
	uint8_t isLongPressing;			//是否正在长按
	uint8_t pressEvent;				//未处理的按下事件
	uint8_t longPressEvent;			//未处理的长按事件
	uint32_t pressStartTick;		//按下瞬间的时间
	//uint32_t pressEndTick;		//松开瞬间的时间
} BTN_stat_t;

extern BTN_stat_t BTN_stat;

void BTN_init(void);

void BtnTask(void);

#endif /* MISC_H_ */
