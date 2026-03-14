#include "OLED_UI_MenuData.h"
#include "OLED_UI.h"
#include "User_Key.h"
/*此文件用于存放菜单数据。实际上菜单数据可以存放在任何地方，存放于此处是为了规范与代码模块化*/

// ColorMode 是一个在OLED_UI当中定义的bool类型变量，用于控制OLED显示的颜色模式， DARKMODE 为深色模式， LIGHTMOOD 为浅色模式。这里将其引出是为了创建单选框菜单项。
extern bool ColorMode;
extern bool OLED_UI_ShowFps;
//extern uint8_t Trigger_Mod;
// OLED_UI_Brightness 是一个在OLED_UI当中定义的int16_t类型变量，用于控制OLED显示的亮度。这里将其引出是为了创建调整亮度的滑动条窗口，范围0-255。
extern int16_t OLED_UI_Brightness;
//extern float yaw_v,pitch_v,roll_v;
float testfloatnum = 0.5;
int16_t testintnum = 1;
#define SPEED 1



//关于窗口的结构体
MenuWindow SetBrightnessWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "屏幕亮度屏幕亮度",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 4.0,						//窗口持续时间

	.Prob_Data_Int = &OLED_UI_Brightness,				//显示的变量地址
	.Prob_DataStep = 5,								//步长
	.Prob_MinData = 5,									//最小值
	.Prob_MaxData = 255, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,								//边距
};






//关于窗口的结构体
MenuWindow adjustingWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Calibrating...",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 20.0,						//窗口持续时间

	.Prob_SideDistance = 4,								//边距
};

//关于选择RT模式窗口的结构体
MenuWindow SittingRTModWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 								//窗口高度
	.Text_String = "RT_Mod",							//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,					//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 		//窗口类型
	.General_ContinueTime = 2.0,						//窗口持续时间

	.Prob_Data_Int = (int16_t*)&User_Keyboard_Config_File.Trigger_mode,
	.Prob_MinData = 0,									//最小值
	.Prob_MaxData = 3, 									//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,								//边距
};

//关于ConfigReset结构体--
MenuWindow Config_reset = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 								//窗口高度
	.Text_String = "ConfigReset",						//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,					//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 		//窗口类型
	.General_ContinueTime = 1.0,						//窗口持续时间


	.Prob_SideDistance = 4,
};

//Draw yaw窗口的结构体
//MenuWindow YawFloatDataWindow = {
//	.General_Width = 80,								//窗口宽度
//	.General_Height = 28, 							//窗口高度
//	.Text_String = "Yaw Speed",					//窗口标题
//	.Text_FontSize = OLED_UI_FONT_12,				//字高
//	.Text_FontSideDistance = 4,							//字体距离左侧的距离
//	.Text_FontTopDistance = 3,							//字体距离顶部的距离
//	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
//	.General_ContinueTime = 4.0,						//窗口持续时间
//
//	.Prob_Data_Float = &yaw_v,				//显示的变量地址
//	.Prob_DataStep = 0.01,								//步长
//	.Prob_MinData = 0,									//最小值
//	.Prob_MaxData = 360, 								//最大值
//	.Prob_BottomDistance = 3,							//底部间距
//	.Prob_LineHeight = 8,								//进度条高度
//	.Prob_SideDistance = 4,
//};
/**
 * @brief 创建绘制yaw窗口
 */

//Draw pitch窗口的结构体
//MenuWindow PitchFloatDataWindow = {
//	.General_Width = 80,								//窗口宽度
//	.General_Height = 28, 							//窗口高度
//	.Text_String = "Pitch Speed",					//窗口标题
//	.Text_FontSize = OLED_UI_FONT_12,				//字高
//	.Text_FontSideDistance = 4,							//字体距离左侧的距离
//	.Text_FontTopDistance = 3,							//字体距离顶部的距离
//	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
//	.General_ContinueTime = 4.0,						//窗口持续时间
//
//	.Prob_Data_Float = &pitch_v,				//显示的变量地址
//	.Prob_DataStep = 0.01,								//步长
//	.Prob_MinData = 0,									//最小值
//	.Prob_MaxData = 360, 								//最大值
//	.Prob_BottomDistance = 3,							//底部间距
//	.Prob_LineHeight = 8,								//进度条高度
//	.Prob_SideDistance = 4,
//};

