//***********************************************************************
//               MSP430配置头文件
//***********************************************************************
#include <msp430x14x.h>

uint Device_code;                       //TFT控制IC型号，2.8寸为ILI9320

ulong cardSize = 0;
uchar status = 1;
uint timeout = 0;
int i = 0;
uint BlockLength=512;                    //MMC/SD卡块大小，CSD寄存器记录了卡本身允许的大小，一般为512
ulong numSector=200;	                 //向SD卡中写入数据的地址，为扇区数，对于一个扇区为512字节的SD卡实际地址为numSector*512字节

/********************************************************************
			初始化TFT相关IO口子程序
********************************************************************/
void TFT_Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT数据口
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT显示控制线
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;       //触摸控制线，P60~P64，2条输入线，4条输出线
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
            TFT显示功能函数-竖屏显示和触摸功能测试
触摸采用描点测试，测试时可以在屏幕上画线，满1000次触摸点击后失效，可进入其他测试功能
********************************************************************/
void Test_TFT_Show_Touch(void)
{
  uchar y;
  uint TouchCount=0x00;
  
  TFT_Port_Init();                   //系统初始化，设置IO口属性 
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
  start_7843();                      //打开触摸功能
    
  CLR_Screen(Black);               //用背景色清屏
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
  
  CLR_Screen(Black);                                     //用背景色清屏
    
    for(y=0;y<10;y++)
    {
      LCD_PutString(52,y*32,"欣创电子,与您同行",White,Black);      //汉字显示
      delay_ms(30);
    }
    delay_ms(300);
    
    CLR_Screen(Black);                                             //用背景色清屏
    for(y=0;y<10;y++)
    {
      LCD_PutString(24,y*32,"宁波欣创电子科技有限公司",White,Black);      //汉字显示
      delay_ms(30);
    }
    delay_ms(300);
        
    Show_RGB(0,240,0,64,Blue);                              //5种颜色将屏分为5个区域
    Show_RGB(0,240,64,128,Green);
    Show_RGB(0,240,128,192,Magenta);
    Show_RGB(0,240,192,256,Red);
    Show_RGB(0,240,256,320,Yellow);

  CLR_Screen(Blue);                                       //清屏				
  LCD_PutString(16,5,"Please write on the board!",Magenta,Blue);
  
  while(TouchCount<1000)  //计数1000次触摸，为的是可以退出这个测试界面，如果不在屏幕画线，就不能退出，一定要测试
  {	
    if(Getpix()==1)   
    {
      drawpoint(lx,ly,White);             //写（x，y）点为白色
      TouchCount++;
    }
  }
}

