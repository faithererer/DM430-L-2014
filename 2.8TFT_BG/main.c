/********************************************************************
//DM430-L����Сϵͳ�����2.8��TFT�����������Ʊ����Գ���
//��TFT�����Ӧ�ӿڼ��ɣ�δ�õ��������ܣ���������ʾ���ԣ����ܴ��ڲ���bug
//ע��ѡ��Һ���ĵ�Դ��λ�ڵ�λ����������ѡ5V��3.3V������Һ����ѹ����ѡ��Ĭ������Ϊ5V
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //����ͷ�ļ�����Ӳ����ص��������������
#include "GUI.h"
#include "Ascii_8x16.h"                 //8x16��С�ַ�
#include "GB2424.h"                     //24x24���ش�С�ĺ���
#include "Chinese.h"                    //16x16���ش�С�ĺ���
#include "Touch.h"                      //TFT��������ͷ�ļ�
#include "Touch.c"                      //TFT����������ʼ��������
#include "TFT28.h"                      //TFT��ʾͷ�ļ�
#include "TFT28.c"                      //TFT��ʾ������ʼ��������
#include "GUI.c"

uint Device_code;      //TFT����IC�ͺţ��°�2.8��ΪILI9320

extern void delayms(uint count);

/********************************************************************
			��ʼ��IO���ӳ���
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT���ݿ�
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT��ʾ������
  
  P6SEL=0x00;                               //����IO��Ϊ��ͨI/Oģʽ
  P6DIR = 0xff;                             //����IO�ڷ���Ϊ���
  P6OUT = 0x00;                             //��ʼ����Ϊ00,LED������IO��
  }

/********************************************************************
	LED��˸һ�Σ�������Ҫ�鿴����ִ��λ��ʱ������ã����ƶϵ�
********************************************************************/
void LED_Light()
{
    LED8=0x00;                              //����LED
    delay_ms(500);
    LED8=0xff;                              //Ϩ��LED
    delay_ms(500);
}
/********************************************************************
                      ������
********************************************************************/
main()
{
  WDT_Init();                        //���Ź�����
  Clock_Init();                      //ϵͳʱ������
  Port_Init();                       //ϵͳ��ʼ��������IO������
  LED_Light();                       //LED����һ�Σ���������˵����Ƭ����ʼ���ɹ�   
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	
    
   while(1)                           //ѭ��ִ�г���
   {
    CLR_Screen(Black);               //�ñ���ɫ����
    LCD_PutString24(75,85,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����
    delay_ms(500); 
    LCD_PutString24(115,119,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(145,119,"ӭ",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(175,119,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString(102,222,"www.avrgcc.com",White,Black);  	//�ַ���ʾ�ٷ���վ
    delay_ms(800);  
    CLR_Screen(Black);                                          //�ñ���ɫ����

    while(1)                                                    //ѭ��ִ�г���
   {
    GUITable(0,0,319,239,5,2,Yellow);                           //������λ���������еı��
    delay_ms(800); 
    CLR_Screen(Blue);
    GUITable(0,0,319,239,7,4,White);
    delay_ms(800);  
    CLR_Screen(White);
    GUITable(10,10,300,200,4,4,Black);
    delay_ms(800);
    CLR_Screen(Yellow);
    GUITable(40,50,250,200,6,4,Red);
    delay_ms(800);
    CLR_Screen(Black);
   }  
   }  
}