//Draw pitch窗口的结构体
//MenuWindow RollFloatDataWindow = {
//	.General_Width = 80,								//窗口宽度
//	.General_Height = 28, 							//窗口高度
//	.Text_String = "Roll Speed",					//窗口标题
//	.Text_FontSize = OLED_UI_FONT_12,				//字高
//	.Text_FontSideDistance = 4,							//字体距离左侧的距离
//	.Text_FontTopDistance = 3,							//字体距离顶部的距离
//	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
//	.General_ContinueTime = 4.0,						//窗口持续时间
//
//	.Prob_Data_Float = &roll_v,				//显示的变量地址
//	.Prob_DataStep = 0.01,								//步长
//	.Prob_MinData = 0,									//最小值
//	.Prob_MaxData = 360, 								//最大值
//	.Prob_BottomDistance = 3,							//底部间距
//	.Prob_LineHeight = 8,								//进度条高度
//	.Prob_SideDistance = 4,
//};




//关于窗口的结构体
MenuWindow NullWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 4.0,						//窗口持续时间
};

//关于窗口的结构体
MenuWindow TextWindow = {
	.General_Width = 75,								//窗口宽度
	.General_Height = 18, 							//窗口高度
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 4.0,						//窗口持续时间

	.Text_String = "文字text",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_16,				//字高
	.Text_FontSideDistance = 8,							//字体距离左侧的距离
	.Text_FontTopDistance = 2,							//字体距离顶部的距离
	

};

//关于窗口的结构体
MenuWindow ApplyWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Apply!",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_16,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = .5,						//窗口持续时间


};
//关于窗口的结构体
MenuWindow Down_ThresholdWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Down_Threshold",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_16,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 1.0,						//窗口持续时间

	.Prob_Data_Float = &Down_Threshold_MM,				//显示的变量地址
	.Prob_DataStep = 0.05,								//步长
	.Prob_MinData = 0,									//最小值
	.Prob_MaxData = TRAVEL_MAX_MM, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,
};//关于窗口的结构体
MenuWindow Hight_Dead_BandWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Hight_Dead_Band",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_16,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 1.0,						//窗口持续时间

	.Prob_Data_Float = &Hight_Dead_Band_MM,				//显示的变量地址
	.Prob_DataStep = 0.05,								//步长
	.Prob_MinData = 0,									//最小值
	.Prob_MaxData = TRAVEL_MAX_MM, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,
};//关于窗口的结构体
MenuWindow Low_Dead_BandaWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Low_Dead_Band",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_16,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 1.0,						//窗口持续时间

	.Prob_Data_Float = &Low_Dead_Band_MM,				//显示的变量地址
	.Prob_DataStep = 0.05,								//步长
	.Prob_MinData = 0,									//最小值
	.Prob_MaxData = TRAVEL_MAX_MM, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,
};//关于窗口的结构体
MenuWindow Up_ThresholdWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Up_Threshold",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 1.0,						//窗口持续时间

	.Prob_Data_Float = &Up_Threshold_MM,				//显示的变量地址
	.Prob_DataStep = 0.05,								//步长
	.Prob_MinData = 0,									//最小值
	.Prob_MaxData = TRAVEL_MAX_MM, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,
};//关于窗口的结构体
MenuWindow Regular_ThresholdWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "Regular_Threshold",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 1.0,						//窗口持续时间

	.Prob_Data_Float = &Regular_Threshold_MM,				//显示的变量地址
	.Prob_DataStep = 0.1,								//步长
	.Prob_MinData = 0,									//最小值
	.Prob_MaxData = TRAVEL_MAX_MM, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,
};//关于窗口的结构体
MenuWindow FloatDataWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "浮点数据测试",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 4.0,						//窗口持续时间

	.Prob_Data_Float = &testfloatnum,				//显示的变量地址
	.Prob_DataStep = 0.1,								//步长
	.Prob_MinData = -100,									//最小值
	.Prob_MaxData = 100, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,	
};

