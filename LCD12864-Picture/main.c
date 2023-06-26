/********************************************************************
//DM430-L型系统板控制带字库型12864液晶模块显示测试程序，显示2幅图片
//请注意安装位置，左边有字符说明，为靠近1602接口的1X20座子
//注意选择液晶的电源，位于电位器附近，可选5V或3.3V，根据液晶电压进行选择，默认5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"
#include "Picture.c"

#define X1address       0x80        //12864上半屏X轴起始地址
#define X2address       0x88        //12864下半屏X轴起始地址
#define Yaddress        0x80        //Y轴起始地址

//*************************************************************************
//	初始化IO口子程序
//*************************************************************************
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT5 + BIT6 + BIT7;
  PSB_SET;		          //液晶并口方式
  RST_SET;		          //复位脚RST置高
}

//***********************************************************************
//	显示屏命令写入函数
//***********************************************************************
void LCD_write_com(unsigned char com) 
{	
  RS_CLR;
  RW_CLR;
  EN_SET;
  DataPort = com;
  delay_us(10);
  EN_CLR;
}

//***********************************************************************
//	显示屏数据写入函数
//***********************************************************************
void LCD_write_data(unsigned char data) 
{
  RS_SET;
  RW_CLR;
  EN_SET;
  DataPort = data;
  delay_us(10);
  EN_CLR;
}

//***********************************************************************
//	显示屏清空显示
//***********************************************************************

void LCD_clear(void) 
{
  LCD_write_com(0x01);
  delay_ms(1);
}

//***********************************************************************
//函数名称：DisplayCgrom(uchar hz)显示CGROM里的汉字
//***********************************************************************
void DisplayCgrom(uchar addr,uchar *hz)
{
  LCD_write_com(addr);
  delay_ms(1);
  while(*hz != '\0')  
  {
    LCD_write_data(*hz);
    hz++;
    delay_ms(1);
  }

} 

//****************************************************************
//函数名称：Display()显示测试结果
//****************************************************************
void Display(void)
{
  DisplayCgrom(0x80,"欣世纪电子欢迎你");
  DisplayCgrom(0x88,"旺:jingyehanxing");
  DisplayCgrom(0x90,"www.avrgcc.com  ");
  DisplayCgrom(0x98,"电话057487476870");
}

//***********************************************************************
//	显示屏初始化函数
//***********************************************************************
void LCD_init(void) 
{
  LCD_write_com(FUN_MODE);			//显示模式设置
  delay_ms(1);
  LCD_write_com(FUN_MODE);			//显示模式设置
  delay_ms(1);
  LCD_write_com(DISPLAY_ON);			//显示开
  delay_ms(1);
  LCD_write_com(CLEAR_SCREEN);			//清屏
  delay_ms(1);
}

//****************************************************************
//函数名称：Display_photo(uchar *hz)显示自定义图形，分上下半屏来写
//****************************************************************

void Display_photo1(const uchar *img1)           //写上半屏图形数据函数
{
   int i,j;     

   for(i=0;i<32;i++)                             //上半屏32行
    {  
	LCD_write_com(FUN_MODEK);                //扩展指令，开绘图显示
        delay_us(50);
     
 	LCD_write_com(Yaddress+i);               //先写垂直地址，即Y地址，不能自动加一
        delay_us(50);

        LCD_write_com(X1address);                //再写水平地址，即X地址
        delay_us(50);
      
 	for(j=0;j<8;j++)                         //连续写入2个字节的数据，一共8次，为一行，即16*8位数据
        {  			                                     
		LCD_write_data(img1[i*16+j*2]);
		delay_us(50);                     //这个延时是必须的，因为没有对液晶进行判忙操作，所以进行延时
		LCD_write_data(img1[i*16+j*2+1]); 
		delay_us(50);          
        }

    }
}

void Display_photo2(const uchar *img2)           //写下半屏图形数据
{
	int i,j;

	for(i=0;i<32;i++)                        //下半屏32行
	{  

	 LCD_write_com(Yaddress+i);       //先写垂直地址，即Y地址，不能自动加一
	 delay_us(50);
	 LCD_write_com(X2address);        //再写水平地址，即X地址
	 delay_us(50);
	 	 for(j=0;j<8;j++)         //连续写入2个字节的数据，一共8次，为一行，即16*8位数据
	    {
			
			LCD_write_data(img2[i*16+j*2]);
			delay_us(50);                    
			LCD_write_data(img2[i*16+j*2+1]);  
			delay_us(50);  
      
		}

	}

}

//****************************************************************
//函数名称：主函数，调用相关子程序，显示图形
//****************************************************************

int main(void)
{
  WDT_Init();                                   //看门狗设置
  Clock_Init();                                 //系统时钟设置
  Port_Init();                                  //系统初始化，设置IO口属性
  delay_ms(10);                                //延时10ms
  LCD_init();                                   //液晶参数初始化设置
  LCD_clear();                                  //清屏
  while(1)
  {
    Display_photo1(photo1);                     //显示上半屏数据，第一幅图
    Display_photo2(photo2);                     //显示下半屏数据
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    
    Display_photo1(photo3);                     //显示上半屏数据，第二幅图
    Display_photo2(photo4);                     //显示下半屏数据
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
  }
}

