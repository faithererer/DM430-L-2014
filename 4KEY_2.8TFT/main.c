/********************************************************************
//DM430-L型最小系统板4位独立按键显示键值到2.8寸TFT彩屏
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
#include "TFT28.h"                      //TFT头文件
#include "TFT28.c"                      //TFT操作初始化及函数

//******************全局变量***************************
unsigned int Device_code;               //TFT控制IC型号，2.8寸为ILI9320
extern void delayms(unsigned int count);
uchar key;

/********************************************************************
			初始化IO口子程序
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;                   //TFT数据口
  P4DIR = 0xFF;
  P5SEL = 0x00;                   //TFT控制口
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
  
  P1SEL = 0x00;                   //P1普通IO功能
  P1DIR = 0xF0;                   //P10~P13输入模式，外部电路已接上拉电阻
  P6SEL = 0x00;                   //P6口普通IO功能
  P6DIR = 0xFF;                   //P6口输出模式
}

/********************************************************************
	LED闪烁一次，可在需要查看程序执行位置时灵活设置，类似断点
********************************************************************/
void LED_Light()
{
    LED8=0x00;                    //点亮LED
    delay_ms(500);
    LED8=0xff;                    //熄灭LED
    delay_ms(500);
}

//**********************************************************************
//	键盘扫描子程序，采用逐键扫描的方式
//**********************************************************************

uchar Key_Scan(void) 
{
  uchar key_check;
  uchar key_checkin;
  key_checkin=KeyPort;          	//读取IO口状态，判断是否有键按下
  key_checkin&= 0x0F;          		//读取IO口状态，判断是否有键按下
  if(key_checkin!=0x0F)            	//IO口值发生变化则表示有键按下
    {
      delay_ms(20);                  	//键盘消抖，延时20MS
      key_checkin=KeyPort;
      if(key_checkin!=0x1F)
        {  
          key_check=KeyPort;
          switch (key_check & 0x0F)
            {
              case 0x0E:key=1;break;
              case 0x0D:key=2;break;
              case 0x0B:key=3;break;
              case 0x07:key=4;break;
            }
          
        }
      
   }
  else
   {
     key=0xFF;        
   }
  return key;
} 

/********************************************************************
                     键值显示函数
********************************************************************/
void  LCD_DisplayKey(uchar Key_num)
{
  LCD_PutChar(129,0,Key_num+0x30,White,Black);
}

/********************************************************************
                      主函数
********************************************************************/
main()
{
   uint i,y;

  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  Port_Init();                       //系统初始化，设置IO口属性
  LED_Light();                       //LED点亮一次，如有现象，说明单片机初始化成功   
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	 

  while(1)                           //循环执行程序
   {
        
    CLR_Screen(Magenta);               //用背景色清屏
    LCD_PutString24(35,140,"欣世纪电子科技",Yellow,Magenta); //欢迎界面，24x24大小汉字，字模软件隶书小二号
    delay_ms(500);    
    LCD_PutString24(83,170,"欢",Yellow,Magenta);
    delay_ms(300);
    LCD_PutString24(107,170,"迎",Yellow,Magenta);
    delay_ms(300);
    LCD_PutString24(131,170,"您",Yellow,Magenta);
    delay_ms(300);
    LCD_PutString(69,300,"www.avrgcc.com",White,Magenta);  //字符显示官方网站
    delay_ms(300);
    
    CLR_Screen(Black);                                     //用背景色清屏
    
    LCD_PutString(0,0,"The KeyNum is : ",White,Black);  //温度显示提示字符

    while(1)
    {
      Key_Scan();                       //键盘扫描，看是否有按键按下
      if(key!=0xff)                     //如果有按键按下，则显示该按键键值1～4
        {
	  {
            switch(key)
              {
	        case 1: LED8 = 0xFC;LCD_DisplayKey(1);break;     //给不同的键赋键值，键值1，亮2个LED灯
                case 2: LED8 = 0xF3;LCD_DisplayKey(2);break;     //给不同的键赋键值，键值2，亮2个LED灯
                case 3: LED8 = 0xCF;LCD_DisplayKey(3);break;	 //给不同的键赋键值，键值3，亮2个LED灯
                case 4: LED8 = 0x3F;LCD_DisplayKey(4);break;	 //给不同的键赋键值，键值4，亮2个LED灯
              }

          }
	
       }
     else
      {
        //LED=key;              	//没有按键的时候显示上次的键值
      }
    }

    
   }
 
    
}