//关于窗口的结构体
MenuWindow IntDataWindow = {
	.General_Width = 80,								//窗口宽度
	.General_Height = 28, 							//窗口高度
	.Text_String = "整数数据测试",					//窗口标题
	.Text_FontSize = OLED_UI_FONT_12,				//字高
	.Text_FontSideDistance = 4,							//字体距离左侧的距离
	.Text_FontTopDistance = 3,							//字体距离顶部的距离
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//窗口类型
	.General_ContinueTime = 4.0,						//窗口持续时间

	.Prob_Data_Int = &testintnum,				//显示的变量地址
	.Prob_DataStep = 1,								//步长
	.Prob_MinData = -100,									//最小值
	.Prob_MaxData = 100, 								//最大值
	.Prob_BottomDistance = 3,							//底部间距
	.Prob_LineHeight = 8,								//进度条高度
	.Prob_SideDistance = 4,	
};

//主LOGO移动的结构体
OLED_ChangePoint LogoMove;
//主LOGO文字移动的结构体
OLED_ChangePoint LogoTextMove;
//welcome文字移动的结构体
OLED_ChangePoint WelcomeTextMove;

extern OLED_ChangePoint OLED_UI_PageStartPoint ;



//设置菜单项的辅助显示函数
void SettingAuxFunc(void){
	//在规定位置显示LOGO
	if(fabs(OLED_UI_PageStartPoint.CurrentPoint.X - OLED_UI_PageStartPoint.TargetPoint.X) < 4){
		LogoMove.TargetPoint.X = 0;
		LogoMove.TargetPoint.Y = 0;
	}
	//将LOGOTEXT移动到屏幕右侧看不见的地方
	LogoTextMove.TargetPoint.X = 129;
	LogoTextMove.TargetPoint.Y = 0;
	//将Welcome文字移动到屏幕底部看不见的地方
	WelcomeTextMove.TargetPoint.X = 128;
	WelcomeTextMove.TargetPoint.Y = 0;
	ChangePoint(&LogoMove);
	OLED_ShowImageArea(LogoMove.CurrentPoint.X,LogoMove.CurrentPoint.Y,32,64,0,0,128,128,OLED_UI_SettingsLogo);
	ChangePoint(&LogoTextMove);
	OLED_ShowImageArea(LogoTextMove.CurrentPoint.X,LogoTextMove.CurrentPoint.Y,26,64,0,0,128,128,OLED_UI_LOGOTEXT64);
	ChangePoint(&WelcomeTextMove);
	OLED_ShowImageArea(WelcomeTextMove.CurrentPoint.X,WelcomeTextMove.CurrentPoint.Y,16,64,0,0,128,128,OLED_UI_LOGOGithub);
}
//Keyboard_Settings的辅助显示函数
void Keyboard_SettingsAuxFunc(void){

	LogoMove.TargetPoint.X = 0;
	LogoMove.TargetPoint.Y = -80;
}
//关于菜单的辅助显示函数
void AboutThisDeviceAuxFunc(void){
	//将LOGO移动到屏幕上方看不见的地方
	LogoMove.TargetPoint.X = 0;
	LogoMove.TargetPoint.Y = -80;
	ChangePoint(&LogoMove);
    OLED_ShowImageArea(LogoMove.CurrentPoint.X,LogoMove.CurrentPoint.Y,32,64,0,0,128,128,OLED_UI_SettingsLogo);
	//在屏幕右侧显示LOGO文字
	if(fabs(OLED_UI_PageStartPoint.CurrentPoint.X - OLED_UI_PageStartPoint.TargetPoint.X) < 4){
		LogoTextMove.TargetPoint.X = 102;
		LogoTextMove.TargetPoint.Y = 0;
	}
	ChangePoint(&LogoTextMove);
	OLED_ShowImageArea(LogoTextMove.CurrentPoint.X,LogoTextMove.CurrentPoint.Y,26,64,0,0,128,128,OLED_UI_LOGOTEXT64);
}
//关于OLED UI的辅助显示函数
void AboutOLED_UIAuxFunc(void){
	//将LOGO移动到屏幕上方看不见的地方
	LogoMove.TargetPoint.X = 0;
	LogoMove.TargetPoint.Y = -80;
	ChangePoint(&LogoMove);
	OLED_ShowImageArea(LogoMove.CurrentPoint.X,LogoMove.CurrentPoint.Y,32,64,0,0,128,128,OLED_UI_SettingsLogo);
	//在屏幕右测显示Welcome文字
	if(fabs(OLED_UI_PageStartPoint.CurrentPoint.X - OLED_UI_PageStartPoint.TargetPoint.X) < 4){
		WelcomeTextMove.TargetPoint.X = 110;
		WelcomeTextMove.TargetPoint.Y = 0;
	}
	ChangePoint(&WelcomeTextMove);
	OLED_ShowImageArea(WelcomeTextMove.CurrentPoint.X,WelcomeTextMove.CurrentPoint.Y,16,64,0,0,128,128,OLED_UI_LOGOGithub);

}
//关于Draw的辅助显示函数
void DrawAuxFunc(void){
	DrawCube3D(96, 32, 24, 0); // 平行投影
}
//主菜单的辅助显示函数
void MainAuxFunc(void){
	//不显示
	LogoMove.TargetPoint.X = -200;
	LogoMove.TargetPoint.Y = 0;
	LogoMove.CurrentPoint.X = -200;
	LogoMove.CurrentPoint.Y = 0;

	LogoTextMove.TargetPoint.X = 129;
	LogoTextMove.TargetPoint.Y = 0;
	LogoTextMove.CurrentPoint.X = 129;
	LogoTextMove.CurrentPoint.Y = 0;
	
	WelcomeTextMove.TargetPoint.X = 128;
	WelcomeTextMove.TargetPoint.Y = 0;
	WelcomeTextMove.CurrentPoint.X = 128;
	WelcomeTextMove.CurrentPoint.Y = 0;
}




