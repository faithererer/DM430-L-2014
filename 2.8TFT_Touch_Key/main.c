/********************************************************************
//DM430-L����Сϵͳ�崥��������ʾ���̣����ڴ����̿�ʵ�ּ��׼������ȹ��ܣ��ʵ������㷨����
//ֱ�ӽ�TFT�����ӦTFT�ӿڣ�ע��TFT��װ�����ǳ���
//ע��ѡ��Һ���ĵ�Դ��λ��TFT�ӿڸ�������ѡ5V��3.3V������Һ����ѹ����ѡ��Ĭ������Ϊ5V
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2014.03.01
********************************************************************/
#include <msp430x14x.h>
#include "Config.h"                     //����ͷ�ļ�����Ӳ����ص��������������
#include "GUI.h"                        //GUIͷ�ļ�
#include "Ascii_8x16.h"                 //8x16��С�ַ�
#include "GB2424.h"                     //24x24���ش�С�ĺ���
#include "Chinese.h"                    //16x16���ش�С�ĺ���
#include "GB2435.h"                     //24x35���ش�С�ĺ���
#include "Touch.h"                      //TFT��������ͷ�ļ�
#include "Touch.c"                      //TFT����������ʼ��������
#include "TFT28.h"                      //TFT��ʾͷ�ļ�
#include "TFT28.c"                      //TFT��ʾ������ʼ��������
#include "GUI.c"                        //GUI����
#include "Key_Dec.c"                    //����������⺯��

/********************************************************************
			����������
********************************************************************/
/*������ť��״̬��־λ*/
uchar 	Button_Flag=0;			//�������±�־

uchar 	Button_11=0;                    //��һ�е�һ�а�ť
uchar 	Button_12=0;
uchar	Button_13=0;

uchar	Button_21=0;		        //�ڶ��е�һ�а�ť
uchar	Button_22=0;
uchar	Button_23=0;

uchar 	Button_31=0;		        //�����е�һ�а�ť
uchar	Button_32=0;
uchar	Button_33=0;

uchar	Button_41=0;                    //�����е�һ�а�ť
uchar 	Button_42=0;
uchar	Button_43=0;

uchar   Button_Back=0;	                //�˸�ť
uchar   Button_Clear=0;	                //�����ť

uint  	LCD_X,LCD_Y;

uint    Device_code;                    //TFT����IC�ͺţ�2.8��ΪILI9320
extern void delayms(unsigned int count);

uchar Tab[][3]={"1","2","3","4",        //��ť��ֵ��ʾ
		 "5","6","7","8",
		 "9","0","B","C"};

/********************************************************************
			��ʼ��IO���ӳ���
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT���ݿ�
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT��ʾ������
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;               //����������
}

/********************************************************************
	������Խ�����ƣ�ֱ�Ӷ�ָ��������䵥ɫ���ٶ���ԽϿ�
        50X60�İ�ť���ƣ���ֵ������ʾ
********************************************************************/
void DisplayDesk(void)
{
  uint i,j,xs,ys,xe,ye;	 
	
  CLR_Screen(Black);
  LCD_PutString24(72,0,"��������",Yellow,Black); 	
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
      LCD_PutString(xs+26,ys+17,Tab[i*3+j],Black,White);  //��ťֵ��ʾ
    }
  }
}

/********************************************************************
                      ������
********************************************************************/
main()
{
  WDT_Init();                        //���Ź�����
  Clock_Init();                      //ϵͳʱ������
  Port_Init();                       //ϵͳ��ʼ��������IO������ 
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	
  start_7843();                      //�򿪴�������
    
  CLR_Screen(Black);                 //�ñ���ɫ����
  LCD_PutString24(35,140,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����
  delay_ms(500);    
  LCD_PutString24(83,170,"��",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(107,170,"ӭ",Yellow,Black);
  delay_ms(300);
  LCD_PutString24(131,170,"��",Yellow,Black);
  delay_ms(300);
  LCD_PutString(69,300,"www.avrgcc.com",White,Black);   //�ַ���ʾ�ٷ���վ
  delay_ms(300);
 
  DisplayDesk();	
  while(1)
  {
    ShowBotton();                       //������ֵ��ʾ����һ����ť����ʾһ��ֵ��֧���˸���������
  }
  
}