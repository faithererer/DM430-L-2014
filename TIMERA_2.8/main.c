/********************************************************************
//DM430-L型开发板使用TIMERA进行UP定时模式实验，最大定时99秒,通过2.8寸彩屏显示
//程序设置TIMERA每10ms中断一次，定时数据显示在彩屏上，请直接查看时间值
//LED灯D2会每一秒闪烁一次，配合时间进行，便于没有TFT彩屏的客户查看
//只进行了秒数据定时，如果想实现时钟，请加上小时以及分判断等就可以了
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/

#include <msp430x14x.h>
#include "Config.h"                      //开发板配置头文件，主要配置IO端口信息
#include "Ascii_8x16.h"                 //8x16大小字符
#include "GB2424.h"                     //24x24像素大小的汉字
#include "Chinese.h"                    //16x16像素大小的汉字
#include "TFT28.h"                      //TFT头文件
#include "TFT28.c"                      //TFT操作初始化及函数

uchar Flag=0;                            //标志位
uchar Count=0;                           //时间计数变量
uchar Second=0;                          //秒时间变量
uint Device_code;                       //TFT控制IC型号，2.8寸为ILI9320
//***********************************************************************
//               MSP430IO口初始化
//***********************************************************************
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
  
  P6DIR  = 0xFF;                      //设置IO口方向为输出
  LED8 = 0xFF;                        //P6口初始设置为FF
}

//*************************************************************************
//	    显示函数
//*************************************************************************

void Display_Time(uchar Time)
{
  
  LCD_PutChar(112,0,Time/10+0x30,White,Black);
  LCD_PutChar(120,0,Time%10+0x30,White,Black);
  LCD_PutChar(128,0,'s',White,Black);
                 
}

//***********************************************************************
//             TIMERA初始化，设置为UP模式计数
//***********************************************************************
void TIMERA_Init(void)                                   //UP模式计数，计数周期为CCR0+1
{
  TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK做时钟源，8分频，增加计数模式，开中断
  TACCR0 = 9999;                                          //CCR0=9999，10ms中断一次
}

//***********************************************************************
//             TIMERA中断服务程序，需要判断中断类型
//***********************************************************************
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch(TAIV)                                  //需要判断中断的类型
  {
  case 2:break;
  case 4:break;
  case 10:Count++;break;                         //设置标志位Flag
  }
  if(Count==100)                                 //100次为1秒
  {
    Second++;
    Count=0;
    P6OUT = ~(P6OUT&BIT1);                        //P61取反闪烁
  }
  while(Second>99)Second=0;                       //最大计数99秒
}

//*************************************************************************
//           主函数
//*************************************************************************
void main(void)
{ 
  WDT_Init();                                   //看门狗设置
  Clock_Init();                                 //系统时钟设置
  Port_Init();                                  //端口初始化
  TIMERA_Init();                                //设置TIMERA，P12输出PWM信号
  Device_code=0x9320;                           //TFT控制IC型号
  TFT_Initial();                                //初始化LCD	
  CLR_Screen(Black);                          //用背景色清屏
  LCD_PutString24(35,140,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
  delay_ms(500);    
  LCD_PutString24(83,170,"欢",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(107,170,"迎",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(131,170,"您",Yellow,Black);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Black);     //字符显示官方网站
  delay_ms(300);
    
  CLR_Screen(Black);                                      //用背景色清屏
    
  LCD_PutString(0,0,"The Time is : ",White,Black);        //走时显示提示字符
  
  _EINT();                                                //开中断
  while(1)
  {
    Display_Time(Second);                                  //显示时间值，最大99秒，然后清零
  }
}