MenuPage MainMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_TILES,  		 //菜单类型为磁贴类型
	.General_CursorStyle = NOT_SHOW,			 //光标类型
	.General_FontSize = OLED_UI_FONT_16,			//字高
	.General_ParentMenuPage = NULL,				//由于这是根菜单，所以父菜单为NULL
	.General_LineSpace = 5,						//磁贴间距 单位：像素（对于磁贴类型菜单，此值表示每个磁贴之间的间距，对于列表类型菜单，此值表示行间距）
	.General_MoveStyle = UNLINEAR,				//移动方式
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = MainAuxFunc,		 //显示辅助函数
	.General_MenuItems = MainMenuItems,			//菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.Tiles_ScreenHeight = 64,					//屏幕高度
	.Tiles_ScreenWidth = 128,						//屏幕宽度
	.Tiles_TileWidth = 32,						 //磁贴宽度
	.Tiles_TileHeight = 32,						 //磁贴高度
};
MenuPage SettingsMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MainMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 3,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = SettingAuxFunc,		 //显示辅助函数
	.General_MenuItems = SettingsMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {32, 0, 95, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标
};



MenuPage AdjustingPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = NOT_SHOW,	 //光标类型
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &Keyboard_SettingsMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = AdjustingAuxFunc,		 //显示辅助函数
	.General_MenuItems = KeyboardSnowItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {32, 0, 95, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标
};


MenuPage AboutThisDeviceMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_BLOCK,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &SettingsMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = AboutThisDeviceAuxFunc,		 //显示辅助函数
	.General_MenuItems = AboutThisDeviceMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 100, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = false,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};
MenuPage Keyboard_SettingsMenuPage = {
		//通用属性，必填
		.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
		.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为
		.General_FontSize = OLED_UI_FONT_16,			//字高
		.General_ParentMenuPage = &SettingsMenuPage,		 //父菜单为设置
		.General_LineSpace = 2,						//行间距 单位：像素
		.General_MoveStyle = UNLINEAR,				//移动动画
		.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
		.General_ShowAuxiliaryFunction = Keyboard_SettingsAuxFunc,		 //显示辅助函数
		.General_MenuItems = Keyboard_SettingsMenuItems,		 //菜单项内容数组

		//特殊属性，根据.General_MenuType的类型选择
		.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
		.List_IfDrawFrame = false,					 //是否显示边框
		.List_IfDrawLinePerfix = false,				 //是否显示行前缀
		.List_StartPointX = 4,                        //列表起始点X坐标
		.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage KeyboardSnowPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = NOT_SHOW,	 //光标类型
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MainMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = KeyboardSnowAuxFunc,		 //显示辅助函数
	.General_MenuItems = KeyboardSnowItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 0, 0},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标
};

