#include <msp430x14x.h>         //430头文件

unsigned char usart_tx_data,usart_rx_data;
unsigned char testcount=0;
//*************************************************************************
//               MSP430串口初始化
//*************************************************************************
void UART_Init()
{
  U0CTL|=SWRST;               //复位SWRST
  U0CTL|=CHAR;                //8位数据模式 
  U0TCTL|=SSEL1;              //SMCLK为串口时钟
  U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //微调寄存器为0，波特率9600bps
  ME1|=UTXE0;                 //UART1发送使能
  ME1|=URXE0;                 //UART1接收使能
  U0CTL&=~SWRST;
  IE1|=URXIE0;                //接收中断使能位
  
  P3SEL|= BIT4;               //设置IO口为普通I/O模式
  P3DIR|= BIT4;               //设置IO口方向为输出
  P3SEL|= BIT5;
}

void UART_Disable(void)
{
  U0CTL|=SWRST + CHAR;                //复位SWRST，8位数据模式
  U0TCTL|=SSEL1;                      //SMCLK为串口时钟
  U0BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                        //微调寄存器为0，波特率9600bps
  ME1&=~UTXE0;                        //UART0发送关闭
  ME1&=~URXE0;                        //UART0接收关闭
  U0CTL&=~SWRST;
  IE1 &=~URXIE0;                      //接收中断关闭
  
  P3SEL=0x00;;                        //设置IO口为普通IO模式
  P3DIR|= BIT4;                       //设置TXD0口方向为输出
}

//*************************************************************************
//              串口0发送数据函数
//*************************************************************************

void Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //发送寄存器空的时候发送数据
    U0TXBUF=data;
    delay_ms(20);                         //延时20ms
}

//*************************************************************************
//               处理来自串口 0 的接收中断
//*************************************************************************

#pragma vector=UART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  //uchar data=0;
  usart_rx_data=U0RXBUF;              //接收到的数据存起来
  //Send_Byte(data);                  //将接收到的数据再发送出去
  
  if(usart_rx_data==(testcount)){LED8 = usart_rx_data;}
  else LED8 = 0xff;
  delay_ms(400);
}

//*************************************************************************
//           串口测试函数
//*************************************************************************
void Test_UART(void)
{ 
  delay_ms(200);                      //增加一个200ms的延时，避免键盘抖动
  
  usart_tx_data=(++testcount);        //每测试一次，发送的数据加一，这样可以保证测试的准确性

  UART_Init();                        //串口设置初始化

  _EINT();                            //开总中断

  Send_Byte(usart_tx_data);
  

}