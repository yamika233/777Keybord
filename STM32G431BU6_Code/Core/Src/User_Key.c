/*
 * User_Key.c
 *
 *  Created on: Mar 30, 2025
 *      Author: admin
 */
//_________________
//键盘判断函数
#include "User_Key.h"
#include "stm32g4xx_hal.h"
#include <stdio.h>

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "Flash.h"
#include "usb_device.h"
#include "usart.h"


#include <stdint.h>
#include <string.h>

//uint32_t ADC_Sps=0;
uint32_t ADC_To_DMA[4]={0};
uint32_t ADC_To_DMA_2[3]={0};	//两个ADC的转换结果

uint16_t ADC_Value[7]={0};		//键盘ADC数据用于转换行程
uint16_t mx_pBuffer[7][2]={0};	//用于键盘校准的数据

extern UART_HandleTypeDef huart1;
uint8_t Trigger_Mod;	//触发模式


Key_Target Key_Target_list[KEY_MUN];
Keyboard_Config_File User_Keyboard_Config_File={0};
float Down_Threshold_MM;
float Hight_Dead_Band_MM;
float Low_Dead_Band_MM;
float Up_Threshold_MM;
float Regular_Threshold_MM;

//读FLASH里的键盘数据
void Keyboard_Init(){

//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	uint8_t rData[sizeof(User_Keyboard_Config_File)]={0};
	BSP_W25Q_Read(rData,0x00,sizeof(User_Keyboard_Config_File));
	// 使用 memcpy 将 rData 的内容复制到 User_Keyboard_Config_File
	memcpy(&User_Keyboard_Config_File, rData, sizeof(Keyboard_Config_File));
	HAL_UART_Transmit(Debug_USART, rData, sizeof(User_Keyboard_Config_File),99);
    for (int i = 0; i < 7; ++i) {
        Key_Target_list[i].KEY_Value=User_Keyboard_Config_File.Keyboard_Config[i].Value;
        Key_Target_list[i].Delta_ADC=User_Keyboard_Config_File.Keyboard_Config[i].MAX_ADC\
                                                -User_Keyboard_Config_File.Keyboard_Config[i].MIN_ADC;
        		mx_pBuffer[i][0]=1000;
		mx_pBuffer[i][1]=30000;
    }


    Trigger_Mod=User_Keyboard_Config_File.Other&&0x03;

	Down_Threshold_MM=\
	(User_Keyboard_Config_File.Trigger.Down_Threshold/1000);

	Hight_Dead_Band_MM=\
	(User_Keyboard_Config_File.Trigger.Hight_Dead_Band/1000);

	Low_Dead_Band_MM=\
	(User_Keyboard_Config_File.Trigger.Low_Dead_Band/1000);

	Up_Threshold_MM=\
	(User_Keyboard_Config_File.Trigger.Up_Threshold/1000);

	Regular_Threshold_MM=\
	(User_Keyboard_Config_File.Trigger.Regular_Threshold/1000);



//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

}
//重置键盘配置
void Keyboard_Config_reset(void)
{
    memset(&User_Keyboard_Config_File, 0, sizeof(User_Keyboard_Config_File));

    User_Keyboard_Config_File.Config_The_Head[0] = 'C';
    User_Keyboard_Config_File.Config_The_Head[1] = 'F';
    User_Keyboard_Config_File.Config_The_Head[2] = 'G';
    User_Keyboard_Config_File.Config_The_End[0] = 'E';
    User_Keyboard_Config_File.Config_The_End[1] = 'N';
    User_Keyboard_Config_File.Config_The_End[2] = 'D';
    User_Keyboard_Config_File.Other=0;
    for(int i = 0; i < 7; i++) {
        User_Keyboard_Config_File.Trigger.Down_Threshold=100;
        User_Keyboard_Config_File.Trigger.Hight_Dead_Band=3000.1;
        User_Keyboard_Config_File.Trigger.Up_Threshold=600;
        User_Keyboard_Config_File.Trigger.Low_Dead_Band=100;
        User_Keyboard_Config_File.Trigger.Regular_Threshold=2000.5;
    }
    User_Keyboard_Config_File.Other=0;
    User_Keyboard_Config_File.Keyboard_Config[0].Value='d';
    User_Keyboard_Config_File.Keyboard_Config[1].Value='f';
    User_Keyboard_Config_File.Keyboard_Config[2].Value=0x1b;
    User_Keyboard_Config_File.Keyboard_Config[3].Value='`';
    User_Keyboard_Config_File.Keyboard_Config[4].Value='j';
    User_Keyboard_Config_File.Keyboard_Config[5].Value='k';
    User_Keyboard_Config_File.Keyboard_Config[6].Value='l';
}

