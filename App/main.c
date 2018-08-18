/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"



//ͼ�����߱���
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_H][CAMERA_W]; //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
uint8 img2[60][80];
uint8 width[60];
uint8 center[60];                                      //�������鴢������
uint8 center_ave=0;                                     //�������߾�ֵ����
uint8 Left_line[60],Right_line[60];                             //��������洢���ұ���
int16 middleline_last=40,middleline;
uint8 sdiam=0;
uint8 swan_flag=0;
//ͼ��·��־λ
uint8 Hlin_flag =0;//����·����߶���
uint8 Hlin_flag0=0;//����·����߶���ԭ��
uint8 Hrin_flag =0;//����·�ұ��߶���
uint8 Hrin_flag0=0;//����·�ұ��߶���ԭ��

uint8 Hlin_flag1=0;//�뻷·����
uint8 Hrin_flag1=0;//�뻷·����

uint8 Hlout_flag =0;
uint8 Hlout_flag0=0;
uint8 Hrout_flag =0;
uint8 Hrout_flag0=0;

uint8 Huanlzhi_flag;
uint8 Huanl_point;
uint16 Huanlzhi_point;
//ͼ���־λ
uint8 stop_flag=0;
uint8 shizi_FLAG=0;
uint8 stra_flag=0;
uint8 zuoguaidian=0,youguaidian=0,zuoshangguaidian=0,youshangguaidian=0;
uint8 guoguaidian_flag=0,guaidian_flag=0;//zuoguaidian_flag=0, youguaidian_flag=0,zuoshangguaidian_flag=0,youshangguaidian_flag=0;
//·��
uint16 Hdist1=0;//�뻷·����·��
uint16 Hdist2=0;//����·����·��

//servo
uint16 servo_duty=0;
uint16 servo_mid=SERVO_MID;

//�������
uint16 speed=0;
uint16 speed_set=65;
int16 speed_error[10]={0,0,0,0,0,0,0,0,0,0};
int16 motor_pwm=0;
uint16 motor_Ki=60;
uint16 motor_Kp=15;
uint16 motor_Kd=5;

uint16 distance=0;
//����ʱ��

/*!
*  @brief      main���� �޸�ʱ��:2018.4.14
 *  @since      v5.3
 *  @note       ̩ɽ����������
 */
uint32 run_time=0;
void  main(void)
{

         
	BSP_init();//�ܳ�ʼ������;


	while(1)
	{
          		 pit_time_start(PIT3);
                      
#if CAMERA_MODE
		camera_get_img();    //����ͷ��ȡͼ��                
		//�ڰ�����ͷ               
		img_extract(img, imgbuff,CAMERA_SIZE);//��ѹͼ��
#endif
                //beep_on();
		get_center();
		servo_control();
                motor_control();
                RLC();//OLED��ʾ����
               
                
                if(DSW_Read(2)==DIP_DOWN)//������뿪��2�²�
                img_sd_save(imgbuff,CAMERA_SIZE);//1.34ms

                  run_time=pit_time_get_us(PIT3);
                //beep_off();   qqqqqqqqqqqq2]

		//ͨ������˸���۲�����Ƿ�������
               
                 
          
          /*  pit_time_start(PIT3);
		camera_get_img();    //����ͷ��ȡͼ��
               run_time=pit_time_get_us(PIT3);
		//�ڰ�����ͷ
               
		img_extract(img, imgbuff,CAMERA_SIZE);//��ѹͼ��
		get_center();
		servo_control();
                RLC();//OLED��ʾ����
               
                if(DSW_Read(2)==DIP_UP)//������뿪��2�ϲ�
                img_sd_save(imgbuff,CAMERA_SIZE);//1.34ms
		 

		//ͨ������˸���۲�����Ƿ�������*/
	
                 
                

                 
                 
	}
}

