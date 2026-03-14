/*
 * User_Key.h
 *
 *  Created on: Mar 30, 2025
 *      Author: admin
 */

#ifndef INC_USER_KEY_H_
#define INC_USER_KEY_H_


#include "stm32g4xx_hal.h"
#include "main.h"
#include "stdbool.h"

//#include "stdbool.h"
//CONST DEFLINE
#define	RT_Trigger		(uint8_t)0x00
#define	RT_Trigger_2	(uint8_t)0x02
#define RG_Trigger		(uint8_t)0x01	//常规触发
#define KEY_MUN			7
#define TRAVEL_MAX_UM   4000.0f    // 按键最大行程（4000um）
#define TRAVEL_MIN_MM   0.0f    // 按键最小行程
#define TRAVEL_MAX_MM   4.0f    // 按键最大行程（4mm）

// 参数定义（需根据实际传感器特性调整）
#define ADC_MAX_MUN         4095    // 12位ADC最大值

//按键的基本状态
typedef struct{
	//按键基本属性
	char 	KEY_Value;
	// 状态变量
//	uint16_t* KEY_ADC_Value_POT;//指向ADC_Value列表的值的指针
	double	Travel;			//当前按键位置（um）
	double	Prev_Travel;	//上一次按键位置（um）
	double	Minimum_travel;	//触发后最小行程（um）
	uint8_t Is_Pressed;
	//用于单位换算
	uint16_t Delta_ADC;		//最大最小值的差值,由Keyboard_Init()运行后得出
}Key_Target;

//每个按键的单独配置
typedef struct{
	uint16_t MAX_ADC;			//ADC最大值	2byte
	uint16_t MIN_ADC;				//ADC最小值	2byte
	char 	Value;					//按下按键输出的字母	1byte
	uint8_t K_Oter;//按键不受总设置影响	1Byte
	/*按位
	 * HSB
	 * 8	NULL
	 * 7	NULL
	 * 6	NULL
	 * 5
	 * 4
	 * 3
	 * 2
	 * 1	NULL
	 * LSB
	 */
}Keyboard_Config;

typedef struct{
	double Down_Threshold;   	//按下触发点	8byte	12
	double Hight_Dead_Band;   	//上死区	8byte	20
	double Low_Dead_Band;		//下死区
	double Up_Threshold;    	// 抬起触发阈值	8byte	28
	double Regular_Threshold;  	// 常规基础触发阈值	8byte	36
}Trigger_Config;	//294

typedef struct{
	char 		Config_The_Head[3];  //键盘配置文件头标志		3byet
	//配置项
	Trigger_Config Trigger;
	uint8_t Trigger_mode;
	bool		Other;			//其他配置				1byte
//	uint8_t		Keyboard_Mun;//				1byte

	Keyboard_Config Keyboard_Config[KEY_MUN];
	//配置项结束
	uint8_t 	CheckByte;		//配置项校验字节			1byte
	char		Config_The_End[3];		//文件末尾				3byte
}Keyboard_Config_File;	//294

//extern Keyboard_Config	Keyboard[KEY_MUN];
extern Keyboard_Config_File User_Keyboard_Config_File;//作为键盘配置
extern Key_Target Key_Target_list[KEY_MUN];

extern uint32_t ADC_Sps;
extern uint32_t ADC_To_DMA[4];
extern uint32_t ADC_To_DMA_2[3];
extern uint16_t ADC_Value[7];
extern uint16_t mx_pBuffer[7][2];//0x 1m

extern float Down_Threshold_MM;
extern float Hight_Dead_Band_MM;
extern float Low_Dead_Band_MM;
extern float Up_Threshold_MM;
extern float Regular_Threshold_MM;


void Keyboard_Init();										//键盘初始化函数
void Keyboard_Config_reset();								//键盘存在flash的数据重置
void Save_Keyboard_Config();							//将数据保存在flash
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
uint8_t *Keyboqrd_read();
void Keyboard_Report(uint8_t *pData,uint8_t len);
void rapid_trigger_algorithm_2(void);
double get_travel_position(uint8_t ch);

uint8_t ascii_to_hid_report(char c, uint8_t report[]);
void USB_report();

#endif /* INC_USER_KEY_H_ */