void Save_Keyboard_Config(void) {
	for(int n=0;n<7;n++){
		User_Keyboard_Config_File.Keyboard_Config[n].MAX_ADC=mx_pBuffer[n][0];
		User_Keyboard_Config_File.Keyboard_Config[n].MIN_ADC=mx_pBuffer[n][1];
	}
//    Keyboard_Config_reset();
	BSP_W25Q_Erase_Block(0x00);
	// 初始化 wData 指针
	uint8_t * wData = NULL;
	//将 User_Keyboard_Config_File 的地址赋值给 wData
	User_Keyboard_Config_File.Trigger.Down_Threshold=(float)1000*Down_Threshold_MM;
	User_Keyboard_Config_File.Trigger.Hight_Dead_Band=(float)1000*Hight_Dead_Band_MM;
	User_Keyboard_Config_File.Trigger.Low_Dead_Band=(float)1000*Low_Dead_Band_MM;
	User_Keyboard_Config_File.Trigger.Up_Threshold=(float)1000*Up_Threshold_MM;
	User_Keyboard_Config_File.Trigger.Regular_Threshold=(float)1000*Regular_Threshold_MM;
	wData = (uint8_t *)&User_Keyboard_Config_File;
	BSP_W25Q_Write(wData,0x00,sizeof(User_Keyboard_Config_File));
	Keyboard_Init();
}



// 获取霍尔传感器ADC值并转换为行程（mm）
double get_travel_position(uint8_t ch)
{
	extern Keyboard_Config_File User_Keyboard_Config_File;//作为键盘配置

	extern Key_Target Key_Target_list[KEY_MUN];
//	extern uint16_t ADC_Value[9];
	double t;
	static uint16_t last[KEY_MUN];
    // 假设ADC值线性对应0~4mm（需根据传感器校准）
//	uint16_t V=&Key_Target_list[ch].KEY_ADC_Value_POT;//承接

	last[ch] = ADC_Value[ch];
	uint16_t ADC_Average= (last[ch]+ADC_Value[ch])/2;//这一次与上一次转换的中值消抖
	last[ch] = ADC_Value[ch];
	t =((ADC_Average-User_Keyboard_Config_File.Keyboard_Config[ch].MIN_ADC)/ (double)\
    		Key_Target_list[ch].Delta_ADC) * TRAVEL_MAX_UM;
	Key_Target_list[ch].Travel = t;
    return t;
}

// RT算法核心逻辑
void rapid_trigger_algorithm()
{
	extern Keyboard_Config_File User_Keyboard_Config_File;//键盘配置

	extern Key_Target Key_Target_list[7];

    for (int i = 0; i < 7; i++)
    {
        double Now=get_travel_position(i);

        // 计算行程变化量
//    	double delta = Now - Key_Target_list[i].Minimum_travel;

//         判断触发或重置
        if (Now<User_Keyboard_Config_File.Trigger.Hight_Dead_Band\
        		&& (Key_Target_list[i].Minimum_travel)>=Now)
        {
//			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
            	Key_Target_list[i].Minimum_travel=Now;//重置最小行程
//                trigger_key(i); // 触发按键按下事件
            	Key_Target_list[i].Is_Pressed = 1;
        }else{
            if (Now>User_Keyboard_Config_File.Trigger.Low_Dead_Band\
            		&&(Key_Target_list[i].Minimum_travel+User_Keyboard_Config_File.Trigger.Up_Threshold)<Now){

               	Key_Target_list[i].Minimum_travel=Now-\
               			User_Keyboard_Config_File.Trigger.Down_Threshold;
//                reset_key(i); // 触发按键释放事件
               	Key_Target_list[i].Is_Pressed = 0;
            }
        }
    }
}


