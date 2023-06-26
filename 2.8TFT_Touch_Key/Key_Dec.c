/*****************************************************************************
文件功能：界面按键触摸检测
*****************************************************************************/   
//#include "TFT28.h"											 //TFT相关的函数声明头文件
//#include "Touch.h"


extern 	uchar 	Button_Flag;										//按键按下标志

extern	uchar 	Button_11;                      //第一行第一列按钮
extern	uchar 	Button_12;
extern	uchar	Button_13;

extern	uchar	Button_21;											//第二行第一列按钮
extern	uchar	Button_22;
extern	uchar	Button_23;


extern	uchar 	Button_31;		 									//第三行第一列按钮
extern	uchar	Button_32;
extern	uchar	Button_33;

extern	uchar	Button_41;
extern	uchar 	Button_42;
extern	uchar	Button_43;

extern  uchar   Button_Back;                    //退格按钮
extern uchar   Button_Clear;	                //清除按钮

extern 	uint  	LCD_X,LCD_Y;

static uchar CharCount=0;

#define xs(j)   (j*60+15*j+15)                    //按钮横坐标起点
#define ys(i)   (80+i*50+10*i)										//按钮纵坐标起点
#define xe(j)   (j*60+15*j+15+60)                 //按钮横坐标终点
#define ye(i)   (80+i*50+10*i+50)                //按钮纵坐标终点

// void CoordinateCreate(i,j)
// {
// 		xs=j*70+8*j+8;
// 		ys=37+i*60+7*i;
// 		xe=j*70+8*j+8+70;
// 		ye=37+i*60+7*i+60;
// }

void GUIsquare2pix(uint x0,uint y0,uint x1,uint y1,uint full_colour) ;
void LED(void);
void ADC(void);
void KEY(void);
void DAC_Show(void);
void UART(void);
void CAN(void);
void SDC(void);
void RTC_Show(void);
void TFT_Show(void);
void REV(void);




