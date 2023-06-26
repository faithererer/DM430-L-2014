#define CPU_F ((double)8000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/*当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数*/
#define baud           9600                                //设置波特率的大小
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //波特率计算公式
#define baud_h         (uchar)(baud_setting>>8)            //提取高位
#define baud_l         (uchar)(baud_setting)               //低位

//以下是TFT显示控制相关硬件配置
#define RS_CLR	        P5OUT &= ~BIT5           //RS置低
#define RS_SET	        P5OUT |=  BIT5           //RS置高

#define RW_CLR	        P5OUT &= ~BIT6           //RW置低
#define RW_SET	        P5OUT |=  BIT6           //RW置高

#define RD_CLR	        P5OUT &= ~BIT7           //E置低
#define RD_SET	        P5OUT |=  BIT7           //E置高

#define CS_CLR	        P5OUT &= ~BIT0            //CS置低
#define CS_SET	        P5OUT |=  BIT0            //CS置高

#define RST_CLR	        P5OUT &= ~BIT3            //RST置低
#define RST_SET	        P5OUT |=  BIT3            //RST置高

#define LE_CLR	        P5OUT &= ~BIT1            //LE置低
#define LE_SET	        P5OUT |=  BIT1            //LE置高

//以下是TFT触摸屏控制相关硬件配置
#define PEN_CLR	        P2OUT &= ~BIT0           //PEN置低,触碰触摸屏时，Penirq引脚由未触摸时的高电平变为低电平
#define PEN_SET	        P2OUT |=  BIT0           //PEN置高
#define PEN             (P2IN & 0x01)            //P2.0输入的值

#define TPDO_CLR	P2OUT &= ~BIT1           //TPDO置低
#define TPDO_SET	P2OUT |=  BIT1           //TPDO置高
#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1输入的值

#define BUSY_CLR	P2OUT &= ~BIT3           //BUSY置低
#define BUSY_SET	P2OUT |=  BIT3           //BUSY置高

#define TPDI_CLR	P2OUT &= ~BIT4            //TPDI置低
#define TPDI_SET	P2OUT |=  BIT4            //TPDI置高

#define TPCS_CLR	P2OUT &= ~BIT5            //TPCS置低
#define TPCS_SET	P2OUT |=  BIT5            //TPCS置高

#define TPCLK_CLR	P2OUT &= ~BIT6            //TPCLK置低
#define TPCLK_SET	P2OUT |=  BIT6            //TPCLK置高

#define DataPort        P4OUT                     //P4口为数据口

#define LED8            P6OUT                      //P6口接LED灯，8个

/*全局变量-颜色代码*/

#define White          0xFFFF           													//显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

//***********************************************************************
//                   系统时钟初始化
//***********************************************************************
void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
  BCSCTL2|=SELM1+SELS;              //MCLK为8MHZ，SMCLK为8MHZ
  do{
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
  IFG1&=~OFIFG; 
}
//***********************************************************************
//               MSP430内部看门狗初始化
//***********************************************************************
void WDT_Init()
{
   WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
}

