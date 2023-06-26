/********************************************************************
//DM430-L����Сϵͳ���ⲿ��Դ�����ļ�Config.h
//�������ظ�����Դ��Ӳ�����ã�����û�ʹ�ù����У���Ӧ��Ӳ�������˸��ģ������ø�ͷ�ļ�����ʹ��
//SD/MMC����ʼ��Ӳ������δ����
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2014.03.01
********************************************************************/
//��ʱ������IAR�Դ�������ʹ�õ�
#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

//�Զ������ݽṹ������ʹ��
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//8��LED�ƣ�������P6�ڣ���ͨ���Ͽ���Դֹͣʹ�ã�ADCʹ��ʱ�Ͽ���Դ
#define LED8DIR         P6DIR
#define LED8            P6OUT                             //P6�ڽ�LED�ƣ�8��

//4����������������P10~P13
#define KeyPort         P1IN                              //�������̽���P10~P13

//���ڲ����ʼ��㣬��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��
#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //�����ʼ��㹫ʽ
#define baud_h         (uchar)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (uchar)(baud_setting)               //��λ

//RS485���ƹܽţ�CTR���ڿ���RS485�����ջ��߷�״̬
#define RS485_CTR1      P5OUT |= BIT2;          //�������øߣ�RS485����״̬
#define RS485_CTR0      P5OUT &= ~BIT2;         //�������õͣ�RS485����״̬

//2.8��TFT������ʾ�������Ӳ������
#define RS_CLR	        P5OUT &= ~BIT5           //RS�õ�
#define RS_SET	        P5OUT |=  BIT5           //RS�ø�

#define RW_CLR	        P5OUT &= ~BIT6           //RW�õ�
#define RW_SET	        P5OUT |=  BIT6           //RW�ø�

#define RD_CLR	        P5OUT &= ~BIT7           //E�õ�
#define RD_SET	        P5OUT |=  BIT7           //E�ø�

#define CS_CLR	        P5OUT &= ~BIT0            //CS�õ�
#define CS_SET	        P5OUT |=  BIT0            //CS�ø�

#define RST_CLR	        P5OUT &= ~BIT3            //RST�õ�
#define RST_SET	        P5OUT |=  BIT3            //RST�ø�

#define LE_CLR	        P5OUT &= ~BIT1            //LE�õ�
#define LE_SET	        P5OUT |=  BIT1            //LE�ø�

//2.8��TFT�����������������Ӳ������
#define PEN_CLR	        P2OUT &= ~BIT0           //PEN�õ�,����������ʱ��Penirq������δ����ʱ�ĸߵ�ƽ��Ϊ�͵�ƽ
#define PEN_SET	        P2OUT |=  BIT0           //PEN�ø�
#define PEN             (P2IN & 0x01)            //P2.0�����ֵ

#define TPDO_CLR	P2OUT &= ~BIT1           //TPDO�õ�
#define TPDO_SET	P2OUT |=  BIT1           //TPDO�ø�
#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1�����ֵ

#define BUSY_CLR	P2OUT &= ~BIT3           //BUSY�õ�
#define BUSY_SET	P2OUT |=  BIT3           //BUSY�ø�

#define TPDI_CLR	P2OUT &= ~BIT4            //TPDI�õ�
#define TPDI_SET	P2OUT |=  BIT4            //TPDI�ø�

#define TPCS_CLR	P2OUT &= ~BIT5            //TPCS�õ�
#define TPCS_SET	P2OUT |=  BIT5            //TPCS�ø�

#define TPCLK_CLR	P2OUT &= ~BIT6            //TPCLK�õ�
#define TPCLK_SET	P2OUT |=  BIT6            //TPCLK�ø�

//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P4DIR                     //���ݿڷ���
#define DataPort        P4OUT                     //P4��Ϊ���ݿ�

//12864/1602Һ�����ƹܽ�
#define RS_CLR	        P5OUT &= ~BIT5           //RS�õ�
#define RS_SET	        P5OUT |=  BIT5           //RS�ø�

#define RW_CLR	        P5OUT &= ~BIT6           //RW�õ�
#define RW_SET	        P5OUT |=  BIT6           //RW�ø�

#define EN_CLR	        P5OUT &= ~BIT7           //E�õ�
#define EN_SET	        P5OUT |=  BIT7           //E�ø�

#define PSB_CLR	        P5OUT &= ~BIT0            //PSB�õͣ����ڷ�ʽ
#define PSB_SET	        P5OUT |=  BIT0            //PSB�øߣ����ڷ�ʽ

