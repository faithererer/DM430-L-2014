//***********************************************************************
//               MSP430����ͷ�ļ�
//***********************************************************************
#include <msp430x14x.h>

uint Device_code;                       //TFT����IC�ͺţ�2.8��ΪILI9320

ulong cardSize = 0;
uchar status = 1;
uint timeout = 0;
int i = 0;
uint BlockLength=512;                    //MMC/SD�����С��CSD�Ĵ�����¼�˿���������Ĵ�С��һ��Ϊ512
ulong numSector=200;	                 //��SD����д�����ݵĵ�ַ��Ϊ������������һ������Ϊ512�ֽڵ�SD��ʵ�ʵ�ַΪnumSector*512�ֽ�

/********************************************************************
			��ʼ��TFT���IO���ӳ���
********************************************************************/
void TFT_Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;                                     //TFT���ݿ�
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT��ʾ������
  
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;       //���������ߣ�P60~P64��2�������ߣ�4�������
}

/********************************************************************
     	      �ڴ�����λ�û���
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
            TFT��ʾ���ܺ���-������ʾ�ʹ������ܲ���
�������������ԣ�����ʱ��������Ļ�ϻ��ߣ���1000�δ��������ʧЧ���ɽ����������Թ���
********************************************************************/
void Test_TFT_Show_Touch(void)
{
  uchar y;
  uint TouchCount=0x00;
  
  TFT_Port_Init();                   //ϵͳ��ʼ��������IO������ 
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	
  start_7843();                      //�򿪴�������
    
  CLR_Screen(Black);               //�ñ���ɫ����
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
  
  CLR_Screen(Black);                                     //�ñ���ɫ����
    
    for(y=0;y<10;y++)
    {
      LCD_PutString(52,y*32,"��������,����ͬ��",White,Black);      //������ʾ
      delay_ms(30);
    }
    delay_ms(300);
    
    CLR_Screen(Black);                                             //�ñ���ɫ����
    for(y=0;y<10;y++)
    {
      LCD_PutString(24,y*32,"�����������ӿƼ����޹�˾",White,Black);      //������ʾ
      delay_ms(30);
    }
    delay_ms(300);
        
    Show_RGB(0,240,0,64,Blue);                              //5����ɫ������Ϊ5������
    Show_RGB(0,240,64,128,Green);
    Show_RGB(0,240,128,192,Magenta);
    Show_RGB(0,240,192,256,Red);
    Show_RGB(0,240,256,320,Yellow);

  CLR_Screen(Blue);                                       //����				
  LCD_PutString(16,5,"Please write on the board!",Magenta,Blue);
  
  while(TouchCount<1000)  //����1000�δ�����Ϊ���ǿ����˳�������Խ��棬���������Ļ���ߣ��Ͳ����˳���һ��Ҫ����
  {	
    if(Getpix()==1)   
    {
      drawpoint(lx,ly,White);             //д��x��y����Ϊ��ɫ
      TouchCount++;
    }
  }
}