/********************************************************************
            TFT显示功能函数-横屏显示测试
********************************************************************/
void Test_TFT_Show_H(void)
{
  uchar y;
  
  TFT_Port_Init();                   //系统初始化，设置IO口属性 
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial_H();                     //初始化LCD	
  //start_7843();                      //打开触摸功能
    
  CLR_Screen(Black);               //用背景色清屏
  
    LCD_PutString24_H(75,85,"欣世纪电子科技",Yellow,Black); //欢迎界面，24x24大小汉字，字模软件隶书小二号
    delay_ms(500); 
    LCD_PutString24_H(115,119,"欢",Yellow,Black);
    delay_ms(300);
    LCD_PutString24_H(145,119,"迎",Yellow,Black);
    delay_ms(300);
    LCD_PutString24_H(175,119,"您",Yellow,Black);
    delay_ms(300);
    LCD_PutString_H(102,222,"www.avrgcc.com",White,Black);  	//字符显示官方网站
    delay_ms(800);  
    CLR_Screen(Black);                                       //用背景色清屏
    for(y=0;y<10;y++)
    {
      LCD_PutString_H(32,24*y,"宁波欣创电子科技有限公司与您同行",White,Black);   //汉字显示
      delay_ms(30);
    }
    delay_ms(300);

    Show_RGB_H(0,319,0,39,Blue);                          //6种颜色将屏分为6个区域
    Show_RGB_H(0,319,40,79,Green);
    Show_RGB_H(0,319,80,119,Magenta);
    Show_RGB_H(0,319,120,159,Black);
    Show_RGB_H(0,319,160,199,Yellow);
    Show_RGB_H(0,319,200,239,Red);
    delay_ms(300);
    delay_ms(300);
    Show_RGB_H(0,319,0,39,White);                         //6种颜色将屏分为6个区域
    Show_RGB_H(0,319,40,79,Green);
    Show_RGB_H(0,319,80,119,Red);
    Show_RGB_H(0,319,120,159,Black);
    Show_RGB_H(0,319,160,199,Yellow);
    Show_RGB_H(0,319,200,239,Magenta);
		

    LCD_PutString_H(108,12,"字符显示测试",Blue,White);									//第1个区域显示16x16汉字
    
    LCD_PutString_H(80,40,"0123456789876543210",Black,Green);         //第2个区域显示ascii字符中的数字和符号
    LCD_PutString_H(40,60,"+-+-**,,`,./<>';:[]{}\|?-=+*&^%$",Black,Green);

    LCD_PutString_H(40,80,"abcdefghijklmnopqrstuvwxyz",White,Red);    //第3个区域显示ascii字符中字母
    LCD_PutString_H(40,100,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",White,Red);

    LCD_PutString_H(30,132,"The Device IC Of TFT Is:",Yellow,Black);  //第4个区域显示TFT控制器IC型号
    LCD_PutString_H(222,132,"ILI",Red,Black);

    LCD_PutSingleChar(246, 132, 0x30+(Device_code>>12), Red, Black);
    LCD_PutSingleChar(254, 132, 0x30+((Device_code>>8)&0x000f), Red, Black);
    LCD_PutSingleChar(262, 132, 0x30+((Device_code>>4)&0x000f), Red, Black);
    LCD_PutSingleChar(270, 132, 0x30+(Device_code&0x000f), Red, Black);
    
    LCD_PutString_H(102,222,"www.avrgcc.com",White,Magenta);  	//字符显示官方网站
    delay_ms(400);                                              //显示一段时间

    CLR_Screen(Black);               																	//用背景色清屏

    GUIline(0,0,319,239,Yellow);																			  //任意画线，这里是屏幕对角线
    GUIline(319,0,0,239,Yellow);
    delay_ms(400);                                              //显示一段时间

    CLR_Screen(Black);
				
    GUIfull(0,0,159,119,Red);
    GUIfull(160,0,319,119,Green);
    GUIfull(0,120,159,239,Yellow);
    GUIfull(160,120,319,239,Magenta);
    delay_ms(400);                                              //显示一段时间

    CLR_Screen(Black);
		
    GUIDotline(0,0,319,0,Yellow);		                //画虚线边框																	  //任意画虚线，这里是屏幕边框
    GUIDotline(319,0,319,239,Yellow);																		//任意画虚线，这里是屏幕边框
    GUIDotline(0,239,319,239,Yellow);																		//任意画虚线，这里是屏幕边框
    GUIDotline(0,0,0,239,Yellow);																			  //任意画虚线，这里是屏幕边框

    GUIcircle(50,50,20,Magenta);	                        //画3个大小不同的圆																			//任意画圆形
    GUIcircle(159,119,70,Magenta);
    GUIcircle(270,150,30,Magenta);

    delay_ms(2000);                                             //显示一段时间
}

/********************************************************************
           TFT显示功能函数-SD卡功能测试，仅显示容量
********************************************************************/
void Test_TFT_SD(void)
{
  uchar Status_SD=0;
  
  TFT_Port_Init();                   //系统初始化，设置IO口属性 
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
  //start_7843();                      //打开触摸功能
    
  CLR_Screen(Black);               //用背景色清屏
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
  
  CLR_Screen(Black);                                     //用背景色清屏                                     	//用背景色清屏

    LCD_PutString(0,0,"Starting Init SD",White,Black);  		//字符串显示调用
    LCD_PutString(0,16,"Waiting...",White,Black);  			//字符串显示调用
    delay_ms(1);
		 
		 
    while (status != 0)         					// 如果返回非零值，则表示出错，SD卡继续重新初始化                                           
  	{
    	status = InitMMC();
    	timeout++;
    	if (timeout == 50)       //初始化50次MMC/SD卡，如果依然返回错误代码，则初始化失败，可能是没有SD卡或损坏
    		{
                  LCD_PutString(0,32,"Init Failure",White,Black);       //字符串显示调用
		  LCD_PutString(0,48,"Please Check SD",White,Black);  	//字符串显示调用
                  Status_SD=1;
                  break;
     		}
  	}                     		 
  if(Status_SD==0)
  {
    LCD_PutString(0,32,"Init SD Success!",White,Black);  				
    Print_SDSize(MMC_ReadCardSize());
  }
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
     TFT显示功能函数-显示温度值，LED灯D1停止闪烁后表示温度测试结束
********************************************************************/
void Test_TFT_18B20(void)
{
  uchar i,j;
  
  TFT_Port_Init();                   //系统初始化，设置IO口属性 
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD	
  //start_7843();                      //打开触摸功能
  CLR_Screen(Black);                  //用背景色清屏
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
    
    LCD_PutString(0,0,"The Temperature is : ",White,Black);  //温度显示提示字符
    
    DS18B20_Reset();			  //复位D18B20
  
   for(i=0;i<30;i++)
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
