/********************************************************************
//DM430-L型开发板使用TIMERA进行连续计数模式的实验，通过P61口输出电平变化
//程序设置TIMERA每计数到0XFFFF中断一次，每次中断取反一次P61口，对应的LED灯闪烁
//如果有示波器，可以通过示波器查看P61的信号波形
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/

#include <msp430x14x.h>
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息

uchar Flag=0;                           //标志位
uchar Time=0;                           //时间计数变量

//***********************************************************************
//               MSP430IO口初始化
//***********************************************************************
void Port_Init()
{
  P6DIR  = 0xFF;                      //设置IO口方向为输出
  LED8 = 0xFF;                        //P6口初始设置为FF
}

//***********************************************************************
//             TIMERA初始化，设置为UP模式计数
//***********************************************************************
void TIMERA_Init(void)                                   //连续计数模式，计数到0XFFFF产生中断
{
  TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC1 + TAIE;     //SMCLK做时钟源，8分频，连续计数模式，计数到0XFFFF，开中断
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
  case 10:Flag=1;break;                         //设置标志位Flag
  }
}

//*************************************************************************
//           主函数
//*************************************************************************
void main(void)
{ 
  WDT_Init();                                   //看门狗设置
  Clock_Init();                                 //系统时钟设置
  Port_Init();                                  //端口初始化
  TIMERA_Init();                                //设置TIMERA
  _EINT();
  while(1)
  {
    while(Flag)                                 //判断Flag标志位循环
    {
      Flag = 0;
      Time++;
      if(Time==1)                               //每中断一次对P61取反一次
      {
        P6OUT = ~(P6OUT&BIT1);                 //P61取反闪烁
        Time=0;
      }
    }
  }
}