/********************************************************************
            TFT��ʾ���ܺ���-������ʾ����
********************************************************************/
void Test_TFT_Show_H(void)
{
  uchar y;
  
  TFT_Port_Init();                   //ϵͳ��ʼ��������IO������ 
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial_H();                     //��ʼ��LCD	
  //start_7843();                      //�򿪴�������
    
  CLR_Screen(Black);               //�ñ���ɫ����
  
    LCD_PutString24_H(75,85,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����
    delay_ms(500); 
    LCD_PutString24_H(115,119,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString24_H(145,119,"ӭ",Yellow,Black);
    delay_ms(300);
    LCD_PutString24_H(175,119,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString_H(102,222,"www.avrgcc.com",White,Black);  	//�ַ���ʾ�ٷ���վ
    delay_ms(800);  
    CLR_Screen(Black);                                       //�ñ���ɫ����
    for(y=0;y<10;y++)
    {
      LCD_PutString_H(32,24*y,"�����������ӿƼ����޹�˾����ͬ��",White,Black);   //������ʾ
      delay_ms(30);
    }
    delay_ms(300);

    Show_RGB_H(0,319,0,39,Blue);                          //6����ɫ������Ϊ6������
    Show_RGB_H(0,319,40,79,Green);
    Show_RGB_H(0,319,80,119,Magenta);
    Show_RGB_H(0,319,120,159,Black);
    Show_RGB_H(0,319,160,199,Yellow);
    Show_RGB_H(0,319,200,239,Red);
    delay_ms(300);
    delay_ms(300);
    Show_RGB_H(0,319,0,39,White);                         //6����ɫ������Ϊ6������
    Show_RGB_H(0,319,40,79,Green);
    Show_RGB_H(0,319,80,119,Red);
    Show_RGB_H(0,319,120,159,Black);
    Show_RGB_H(0,319,160,199,Yellow);
    Show_RGB_H(0,319,200,239,Magenta);
		

    LCD_PutString_H(108,12,"�ַ���ʾ����",Blue,White);									//��1��������ʾ16x16����
    
    LCD_PutString_H(80,40,"0123456789876543210",Black,Green);         //��2��������ʾascii�ַ��е����ֺͷ���
    LCD_PutString_H(40,60,"+-+-**,,`,./<>';:[]{}\|?-=+*&^%$",Black,Green);

    LCD_PutString_H(40,80,"abcdefghijklmnopqrstuvwxyz",White,Red);    //��3��������ʾascii�ַ�����ĸ
    LCD_PutString_H(40,100,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",White,Red);

    LCD_PutString_H(30,132,"The Device IC Of TFT Is:",Yellow,Black);  //��4��������ʾTFT������IC�ͺ�
    LCD_PutString_H(222,132,"ILI",Red,Black);

    LCD_PutSingleChar(246, 132, 0x30+(Device_code>>12), Red, Black);
    LCD_PutSingleChar(254, 132, 0x30+((Device_code>>8)&0x000f), Red, Black);
    LCD_PutSingleChar(262, 132, 0x30+((Device_code>>4)&0x000f), Red, Black);
    LCD_PutSingleChar(270, 132, 0x30+(Device_code&0x000f), Red, Black);
    
    LCD_PutString_H(102,222,"www.avrgcc.com",White,Magenta);  	//�ַ���ʾ�ٷ���վ
    delay_ms(400);                                              //��ʾһ��ʱ��

    CLR_Screen(Black);               																	//�ñ���ɫ����

    GUIline(0,0,319,239,Yellow);																			  //���⻭�ߣ���������Ļ�Խ���
    GUIline(319,0,0,239,Yellow);
    delay_ms(400);                                              //��ʾһ��ʱ��

    CLR_Screen(Black);
				
    GUIfull(0,0,159,119,Red);
    GUIfull(160,0,319,119,Green);
    GUIfull(0,120,159,239,Yellow);
    GUIfull(160,120,319,239,Magenta);
    delay_ms(400);                                              //��ʾһ��ʱ��

    CLR_Screen(Black);
		
    GUIDotline(0,0,319,0,Yellow);		                //�����߱߿�																	  //���⻭���ߣ���������Ļ�߿�
    GUIDotline(319,0,319,239,Yellow);																		//���⻭���ߣ���������Ļ�߿�
    GUIDotline(0,239,319,239,Yellow);																		//���⻭���ߣ���������Ļ�߿�
    GUIDotline(0,0,0,239,Yellow);																			  //���⻭���ߣ���������Ļ�߿�

    GUIcircle(50,50,20,Magenta);	                        //��3����С��ͬ��Բ																			//���⻭Բ��
    GUIcircle(159,119,70,Magenta);
    GUIcircle(270,150,30,Magenta);

    delay_ms(2000);                                             //��ʾһ��ʱ��
}

/********************************************************************
           TFT��ʾ���ܺ���-SD�����ܲ��ԣ�����ʾ����
********************************************************************/
void Test_TFT_SD(void)
{
  uchar Status_SD=0;
  
  TFT_Port_Init();                   //ϵͳ��ʼ��������IO������ 
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	
  //start_7843();                      //�򿪴�������
    
  CLR_Screen(Black);               //�ñ���ɫ����
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
  
  CLR_Screen(Black);                                     //�ñ���ɫ����                                     	//�ñ���ɫ����

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
                      �¶�ֵ��ʾ����
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
     TFT��ʾ���ܺ���-��ʾ�¶�ֵ��LED��D1ֹͣ��˸���ʾ�¶Ȳ��Խ���
********************************************************************/
void Test_TFT_18B20(void)
{
  uchar i,j;
  
  TFT_Port_Init();                   //ϵͳ��ʼ��������IO������ 
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD	
  //start_7843();                      //�򿪴�������
  CLR_Screen(Black);                  //�ñ���ɫ����
   LCD_PutString24(35,140,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����
    delay_ms(500);    
    LCD_PutString24(83,170,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(107,170,"ӭ",Yellow,Black);
    delay_ms(300);
    LCD_PutString24(131,170,"��",Yellow,Black);
    delay_ms(300);
    LCD_PutString(69,300,"www.avrgcc.com",White,Black);  //�ַ���ʾ�ٷ���վ
    delay_ms(300);
    
    CLR_Screen(Black);                                     //�ñ���ɫ����
    
    LCD_PutString(0,0,"The Temperature is : ",White,Black);  //�¶���ʾ��ʾ�ַ�
    
    DS18B20_Reset();			  //��λD18B20
  
   for(i=0;i<30;i++)
    {
    ds1820_start();		          //����һ��ת��
    ds1820_read_temp();		          //��ȡ�¶���ֵ
    data_do(temp_value);                  //�������ݣ��õ�Ҫ��ʾ��ֵ
    LED8 &= ~(1<<0);                      //D1����˸��ʾ���ڲ����¶�
    for(j=0;j<30;j++)
    {	    
     LCD_DisplayTemp(A1,A2,A3);           //�����¶���ʾ�����������������ʾ
     LED8 |= 1<<0;                        //LED����˸
    }

    
   }

  
}
