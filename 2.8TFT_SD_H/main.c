/********************************************************************
//DM430-L����Сϵͳ�����2.8��TFT������MMC/SD�����Գ���
//��TFT����TFT�ӿڣ������⣬ע��رյ�Դ��װ
//SD��ѡ��2GB���£���SDHC��������ʾSD���������ڲ���Ӳ����ȷ
//SD����λ��2.8��TFT�����ϣ�����SPI����ģʽ��������Լ��ӵ�SD�����ο�����Ӳ������
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
#include "SPI.c"
#include "MMC.c"

uint Device_code;      //TFT����IC�ͺţ��°�2.8��ΪILI9320

ulong cardSize = 0;
uchar status = 1;
uint timeout = 0;
int i = 0;
uint BlockLength=512;                    //MMC/SD�����С��CSD�Ĵ�����¼�˿���������Ĵ�С��һ��Ϊ512
ulong numSector=200;	                 //��SD����д�����ݵĵ�ַ��Ϊ������������һ������Ϊ512�ֽڵ�SD��ʵ�ʵ�ַΪnumSector*512�ֽ�

//**************�����ⲿ�����ͱ���********************
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
  
  P6SEL = 0x00;                                   //����IO��Ϊ��ͨI/Oģʽ
  P6DIR = 0xff;                                   //����IO�ڷ���Ϊ���
  P6OUT = 0x00;                                   //��ʼ����Ϊ00,LED������IO��
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;       //���������ߣ�2�������ߣ�4�������
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
  uint y;
  
  WDT_Init();                        //���Ź�����
  Clock_Init();                      //ϵͳʱ������
  Port_Init();                       //ϵͳ��ʼ��������IO������
  LED_Light();                       //LED����һ�Σ���������˵����Ƭ����ʼ���ɹ�   
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	

  while(1)                           					//ѭ��ִ�г���
   {
    CLR_Screen(Black);               					//�ñ���ɫ����
    LCD_PutString24(75,85,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����
    delay_ms(500); 
    LCD_PutString24(115,119,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(145,119,"ӭ",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(175,119,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString(102,222,"www.avrgcc.com",White,Black);  		//�ַ���ʾ�ٷ���վ
    delay_ms(800);  
    CLR_Screen(Black);                                       	//�ñ���ɫ����

    LCD_PutString(0,0,"Starting Init SD",White,Black);  		//�ַ�����ʾ����
    LCD_PutString(0,16,"Waiting...",White,Black);  			//�ַ�����ʾ����
    delay_ms(1);
		 
		 
    while (status != 0)         					// ������ط���ֵ�����ʾ����SD���������³�ʼ��                                           
  	{
    	status = InitMMC();
    	timeout++;
    	if (timeout == 50)       //��ʼ��50��MMC/SD���������Ȼ���ش�����룬���ʼ��ʧ�ܣ�������û��SD������
    		{
                  LCD_PutString(0,32,"Init Failure",White,Black);       //�ַ�����ʾ����
		  LCD_PutString(0,48,"Please Check SD",White,Black);  	//�ַ�����ʾ����  		
     		}
  	}                     		 
		LCD_PutString(0,32,"Init SD Success!",White,Black);  				
	
		Print_SDSize(MMC_ReadCardSize());
		 
  while(1);
}
}