MenuPage AboutOLED_UIMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_BLOCK,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &SettingsMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = AboutOLED_UIAuxFunc,		 //显示辅助函数
	.General_MenuItems = AboutOLED_UIMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 105, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = false,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage DrawMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为线型
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MainMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = DrawAuxFunc,		 //显示辅助函数
	.General_MenuItems = DrawMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 64, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标
};

MenuPage MoreMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MainMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = MoreMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {1, 1, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage Font8MenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_8,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 5,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = Font8MenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage Font12MenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = Font12MenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage Font16MenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_16,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 5,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = Font16MenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {1, 1, 126, 62},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage Font20MenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_20,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 10,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = Font20MenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage LongMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = LongMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage SpringMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = PID_CURVE,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = SpringMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage LongListMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 4,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = LongListMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {0, 0, 128, 64},			 //列表显示区域
	.List_IfDrawFrame = false,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};

MenuPage SmallAreaMenuPage = {
	//通用属性，必填
	.General_MenuType = MENU_TYPE_LIST,  		 //菜单类型为列表类型
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //光标类型为圆角矩形
	.General_FontSize = OLED_UI_FONT_12,			//字高
	.General_ParentMenuPage = &MoreMenuPage,		 //父菜单为主菜单
	.General_LineSpace = 6,						//行间距 单位：像素
	.General_MoveStyle = UNLINEAR,				//移动方式为非线性曲线动画
	.General_MovingSpeed = SPEED,					//动画移动速度(此值根据实际效果调整)
	.General_ShowAuxiliaryFunction = NULL,		 //显示辅助函数
	.General_MenuItems = SmallAreaMenuItems,		 //菜单项内容数组

	//特殊属性，根据.General_MenuType的类型选择
	.List_MenuArea = {10, 10, 60, 36},			 //列表显示区域
	.List_IfDrawFrame = true,					 //是否显示边框
	.List_IfDrawLinePerfix = true,				 //是否显示行前缀
	.List_StartPointX = 4,                        //列表起始点X坐标
	.List_StartPointY = 2,                        //列表起始点Y坐标

};


void FadjustingWindow(void){
	extern uint16_t mx_pBuffer[7][2];//0x 1m

	for(int n=0;n<7;n++){//初始化
		mx_pBuffer[n][0]=1000;
		mx_pBuffer[n][1]=30000;
	}
}
///*
//* @brief 创建绘制yaw窗口
//*/
//void ShowRollFloatDataWindow(void){
//	OLED_UI_CreateWindow(&RollFloatDataWindow);
//}

void Sitting_RT_Mod_Window(void){
	OLED_UI_CreateWindow(&SittingRTModWindow);
}
/**
 * @brief 创建显示亮度窗口
 */
void EmptyWindow(void){
	OLED_UI_CreateWindow(&NullWindow);
}

/**
 * @brief 创建显示亮度窗口
 */
void ShowIntDataWindow(void){
	OLED_UI_CreateWindow(&IntDataWindow);
}

/**
 * @brief 创建绘制yaw窗口
 */
//void ShowPitchFloatDataWindow(void){
//	OLED_UI_CreateWindow(&PitchFloatDataWindow);
//}

/**
 * @brief 创建显示Float窗口
 */
void ShowDown_ThresholdWindow(void){
	OLED_UI_CreateWindow(&Down_ThresholdWindow);
}
void ShowApplyWindow(void){
	Save_Keyboard_Config();
	OLED_UI_CreateWindow(&ApplyWindow);
}


/**
 * @brief 创建显示Down_Threshold窗口
 */
void ShowHight_Dead_BandWindow(void){
	OLED_UI_CreateWindow(&Hight_Dead_BandWindow);
}/**
 * @brief 创建显示Hight_Dead_Band窗口
 */
void ShowLow_Dead_BandaWindow(void){
	OLED_UI_CreateWindow(&Low_Dead_BandaWindow);
}/**
 * @brief 创建显示Low_Dead_Band窗口
 */
