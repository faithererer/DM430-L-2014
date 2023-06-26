/********************************************************************
//DM430-L型最小系统板触摸按键显示例程，基于此例程可实现简易计算器等功能，适当增加算法即可
//直接将TFT插入对应TFT接口，注意TFT安装方向，是朝外
//注意选择液晶的电源，位于TFT接口附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //配置头文件，与硬件相关的配置在这里更改
#include "GUI.h"                        //GUI头文件
#include "Ascii_8x16.h"                 //8x16大小字符
#include "GB2424.h"                     //24x24像素大小的汉字
#include "Chinese.h"                    //16x16像素大小的汉字
#include "GB2435.h"                     //24x35像素大小的汉字
#include "Touch.h"                      //TFT触摸操作头文件
#include "Touch.c"                      //TFT触摸操作初始化及函数
#include "TFT28.h"                      //TFT显示头文件
#include "TFT28.c"                      //TFT显示操作初始化及函数
#include "GUI.c"                        //GUI函数
#include "Key_Dec.c"                    //触摸按键检测函数

/********************************************************************
			变量定义区
********************************************************************/
/*触摸按钮等状态标志位*/
uchar 	Button_Flag=0;			//按键按下标志

uchar 	Button_11=0;                    //第一行第一列按钮
uchar 	Button_12=0;
uchar	Button_13=0;

uchar	Button_21=0;		        //第二行第一列按钮
uchar	Button_22=0;
uchar	Button_23=0;

uchar 	Button_31=0;		        //第三行第一列按钮
uchar	Button_32=0;
uchar	Button_33=0;

uchar	Button_41=0;                    //第四行第一列按钮
uchar 	Button_42=0;
uchar	Button_43=0;

uchar   Button_Back=0;	                //退格按钮
uchar   Button_Clear=0;	                //清除按钮

uint  	LCD_X,LCD_Y;

uint    Device_code;                    //TFT控制IC型号，2.8寸为ILI9320
extern void delayms(unsigned int count);

uchar Tab[][3]={"1","2","3","4",        //按钮键值显示
		 "5","6","7","8",
		 "9","0","B","C"};

/********************************************************************
			初始化IO口子程序
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT数据口
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT显示控制线
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;               //触摸控制线
}

/********************************************************************
	整板测试界面绘制，直接对指定窗口填充单色，速度相对较快
        50X60的按钮绘制，键值居中显示
********************************************************************/
void DisplayDesk(void)
{
  uint i,j,xs,ys,xe,ye;	 
	
  CLR_Screen(Black);
  LCD_PutString24(72,0,"触摸按键",Yellow,Black); 	
  GUIline(1,25,240,25,Yellow);
  GUIline(1,70,240,70,Yellow);
  GUIline(1,319,240,319,Yellow);
  GUIline(1,25,1,319,Yellow);
  GUIline(239,25,239,319,Yellow);
  
  for(i=0;i<4;i++)
			
  {
    for(j=0;j<3;j++)
    {
      xs=j*60+15*j+15;
      ys=80+i*50+10*i;
      xe=j*60+15*j+15+60;
      ye=80+i*50+10*i+50;
      
      LCD_Full(xs,xe,ys,ye,White);
      LCD_PutString(xs+26,ys+17,Tab[i*3+j],Black,White);  //按钮值显示
    }
  }
}

/********************************************************************
                      主函数
********************************************************************/
main()
{
  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  Port_Init();                       //系统初始化，设置IO口属性 
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
  start_7843();                      //打开触摸功能
    
  CLR_Screen(Black);                 //用背景色清屏
  LCD_PutString24(35,140,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
  delay_ms(500);    
  LCD_PutString24(83,170,"欢",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(107,170,"迎",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(131,170,"您",Yellow,Black);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Black);   //字符显示官方网站
  delay_ms(300);
 
  DisplayDesk();	
  while(1)
  {
    ShowBotton();                       //触摸键值显示，点一个按钮，显示一个值，支持退格和清除功能
  }
  
}