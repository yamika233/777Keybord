#ifndef __OLED_UI_DRIVER_H
#define __OLED_UI_DRIVER_H
/*【如果您需要移植此项目，则需要更改以下函数的实现方式。】 */
#include "stm32g4xx_hal.h" // Device header
#include "stm32g4xx.h"
#include "misc.h"

// 获取确认，取消，上，下按键状态的函数(【Q：为什么使用宏定义而不是函数？A：因为这样可以提高效率，减少代码量】)
// #define Key_GetEnterStatus()	(!BTN_stat.isDebouncedPressing)
// #define Key_GetBackStatus()		(1)
// #define Key_GetUpStatus()		(1)
// #define Key_GetDownStatus()		(1)

//#define Key_GetEnterStatus()    HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
//#define Key_GetBackStatus()     HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
//#define Key_GetUpStatus()       HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
//#define Key_GetDownStatus()     HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)

//获取确认，取消，上，下按键状态的函数(【Q：为什么使用宏定义而不是函数？A：因为这样可以提高效率，减少代码量】)
#define Key_GetEnterStatus()	(HAL_GPIO_ReadPin(K_Z_GPIO_Port,K_Z_Pin))
#define Key_GetBackStatus()		(1)
#define Key_GetUpStatus()		(1)//(Encoder_Get()<512)?0:1
#define Key_GetDownStatus()		(1)//(Encoder_Get()>512)?0:1






// 定时器中断初始化函数
void Timer_Init(void);

// 按键初始化函数
void Key_Init(void);
// 按键长时间无操作检测
int Key_GetStatus(void);
//编码器初始化函数
void Encoder_Init(void);
// 编码器使能函数
void Encoder_Enable(void);
//编码器失能函数
void Encoder_Disable(void);
//读取编码器值
int16_t Encoder_Get(void);
//重置编码器值
void Encoder_Reset(void);

// 延时函数
// void Delay_us(uint32_t xus);
void Delay_ms(uint32_t xms);
void Delay_s(uint32_t xs);

#endif
