#include "main.h"

//sbit RS=P2^6; //串口时为CS
//sbit RW=P2^5; //串口为SID
//sbit E=P2^4; //串口为时钟SCLK
//sbit RST=P2^0;

//sbit PSB=P2^3;

#define Lcm_Data P1

#define uchar unsigned char 
#define uint unsigned int 
extern uint8_t signlcd;
void CS(unsigned char State);
extern void CLK(unsigned char State);
extern void CLK2(unsigned char State);
void SIO(unsigned char State);
void Reset(unsigned char State);
void Lcm_Wr_Data(uchar wrdata); //写数据
void Lcm_Wr_Command(uchar wrcommand); //写指令
void Senddata(uchar lcmdata);  //串口数据转换
void Lcm_Init(void);//液晶初始化
void Lcm_GotoXY(uchar pos_X,uchar pos_y,uchar sign);
void Lcm_Disp_Onechar(uchar onechar);//显示单个字符
void Lcm_Disp_String(uchar *string);//显示字符串
void Wr_Gdram(uchar pos_x,uchar pos_y,uint length,uchar width,uchar *table);
void Wr_Gdram1(uchar pos_x,uchar pos_y,uint length,uchar width);


void Clean_Gdram(void);//清除GDRAM
void Wr_Cgram(uchar addr,uchar *table);
void Disp_Cgram(uchar addr_data);
void Delay_1ms(uint x);//1ms延时
void Lcm_Delay(void);
extern uint8_t pic[];
extern uint8_t font1[];
extern uint8_t font2[];
extern uint8_t font3[];
extern uint8_t font4[];
