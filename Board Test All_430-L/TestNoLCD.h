//***********************************************************************
//               MSP430IO口初始化
//***********************************************************************
#include <msp430x14x.h>

extern uchar key=0xff;

//*************************************************************************
//	初始化IO口子程
//*************************************************************************
void KeyPort_Init()
{

  P1SEL = 0x00;                   //P1普通IO功能
  P1DIR &= 0xF0;                  //P10~P13输入模式，外部电路已接上拉电阻
}

//**********************************************************************
//	键盘扫描子程序，采用逐键扫描的方式
//**********************************************************************

uchar Key_Scan(void) 
{
  uchar key_check;
  uchar key_checkin;
  
  KeyPort_Init();                        //系统初始化，设置IO口属性
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
//**********************************************************************
//  无TFT彩屏时系统板测试功能函数，主要测试1602、12864、DS18B20、UART
//**********************************************************************
void TestMode_NoLCDFunction()
{
  delay_ms(200);
  while(1)
    {  
      while(Key_Scan()==0xff);               //等待按键按下选择测试模式
      if(key!=0xff)                     //如果有按键按下，则显示该按键键值1～4
        {
	  {
            switch(key)
              {
	        case 1: Test_LCD1602();break;  //给不同的键赋键值，键值1，亮2个LED灯
                case 2: Test_LCD12864();break;    //给不同的键赋键值，键值2，亮2个LED灯
                case 3: Test_DS18B20();break;	 //给不同的键赋键值，键值3，亮2个LED灯
                case 4: Test_UART();break;	 //给不同的键赋键值，键值4，亮2个LED灯
              }

          }
	
       }
     else
      {
        //LED=key;              	//没有按键的时候显示上次的键值
      }
    }
  
}