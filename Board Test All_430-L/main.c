/********************************************************************
//DM430-Lϵͳ�����幦�ܲ��Գ�������ģʽ���������Լ�˲��Ե������ⲿģ��
//����ͬ�İ�������ʾ��ͬ��LED�ƣ������뿴����
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2013.05.19
********************************************************************/

#include <msp430x14x.h>         //430ͷ�ļ�
#include "Config.h"             //�����ⲿ��Դ����ͷ�ļ�
#include "LED8.h"               
#include "18B20.h"
#include "LCD1602.h"               
#include "LCD12864.h"
#include "UART.h"
#include "TestNoLCD.h"
#include "Ascii_8x16.h"                 //8x16��С�ַ�
#include "GB2424.h"                     //24x24���ش�С�ĺ���
#include "Chinese.h"                    //16x16���ش�С�ĺ���
#include "TFT28.h"                      //TFTͷ�ļ�
#include "TFT28.c"                      //TFT������ʼ��������
#include "Touch.h"                      //TFT����ͷ�ļ�
#include "Touch.c"                      //TFT������غ���
#include "GUI.h"                        //TFT��ͼͷ�ļ�
#include "GUI.c"                        //TFT��ͼ��غ���
#include "SPI.c"
#include "MMC.c"
#include "TFT28Show.h" 
#include "TestLCD.h"

uchar TestMode=0x00;            //����ģʽ��������4�ֲ���ģʽ

#define TestMode_Ex32768 (0x01) //�ⲿ32.678K�������ģʽ
#define TestMode_Inc     (0x02) //�ڲ�RC�������ģʽ
#define TestMode_NoLCD   (0x03) //��Һ����ʾ������ģʽ
#define TestMode_LCD     (0x04) //��Һ����ʾ����ģʽ


//*************************************************************************
//		������
//*************************************************************************

void main(void)
{     
  WDT_Init();                            //���Ź�����
  Clock_Init();
  LED8Port_Init();
  while(1){
  
  while(Key_Scan()==0xff);               //�ȴ���������ѡ�����ģʽ
  
  if(Key_Scan()==1)                      //S1���£������ⲿ��Ƶ����32.768K
  {
    Clock_Init_Ex32768();
    TestMode = TestMode_Ex32768;
    key=0xff;
    delay_ms(1);
  }
  if(Key_Scan()==2)                      //S2���£������ڲ�RC�����Ƿ�����
  {
    Clock_Init_Inc();
    TestMode = TestMode_Inc;
    key=0xff;
    delay_ms(20);
  }
  if(Key_Scan()==3)                      //S3���£�����û��Һ����ʾʱ���ֹ��ܣ�Ϊ����û����TFTҺ���Ŀͻ��������湦��
  {
    Clock_Init();
    TestMode = TestMode_NoLCD;
    key=0xff;
    delay_ms(20);
  }
  if(Key_Scan()==4)                      //S4���£���TFTҺ��ʱ�Ĳ��ԣ������������ݣ����������ʾ�¶�ֵ�ȣ����忴ִ��
  {
    Clock_Init();
    TestMode = TestMode_LCD;
    key=0xff;
    delay_ms(20);
  }

  switch(TestMode)
  {
    case TestMode_Ex32768: LED8_Run_1Time();Clock_Init_Inc();break; //��ˮ��ʾ8��LED�ƣ�����л����ڲ�RC���񣬱��ⰴ�����ʱ�����
    case TestMode_Inc: LED8_8();Clock_Init();break;              //8��LED����˸������л����ⲿ��Ƶ����
    case TestMode_NoLCD: LED8=0xFE;TestMode_NoLCDFunction();break;//����D1�������������ܲ���ģʽ
    case TestMode_LCD: LED8=0x7F;TestMode_LCDFunction();break;//����D8�������TFT�Ĺ��ܲ���ģʽ
  }
  
  }

 }

