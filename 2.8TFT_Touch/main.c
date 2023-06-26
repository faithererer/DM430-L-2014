/********************************************************************
//DM430-L型最小系统板控制2.8寸TFT彩屏触摸显示测试程序
//直接将TFT插入对应TFT接口，注意TFT安装方向，是朝外
//注意选择液晶的电源，位于TFT接口附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //配置头文件，与硬件相关的配置在这里更改
#include "Ascii_8x16.h"                 //8x16大小字符
#include "GB2424.h"                     //24x24像素大小的汉字
#include "Chinese.h"                    //16x16像素大小的汉字
#include "Touch.h"                      //TFT触摸操作头文件
#include "Touch.c"                      //TFT触摸操作初始化及函数
#include "TFT28.h"                      //TFT显示头文件
#include "TFT28.c"                      //TFT显示操作初始化及函数

//******************全局变量***************************
#define White          0xFFFF           //显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

uint Device_code;                       //TFT控制IC型号，2.8寸为ILI9320

//**************声明外部函数和变量********************
extern void delayms(unsigned int count);

/********************************************************************
			初始化IO口子程序
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT数据口
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT显示控制线
  
  P6SEL=0x00;                               //设置IO口为普通I/O模式
  P6DIR = 0xff;                             //设置IO口方向为输出
  P6OUT = 0x00;                             //初始设置为00,LED灯所在IO口
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;       //触摸控制线，P60~P64，2条输入线，4条输出线
}

/********************************************************************
	LED闪烁一次，可在需要查看程序执行位置时灵活设置，类似断点
********************************************************************/
void LED_Light()
{
    LED8=0x00;                              //点亮LED
    delay_ms(500);
    LED8=0xff;                              //熄灭LED
    delay_ms(500);
}

/********************************************************************
     	      在触摸点位置画点
********************************************************************/
void drawpoint(unsigned int x,unsigned int y,unsigned int color)
{
    LCD_SetPos(x,x+1,y,y+1);
    Write_Data_U16(color);
    Write_Data_U16(color);
    Write_Data_U16(color);
    Write_Data_U16(color);
} 

/********************************************************************
                      主函数
********************************************************************/
main()
{
  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  Port_Init();                       //系统初始化，设置IO口属性
  LED_Light();                       //LED点亮一次，如有现象，说明单片机初始化成功   
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
  start_7843();                      //打开触摸功能
    
  CLR_Screen(Black);               //用背景色清屏
  LCD_PutString24(35,140,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
  delay_ms(500);    
  LCD_PutString24(83,170,"欢",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(107,170,"迎",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(131,170,"您",Yellow,Black);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Black);   //字符显示官方网站
  delay_ms(300);

  CLR_Screen(Blue);                                       //清屏				
  LCD_PutString(16,5,"Please write on the board!",Magenta,Blue);
  
  while(1)
  {	
    if(Getpix()==1)   drawpoint(lx,ly,White);             //写（x，y）点为白色
  }
   
}