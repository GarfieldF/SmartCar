////B车后轮直径56mm，大齿轮106齿,512线编码器齿轮44
////2ms周期,设测得脉冲数为N ,
////转速V
////
//// 3.6cm/r
////轮子周长17.584cm
////编码器转1圈步进7.3cm
////v= 0.0713*N m/s = 7.13*N cm/s
////2ms,步进 0.01426cm, 1cm 70个脉冲
////
#include   "common.h"
#include   "include.h"
#include    "motor.h"

uint16 dist_buff=0;

void motor_control(void)

{       uint8 i = 0;
        uint16 far_center=0;
        uint8 far_error=0;
        //设定速度
        //直道加速 弯道减速,待修改
        for(i=1;i<=9;i++)
        {
          far_center+=center[i];
        }
        
        far_center=far_center/9;
        
        far_error=abs(center[1]-center[9]);
        if((far_center>52||far_center<28)&&shizi_FLAG!=1)
        { //beep_on();
        speed_set=55;}
        else
        {speed_set=70;
        //beep_off();
        }
        if(Hlin_flag||Hlout_flag)speed_set=40;
        //if(stop_flag)speed_set=0;
       
      //获取实际速度  FTM 正交解码 的脉冲数(负数表示反方向)
        speed = -ftm_quad_get(FTM2);  
	ftm_quad_clean(FTM2);
        //速度积分算路程
        dist_buff+=speed;
          if(dist_buff>350)
          {
            distance++;
            dist_buff=0;
          }
        //更新速度差值  队列
        for(i = 9; i > 0; i--)
        speed_error[i] = speed_error[i-1];
       
        
        speed_error[0]=speed_set-speed;//目标值-实际值
        
        motor_pwm=motor_pwm+
          speed_error[0]*motor_Ki+
          (speed_error[0]-speed_error[1])*motor_Kp/10+
            (speed_error[0]-2*speed_error[1]+speed_error[2])*motor_Kd/10;
        
        //bangbang control
        if(speed_error[0]>=20&&speed_set==70)motor_pwm=5000;
        if(speed_error[0]<=-20)
        {
          motor_pwm=-5000;
          //beep_on();
        }
       // else
        
         //beep_off();
        
        
        
        if(motor_pwm>5000)motor_pwm=5000;
         if(motor_pwm<-5000)motor_pwm=-5000;
         
        
        if(stop_flag==1)
        {
          ftm_pwm_duty(FTM0, FTM_CH2,0);      
            ftm_pwm_duty(FTM0, FTM_CH1,0);
        }
        else
        {
            if(motor_pwm>0)
            {
            ftm_pwm_duty(FTM0, FTM_CH2,motor_pwm);      
            ftm_pwm_duty(FTM0, FTM_CH1,0);
            }
            else
            {
              motor_pwm=-motor_pwm;
               ftm_pwm_duty(FTM0, FTM_CH2,0);      
            ftm_pwm_duty(FTM0, FTM_CH1,motor_pwm);
            }
        }
     

}