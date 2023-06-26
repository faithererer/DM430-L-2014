/********************************************************************
//DM430-L型开发板2.8寸TFT液晶显示ADC转换结果程序，显示输入到ADC的模拟电压大小
//MSP430单片机内部12位ADC，采用内部2.5V基准，单通道单次转换，中断模式，有精度误差
//通过杜邦线将需要转换的电压加入到ADC0，也就是P60，可以更改输入电压，最大显示量2.5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/

#include <msp430x14x.h>
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息
#include "Ascii_8x16.h"                 //8x16大小字符
#include "GB2424.h"                     //24x24像素大小的汉字
#include "Chinese.h"                    //16x16像素大小的汉字
#include "TFT28.h"                      //TFT头文件
#include "TFT28.c"                      //TFT操作初始化及函数

//**************声明外部函数和变量********************
unsigned int Device_code;               //TFT控制IC型号，2.8寸为ILI9320
extern void delayms(unsigned int count);

static uchar Flag=0;                    //标志变量
uint TEMP=0;                            //ADC值暂存变量 
uchar    temp,A1,A2,A3,A4,A5,A6,A7;      //定义的变量,显示数据处理
uchar   Temp_Value[5];                  //显示用的电压数据，分离用放入数组准备调用

/********************************************************************
        初始化IO口子程序，设置TFT数据口和控制口属性
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
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


//*************************************************************************
//		数字量显示处理函数
//*************************************************************************
void Data_do(uint temp_d)
{
  uint temp_1,temp_2;
  A1=temp_d/1000;                       //分出千，百，十，和个位
  temp_1=temp_d%1000;
  A2=temp_1/100;
  temp_2=temp_1%100;
  A3=temp_2/10;
  A4=temp_2%10;
}

//*************************************************************************
//		电压数据显示处理函数
//*************************************************************************
void Voltage_do(uint temp_d)
{
  uint temp_1,temp_2;
  ulong temp_3;
  
  temp_3=(ulong)(temp_d)*250;            //转换公式，ADC数字量转换为电压大小，注意数据类型
  temp_d=temp_3/4095;                    //12位精度，除以4095
  
  A5=temp_d/100;                        //分出百，十，和个位
  temp_1=temp_d%100;
  A6=temp_1/10;
  temp_2=temp_1%10;
  A7=temp_2;
  
  Temp_Value[0]=A5+0x30;
  Temp_Value[1]='.';
  Temp_Value[2]=A6+0x30;
  Temp_Value[3]=A7+0x30;
  Temp_Value[4]='V';
}

/********************************************************************
                      温度值显示函数
********************************************************************/
void  LCD_DisplayADC()
{
  LCD_PutChar(169,0,A5+0x30,White,Black);
  LCD_PutChar(177,0,'.',White,Black);
  LCD_PutChar(185,0,A6+0x30,White,Black);
  LCD_PutChar(193,0,A7+0x30,White,Black);
  LCD_PutChar(201,0,'V',White,Black);
}

//*************************************************************************
//	ADC初始化程序，用于配置ADC相关寄存器
//*************************************************************************
void ADC_Init()
{
  P6SEL|=0x01;                                    //选择ADC通道
  ADC12CTL0|= ADC12ON + SHT0_2 + REF2_5V + REFON; //ADC电源控制开，16个CLK，内部基准2.5V
  ADC12CTL1|= ADC12SSEL1 + ADC12SSEL0;            //SMCLK做时钟源
  ADC12MCTL0= SREF0 + INCH_0;                     //参考控制位及通道选择，这里选择通道0
  ADC12IE|= 0x01;                                 //中断允许
  ADC12CTL0|= ENC;                                //使能转换器
}

//*************************************************************************
//	ADC中断服务程序
//*************************************************************************
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR(void)
{
  uchar j;
  while((ADC12CTL1&0x01)==1);           //如果ADC忙，则等待，否则读取ADC转换数值
  Flag = 1 ;
  TEMP = ADC12MEM0;                     //读取ADC转换值
  Data_do(TEMP);                        //处理ADC值，用于显示，数字量
  Voltage_do(TEMP);                     //处理ADC值，用于显示，模拟电压值
  for(j=0;j<30;j++)
  {
    LCD_DisplayADC();                    //显示ADC的电压值
  }
}

//***********************************************************************
//            主程序
//***********************************************************************
void main(void)
{ 
  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  ADC_Init();                         //初始化ADC配置
  delay_ms(100);                      //延时100ms
  Port_Init();                       //系统初始化，设置IO口属性
  LED_Light();                       //LED点亮一次，如有现象，说明单片机初始化成功   
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	 
      
  CLR_Screen(Black);               //用背景色清屏
  LCD_PutString24(35,140,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
  delay_ms(500);    
  LCD_PutString24(83,170,"欢",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(107,170,"迎",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(131,170,"您",Yellow,Black);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Black);  //字符显示官方网站
  delay_ms(300);
    
  CLR_Screen(Black);                                     //用背景色清屏
    
  LCD_PutString(0,0,"The ADC0 Voltage is : ",White,Black);  //温度显示提示字符


  _EINT();                            //使能中断
  Flag=1;                             //标志位先置1
  
  while(1)
  {
    while(Flag==1)
    {
      ADC12CTL0 |= ADC12SC;           //开启转换
      ADC12CTL0 &= ~ADC12SC;          //清零
      Flag=0;                         //清零标志位
    }
  }
}