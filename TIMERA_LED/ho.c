#include <msp430x14x.h>
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息


void TIMERA_Init(void)                                   //连续计数模式，计数到0XFFFF产生中断
{
  TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK做时钟源，8分频，增加计数模式，开中断
  TACCR0 = 9999;                                         //CCR0=9999，10ms中断一次
}


#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  
}



void main(){
    
}