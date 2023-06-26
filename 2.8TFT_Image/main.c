/********************************************************************
//DM430-L型最小系统板控制2.8寸TFT彩屏图片显示测试程序，仅供参考，可自行更改
//将TFT插入对应接口即可，程序比较大，BSL下载会比较慢
//注意选择液晶的电源，位于电位器附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //配置头文件，与硬件相关的配置在这里更改
#include "qqpic.h"			//80x80图形文件点阵，由Image2LCD软件生成
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
  
  P3SEL=0x00;                               //设置IO口为普通I/O模式
  P3DIR = 0xff;                             //设置IO口方向为输出
  P3OUT = 0x00;                             //初始设置为00,LED灯所在IO口
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;       //触摸控制线，P23~P26，2条输入线，4条输出线
}

/***************************************************************************************************
//	实现功能：	任意位置显示任意大小图片，前提是单片机可以装下数据
//  输入参数：  x0，y0 起始坐标
//              x1，y1 结束坐标
//  注意事项：	1、图片大小建议不要太大，最好是小图，比如40x40、80x80，太大单片机装不下
				2、图片数据是放在单片机FLASH中的，所以要用pgm_read_byte函数读取出来再送入GRAM中
				3、显示前LCD_SetPos用来设置图片显示区域，从0开始，结束坐标要减1
				4、获取数据的位置函数见具体操作函数
				5、Imag2LCD软件提取用16彩色，高字节在高位，低字节在低位，即小端数据存储格式
***************************************************************************************************/
void Show_Image(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
	unsigned int i,j;
	LCD_SetPos(x0,x1-1,y0,y1-1);      //设置显示位置
	for (i=y0-y0;i<y1-y0;i++)         //起始位置应该从0开始，便于提取数据
	{
	   for (j=x0-x0;j<x1-x0;j++)      //起始位置应该从0开始，便于提取数据
	    //小端数据格式，用pgm_read_byte函数从FLASH中读取图像数据，图像数据用Image2LCD软件提取，16位彩色
	    Write_Data(gImage_qqp[i*(x1-x0)*2+j*2+1],gImage_qqp[i*(x1-x0)*2+j*2] );//注意算法
	}
}

/***************************************************************************************************
//	实现功能：	图片动态显示效果
//  输入参数：  x0，y0 起始坐标
//              x1，y1 结束坐标
//				xm, ym x,y方向移动的像素
//				bColor为背景色，移动后清除原先的图像数据
//  注意事项：	1、图片大小建议不要太大，最好是小图，比如40x40、80x80，太大单片机装不下
				2、图片数据是放在单片机FLASH中的，所以要用pgm_read_byte函数读取出来再送入GRAM中
				3、显示前LCD_SetPos用来设置图片显示区域，从0开始，结束坐标要减1
				4、获取数据的位置函数见具体操作函数
				5、Imag2LCD软件提取用16彩色，高字节在高位，低字节在低位，即小端数据存储格式
***************************************************************************************************/
void Image_Move(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,uchar xm,uchar ym,uint bColor)
{
	uint i,j,k;
	
  for(k=0;k<7;k++)
  {
   //m=k*xm;
   //n=k*ym;
   LCD_SetPos(x0+k*xm,x1+k*xm-1,y0+k*ym,y1+k*ym-1);      //设置显示位置
	for (i=y0-y0;i<y1-y0;i++)         //起始位置应该从0开始，便于提取数据
	{
	   for (j=x0-x0;j<x1-x0;j++)      //起始位置应该从0开始，便于提取数据
	    //小端数据格式，用pgm_read_byte函数从FLASH中读取图像数据，图像数据用Image2LCD软件提取，16位彩色
	    Write_Data(gImage_qqp[i*(x1-x0)*2+j*2+1],gImage_qqp[i*(x1-x0)*2+j*2] );//注意算法
	}

	delay_ms(500);
	delay_ms(500);

	for (i=y0-y0;i<y1-y0;i++)         //起始位置应该从0开始，便于提取数据
	{
	   for (j=x0-x0;j<x1-x0;j++)      //起始位置应该从0开始，便于提取数据
	    //小端数据格式，用pgm_read_byte函数从FLASH中读取图像数据，图像数据用Image2LCD软件提取，16位彩色
	    Write_Data_U16(bColor);//注意算法
	}
  }
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
  uint i,j;
  
  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  Port_Init();                       //系统初始化，设置IO口属性
  LED_Light();                       //LED点亮一次，如有现象，说明单片机初始化成功   
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
    
  CLR_Screen(Magenta);               //用背景色清屏
  LCD_PutString24(35,140,"欣世纪电子科技",Yellow,Magenta); //欢迎界面，24x24大小汉字，字模软件隶书小二号
  delay_ms(500);    
  LCD_PutString24(83,170,"欢",Yellow,Magenta);
  delay_ms(300);
  LCD_PutString24(107,170,"迎",Yellow,Magenta);
  delay_ms(300);
  LCD_PutString24(131,170,"您",Yellow,Magenta);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Magenta);   //字符显示官方网站
  delay_ms(300);
  CLR_Screen(White);				        //清背景色
  for(i=0;i<4;i++)					//显示12个甲壳虫图标，每个80x80
   {
  	for(j=0;j<3;j++)
		{
			Show_Image(j*80,j*80+80,i*80,i*80+80);
		}
   }

  CLR_Screen(White);					//清背景色

  for(j=0;j<3;j++)            				//图形移动显示
  {
    Image_Move(0,80,0,80,15,15,White);			//每次移动15个像素，单方向移动
  }  
   
}