double lower=0.1f;
double upper=0.2f;
// RT算法核心逻辑
void rapid_trigger_algorithm_2(void) {
	// extern Key_Target Key_Target_list[7];

	for (int i = 0; i < 7; i++)
	{
    	// 1. 读取磁轴当前位置（通过霍尔传感器/模拟电路）
    	double new_position=get_travel_position(i);

    // 2. 计算两次扫描间的位移变化量（关键！）
    int16_t delta = (int16_t)(new_position - Key_Target_list[i].Prev_Travel);

    // 3. 动态触发判定（核心算法）
    if (!Key_Target_list[i].Is_Pressed) {
        // 抬起状态：检测是否满足按下条件
        if (delta >= lower) {
//            trigger_key_press();          // 发送按下事件
        	Key_Target_list[i].Is_Pressed = 1;          // 更新状态
        	Key_Target_list[i].Prev_Travel  = new_position; // 重置参考点
        }
    } else {
        // 按下状态：检测是否满足抬起条件
        if (delta <= -(upper)) {
//            trigger_key_release();        // 发送抬起事件
        	Key_Target_list[i].Is_Pressed = 0;          // 更新状态
            Key_Target_list[i].Prev_Travel = new_position; // 重置参考点
        }
    }

    // 4. 更新位置记录（即使未触发事件）
    Key_Target_list[i].Prev_Travel = new_position;
    }
}
//常规触发模式
void regular_trigger_algorithm()
{

	for(int i=0;i<7;i++)
	{
		double Now=get_travel_position(i);
		if(Now>User_Keyboard_Config_File.Trigger.Regular_Threshold)
		{
			Key_Target_list[i].Is_Pressed = 0;

		}else
		{
			Key_Target_list[i].Is_Pressed = 1;

		}
	}
}

//检测键是否是触发的，是 则返回键值
uint8_t *Keyboard_read()
{
	static uint8_t Is_Pressed_Key_List[8];
	for(uint8_t p=0;p<7;p++)
	{
		Is_Pressed_Key_List[p]=0;
	}
	uint8_t n=2;
	for(uint8_t i=0;i<7;i++)
	{
		if(Key_Target_list[i].Is_Pressed == 1)
		{
			Is_Pressed_Key_List[n]=Key_Target_list[i].KEY_Value;
			n++;
			if(n>8)
			{
				return Is_Pressed_Key_List;
			}
		}
	}
		return Is_Pressed_Key_List;
}
//把串口传输的数据打包成ch9329规定的帧格式
void Keyboard_Report(uint8_t *pData,uint8_t len){
	static uint8_t Report[32];
	for(int s=0;s<32;s++){
		Report[s]=0;
	}
	//如果缓冲区是一个局部变量（非static），当函数退出时，该局部变量所在的栈空间可能被回收，或者被其他函数覆盖。
	static uint8_t R[4]={0x57,0xAB,0x00,0x02};//普通键盘帧格式
	for(int i=0;i<4;i++)
	{
		Report[i]=R[i];
	}
	Report[4]=len;//键盘+该字节数据长度
	for(uint8_t p=0;p<len;p++)
	{
		Report[5+p]=pData[p];
	}
	int Report_Sum=0;
	for(uint8_t u=0;u<len+6-1;u++)//除了最后一项的累加和
	{
		Report_Sum+=Report[u];
	}
	Report[len+6-1]=Report_Sum;
//	HAL_UART_Transmit_DMA(&huart1,Report,len+6);

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc==&hadc1){
//		extern uint32_t ADC_Sps;
//		ADC_Sps ++;
		for(int i=0;i<4;i++){
			ADC_Value[i+3]=(uint16_t)ADC_To_DMA[i];
		}
		for(int i=0;i<3;i++){
			ADC_Value[i]=(uint16_t)ADC_To_DMA_2[i];
		}
		switch (Trigger_Mod) {
		case RT_Trigger:
			rapid_trigger_algorithm();
		break;
		case RT_Trigger_2:
			rapid_trigger_algorithm_2();

		break;
		case RG_Trigger:
			regular_trigger_algorithm();
		break;

//        Keyboard_read();

		}
	}
}



