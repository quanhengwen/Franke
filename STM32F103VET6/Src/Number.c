#include "Number.h"
#define uchar unsigned char
#define uint unsigned int

uchar Num0[] =
{
    //U+0030(0)
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xFF, 0xC0, 0x03, 0xFF, 0xE0, 0x03, 0xC1, 0xE0, 0x07,
    0x80, 0xF0, 0x0F, 0x00, 0x70, 0x0F, 0x00, 0x78, 0x0E, 0x00, 0x38, 0x0E, 0x00, 0x38, 0x1E, 0x00,
    0x3C, 0x1E, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C,
    0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1C, 0x00, 0x3C, 0x1E,
    0x00, 0x38, 0x1E, 0x00, 0x38, 0x0E, 0x00, 0x38, 0x0E, 0x00, 0x78, 0x0F, 0x00, 0x70, 0x07, 0x80,
    0xF0, 0x07, 0xC1, 0xE0, 0x03, 0xFF, 0xC0, 0x01, 0xFF, 0x80, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
};

uchar Num1[] =
{
    //U+0031(1)
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x7F, 0x00, 0x03,
    0xFF, 0x00, 0x03, 0xEF, 0x00, 0x03, 0x8F, 0x00, 0x02, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
};

uchar Num2[] =
{

    //U+0032(2)
    0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x03, 0xFF, 0x80, 0x07, 0xFF, 0xC0, 0x0F, 0x83, 0xE0, 0x0E,
    0x01, 0xF0, 0x0C, 0x00, 0xF0, 0x08, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00,
    0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x01, 0xE0, 0x00, 0x03, 0xC0,
    0x00, 0x07, 0x80, 0x00, 0x0F, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x7C, 0x00, 0x00, 0xF0, 0x00, 0x01,
    0xE0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0x80, 0x00, 0x0F, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00,
    0x00, 0x1E, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x1F, 0xFF, 0xF8, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x00,
};

uchar Num3[] =
{
    //U+0033(3)
    0x00, 0x00, 0x00, 0x01, 0xFE, 0x00, 0x07, 0xFF, 0x80, 0x07, 0xFF, 0xC0, 0x06, 0x07, 0xE0, 0x00,
    0x01, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0xE0, 0x00, 0x01, 0xE0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0x80, 0x03, 0xFF, 0x00, 0x03, 0xFE, 0x00,
    0x03, 0xFF, 0x80, 0x00, 0x07, 0xE0, 0x00, 0x01, 0xE0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x70, 0x00,
    0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0xF0, 0x00, 0x01,
    0xE0, 0x0E, 0x07, 0xE0, 0x0F, 0xFF, 0xC0, 0x0F, 0xFF, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0x00,
};

uchar Num4[] =
{
    //U+0034(4)
    0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x03, 0xC0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0xC0, 0x00,
    0x07, 0xC0, 0x00, 0x0F, 0xC0, 0x00, 0x1D, 0xC0, 0x00, 0x1D, 0xC0, 0x00, 0x39, 0xC0, 0x00, 0x79,
    0xC0, 0x00, 0x71, 0xC0, 0x00, 0xE1, 0xC0, 0x01, 0xE1, 0xC0, 0x01, 0xC1, 0xC0, 0x03, 0x81, 0xC0,
    0x07, 0x81, 0xC0, 0x0F, 0x01, 0xC0, 0x0E, 0x01, 0xC0, 0x1C, 0x01, 0xC0, 0x38, 0x01, 0xC0, 0x7F,
    0xFF, 0xFC, 0x7F, 0xFF, 0xFC, 0x7F, 0xFF, 0xFC, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01,
    0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
};

uchar Num5[] =
{
    //U+0035(5)
    0x00, 0x00, 0x00, 0x03, 0xFF, 0xF0, 0x03, 0xFF, 0xF0, 0x03, 0xFF, 0xF0, 0x03, 0x80, 0x00, 0x03,
    0x80, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0xFE, 0x00, 0x07, 0xFF, 0x80, 0x07, 0xFF, 0xC0,
    0x00, 0x03, 0xE0, 0x00, 0x01, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00,
    0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x70, 0x00, 0x00, 0xF0, 0x08, 0x01,
    0xF0, 0x0E, 0x03, 0xE0, 0x0F, 0xFF, 0xC0, 0x0F, 0xFF, 0x80, 0x03, 0xFC, 0x00, 0x00, 0x00, 0x00,
};


