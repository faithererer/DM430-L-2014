/********************************************************************
//DM430-L型最小系统板控制2.8寸TFT彩屏横屏显示测试程序
//将TFT插入TFT接口，朝向外，注意关闭电源后安装
//注意选择液晶的电源，位于电位器附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //配置头文件，与硬件相关的配置在这里更改
#include "GUI.h"
#include "Ascii_8x16.h"                 //8x16大小字符
#include "GB2424.h"                     //24x24像素大小的汉字
#include "Chinese.h"                    //16x16像素大小的汉字
#include "Touch.h"                      //TFT触摸操作头文件
#include "Touch.c"                      //TFT触摸操作初始化及函数
#include "TFT28.h"                      //TFT显示头文件
#include "TFT28.c"                      //TFT显示操作初始化及函数
#include "GUI.c"

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

uint Device_code;      //TFT控制IC型号，新版2.8寸为ILI9320

//**************声明外部函数和变量********************
extern void delayms(uint count);

/********************************************************************
			初始化IO口子程序
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT数据口
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT显示控制线
  
  P6SEL = 0x00;                                   //设置IO口为普通I/O模式
  P6DIR = 0xff;                                   //设置IO口方向为输出
  P6OUT = 0x00;                                   //初始设置为00,LED灯所在IO口
  
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
                      主函数
********************************************************************/
main()
{
  uint y;
  
  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  Port_Init();                       //系统初始化，设置IO口属性
  LED_Light();                       //LED点亮一次，如有现象，说明单片机初始化成功   
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
    
   while(1)                           //循环执行程序
   {
    CLR_Screen(Black);               //用背景色清屏
    LCD_PutString24(75,85,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
    delay_ms(500); 
    LCD_PutString24(115,119,"欢",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(145,119,"迎",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(175,119,"您",Yellow,Black);
    delay_ms(300);
    LCD_PutString(102,222,"www.avrgcc.com",White,Black);  	//字符显示官方网站
    delay_ms(800);  
    CLR_Screen(Black);                                       //用背景色清屏
    for(y=0;y<10;y++)
    {
      LCD_PutString(32,24*y,"宁波欣创电子科技有限公司与您同行",White,Black);   //汉字显示
      delay_ms(30);
    }
    delay_ms(300);

    Show_RGB(0,319,0,39,Blue);                          //6种颜色将屏分为6个区域
    Show_RGB(0,319,40,79,Green);
    Show_RGB(0,319,80,119,Magenta);
    Show_RGB(0,319,120,159,Black);
    Show_RGB(0,319,160,199,Yellow);
    Show_RGB(0,319,200,239,Red);
    delay_ms(300);
    delay_ms(300);
    Show_RGB(0,319,0,39,White);                         //6种颜色将屏分为6个区域
    Show_RGB(0,319,40,79,Green);
    Show_RGB(0,319,80,119,Red);
    Show_RGB(0,319,120,159,Black);
    Show_RGB(0,319,160,199,Yellow);
    Show_RGB(0,319,200,239,Magenta);
		

    LCD_PutString(108,12,"字符显示测试",Blue,White);									//第1个区域显示16x16汉字
    
    LCD_PutString(80,40,"0123456789876543210",Black,Green);         //第2个区域显示ascii字符中的数字和符号
    LCD_PutString(40,60,"+-+-**,,`,./<>';:[]{}\|?-=+*&^%$",Black,Green);

    LCD_PutString(40,80,"abcdefghijklmnopqrstuvwxyz",White,Red);    //第3个区域显示ascii字符中字母
    LCD_PutString(40,100,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",White,Red);

    LCD_PutString(30,132,"The Device IC Of TFT Is:",Yellow,Black);  //第4个区域显示TFT控制器IC型号
    LCD_PutString(222,132,"ILI",Red,Black);

    LCD_PutSingleChar(246, 132, 0x30+(Device_code>>12), Red, Black);
    LCD_PutSingleChar(254, 132, 0x30+((Device_code>>8)&0x000f), Red, Black);
    LCD_PutSingleChar(262, 132, 0x30+((Device_code>>4)&0x000f), Red, Black);
    LCD_PutSingleChar(270, 132, 0x30+(Device_code&0x000f), Red, Black);
    
    LCD_PutString(102,222,"www.avrgcc.com",White,Magenta);  	//字符显示官方网站
    delay_ms(400);                                              //显示一段时间

    CLR_Screen(Black);               																	//用背景色清屏

    GUIline(0,0,319,239,Yellow);																			  //任意画线，这里是屏幕对角线
    GUIline(319,0,0,239,Yellow);
    delay_ms(400);                                              //显示一段时间

    CLR_Screen(Black);
				
    GUIfull(0,0,159,119,Red);
    GUIfull(160,0,319,119,Green);
    GUIfull(0,120,159,239,Yellow);
    GUIfull(160,120,319,239,Magenta);
    delay_ms(400);                                              //显示一段时间

    CLR_Screen(Black);
		
    GUIDotline(0,0,319,0,Yellow);		                //画虚线边框																	  //任意画虚线，这里是屏幕边框
    GUIDotline(319,0,319,239,Yellow);																		//任意画虚线，这里是屏幕边框
    GUIDotline(0,239,319,239,Yellow);																		//任意画虚线，这里是屏幕边框
    GUIDotline(0,0,0,239,Yellow);																			  //任意画虚线，这里是屏幕边框

    GUIcircle(50,50,20,Magenta);	                        //画3个大小不同的圆																			//任意画圆形
    GUIcircle(159,119,70,Magenta);
    GUIcircle(270,150,30,Magenta);

    delay_ms(2000);                                             //显示一段时间
   }  
}