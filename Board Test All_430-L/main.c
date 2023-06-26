/********************************************************************
//DM430-L系统板整体功能测试程序，四种模式，基本可以兼顾测试到所有外部模块
//按不同的按键，显示不同的LED灯，具体请看程序
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2013.05.19
********************************************************************/

#include <msp430x14x.h>         //430头文件
#include "Config.h"             //板载外部资源配置头文件
#include "LED8.h"               
#include "18B20.h"
#include "LCD1602.h"               
#include "LCD12864.h"
#include "UART.h"
#include "TestNoLCD.h"
#include "Ascii_8x16.h"                 //8x16大小字符
#include "GB2424.h"                     //24x24像素大小的汉字
#include "Chinese.h"                    //16x16像素大小的汉字
#include "TFT28.h"                      //TFT头文件
#include "TFT28.c"                      //TFT操作初始化及函数
#include "Touch.h"                      //TFT触摸头文件
#include "Touch.c"                      //TFT触摸相关函数
#include "GUI.h"                        //TFT绘图头文件
#include "GUI.c"                        //TFT绘图相关函数
#include "SPI.c"
#include "MMC.c"
#include "TFT28Show.h" 
#include "TestLCD.h"

uchar TestMode=0x00;            //测试模式变量，共4种测试模式

#define TestMode_Ex32768 (0x01) //外部32.678K晶振测试模式
#define TestMode_Inc     (0x02) //内部RC晶振测试模式
#define TestMode_NoLCD   (0x03) //无液晶显示器测试模式
#define TestMode_LCD     (0x04) //带液晶显示测试模式


//*************************************************************************
//		主程序
//*************************************************************************

void main(void)
{     
  WDT_Init();                            //看门狗设置
  Clock_Init();
  LED8Port_Init();
  while(1){
  
  while(Key_Scan()==0xff);               //等待按键按下选择测试模式
  
  if(Key_Scan()==1)                      //S1按下，测试外部低频晶振32.768K
  {
    Clock_Init_Ex32768();
    TestMode = TestMode_Ex32768;
    key=0xff;
    delay_ms(1);
  }
  if(Key_Scan()==2)                      //S2按下，测试内部RC晶振是否正常
  {
    Clock_Init_Inc();
    TestMode = TestMode_Inc;
    key=0xff;
    delay_ms(20);
  }
  if(Key_Scan()==3)                      //S3按下，测试没有液晶显示时部分功能，为方便没有配TFT液晶的客户测试整版功能
  {
    Clock_Init();
    TestMode = TestMode_NoLCD;
    key=0xff;
    delay_ms(20);
  }
  if(Key_Scan()==4)                      //S4按下，配TFT液晶时的测试，包含更多内容，比如可以显示温度值等，具体看执行
  {
    Clock_Init();
    TestMode = TestMode_LCD;
    key=0xff;
    delay_ms(20);
  }

  switch(TestMode)
  {
    case TestMode_Ex32768: LED8_Run_1Time();Clock_Init_Inc();break; //流水显示8个LED灯，随后切换到内部RC晶振，避免按键检测时间过长
    case TestMode_Inc: LED8_8();Clock_Init();break;              //8个LED灯闪烁，随后切换到外部高频晶振
    case TestMode_NoLCD: LED8=0xFE;TestMode_NoLCDFunction();break;//点亮D1，进入其他功能测试模式
    case TestMode_LCD: LED8=0x7F;TestMode_LCDFunction();break;//点亮D8，进入带TFT的功能测试模式
  }
  
  }

 }