uchar Num6[] =
{
    //U+0036(6)
    0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x3F, 0xF0, 0x00, 0xFF, 0xF0, 0x01, 0xF8, 0x10, 0x01,
    0xE0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0x80, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x0E, 0x00,
    0x00, 0x0E, 0x00, 0x00, 0x0E, 0x3F, 0x80, 0x0E, 0x7F, 0xE0, 0x1E, 0xFF, 0xF0, 0x1F, 0xC1, 0xF0,
    0x1F, 0x80, 0x78, 0x1F, 0x00, 0x38, 0x1E, 0x00, 0x3C, 0x1E, 0x00, 0x3C, 0x1E, 0x00, 0x3C, 0x0E,
    0x00, 0x1C, 0x0E, 0x00, 0x3C, 0x0E, 0x00, 0x3C, 0x0F, 0x00, 0x38, 0x07, 0x00, 0x78, 0x07, 0x80,
    0x78, 0x03, 0xE1, 0xF0, 0x01, 0xFF, 0xE0, 0x00, 0xFF, 0xC0, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00,
};

uchar Num7[] =
{
    //U+0037(7)
    0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFC, 0x1F, 0xFF, 0xFC, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x78, 0x00,
    0x00, 0x70, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x01, 0xE0, 0x00, 0x01, 0xC0, 0x00, 0x03,
    0xC0, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x0E, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x3C, 0x00, 0x00,
    0x38, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0xF0,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00,
};

uchar Num8[] =
{
    //U+0038(8)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x01, 0xFF, 0x80, 0x03, 0xFF, 0xE0, 0x07, 0xC1, 0xE0, 0x07,
    0x80, 0xF0, 0x0F, 0x00, 0x70, 0x0F, 0x00, 0x78, 0x0F, 0x00, 0x78, 0x0F, 0x00, 0x78, 0x0F, 0x00,
    0x70, 0x07, 0x00, 0x70, 0x07, 0x80, 0xF0, 0x03, 0xC3, 0xE0, 0x01, 0xFF, 0xC0, 0x00, 0xFF, 0x80,
    0x03, 0xFF, 0xE0, 0x07, 0xC1, 0xF0, 0x0F, 0x00, 0x78, 0x0E, 0x00, 0x78, 0x1E, 0x00, 0x3C, 0x1E,
    0x00, 0x3C, 0x1E, 0x00, 0x3C, 0x1E, 0x00, 0x3C, 0x1E, 0x00, 0x3C, 0x1E, 0x00, 0x78, 0x0F, 0x00,
    0x78, 0x0F, 0xC1, 0xF0, 0x07, 0xFF, 0xE0, 0x01, 0xFF, 0xC0, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00,
};

uchar Num9[] =
{
    //U+0039(9)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x01, 0xFF, 0x80, 0x03, 0xFF, 0xC0, 0x07, 0xC3, 0xE0, 0x0F,
    0x00, 0xF0, 0x0E, 0x00, 0x70, 0x1E, 0x00, 0x78, 0x1E, 0x00, 0x38, 0x1C, 0x00, 0x38, 0x1C, 0x00,
    0x38, 0x1C, 0x00, 0x38, 0x1E, 0x00, 0x3C, 0x1E, 0x00, 0x3C, 0x0E, 0x00, 0x7C, 0x0F, 0x00, 0xFC,
    0x07, 0xC1, 0xFC, 0x07, 0xFF, 0xB8, 0x01, 0xFF, 0x38, 0x00, 0x7E, 0x38, 0x00, 0x00, 0x38, 0x00,
    0x00, 0x38, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x03,
    0xE0, 0x04, 0x07, 0xC0, 0x07, 0xFF, 0x80, 0x07, 0xFE, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00,
};


uchar Point[] =
{
    //U+FF0E(．)/*16*16*/
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00
};

//℃太阳警报---------1
uchar SunAlarm[] =
{
   /*
		//U+2103(℃)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0xC0, 0x96, 0x20, 0x64, 0x20, 0x04, 0x00, 0x04, 0x00,
    0x04, 0x00, 0x04, 0x20, 0x06, 0x20, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    //U+00B0(°)
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x0E, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    //    //U+0043(C)
   	//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x11, 0x00, 0x20, 0x00, 0x20, 0x00,
   	//		0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x31, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		*/		
		
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x02,0xE8,0x00,
		0x01,0x10,0x00,0x02,0x08,0x00,0x06,0x0C,0x00,0x02,0x08,0x00,0x01,0x10,0x00,0x02,
		0xE8,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00
};
//℃雪警报---------2
uchar DegreeSnowAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x10,0xA1,0x00,0x21,0x10,0x80,0x0E,0x0E,0x00,0x06,
		0x0C,0x00,0x0A,0x0A,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00,
};