#define RESET_CLR	P5OUT &= ~BIT1            //RST�õ�
#define RESET_SET	P5OUT |= BIT1             //RST�ø�

//12864Ӧ��ָ�
#define CLEAR_SCREEN	0x01		          //����ָ�������ACֵΪ00H
#define AC_INIT		0x02		          //��AC����Ϊ00H�����α��Ƶ�ԭ��λ��
#define CURSE_ADD	0x06		          //�趨�α��Ƶ�����ͼ�������ƶ�����Ĭ���α����ƣ�ͼ�����岻����
#define FUN_MODE	0x30		          //����ģʽ��8λ����ָ�
#define DISPLAY_ON	0x0c		          //��ʾ��,��ʾ�α꣬���α�λ�÷���
#define DISPLAY_OFF	0x08		          //��ʾ��
#define CURSE_DIR	0x14		          //�α������ƶ�:AC=AC+1
#define SET_CG_AC	0x40		          //����AC����ΧΪ��00H~3FH
#define SET_DD_AC	0x80                      //����DDRAM AC
#define FUN_MODEK	0x36		          //����ģʽ��8λ��չָ�

//��ɫ���룬TFT��ʾ��
#define White          0xFFFF           													//��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

//NRF2401ģ�������
#define  RF24L01_CE_0        P1OUT &=~BIT5         //CE��P15         
#define  RF24L01_CE_1        P1OUT |= BIT5        

#define  RF24L01_CSN_0       P2OUT &=~BIT7         //CS��P27
#define  RF24L01_CSN_1       P2OUT |= BIT7     

#define  RF24L01_SCK_0       P3OUT &=~BIT3         //SCK��P33
#define  RF24L01_SCK_1       P3OUT |= BIT3   

#define  RF24L01_MISO_0      P3OUT &=~BIT2         //MISO��P32
#define  RF24L01_MISO_1      P3OUT |= BIT2

#define  RF24L01_MOSI_0      P3OUT &=~BIT1         //MOSI��P31
#define  RF24L01_MOSI_1      P3OUT |= BIT1

#define  RF24L01_IRQ_0       P1OUT &=~BIT4         //IRQ��P14     
#define  RF24L01_IRQ_1       P1OUT |= BIT4

//DS18B20���ƽţ����ſ���
#define DQ_IN	        P1DIR &= ~BIT7		  //�������룬DS18B20�ӵ�Ƭ��P53��
#define DQ_OUT	        P1DIR |= BIT7		  //�������
#define DQ_CLR	        P1OUT &= ~BIT7	          //�õ͵�ƽ
#define DQ_SET	        P1OUT |= BIT7	          //�øߵ�ƽ
#define DQ_R	        P1IN & BIT7		  //����ƽ

//�������ͷH1838���ƽţ����ſ���
#define RED_IN	        P1DIR &= ~BIT6	          //�������룬�������ͷ�ӵ�Ƭ��PE3��
#define RED_OUT	        P1DIR |=  BIT6	          //�������
#define RED_L	        P1OUT &= ~BIT6	          //�õ͵�ƽ
#define RED_H	        P1OUT |= BIT6             //�øߵ�ƽ
#define RED_R	        (P1IN & BIT6)	          //����ƽ

//***********************************************************************
//                   ϵͳʱ�ӳ�ʼ�����ⲿ8M����
//***********************************************************************
void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG; 
}

//***********************************************************************
//                   ϵͳʱ�ӳ�ʼ�����ڲ�RC����
//***********************************************************************
void Clock_Init_Inc()
{
  uchar i;
  
 // DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
 // BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
  
  DCOCTL = 0x60 + 0x00;                       //DCOԼ3MHZ��3030KHZ
  BCSCTL1 = DIVA_0 + 0x07;
  BCSCTL2 = SELM_2 + DIVM_0 + SELS + DIVS_0;
}

//***********************************************************************
//                   ϵͳʱ�ӳ�ʼ�����ⲿ32.768K����
//***********************************************************************
void Clock_Init_Ex32768()
{
  uchar i;

  BCSCTL2|=SELM1 + SELM0 + SELS;    //MCLKΪ32.768KHZ��SMCLKΪ8MHZ
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG; 
}

//***********************************************************************
//               MSP430�ڲ����Ź���ʼ��
//***********************************************************************
void WDT_Init()
{
   WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
}