/*****************************************************************************
//	检测主菜单按钮按下位置，按下区域对应位置标志位置1
//	主菜单共12个按钮，坐标根据按钮位置改变，自行计算
*****************************************************************************/
void Detect_TP(void)
{

     if(Getpix()==1)
      {
       /*第一列4个按钮11,21,31,41*/
	if((LCD_X>=xs(0))&& (LCD_X<=xe(0)))     //依据公式参考桌面绘制时的公式，main函数中，xs和xe，横坐标起点和终点
	{
	if((LCD_Y>=ys(0)) &&(LCD_Y<=ye(0)))  //依据公式，ys和ye，纵坐标起点和终点
	{
          Button_11=1;
	  GUIsquare2pix(xs(0),ys(0),xe(0),ye(0),Red);
	  delay_ms(1);
	  delay_ms(1);
	  delay_ms(1);
	  while(PEN==0);
	  GUIsquare2pix(xs(0),ys(0),xe(0),ye(0),Red);
	}
					
        else if((LCD_Y>=ys(1)) &&(LCD_Y<=ye(1)))
		
        {
        
          Button_21=1;
		
          GUIsquare2pix(xs(0),ys(1),xe(0),ye(1),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(0),ys(1),xe(0),ye(1),Red);
		
        }
	
        else if((LCD_Y>=ys(2)) &&(LCD_Y<=ye(2)))
	
        {

          Button_31=1;
		
          GUIsquare2pix(xs(0),ys(2),xe(0),ye(2),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(0),ys(2),xe(0),ye(2),Red);
		
        }
        
        else if((LCD_Y>=ys(3)) &&(LCD_Y<=ye(3)))
	
        {

          Button_41=1;
		
          GUIsquare2pix(xs(0),ys(3),xe(0),ye(3),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(0),ys(3),xe(0),ye(3),Red);
		
        }
	
        }
      /*第二列4个按钮12,22,32,42*/
        if((LCD_X>=xs(1))&& (LCD_X<=xe(1)))     //依据公式参考桌面绘制时的公式，main函数中，xs和xe，横坐标起点和终点
	
        {
	
          if((LCD_Y>=ys(0)) &&(LCD_Y<=ye(0)))  //依据公式，ys和ye，纵坐标起点和终点
		
          {
          
            Button_12=1;
		
            GUIsquare2pix(xs(1),ys(0),xe(1),ye(0),Red);
		
            delay_ms(1);
		
            delay_ms(1);
		
            delay_ms(1);
		
            while(PEN==0);
		
            GUIsquare2pix(xs(1),ys(0),xe(1),ye(0),Red);
		
          }
		
          
          else if((LCD_Y>=ys(1)) &&(LCD_Y<=ye(1)))
		
          {
          
            Button_22=1;
		
            GUIsquare2pix(xs(1),ys(1),xe(1),ye(1),Red);
		
            delay_ms(1);
		
            delay_ms(1);
		
            delay_ms(1);
		
            while(PEN==0);
		
            GUIsquare2pix(xs(1),ys(1),xe(1),ye(1),Red);
		
          }
		
          else if((LCD_Y>=ys(2)) &&(LCD_Y<=ye(2)))
		
          {
            Button_32=1;
		
            GUIsquare2pix(xs(1),ys(2),xe(1),ye(2),Red);
		
            delay_ms(1);
		
            delay_ms(1);
		
            delay_ms(1);
		
            while(PEN==0);
		
            GUIsquare2pix(xs(1),ys(2),xe(1),ye(2),Red);
		
          }
          else if((LCD_Y>=ys(3)) &&(LCD_Y<=ye(3)))
		
          {
            Button_42=1;
		
            GUIsquare2pix(xs(1),ys(3),xe(1),ye(3),Red);
		
            delay_ms(1);
		
            delay_ms(1);
		
            delay_ms(1);
		
            while(PEN==0);
		
            GUIsquare2pix(xs(1),ys(3),xe(1),ye(3),Red);
		
          }
		
        }
	
        /*第三列4个按钮13,23,33,43*/
      if((LCD_X>=xs(2))&& (LCD_X<=xe(2)))     //依据公式参考桌面绘制时的公式，main函数中，xs和xe，横坐标起点和终点
	
      {
	
        if((LCD_Y>=ys(0)) &&(LCD_Y<=ye(0)))  //依据公式，ys和ye，纵坐标起点和终点
	
        {
        
          Button_13=1;
		
          GUIsquare2pix(xs(2),ys(0),xe(2),ye(0),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(2),ys(0),xe(2),ye(0),Red);
		
        }        
		
        else if((LCD_Y>=ys(1)) &&(LCD_Y<=ye(1)))
	
        {
        
          Button_23=1;
		
          GUIsquare2pix(xs(2),ys(1),xe(2),ye(1),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(2),ys(1),xe(2),ye(1),Red);
		
        }
	
        else if((LCD_Y>=ys(2)) &&(LCD_Y<=ye(2)))
	
        {

          Button_33=1;
		
          GUIsquare2pix(xs(2),ys(2),xe(2),ye(2),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(2),ys(2),xe(2),ye(2),Red);
		
        }
        else if((LCD_Y>=ys(3)) &&(LCD_Y<=ye(3)))
	
        {

          Button_43=1;
		
          GUIsquare2pix(xs(2),ys(3),xe(2),ye(3),Red);
		
          delay_ms(1);
		
          delay_ms(1);
		
          delay_ms(1);
		
          while(PEN==0);
		
          GUIsquare2pix(xs(2),ys(3),xe(2),ye(3),Red);
		
        }
	
      }
	
      
      }

}
/*****************************************************************************
键值显示函数，B键可以退格，C键则清除，清除后默认显示0
*****************************************************************************/
void ShowBotton(void)
{	
	Detect_TP();
	/*第一排三个按钮功能*/
	if(Button_11==1) 
	{	
          
          LCD_PutSingleChar2435(200-CharCount*24,35,1,White,Black);  //显示对应的键值
	  Button_11=0;                                              //按键标志位清零
          GUIsquare2pix(xs(0),ys(0),xe(0),ye(0),White);             //选中边框消除
          if(CharCount<9)CharCount++;                               //每行最多显示9个键值，超过则清除整个数字框后重新显示后续键值
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,1,White,Black);CharCount++;}
	}
	
	if(Button_12==1) 
	{  		
         LCD_PutSingleChar2435(200-CharCount*24,35,2,White,Black);
	 Button_12=0;
         GUIsquare2pix(xs(1),ys(0),xe(1),ye(0),White);
         if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,2,White,Black);CharCount++;}
	}
	if(Button_13==1) 
	{  		
         LCD_PutSingleChar2435(200-CharCount*24,35,3,White,Black);
	 Button_13=0;
         GUIsquare2pix(xs(2),ys(0),xe(2),ye(0),White);
         if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,3,White,Black);CharCount++;}
	}
        /*第二排三个按钮功能*/
	if(Button_21==1) 
	{  		
        LCD_PutSingleChar2435(200-CharCount*24,35,4,White,Black);
	Button_21=0;
        GUIsquare2pix(xs(0),ys(1),xe(0),ye(1),White);
	if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,4,White,Black);CharCount++;}	
        }
	
        if(Button_22==1) 
	
	{	

          LCD_PutSingleChar2435(200-CharCount*24,35,5,White,Black);
		
          Button_22=0;
          GUIsquare2pix(xs(1),ys(1),xe(1),ye(1),White);
          if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,5,White,Black);CharCount++;}
        }
	
	if(Button_23==1) 
		
        {  		

          LCD_PutSingleChar2435(200-CharCount*24,35,6,White,Black);
		
          Button_23=0;
          GUIsquare2pix(xs(2),ys(1),xe(2),ye(1),White);
        if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,6,White,Black);CharCount++;}
	}
        /*第三排三个按钮功能*/
	if(Button_31==1) 
		
        {  		

          LCD_PutSingleChar2435(200-CharCount*24,35,7,White,Black);
		
          Button_31=0;
          GUIsquare2pix(xs(0),ys(2),xe(0),ye(2),White);
	if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,7,White,Black);CharCount++;}
        }
	
        if(Button_32==1) 
	
	{  		

          LCD_PutSingleChar2435(200-CharCount*24,35,8,White,Black);
		
          Button_32=0;
          GUIsquare2pix(xs(1),ys(2),xe(1),ye(2),White);
          if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,8,White,Black);CharCount++;}
        }

       if(Button_33==1) 
	
       {	

         LCD_PutSingleChar2435(200-CharCount*24,35,9,White,Black);
		
         Button_33=0;
         GUIsquare2pix(xs(2),ys(2),xe(2),ye(2),White);
         if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,9,White,Black);CharCount++;}
       }
        /*第四排三个按钮功能*/
	
	if(Button_41==1) 
		
        {  		

          LCD_PutSingleChar2435(200-CharCount*24,35,0,White,Black);
		
          Button_41=0;
          GUIsquare2pix(xs(0),ys(3),xe(0),ye(3),White);
          if(CharCount<9)CharCount++;
          else{ CharCount=0;LCD_Full(2,238,30,68,Black);LCD_PutSingleChar2435(200-CharCount*24,35,0,White,Black);CharCount++;}
        }
	if(Button_42==1) 
	
	{  		

          if(CharCount>=1)LCD_PutSingleChar2435(200-(CharCount-1)*24,35,0x0c,Black,Black);
		
          Button_42=0;
          GUIsquare2pix(xs(1),ys(3),xe(1),ye(3),White);
          if(CharCount>0)CharCount--;
        }
	if(Button_43==1) 
		
        {  		
          LCD_Full(2,238,30,68,Black);
          LCD_PutSingleChar2435(200,35,0,White,Black);
		
          Button_43=0;
          GUIsquare2pix(xs(2),ys(3),xe(2),ye(3),White);
          CharCount=0;
          
        }
}
