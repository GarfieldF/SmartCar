/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"



//图像中线边线
uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_H][CAMERA_W]; //由于鹰眼摄像头是一字节8个像素，因而需要解压为 1字节1个像素，方便处理
uint8 img2[60][80];
uint8 width[60];
uint8 center[60];                                      //定义数组储存中线
uint8 center_ave=0;                                     //定义中线均值变量
uint8 Left_line[60],Right_line[60];                             //定义数组存储左右边线
int16 middleline_last=40,middleline;
uint8 sdiam=0;
uint8 swan_flag=0;
//图像环路标志位
uint8 Hlin_flag =0;//进环路左边线丢线
uint8 Hlin_flag0=0;//进环路左边线丢线原来
uint8 Hrin_flag =0;//进环路右边线丢线
uint8 Hrin_flag0=0;//进环路右边线丢线原来

uint8 Hlin_flag1=0;//入环路结束
uint8 Hrin_flag1=0;//入环路结束

uint8 Hlout_flag =0;
uint8 Hlout_flag0=0;
uint8 Hrout_flag =0;
uint8 Hrout_flag0=0;

uint8 Huanlzhi_flag;
uint8 Huanl_point;
uint16 Huanlzhi_point;
//图像标志位
uint8 stop_flag=0;
uint8 shizi_FLAG=0;
uint8 stra_flag=0;
uint8 zuoguaidian=0,youguaidian=0,zuoshangguaidian=0,youshangguaidian=0;
uint8 guoguaidian_flag=0,guaidian_flag=0;//zuoguaidian_flag=0, youguaidian_flag=0,zuoshangguaidian_flag=0,youshangguaidian_flag=0;
//路程
uint16 Hdist1=0;//入环路持续路程
uint16 Hdist2=0;//出环路持续路程

//servo
uint16 servo_duty=0;
uint16 servo_mid=SERVO_MID;

//电机参数
uint16 speed=0;
uint16 speed_set=65;
int16 speed_error[10]={0,0,0,0,0,0,0,0,0,0};
int16 motor_pwm=0;
uint16 motor_Ki=60;
uint16 motor_Kp=15;
uint16 motor_Kd=5;

uint16 distance=0;
//程序时间

/*!
*  @brief      main函数 修改时间:2018.4.14
 *  @since      v5.3
 *  @note       泰山二队啦啦啦
 */
uint32 run_time=0;
void  main(void)
{

         
	BSP_init();//总初始化函数;


	while(1)
	{
          		 pit_time_start(PIT3);
                      
#if CAMERA_MODE
		camera_get_img();    //摄像头获取图像                
		//黑白摄像头               
		img_extract(img, imgbuff,CAMERA_SIZE);//解压图像
#endif
                //beep_on();
		get_center();
		servo_control();
                motor_control();
                RLC();//OLED显示函数
               
                
                if(DSW_Read(2)==DIP_DOWN)//如果拨码开关2下拨
                img_sd_save(imgbuff,CAMERA_SIZE);//1.34ms

                  run_time=pit_time_get_us(PIT3);
                //beep_off();   qqqqqqqqqqqq2]

		//通过灯闪烁，观察程序是否在运行
               
                 
          
          /*  pit_time_start(PIT3);
		camera_get_img();    //摄像头获取图像
               run_time=pit_time_get_us(PIT3);
		//黑白摄像头
               
		img_extract(img, imgbuff,CAMERA_SIZE);//解压图像
		get_center();
		servo_control();
                RLC();//OLED显示函数
               
                if(DSW_Read(2)==DIP_UP)//如果拨码开关2上拨
                img_sd_save(imgbuff,CAMERA_SIZE);//1.34ms
		 

		//通过灯闪烁，观察程序是否在运行*/
	
                 
                

                 
                 
	}
}

