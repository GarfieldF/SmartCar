#ifndef __K60_OLED_H__
#define __K60_OLED_H__
#include "common.h"
#include "include.h"

#define byte  char
#define uint unsigned int

 #define SCL_PIN PTC5
#define SDA_PIN PTC7
#define RST_PIN PTC9
#define DC_PIN PTC11

#define INIT 0

#define LED_SCL_Init  gpio_init(PTC16,1,INIT) // 时钟初始化定义

#define LED_SDA_Init  gpio_init(PTC17,1,INIT)//数据口D0

#define LED_RST_Init  gpio_init(PTC18,1,INIT)//复位低能电平

#define LED_DC_Init   gpio_init(PTC19,1,INIT)//偏置常低

#define LED_SCLH  gpio_set(PTC16,1)// 时钟定义
#define LED_SCLL  gpio_set(PTC16,0)

#define LED_SDAH  gpio_set(PTC17,1)//数据口D0
#define LED_SDAL  gpio_set(PTC17,0)

#define LED_RSTH  gpio_set(PTC18,1)//复位低能电平
#define LED_RSTL  gpio_set(PTC18,0)

#define LED_DCH   gpio_set(PTC19,1)
#define LED_DCL   gpio_set(PTC19,0)//偏置常低

/************************************************/

void  LEDPIN_Init(void);   //LED控制引脚初始化

void  OLED_Init(void);

 void LED_CLS(void);

 void LED_Set_Pos(byte x, byte y);//设置坐标函数
 void LED_WrDat(uint8 data);   //写数据函数

 void LED_P6x8Char(byte x,byte y,byte ch);
 void LED_P6x8Str(byte x,byte y,byte ch[]);
 void LED_P8x16Char(byte x,byte y,byte ch);
 void LED_P8x16Str(byte x,byte y,byte ch[]);

void  LED_P14x16Str(byte x,byte y,byte ch[]);

 void LED_PrintBMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]);

 void LED_PrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum);//显示二维数组图像

 void LED_Fill(byte dat);

 void LED_PrintValueC(uint8 x, uint8 y,char data);
 void LED_PrintValueI(uint8 x, uint8 y, int data);
 void LED_PrintValueF(uint8 x, uint8 y, float data, uint8 num);

 void LED_Cursor(uint8 cursor_column, uint8 cursor_row);

 extern char logo[];

#endif