void ShowUp_ThresholdWindow(void){
	OLED_UI_CreateWindow(&Up_ThresholdWindow);
}/**
 * @brief 创建显示Up_Threshold窗口
 */
void ShowRegular_ThresholdWindow(void){
	OLED_UI_CreateWindow(&Regular_ThresholdWindow);
}/**
 * @brief 创建显示Regular_Threshold窗口
 */
void ShowFloatDataWindow(void){
	OLED_UI_CreateWindow(&FloatDataWindow);
}
//void ShowYawFloatDataWindow(void){
//	OLED_UI_CreateWindow(&YawFloatDataWindow);
//}
/**
 * @brief 创建显示亮度窗口
 */
void BrightnessWindow(void){
	OLED_UI_CreateWindow(&SetBrightnessWindow);
}


/**
 * @brief 创建显示亮度窗口
 */
void ShowTextWindow(void){
	OLED_UI_CreateWindow(&TextWindow);
}
void ConfigReset(){
	Keyboard_Config_reset();
	OLED_UI_CreateWindow(&Config_reset);

}
void Keyboard_Config_reset_Fun(){
	Keyboard_Config_reset();
	BackEventMenuItem();

}

void KeyboardSnowAuxFunc(void){
//	  OLED_Clear();
	  for(int i=0;i<7;i++){
		  char ADC_Data[21]={0};
		  if(User_Keyboard_Config_File.Other){
		    sprintf(ADC_Data, "[%c]<%04d>",Key_Target_list[i].KEY_Value, (int)Key_Target_list[i].Travel);
		    OLED_ShowString(0, i*8+i, ADC_Data, OLED_6X8_HALF );
		    OLED_DrawRoundedRectangle(55,i*8+i,128-55, 7,3, OLED_UNFILLED);
		    OLED_DrawRoundedRectangle(55+1,i*8+i+2, (int16_t)(Key_Target_list[i].Travel/4000*(128-55)-1), 3,1,OLED_FILLED);
		  }else{
		  sprintf(ADC_Data, "[%c]",Key_Target_list[i].KEY_Value);

		    OLED_ShowString(0, i*8+i, ADC_Data, OLED_6X8_HALF );
		    OLED_DrawRoundedRectangle(24,i*8+i,128-24, 7,3, OLED_UNFILLED);
		    OLED_DrawRoundedRectangle(24+1,i*8+i+2, (int16_t)(Key_Target_list[i].Travel/4000*(128-24)-1), 3,1,OLED_FILLED);
		  }
		    if(Key_Target_list[i].Is_Pressed){
				OLED_ReverseArea(1, i*8+i,17,7);
		    }
	  }
//	  OLED_Update();
}

