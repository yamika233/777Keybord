		#ifndef __WS2812_H__
#define __WS2812_H__

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "stdio.h"
#include "string.h"

//#define CODE_ONE_DUTY 120
//#define CODE_ZERO_DUTY 60
 #define CODE_ONE_DUTY	120
 #define CODE_ZERO_DUTY	50
#define RST_PERIOD_NUM 3
#define WS2812_NUM 7

extern uint32_t ws2812_color[WS2812_NUM];

// 将颜色数组直接更新到 LED，不使用渐变过渡
void ws2812_update(void);

// 渐变的更新LED颜色
void ws2812_gradient(uint8_t steps, uint16_t delay_ms);

// 设置LED颜色（24bit颜色）
void ws2812_set(uint8_t led_id, uint32_t color);

// 设置LED颜色（RGB）
void ws2812_set_rgb(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b);

// 设置所有LED颜色
void ws2812_set_all(uint32_t color);

// RGB转换为24bit颜色
uint32_t rgb_to_color(uint8_t r, uint8_t g, uint8_t b);

// 24bit颜色转换为RGB
void color_to_rgb(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b);

// =============== 以下为额外的效果函数 ===============

// 彩虹颜色生成
uint32_t rainbow_color(float frequency, int phase, int center, int width);

// 彩虹效果
void rainbow_effect(uint8_t steps);

#endif
