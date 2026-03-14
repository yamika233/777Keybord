#include "ws2812.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// LED颜色
uint32_t ws2812_color[WS2812_NUM] = {0};

// 当前LED颜色
static uint32_t _ws2812_color_current[WS2812_NUM];


/**
 * @brief  直接更新LED颜色
 */
void ws2812_update(void)
{
	// 数据缓冲，每个LED占用24个字节，共10个LED，前100个字节用于复位信号
	static uint16_t ws2812_data[RST_PERIOD_NUM + WS2812_NUM * 24];

	for (uint8_t led_id = 0; led_id < WS2812_NUM; led_id++)
	{
		_ws2812_color_current[led_id] = ws2812_color[led_id];
		static uint8_t r, g, b;
		color_to_rgb(_ws2812_color_current[led_id], &r, &g, &b);
		uint16_t *p = ws2812_data + RST_PERIOD_NUM + led_id * 24;
		for (uint8_t i = 0; i < 8; i++)
		{
			p[i] = (r << i) & (0x80) ? CODE_ONE_DUTY : CODE_ZERO_DUTY;
			p[i + 8] = (g << i) & (0x80) ? CODE_ONE_DUTY : CODE_ZERO_DUTY;
			p[i + 16] = (b << i) & (0x80) ? CODE_ONE_DUTY : CODE_ZERO_DUTY;
		}
	}
	WS2812_Star(WS2812, WS2812_CHNNEL,(uint32_t *)ws2812_data,
					sizeof(ws2812_data)/sizeof(uint16_t));//发送数据

//	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,30);
//	HAL_TIMEx_PWMN_Start(&htim8,TIM_CHANNEL_1);


}

/**
 * @brief  通过渐变方式更新LED颜色（线性插值）
 * @param  steps: 渐变步数
 * @param  delay_ms: 每步之间的延迟时间（毫秒）
 */
void ws2812_gradient(uint8_t steps, uint16_t delay_ms)
{
	static uint8_t start_r[WS2812_NUM], start_g[WS2812_NUM], start_b[WS2812_NUM];
	static float r_step[WS2812_NUM], g_step[WS2812_NUM], b_step[WS2812_NUM];

	// 提取初始颜色，并计算每步的渐变步长
	for (uint8_t i = 0; i < WS2812_NUM; i++)
	{
		color_to_rgb(_ws2812_color_current[i], &start_r[i], &start_g[i], &start_b[i]);
		uint8_t target_r, target_g, target_b;
		color_to_rgb(ws2812_color[i], &target_r, &target_g, &target_b);

		r_step[i] = (float)(target_r - start_r[i]) / steps;
		g_step[i] = (float)(target_g - start_g[i]) / steps;
		b_step[i] = (float)(target_b - start_b[i]) / steps;
	}

	// 逐步渐变
	for (uint8_t step = 1; step <= steps; step++)
	{
		for (uint8_t led_id = 0; led_id < WS2812_NUM; led_id++)
		{
			// 计算当前步的颜色
			uint8_t r = (uint8_t)(start_r[led_id] + r_step[led_id] * step);
			uint8_t g = (uint8_t)(start_g[led_id] + g_step[led_id] * step);
			uint8_t b = (uint8_t)(start_b[led_id] + b_step[led_id] * step);

			ws2812_set_rgb(led_id, r, g, b);
		}

		ws2812_update();
		HAL_Delay(delay_ms);
	}
}

/**
 * @brief  设置LED颜色(RGB格式)
 * @param  led_id: LED编号（学习板一共有10个LED，编号范围0-9）
 * @param  r: 红色亮度（0-255）
 * @param  g: 绿色亮度（0-255）
 * @param  b: 蓝色亮度（0-255）
 */
void ws2812_set_rgb(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b)
{
	ws2812_color[led_id] = rgb_to_color(r, g, b);
}

/**
 * @brief  设置LED颜色（24bit颜色格式）
 * @param  led_id: LED编号（学习板一共有10个LED，编号范围0-9）
 * @param  color: 24bit颜色
 */
void ws2812_set(uint8_t led_id, uint32_t color)
{
	ws2812_color[led_id] = color;
}

/**
 * @brief  设置所有LED颜色（24bit颜色格式）
 * @param  color: 24bit颜色
 */
void ws2812_set_all(uint32_t color)
{
	for (uint8_t led_id = 0; led_id < WS2812_NUM; led_id++)
	{
		ws2812_color[led_id] = color;
	}
}

/**
 * @brief  RGB转换为24bit颜色
 * @param  r: 红色亮度（0-255）
 * @param  g: 绿色亮度（0-255）
 * @param  b: 蓝色亮度（0-255）
 * @retval 24bit颜色
 */
uint32_t rgb_to_color(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16) | (g << 8) | b;
}

/**
 * @brief  24bit颜色转换为RGB
 * @param  color: 24bit颜色
 * @param  r: 红色亮度（0-255）
 * @param  g: 绿色亮度（0-255）
 * @param  b: 蓝色亮度（0-255）
 */
void color_to_rgb(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

// =============== 以下为额外的效果演示函数 ================

uint32_t rainbow_color(float frequency, int phase, int center, int width)
{
	float r = sinf(frequency * phase + 0) * width + center;
	float g = sinf(frequency * phase + 2) * width + center;
	float b = sinf(frequency * phase + 4) * width + center;
	return rgb_to_color((uint8_t)r, (uint8_t)g, (uint8_t)b);
}

void rainbow_effect(uint8_t steps)
{
	static uint8_t color_roll =0;
	float frequency = 0.1;
	int center = 128;
	int width = 127;
		for (uint8_t led_id = 0; led_id < WS2812_NUM; led_id++)
		{
			uint32_t color = rainbow_color(frequency,  color_roll + led_id * 2, center, width);
			ws2812_set(led_id, color);

//			OUT_GRB((uint8_t)color<<8,(uint8_t)color,(uint8_t)color<<16);

		}
		ws2812_update();
		color_roll++;

}
