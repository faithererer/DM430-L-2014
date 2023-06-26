/********************************************************************
//DM430-L型最小系统板控制2.8寸TFT彩屏及MMC/SD卡测试程序
//将TFT插入TFT接口，朝向外，注意关闭电源后安装
//SD卡选用2GB以下，非SDHC卡，仅显示SD卡容量用于测试硬件正确
//SD卡座位于2.8寸TFT彩屏上，采用SPI控制模式，如果是自己接的SD卡，参考更改硬件配置
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
#include "SPI.c"
#include "MMC.c"

uint Device_code;      //TFT控制IC型号，新版2.8寸为ILI9320

ulong cardSize = 0;
uchar status = 1;
uint timeout = 0;
int i = 0;
uint BlockLength=512;                    //MMC/SD卡块大小，CSD寄存器记录了卡本身允许的大小，一般为512
ulong numSector=200;	                 //向SD卡中写入数据的地址，为扇区数，对于一个扇区为512字节的SD卡实际地址为numSector*512字节

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
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;       //触摸控制线，2条输入线，4条输出线
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

  while(1)                           					//循环执行程序
   {
    CLR_Screen(Black);               					//用背景色清屏
    LCD_PutString24(75,85,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
    delay_ms(500); 
    LCD_PutString24(115,119,"欢",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(145,119,"迎",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(175,119,"您",Yellow,Black);
    delay_ms(300);
    LCD_PutString(102,222,"www.avrgcc.com",White,Black);  		//字符显示官方网站
    delay_ms(800);  
    CLR_Screen(Black);                                       	//用背景色清屏

    LCD_PutString(0,0,"Starting Init SD",White,Black);  		//字符串显示调用
    LCD_PutString(0,16,"Waiting...",White,Black);  			//字符串显示调用
    delay_ms(1);
		 
		 
    while (status != 0)         					// 如果返回非零值，则表示出错，SD卡继续重新初始化                                           
  	{
    	status = InitMMC();
    	timeout++;
    	if (timeout == 50)       //初始化50次MMC/SD卡，如果依然返回错误代码，则初始化失败，可能是没有SD卡或损坏
    		{
                  LCD_PutString(0,32,"Init Failure",White,Black);       //字符串显示调用
		  LCD_PutString(0,48,"Please Check SD",White,Black);  	//字符串显示调用  		
     		}
  	}                     		 
		LCD_PutString(0,32,"Init SD Success!",White,Black);  				
	
		Print_SDSize(MMC_ReadCardSize());
		 
  while(1);
}
}