/********************************************************************
//DM430-L型最小系统板控制DS18B20温度传感器显示温度至2.8寸TFT彩屏示例程序
//直接将TFT插入对应TFT接口，注意TFT安装方向，是朝外
//注意选择液晶的电源，位于TFT接口附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//运行时D1灯会闪烁
//DS18B20读取当前环境温度，显示精度达0.1度，温度范围0-99度
//DS18B20 详细引脚功能描述1、GND 地信号；2、DQ数据输入出引脚。开漏单总线接口引脚。当被用在寄生电源下
//也可以向器件提供电源；3、VDD可选择的VDD 引脚。当工作于寄生电源时，此引脚必须接地。
//DS18B20 的使用方法。DS18B20 采用的是1－Wire 总线协议方式
//即在一根数据线实现数据的双向传输，数据脚接在P17上
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
#include "DS18B20.c"                    //DS18B20传感器相关函数
#include "TFT28.c"                      //TFT操作初始化及函数

//**************声明外部函数和变量********************
unsigned int Device_code;               //TFT控制IC型号，2.8寸为ILI9320
extern void delayms(unsigned int count);

/********************************************************************
        初始化IO口子程序，设置TFT数据口和控制口属性
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
  
  P6DIR |= (1<<0);
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

/********************************************************************
                      温度值显示函数
********************************************************************/
void  LCD_DisplayTemp(uchar A1,uchar B1,uchar C1)
{
  LCD_PutChar(169,0,A1+0x30,White,Black);
  LCD_PutChar(177,0,B1+0x30,White,Black);
  LCD_PutChar(185,0,'.',White,Black);
  LCD_PutChar(193,0,C1+0x30,White,Black);
  LCD_PutChar(201,0,'C',White,Black);
}

/********************************************************************
                      主函数
********************************************************************/
main()
{
   uint i,y,j;

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
    
    LCD_PutString(0,0,"The Temperature is : ",White,Black);  //温度显示提示字符
    
    DS18B20_Reset();			  //复位D18B20
    while(1)
    {
    ds1820_start();		          //启动一次转换
    ds1820_read_temp();		          //读取温度数值
    data_do(temp_value);                  //处理数据，得到要显示的值
    LED8 &= ~(1<<0);                      //D1灯闪烁表示正在测试温度
    for(j=0;j<30;j++)
    {	    
     LCD_DisplayTemp(A1,A2,A3);           //调用温度显示函数，分离后依次显示
     LED8 |= 1<<0;                        //LED灯闪烁
    }
   }
    
   }
 
    
}