/********************************************************************
//DM430-L�Ϳ�����ʹ��TIMERA����UP��ʱģʽʵ�飬���ʱ99��,ͨ��2.8�������ʾ
//��������TIMERAÿ10ms�ж�һ�Σ���ʱ������ʾ�ڲ����ϣ���ֱ�Ӳ鿴ʱ��ֵ
//LED��D2��ÿһ����˸һ�Σ����ʱ����У�����û��TFT�����Ŀͻ��鿴
//ֻ�����������ݶ�ʱ�������ʵ��ʱ�ӣ������Сʱ�Լ����жϵȾͿ�����
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2014.03.01
********************************************************************/

#include <msp430x14x.h>
#include "Config.h"                      //����������ͷ�ļ�����Ҫ����IO�˿���Ϣ
#include "Ascii_8x16.h"                 //8x16��С�ַ�
#include "GB2424.h"                     //24x24���ش�С�ĺ���
#include "Chinese.h"                    //16x16���ش�С�ĺ���
#include "TFT28.h"                      //TFTͷ�ļ�
#include "TFT28.c"                      //TFT������ʼ��������

uchar Flag=0;                            //��־λ
uchar Count=0;                           //ʱ���������
uchar Second=0;                          //��ʱ�����
uint Device_code;                       //TFT����IC�ͺţ�2.8��ΪILI9320
//***********************************************************************
//               MSP430IO�ڳ�ʼ��
//***********************************************************************
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
  
  P6DIR  = 0xFF;                      //����IO�ڷ���Ϊ���
  LED8 = 0xFF;                        //P6�ڳ�ʼ����ΪFF
}

//*************************************************************************
//	    ��ʾ����
//*************************************************************************

void Display_Time(uchar Time)
{
  
  LCD_PutChar(112,0,Time/10+0x30,White,Black);
  LCD_PutChar(120,0,Time%10+0x30,White,Black);
  LCD_PutChar(128,0,'s',White,Black);
                 
}

//***********************************************************************
//             TIMERA��ʼ��������ΪUPģʽ����
//***********************************************************************
void TIMERA_Init(void)                                   //UPģʽ��������������ΪCCR0+1
{
  TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK��ʱ��Դ��8��Ƶ�����Ӽ���ģʽ�����ж�
  TACCR0 = 9999;                                          //CCR0=9999��10ms�ж�һ��
}

//***********************************************************************
//             TIMERA�жϷ��������Ҫ�ж��ж�����
//***********************************************************************
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch(TAIV)                                  //��Ҫ�ж��жϵ�����
  {
  case 2:break;
  case 4:break;
  case 10:Count++;break;                         //���ñ�־λFlag
  }
  if(Count==100)                                 //100��Ϊ1��
  {
    Second++;
    Count=0;
    P6OUT = ~(P6OUT&BIT1);                        //P61ȡ����˸
  }
  while(Second>99)Second=0;                       //������99��
}

//*************************************************************************
//           ������
//*************************************************************************
void main(void)
{ 
  WDT_Init();                                   //���Ź�����
  Clock_Init();                                 //ϵͳʱ������
  Port_Init();                                  //�˿ڳ�ʼ��
  TIMERA_Init();                                //����TIMERA��P12���PWM�ź�
  Device_code=0x9320;                           //TFT����IC�ͺ�
  TFT_Initial();                                //��ʼ��LCD	
  CLR_Screen(Black);                          //�ñ���ɫ����
  LCD_PutString24(35,140,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����
  delay_ms(500);    
  LCD_PutString24(83,170,"��",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(107,170,"ӭ",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(131,170,"��",Yellow,Black);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Black);     //�ַ���ʾ�ٷ���վ
  delay_ms(300);
    
  CLR_Screen(Black);                                      //�ñ���ɫ����
    
  LCD_PutString(0,0,"The Time is : ",White,Black);        //��ʱ��ʾ��ʾ�ַ�
  
  _EINT();                                                //���ж�
  while(1)
  {
    Display_Time(Second);                                  //��ʾʱ��ֵ�����99�룬Ȼ������
  }
}