void AdjustingAuxFunc(void){
	extern	uint16_t mx_pBuffer[7][2];
 	for(int n=0;n<7;n++){
		if(ADC_Value[n]>mx_pBuffer[n][0]){
			mx_pBuffer[n][0]=ADC_Value[n];//max
		}
		if(ADC_Value[n]<mx_pBuffer[n][1]){
			mx_pBuffer[n][1]=ADC_Value[n];
		}
	}
 	char ADC_Data[21]={0};
	for(int i=0;i<7;i++){
	    sprintf(ADC_Data, "%c{%d>%d}%d",Key_Target_list[i].KEY_Value,mx_pBuffer[i][0],mx_pBuffer[i][1],ADC_Value[i]);
	    OLED_ShowString(0, i*8+i, ADC_Data, OLED_6X8_HALF );
	}
}
;
//菜单选项
//主菜单的菜单项
MenuItem MainMenuItems[] = {

	{.General_item_text = "Settings",.General_callback = NULL,.General_SubMenuPage = &SettingsMenuPage,.Tiles_Icon = Image_setings},
	{.General_item_text = "KeyboardSnow",.General_callback = NULL,.General_SubMenuPage = &KeyboardSnowPage,.Tiles_Icon = Image_KeyboardSnow},
	{.General_item_text = "More",.General_callback = NULL,.General_SubMenuPage = &MoreMenuPage,.Tiles_Icon = Image_more},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/

};
MenuItem KeyboardSnowItems[]={
		{.General_item_text = " ",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/

};
//设置菜单项内容数组
MenuItem SettingsMenuItems[] = {
	{.General_item_text = "亮度",.General_callback = BrightnessWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL,.List_IntBox = &OLED_UI_Brightness},
	{.General_item_text = "黑暗模式",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = &ColorMode},
	{.General_item_text = "显示帧率",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = &OLED_UI_ShowFps},
//	{.General_item_text = "UI_TEST",.General_callback = NULL,.General_SubMenuPage = &DrawMenuItems,.List_BoolRadioBox = NULL},
	{.General_item_text = "此设备",.General_callback = NULL,.General_SubMenuPage = &AboutThisDeviceMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "Keyboard_Settings",.General_callback = NULL,.General_SubMenuPage = &Keyboard_SettingsMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "关于OLED UI",.General_callback = NULL,.General_SubMenuPage = &AboutOLED_UIMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "感谢观看,一键三连! Thanks for watching, three clicks!",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem Keyboard_SettingsMenuItems[] = {
		{.General_item_text = "RT模式",.General_callback = Sitting_RT_Mod_Window,.General_SubMenuPage = NULL,.List_BoolRadioBox =NULL,.List_IntBox = NULL},
		{.General_item_text = "更多信息",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = &User_Keyboard_Config_File.Other},
		{.General_item_text = "DownThreshold",.General_callback = ShowDown_ThresholdWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "HightDeadBand",.General_callback = ShowHight_Dead_BandWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "LowDeadBand",.General_callback = ShowLow_Dead_BandaWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "UpThreshold",.General_callback = ShowUp_ThresholdWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "RegularThreshold",.General_callback = ShowRegular_ThresholdWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "Adjusting",.General_callback = NULL,.General_SubMenuPage = &AdjustingPage,.List_BoolRadioBox = NULL},
		{.General_item_text = "ConfigReset",.General_callback = ConfigReset,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "Apply",.General_callback = ShowApplyWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "[break]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
		{.General_item_text = "[save and break]",.General_callback = Save_Keyboard_Config,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

		{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/

};


MenuItem AboutThisDeviceMenuItems[] = {
	{.General_item_text = "-[MCU:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " STM32G431",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " RAM:192+4KB",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " ROM:1024KB",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[Screen:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " SSD1306 128x64 OLED",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[CP:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " HardWare SPI",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem AboutOLED_UIMenuItems[] = {
	{.General_item_text = "-[Author:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " bilibili @上nm网课呢 @5AKURA1.",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[Version:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " Ver.0.2.1",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[Adress:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " https://github.com/bdth-7777777/OLED_UI",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem DrawMenuItems[] = {
//	{.General_item_text = "Yaw",.General_callback = ShowYawFloatDataWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL,.List_FloatBox = &yaw_v},
//	{.General_item_text = "Pitch",.General_callback = ShowPitchFloatDataWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL,.List_FloatBox = &pitch_v},

	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem MoreMenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "字体高度8demo",.General_callback = NULL,.General_SubMenuPage = &Font8MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "字体高度12demo",.General_callback = NULL,.General_SubMenuPage = &Font12MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "字体高度16demo",.General_callback = NULL,.General_SubMenuPage = &Font16MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "字体高度20demo",.General_callback = NULL,.General_SubMenuPage = &Font20MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "超长文本demo",.General_callback = NULL,.General_SubMenuPage = &LongMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "回弹动画demo",.General_callback = NULL,.General_SubMenuPage = &SpringMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "超长菜单列表demo",.General_callback = NULL,.General_SubMenuPage = &LongListMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "超小区域菜单demo",.General_callback = NULL,.General_SubMenuPage = &SmallAreaMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "空窗口demo",.General_callback = EmptyWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "文字窗口demo",.General_callback = ShowTextWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "浮点数进度条窗口demo",.General_callback = ShowFloatDataWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "整数进度条窗口demo",.General_callback = ShowIntDataWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem Font8MenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem Font12MenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem Font16MenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem Font20MenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem LongMenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "非常非常非常长中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Very Very Very Long English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem SpringMenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem LongListMenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item1",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item2",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item3",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item4",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item5",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item6",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};

MenuItem SmallAreaMenuItems[] = {
	{.General_item_text = "[返回]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "中文文本",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*最后一项的General_item_text置为NULL，表示该项为分割线*/
};



