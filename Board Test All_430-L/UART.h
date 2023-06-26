#include <msp430x14x.h>         //430ͷ�ļ�

unsigned char usart_tx_data,usart_rx_data;
unsigned char testcount=0;
//*************************************************************************
//               MSP430���ڳ�ʼ��
//*************************************************************************
void UART_Init()
{
  U0CTL|=SWRST;               //��λSWRST
  U0CTL|=CHAR;                //8λ����ģʽ 
  U0TCTL|=SSEL1;              //SMCLKΪ����ʱ��
  U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //΢���Ĵ���Ϊ0��������9600bps
  ME1|=UTXE0;                 //UART1����ʹ��
  ME1|=URXE0;                 //UART1����ʹ��
  U0CTL&=~SWRST;
  IE1|=URXIE0;                //�����ж�ʹ��λ
  
  P3SEL|= BIT4;               //����IO��Ϊ��ͨI/Oģʽ
  P3DIR|= BIT4;               //����IO�ڷ���Ϊ���
  P3SEL|= BIT5;
}

void UART_Disable(void)
{
  U0CTL|=SWRST + CHAR;                //��λSWRST��8λ����ģʽ
  U0TCTL|=SSEL1;                      //SMCLKΪ����ʱ��
  U0BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                        //΢���Ĵ���Ϊ0��������9600bps
  ME1&=~UTXE0;                        //UART0���͹ر�
  ME1&=~URXE0;                        //UART0���չر�
  U0CTL&=~SWRST;
  IE1 &=~URXIE0;                      //�����жϹر�
  
  P3SEL=0x00;;                        //����IO��Ϊ��ͨIOģʽ
  P3DIR|= BIT4;                       //����TXD0�ڷ���Ϊ���
}

//*************************************************************************
//              ����0�������ݺ���
//*************************************************************************

void Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //���ͼĴ����յ�ʱ��������
    U0TXBUF=data;
    delay_ms(20);                         //��ʱ20ms
}

//*************************************************************************
//               �������Դ��� 0 �Ľ����ж�
//*************************************************************************

#pragma vector=UART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  //uchar data=0;
  usart_rx_data=U0RXBUF;              //���յ������ݴ�����
  //Send_Byte(data);                  //�����յ��������ٷ��ͳ�ȥ
  
  if(usart_rx_data==(testcount)){LED8 = usart_rx_data;}
  else LED8 = 0xff;
  delay_ms(400);
}

//*************************************************************************
//           ���ڲ��Ժ���
//*************************************************************************
void Test_UART(void)
{ 
  delay_ms(200);                      //����һ��200ms����ʱ��������̶���
  
  usart_tx_data=(++testcount);        //ÿ����һ�Σ����͵����ݼ�һ���������Ա�֤���Ե�׼ȷ��

  UART_Init();                        //�������ó�ʼ��

  _EINT();                            //�����ж�

  Send_Byte(usart_tx_data);
  

}