// HID键盘Usage ID映射表 (ASCII -> HID Usage ID)
 static const uint8_t ascii_to_hid_map[128] = {
    [0x00] = 0,      // NUL (保留)
    [0x01] = 0,      // SOH (保留)
    [0x02] = 0,      // STX (保留)
    [0x03] = 0,      // ETX (保留)
    [0x04] = 0,      // EOT (保留)
    [0x05] = 0,      // ENQ (保留)
    [0x06] = 0,      // ACK (保留)
    [0x07] = 0,      // BEL (保留)
    [0x08] = 0x2A,   // Backspace
    [0x09] = 0x2B,   // Tab
    [0x0A] = 0,      // LF (通常用Enter代替)
    [0x0B] = 0,      // VT (保留)
    [0x0C] = 0,      // FF (保留)
    [0x0D] = 0x28,   // Carriage Return (Enter)
    [0x0E] = 0,      // SO (保留)
    [0x0F] = 0,      // SI (保留)
    [0x10] = 0,      // DLE (保留)
    [0x11] = 0,      // DC1 (保留)
    [0x12] = 0,      // DC2 (保留)
    [0x13] = 0,      // DC3 (保留)
    [0x14] = 0,      // DC4 (保留)
    [0x15] = 0,      // NAK (保留)
    [0x16] = 0,      // SYN (保留)
    [0x17] = 0,      // ETB (保留)
    [0x18] = 0,      // CAN (保留)
    [0x19] = 0,      // EM (保留)
    [0x1A] = 0,      // SUB (保留)
    [0x1B] = 0x29,   // ESC
    [0x1C] = 0,      // FS (保留)
    [0x1D] = 0,      // GS (保留)
    [0x1E] = 0,      // RS (保留)
    [0x1F] = 0,      // US (保留)
    [0x20] = 0x2C,   // Space
    [0x21] = 0x1E,   // ! (Shift+1)
    [0x22] = 0x34,   // " (Shift+')
    [0x23] = 0x20,   // # (Shift+3)
    [0x24] = 0x21,   // $ (Shift+4)
    [0x25] = 0x22,   // % (Shift+5)
    [0x26] = 0x24,   // & (Shift+7)
    [0x27] = 0x34,   // '
    [0x28] = 0x26,   // ( (Shift+9)
    [0x29] = 0x27,   // ) (Shift+0)
    [0x2A] = 0x25,   // * (Shift+8)
    [0x2B] = 0x2E,   // + (Shift+=)
    [0x2C] = 0x36,   // ,
    [0x2D] = 0x2D,   // -
    [0x2E] = 0x37,   // .
    [0x2F] = 0x38,   // /
    [0x30] = 0x27,   // 0
    [0x31] = 0x1E,   // 1
    [0x32] = 0x1F,   // 2
    [0x33] = 0x20,   // 3
    [0x34] = 0x21,   // 4
    [0x35] = 0x22,   // 5
    [0x36] = 0x23,   // 6
    [0x37] = 0x24,   // 7
    [0x38] = 0x25,   // 8
    [0x39] = 0x26,   // 9
    [0x3A] = 0x33,   // : (Shift+;)
    [0x3B] = 0x33,   // ;
    [0x3C] = 0x36,   // < (Shift+,)
    [0x3D] = 0x2E,   // =
    [0x3E] = 0x37,   // > (Shift+.)
    [0x3F] = 0x38,   // ? (Shift+/)
    [0x40] = 0x1F,   // @ (Shift+2)
    [0x41] = 0x04,   // A
    [0x42] = 0x05,   // B
    [0x43] = 0x06,   // C
    [0x44] = 0x07,   // D
    [0x45] = 0x08,   // E
    [0x46] = 0x09,   // F
    [0x47] = 0x0A,   // G
    [0x48] = 0x0B,   // H
    [0x49] = 0x0C,   // I
    [0x4A] = 0x0D,   // J
    [0x4B] = 0x0E,   // K
    [0x4C] = 0x0F,   // L
    [0x4D] = 0x10,   // M
    [0x4E] = 0x11,   // N
    [0x4F] = 0x12,   // O
    [0x50] = 0x13,   // P
    [0x51] = 0x14,   // Q
    [0x52] = 0x15,   // R
    [0x53] = 0x16,   // S
    [0x54] = 0x17,   // T
    [0x55] = 0x18,   // U
    [0x56] = 0x19,   // V
    [0x57] = 0x1A,   // W
    [0x58] = 0x1B,   // X
    [0x59] = 0x1C,   // Y
    [0x5A] = 0x1D,   // Z
    [0x5B] = 0x2F,   // [
    [0x5C] = 0x31,   // Backslash
    [0x5D] = 0x30,   // ]
    [0x5E] = 0x23,   // ^ (Shift+6)
    [0x5F] = 0x2D,   // _ (Shift+-)
    [0x60] = 0x35,   // `
    [0x61] = 0x04,   // a
    [0x62] = 0x05,   // b
    [0x63] = 0x06,   // c
    [0x64] = 0x07,   // d
    [0x65] = 0x08,   // e
    [0x66] = 0x09,   // f
    [0x67] = 0x0A,   // g
    [0x68] = 0x0B,   // h
    [0x69] = 0x0C,   // i
    [0x6A] = 0x0D,   // j
    [0x6B] = 0x0E,   // k
    [0x6C] = 0x0F,   // l
    [0x6D] = 0x10,   // m
    [0x6E] = 0x11,   // n
    [0x6F] = 0x12,   // o
    [0x70] = 0x13,   // p
    [0x71] = 0x14,   // q
    [0x72] = 0x15,   // r
    [0x73] = 0x16,   // s
    [0x74] = 0x17,   // t
    [0x75] = 0x18,   // u
    [0x76] = 0x19,   // v
    [0x77] = 0x1A,   // w
    [0x78] = 0x1B,   // x
    [0x79] = 0x1C,   // y
    [0x7A] = 0x1D,   // z
    [0x7B] = 0x2F,   // { (Shift+[)
    [0x7C] = 0x31,   // | (Shift+\)
    [0x7D] = 0x30,   // } (Shift+])
    [0x7E] = 0x24,   // ~ (Shift+`)
    [0x7F] = 0x2A,   // Delete (映射到Backspace)
};
// 检查字符是否需要Shift修饰键
static uint8_t needs_shift(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= '!' && c <= '@' && c != '\'' && c != ',' && c != '.' && c != '/') ||
           (c >= '[' && c <= '`') ||
           (c >= '{' && c <= '~');
}

