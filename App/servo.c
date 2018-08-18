#include "common.h"
#include "include.h"
#include "servo.h"
#include "img.h"


void key(void);

//舵机 P,D初始化

int8 error=0;
int8 error_last=0;

int servo_error[20]={0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0};//没有用到？？

uint16 p_servo=0;
uint16 d_servo=0;
uint16 var[1];
int16 servo_delta=0;
uint8 center_want=39;
#if 0
void servo_control(void)
{
  
  d_servo=1000;
    error_last=error;
     center_ave=((center[12]+center[14]+center[17]+center[22])*25/4+(center[27]+center[32]+center[34]+center[36])*10+(center[38]+center[41])*35/2)/100;
     error=center_ave-39;
      if(abs(error)<5)

      p_servo=38;
    else if(abs(error)<10)
        p_servo=50;
     else  p_servo=60;
    servo_duty=servo_mid+p_servo*error+d_servo*(error-error_last)/10;
   
    if(servo_duty<=servo_mid-690)
    {
    servo_duty=servo_mid-690;
    }
    if(servo_duty>=servo_mid+700)
    {
    servo_duty=servo_mid+700;
    }
    //key();

    ftm_pwm_duty(SD5_FTM, SD5_CH,servo_duty);
    
    
  
   
   
}
#endif
#if 1
void servo_control(void)
{
  int i=0,a=0,b=0,c=0,d=0;
  
    d_servo=30;
    error_last=servo_error[0]-servo_error[3];
    
    //(Hlin_flag||Hlout_flag)?(servo_mid=4300):(servo_mid=4630);
    if(Hlin_flag)servo_mid=SERVO_MID-360;
    //else if(Hlout_flag)servo_mid=3900;
     if(Hlin_flag==0&&Hlout_flag==0)servo_mid=SERVO_MID;
    //Hlin_flag?(center_want=20):(center_want=39);
//   (Hlout_flag&&!Hlin_flag)?(servo_mid=4300):(servo_mid=4630);
//   if(Hlout_flag)
//     servo_mid=4300;
    for(i=19;i>0;i--)//18到19,17到18，
       servo_error[i]=servo_error[i-1];//偏差队列,旧的值后移
    
//    if(shizi_FLAG==1){a=15;b=16;c=17;d=18;}
//     
//    else
    {
      a=20;
    b=22;
    c=24;
    d=26;}
    center_ave=(3*(center[14]+center[16]+center[17]+center[19])/4+
                 6*(center[a]+center[b]+center[c]+center[d])/4+
                  1*(center[35]+center[37]+center[40])/3)/10;
       /*(2*(center[10]+center[12]+center[14]+center[16])/4+
                 7*(center[22]+center[24]+center[27]+center[30])/4+
                  1*(center[32]+center[34]+center[36])/3)/10;*/
     error=center_ave-center_want;//目标值-实际值
     
    
     servo_error[0]=error;
     if(abs(error)<=4)
      p_servo=18;
    else if(abs(error)<=10)
      p_servo=25;
    else if(abs(error)<=20)
      p_servo=28;
    else p_servo=abs(30*(abs(error)-10))/100+28;//(abs(error))*(abs(error))/100+40; /**/
     
     /*if(abs(error)<=5)
      p_servo=45;
    else p_servo=55;
    
   if(abs(error)>=5)
      d_servo=50;
    else
      d_servo=0; */
    servo_delta=(p_servo*error)+d_servo*(error_last);
    servo_duty=servo_mid+servo_delta;
    
    if(Hlout_flag)servo_duty=SERVO_MID-730;
    
    if(servo_duty<=SERVO_MID-730)
    {
    servo_duty=SERVO_MID-730;
    }
    if(servo_duty>=SERVO_MID+740)
    {
    servo_duty=SERVO_MID+740;
    }
//    if(servo_duty==(servo_mid-730)||servo_duty==(servo_mid+740))beep_on();
//   else beep_off();
    
#if MYDEBUG
      var[0]=servo_duty;
    vcan_sendware((uint16_t *)var, sizeof(var));
#endif
    ftm_pwm_duty(SD5_FTM, SD5_CH,servo_duty);
    
   
   
}
#endif



   
