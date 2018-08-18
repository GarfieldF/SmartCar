/******************** LQ_K60_函数库 v1.0 *************************************
 * 功能             ：OV7620实现光标追踪
 * 日期             ：2016-03-21
 * 实验平台         ：龙邱K60P144SYSVG母板VC
 * 晶振             ：有源50MHZ
 * 内核             ：200MHZ
 * 总线             ：40MHZ
 * 开发环境         ：IAR 7.3及以上
 * 作者             ：chiusir
 * 淘宝店           ：https://longqiu.taobao.com
 * 龙丘智能车讨论群 ：202949437
*************************************************************/

#ifndef __KEY_H__
#define __KEY_H__

//定义模块号
typedef enum
{

	DSW1=1,
	DSW2=2,
	DSW3=3,
	DSW4=4,//DIP SWitch 拨码开关,1-6
	DSW5=5,
	DSW6=6,

} KEYn_e;

// 按键分布顺序：
//  EXIT  UP    OK
//  LEFT  DOWN  RIGHT
// 如按下第一个按键EXIT,返回KEY_EXIT

#define BEEP PTC6

#define DIP_DOWN 1
#define DIP_UP 0

#define  KEY_UP         1
#define  KEY_UP_PORT    PTD1   //上键 

#define  KEY_DOWN       2
#define  KEY_DOWN_PORT  PTD2   //下键

#define  KEY_LEFT       3
#define  KEY_LEFT_PORT  PTD3    //左键    

#define  KEY_RIGHT      4
#define  KEY_RIGHT_PORT PTD4    //右键  

// #define  KEY_OK         5
// #define  KEY_OK_PORT    PTD5    //确认键 
 
//#define	RLED	PTA16
//#define	YLED	PTA19 ???

/*********************** 函数 **************************/
//初始化
extern void IO_Init(void);//按键和拨码开关初始化
extern unsigned char DSW_Read(unsigned char keyno);
extern unsigned char Key_Scan(unsigned char mode);
extern unsigned char DSW_Scan(void);
extern void beep_on(void);
extern void beep_off(void);
extern void beep_ms(unsigned int time);

//按键扫描

/********************************************************************/

#endif