/**
 * @brief 将ASCII字符转换为HID键盘报告
 * @param c 输入的ASCII字符
 * @param report 输出缓冲区（必须至少17字节）
 * @return 成功返回0x00，无效字符返回0x01
 */
uint8_t ascii_to_hid_report(char c, uint8_t report[]) {

    // 检查ASCII范围
    if ((uint8_t)c > 127) return 0x01;

    // 获取HID Usage ID
    uint8_t usage = ascii_to_hid_map[(uint8_t)c];
    if (usage == 0) return 0x01;  // 无效字符

    // 初始化报告（全0）
//    memset(report, 0, 17);
    report[0] = 0x01;  // 报告ID

    // 设置修饰键（Shift）
//    if (needs_shift(c)) {
//        report[1] = 0x02;  // Left Shift
//    }

    // 在键位图中设置对应位
    if (usage != 0) {
        uint8_t byte_index = 2 + (usage / 8);   // 从第2字节开始
        uint8_t bit_position = usage % 8;
        report[byte_index] |= (1 << bit_position);
    }

    return 0x00;
}

void USB_report(){
	static uint8_t keyboard_report[17] = {0}; // 初始化为全0
	static uint8_t keyboard_report_2[17] = {0}; // 初始化为全0
	static uint8_t *p;
	static uint8_t *p_keyboard_report=keyboard_report;
	static uint8_t *p_keyboard_report_2=keyboard_report_2;
	for (int i = 0; i < 7; ++i) {
		if(Key_Target_list[i].Is_Pressed){
			ascii_to_hid_report(Key_Target_list[i].KEY_Value,p_keyboard_report);
		}

	}

	p_keyboard_report[0] = 0x01;  // 报告ID
	memset(p_keyboard_report_2, 0, 17);
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,p_keyboard_report, sizeof(keyboard_report));
	// 交换指针，确保数据一致性
	p = p_keyboard_report;
	p_keyboard_report = p_keyboard_report_2;
	p_keyboard_report_2 = p;
}
