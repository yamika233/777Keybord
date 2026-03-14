#ifndef __OLED_UI_MENUDATA_H
// 检测是否是C++编译器
#ifdef __cplusplus
extern "C" {
#endif
#include "OLED_UI.h"

//进行前置声明
extern MenuItem MainMenuItems[],
	KeyboardSnowItems[],
	SettingsMenuItems[],
	AboutThisDeviceMenuItems[],
	Keyboard_SettingsMenuItems[],
	AboutOLED_UIMenuItems[],
	DrawMenuItems[],
	MoreMenuItems[],
	Font8MenuItems[] ,
	Font12MenuItems[] ,
	Font16MenuItems[] ,
	Font20MenuItems[],
	LongMenuItems[],
	SpringMenuItems[],
	LongListMenuItems[],
	SmallAreaMenuItems[];

extern MenuPage MainMenuPage,
	SettingsMenuPage,
	AboutThisDeviceMenuPage,
	Keyboard_SettingsMenuPage,
	KeyboardSnowPage,
	AboutOLED_UIMenuPage,
	DrawMenuPage,
	MoreMenuPage,
	Font8MenuPage,
	Font12MenuPage,
	Font16MenuPage,
	Font20MenuPage,
	LongMenuPage,
	SpringMenuPage,
	LongListMenuPage,
	SmallAreaMenuPage;

extern MenuWindow adjustingWindow,SittingRTModWindow;


void KeyboardSnowAuxFunc(void);
void AdjustingAuxFunc();
void FadjustingWindow(void);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
#define __OLED_UI_MENUDATA_H
