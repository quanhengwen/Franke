#include "main.h"

//sbit RS=P2^6; //����ʱΪCS
//sbit RW=P2^5; //����ΪSID
//sbit E=P2^4; //����Ϊʱ��SCLK
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
void Lcm_Wr_Data(uchar wrdata); //д����
void Lcm_Wr_Command(uchar wrcommand); //дָ��
void Senddata(uchar lcmdata);  //��������ת��
void Lcm_Init(void);//Һ����ʼ��
void Lcm_GotoXY(uchar pos_X,uchar pos_y,uchar sign);
void Lcm_Disp_Onechar(uchar onechar);//��ʾ�����ַ�
void Lcm_Disp_String(uchar *string);//��ʾ�ַ���
void Wr_Gdram(uchar pos_x,uchar pos_y,uint length,uchar width,uchar *table);
void Wr_Gdram1(uchar pos_x,uchar pos_y,uint length,uchar width);


void Clean_Gdram(void);//���GDRAM
void Wr_Cgram(uchar addr,uchar *table);
void Disp_Cgram(uchar addr_data);
void Delay_1ms(uint x);//1ms��ʱ
void Lcm_Delay(void);
extern uint8_t pic[];
extern uint8_t font1[];
extern uint8_t font2[];
extern uint8_t font3[];
extern uint8_t font4[];
