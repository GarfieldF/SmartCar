/******************** LQ_K60_������ v1.0 *************************************
 * ����             ��OV7620ʵ�ֹ��׷��
 * ����             ��2016-03-21
 * ʵ��ƽ̨         ������K60P144SYSVGĸ��VC
 * ����             ����Դ50MHZ
 * �ں�             ��200MHZ
 * ����             ��40MHZ
 * ��������         ��IAR 7.3������
 * ����             ��chiusir
 * �Ա���           ��https://longqiu.taobao.com
 * �������ܳ�����Ⱥ ��202949437
*************************************************************/

#ifndef __KEY_H__
#define __KEY_H__

//����ģ���
typedef enum
{

	DSW1=1,
	DSW2=2,
	DSW3=3,
	DSW4=4,//DIP SWitch ���뿪��,1-6
	DSW5=5,
	DSW6=6,

} KEYn_e;

// �����ֲ�˳��
//  EXIT  UP    OK
//  LEFT  DOWN  RIGHT
// �簴�µ�һ������EXIT,����KEY_EXIT

#define BEEP PTC6

#define DIP_DOWN 1
#define DIP_UP 0

#define  KEY_UP         1
#define  KEY_UP_PORT    PTD1   //�ϼ� 

#define  KEY_DOWN       2
#define  KEY_DOWN_PORT  PTD2   //�¼�

#define  KEY_LEFT       3
#define  KEY_LEFT_PORT  PTD3    //���    

#define  KEY_RIGHT      4
#define  KEY_RIGHT_PORT PTD4    //�Ҽ�  

// #define  KEY_OK         5
// #define  KEY_OK_PORT    PTD5    //ȷ�ϼ� 
 
//#define	RLED	PTA16
//#define	YLED	PTA19 ???

/*********************** ���� **************************/
//��ʼ��
extern void IO_Init(void);//�����Ͳ��뿪�س�ʼ��
extern unsigned char DSW_Read(unsigned char keyno);
extern unsigned char Key_Scan(unsigned char mode);
extern unsigned char DSW_Scan(void);
extern void beep_on(void);
extern void beep_off(void);
extern void beep_ms(unsigned int time);

//����ɨ��

/********************************************************************/

#endif