//℃大雪雨警报---------3
uchar DegreeSnowRainAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x02,0x08,0x00,0x02,0x08,0x00,0x10,0x41,0x00,0x10,
		0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00,
};

//℃风警报---------4
uchar DegreeWindAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x08,0x70,0x00,0x0E,0x40,0x00,
		0x06,0x40,0x00,0x03,0xF8,0x00,0x00,0x4C,0x00,0x00,0x4E,0x00,0x01,0xC2,0x00,0x01,
		0x80,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00,
};

//华氏度太阳警报---------5
uchar FahrenheitSunAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x02,0xE8,0x00,
		0x01,0x10,0x00,0x02,0x08,0x00,0x06,0x0C,0x00,0x02,0x08,0x00,0x01,0x10,0x00,0x02,
		0xE8,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00
};

//华氏度雪警报---------6
uchar FahrenheitSnowAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x10,0xA1,0x00,0x21,0x10,0x80,0x0E,0x0E,0x00,0x06,
		0x0C,0x00,0x0A,0x0A,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00,
};

//华氏度大雪雨警报---------7
uchar FahrenheitSnowRainAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x02,0x08,0x00,0x02,0x08,0x00,0x10,0x41,0x00,0x10,
		0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00,
};

//华氏度风警报---------8
uchar FahrenheitWindAlarm [] =
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x08,0x70,0x00,0x0E,0x40,0x00,
		0x06,0x40,0x00,0x03,0xF8,0x00,0x00,0x4C,0x00,0x00,0x4E,0x00,0x01,0xC2,0x00,0x01,
		0x80,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x12,0x09,0x00,0x14,0x05,
		0x00,0x14,0x45,0x00,0x14,0x05,0x00,0x12,0x09,0x00,0x08,0x02,0x00,0x00,0x00,0x00,
};



//℃太阳运行---------9
uchar SunRun	[]	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x02,0xE8,0x00,
		0x01,0x10,0x00,0x02,0x08,0x00,0x06,0x0C,0x00,0x02,0x08,0x00,0x01,0x10,0x00,0x02,
		0xE8,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℃雪运行---------10
uchar DegreeSnowRun []	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x10,0xA1,0x00,0x21,0x10,0x80,0x0E,0x0E,0x00,0x06,
		0x0C,0x00,0x0A,0x0A,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℃大雪雨运行---------11
uchar DegreeSnowRainRun	[]	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x02,0x08,0x00,0x02,0x08,0x00,0x10,0x41,0x00,0x10,
		0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℃风运行---------12
uchar DegreeWindRun []	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x14,0xE0,0x00,0x09,0x10,0x00,0x02,0x00,0x00,0x02,
		0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x10,0x00,0x00,0xE0,
		0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x08,0x70,0x00,0x0E,0x40,0x00,
		0x06,0x40,0x00,0x03,0xF8,0x00,0x00,0x4C,0x00,0x00,0x4E,0x00,0x01,0xC2,0x00,0x01,
		0x80,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℉太阳运行---------13
uchar FahrenheitSunRun []	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x02,0xE8,0x00,
		0x01,0x10,0x00,0x02,0x08,0x00,0x06,0x0C,0x00,0x02,0x08,0x00,0x01,0x10,0x00,0x02,
		0xE8,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℉雪运行---------14
uchar FahrenheitSnowRun []	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x10,0xA1,0x00,0x21,0x10,0x80,0x0E,0x0E,0x00,0x06,
		0x0C,0x00,0x0A,0x0A,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℉大雪雨运行---------15
uchar FahrenheitSnowRainRun []	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x0A,0x0A,0x00,0x06,0x0C,0x00,0x0E,0x0E,0x00,0x21,0x10,0x80,
		0x10,0xA1,0x00,0x3F,0xFF,0x80,0x02,0x08,0x00,0x02,0x08,0x00,0x10,0x41,0x00,0x10,
		0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};

//℉风运行---------16
uchar FahrenheitWindRun []	=
{
		0x00,0x00,0x00,0x08,0x00,0x00,0x15,0xF0,0x00,0x09,0x00,0x00,0x01,0x00,0x00,0x01,
		0x00,0x00,0x01,0xF0,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x08,0x70,0x00,0x0E,0x40,0x00,
		0x06,0x40,0x00,0x03,0xF8,0x00,0x00,0x4C,0x00,0x00,0x4E,0x00,0x01,0xC2,0x00,0x01,
		0x80,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x02,0x20,0x00,0x05,0x00,0x00,0x04,0x90,
		0x00,0x01,0x60,0x00,0x02,0x00,0x00,0x15,0x00,0x00,0x08,0x80,0x00,0x00,0x80,0x00,
};
