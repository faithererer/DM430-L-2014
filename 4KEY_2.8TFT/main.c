/********************************************************************
//DM430-L����Сϵͳ��4λ����������ʾ��ֵ��2.8��TFT����
//ֱ�ӽ�TFT�����ӦTFT�ӿڣ�ע��TFT��װ�����ǳ���
//ע��ѡ��Һ���ĵ�Դ��λ��TFT�ӿڸ�������ѡ5V��3.3V������Һ����ѹ����ѡ��Ĭ������Ϊ5V
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //����ͷ�ļ�����Ӳ����ص��������������
#include "Ascii_8x16.h"                 //8x16��С�ַ�
#include "GB2424.h"                     //24x24���ش�С�ĺ���
#include "Chinese.h"                    //16x16���ش�С�ĺ���
#include "TFT28.h"                      //TFTͷ�ļ�
#include "TFT28.c"                      //TFT������ʼ��������

//******************ȫ�ֱ���***************************
unsigned int Device_code;               //TFT����IC�ͺţ�2.8��ΪILI9320
extern void delayms(unsigned int count);
uchar key;

/********************************************************************
			��ʼ��IO���ӳ���
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;                   //TFT���ݿ�
  P4DIR = 0xFF;
  P5SEL = 0x00;                   //TFT���ƿ�
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
  
  P1SEL = 0x00;                   //P1��ͨIO����
  P1DIR = 0xF0;                   //P10~P13����ģʽ���ⲿ��·�ѽ���������
  P6SEL = 0x00;                   //P6����ͨIO����
  P6DIR = 0xFF;                   //P6�����ģʽ
}

/********************************************************************
	LED��˸һ�Σ�������Ҫ�鿴����ִ��λ��ʱ������ã����ƶϵ�
********************************************************************/
void LED_Light()
{
    LED8=0x00;                    //����LED
    delay_ms(500);
    LED8=0xff;                    //Ϩ��LED
    delay_ms(500);
}

//**********************************************************************
//	����ɨ���ӳ��򣬲������ɨ��ķ�ʽ
//**********************************************************************

uchar Key_Scan(void) 
{
  uchar key_check;
  uchar key_checkin;
  key_checkin=KeyPort;          	//��ȡIO��״̬���ж��Ƿ��м�����
  key_checkin&= 0x0F;          		//��ȡIO��״̬���ж��Ƿ��м�����
  if(key_checkin!=0x0F)            	//IO��ֵ�����仯���ʾ�м�����
    {
      delay_ms(20);                  	//������������ʱ20MS
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

/********************************************************************
                     ��ֵ��ʾ����
********************************************************************/
void  LCD_DisplayKey(uchar Key_num)
{
  LCD_PutChar(129,0,Key_num+0x30,White,Black);
}

/********************************************************************
                      ������
********************************************************************/
main()
{
   uint i,y;

  WDT_Init();                        //���Ź�����
  Clock_Init();                      //ϵͳʱ������
  Port_Init();                       //ϵͳ��ʼ��������IO������
  LED_Light();                       //LED����һ�Σ���������˵����Ƭ����ʼ���ɹ�   
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	 

  while(1)                           //ѭ��ִ�г���
   {
        
    CLR_Screen(Magenta);               //�ñ���ɫ����
    LCD_PutString24(35,140,"�����͵��ӿƼ�",Yellow,Magenta); //��ӭ���棬24x24��С���֣���ģ�������С����
    delay_ms(500);    
    LCD_PutString24(83,170,"��",Yellow,Magenta);
    delay_ms(300);
    LCD_PutString24(107,170,"ӭ",Yellow,Magenta);
    delay_ms(300);
    LCD_PutString24(131,170,"��",Yellow,Magenta);
    delay_ms(300);
    LCD_PutString(69,300,"www.avrgcc.com",White,Magenta);  //�ַ���ʾ�ٷ���վ
    delay_ms(300);
    
    CLR_Screen(Black);                                     //�ñ���ɫ����
    
    LCD_PutString(0,0,"The KeyNum is : ",White,Black);  //�¶���ʾ��ʾ�ַ�

    while(1)
    {
      Key_Scan();                       //����ɨ�裬���Ƿ��а�������
      if(key!=0xff)                     //����а������£�����ʾ�ð�����ֵ1��4
        {
	  {
            switch(key)
              {
	        case 1: LED8 = 0xFC;LCD_DisplayKey(1);break;     //����ͬ�ļ�����ֵ����ֵ1����2��LED��
                case 2: LED8 = 0xF3;LCD_DisplayKey(2);break;     //����ͬ�ļ�����ֵ����ֵ2����2��LED��
                case 3: LED8 = 0xCF;LCD_DisplayKey(3);break;	 //����ͬ�ļ�����ֵ����ֵ3����2��LED��
                case 4: LED8 = 0x3F;LCD_DisplayKey(4);break;	 //����ͬ�ļ�����ֵ����ֵ4����2��LED��
              }

          }
	
       }
     else
      {
        //LED=key;              	//û�а�����ʱ����ʾ�ϴεļ�ֵ
      }
    }

    
   }
 
    
}