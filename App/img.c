#include "common.h"
#include "include.h"
#include "img.h"




int Hjumpin();
int Stra();
int Hleftin();
int Rstra();
int Shizi(int a,int b);
int Whiteline(int a,int b);
void Startline();
void Shizi_buxian();

uint8 limitfun(char x)
{
  uint8 z;
  if(x<0)z=0;
  if(x>79)z=79;
  if(x>=0&&x<=79)z=x;
  return z;
}
//中线提取程序
void get_center()
{
	uint8 i,j=0;
	uint8 left_line=0,left_last=5;
	uint8 right_line=79,right_last=70;
	uint8 left_point=0,right_point=0,center_line=40;
        uint8 black_point=0;
        uint8 shizi_flag=0;
        
       

        


	/*****************************提取每行中心线*********************************/

	for(i=59; i>50; i--)                 //前三行判断
	{  if(i>56)
          {
            for(j=0;j<80;j++)
          {
            if(img[i][j]==0)
            black_point++;
            if(black_point>200)
            {
              black_point=0;
              stop_flag=1;//保护程序
              ftm_pwm_duty(FTM0, FTM_CH1,0);
              ftm_pwm_duty(FTM0, FTM_CH3,0);
            }
          }
          }
		int m1=0;
		int  m2=0;
		for(j=10; j<69; j++)
		{
			if (img[i][j]==255)
			{
				m1=m1+j;
				m2++;
			}
		}
		center_line=m1/m2;
		for(j=center_line; j>=2; j--)
		{

			if(img[i][j-2]==0&&img[i][j-1]==0&&img[i][j]==255)//找到黑白跳变点
			{
				left_line=j-1;
				Left_line[i]=j-1;
				break;
			}
			else  //没有找到黑白跳变点
			{
				left_line=0;
				Left_line[i]=0;
			}
		}    //for

		for(j=center_line; j<=77; j++)
		{

			if(img[i][j]==255&img[i][j+1]==0&img[i][j+2]==0)//找到右黑白跳变点
			{
				right_line=j+1;//保存黑线值
				Right_line[i]=j+1;
				break;


			}
			else
			{
				right_line=79;
				Right_line[i]=79;
			}
		} //for
		left_last=left_line;
		right_last=right_line;
		center_line=(Left_line[i]+Right_line[i])/2;
		center[i]=center_line;
		width[i]=Right_line[i]-Left_line[i];

	}
	for(i=50; i>0; i--)
	{
		if(left_last>=76)
		{
			left_line=79;//同生共死
			right_line=79;
			Left_line[i]=79;
			Right_line[i]=79;

		}
		else if(right_last<=3)
		{
			left_line=0;
			right_line=0;
			Left_line[i]=0;
			Right_line[i]=0;
		}
		else
		{
			for(j=center_line; j>0; j--)
			{

				if(img[i][j]==0)//找到黑点
				{
					left_point++;
					if(left_point>=2)//有三个以上黑点
					{
						left_line=j;//保存黑线值

						Left_line[i]=j;
						left_point=0;
						break;
					}

				}
				else  //没有找到黑点
				{
					left_point=0;
					left_line=0;
					Left_line[i]=0;
				}
			}    //for

			for(j=center_line; j<80; j++)
			{

				if(img[i][j]==0)//找到黑点
				{
					right_point++;
					if(right_point>=2)//有三个以上黑点
					{
						right_line=j;//保存黑线值
						right_last=right_line;
						Right_line[i]=j;
						right_point=0;
						break;
					}

				}
				else
				{
					right_point=0;
					right_line=79;
					Right_line[i]=79;
				}
			} //for
		}//ele

		left_last=left_line;
		right_last=right_line;
		center_line=(Left_line[i]+Right_line[i])/2;
		center[i]=center_line;
		width[i]=Right_line[i]-Left_line[i];
		if(i<40)
                { if(Left_line[i]==0&&Right_line[i]<=70)
		{
			center[i]=limitfun(Right_line[i]-width[i+1]/2-3);
			width[i]=width[i+1];
		}
		if(Right_line[i]==79&&Left_line[i]>=10)
		{
			center[i]=limitfun(Left_line[i]+width[i+1]/2+3);
			width[i]=width[i+1];
		}
                }

	}
//dealing

        if(distance>260)//335
          Startline();
        if(stop_flag)beep_on();
        
/*小S弯判断    条件是排除直道弯道和十字***/ 
//uint8 sum=0,sdian=0;
//     if(!(shizi_flag&&Hlin_flag))
//     { for(i=45;i>20;i=i-1)
//         {
//          if((center[i]<60)&&(center[i]>20))
//          sdian++;
//           }
//          if(sdian>20)
//            {
//              swan_flag=1;
//              //beep_on();
//             }
//          else
//            {
//              swan_flag=0;
//              beep_off();
//             } 
//     }
        
/**********十字判断**********/
       if(distance>200)
      shizi_flag=(Whiteline(24,40)>5);
      //shizi_flag?beep_on():beep_off();
      if(shizi_flag)Shizi_buxian();
/********入环路判断***********************/
       if(distance<100&&distance>60&&Hlin_flag==0)
        Hlin_flag=Rstra()&&Hleftin()&&!Stra();
       //if(Hlin_flag)beep_on();
        
       if(Hlin_flag0==0&&Hlin_flag==1)//标志位跳变
        Hdist1=distance;
        
        if(Hlin_flag==1&&distance-Hdist1>45){Hlin_flag=0;Hlin_flag1=1;}
        
        Hlin_flag?beep_on():beep_off();
        
        Hlin_flag0=Hlin_flag;
/**************出环路判断**************************/
//        if(Hlout_flag==0&&Hlin_flag1&&(distance-Hdist1<35))//如果入环结束，3.5米之内
//        {
//          Hlout_flag=(Whiteline(30,40)>=4);
//          
//        }
//        
//        if(Hlout_flag0==0&&Hlout_flag==1)//标志位跳变
//        Hdist2=distance;
//        
//        if(Hlout_flag==1&&distance-Hdist2>10){Hlout_flag=0;}
//        
//        Hlout_flag?beep_on():beep_off();
//        
//        Hlout_flag0=Hlout_flag;
//        //滤波
//        for(i=59;i>1;i--)
//        {
//          if(abs(Right_line[i]-Right_line[i-1])>=10)Right_line[i-1]=Right_line[i];
//          
//          if(abs(Left_line[i]-Left_line[i-1])>=10)Left_line[i-1]=Left_line[i];
//          center_line=(Left_line[i]+Right_line[i])/2;
//          center[i]=center_line;
//        }
//	for(i=30; i>1; i--)
//	{
//		if(center[i]<=10)center[i-1]=0;
//		if(center[i]>=70)center[i-1]=79;
                

//	}

        
        
	for(i=0; i<=59; i++)
	{
		img[i][center[i]]=0;
	}
        
        

}//get_center
//显示
int Whiteline(int a,int b)
{
   int c;
    if(a>=b)
  {c=a;a=b;b=c;}//a是最小值，B是最大值
  
  uint8 i=0;
  uint8 whiteline_num=0;
   for(i=a;i<b;i++)
   {
     if(img[i][0]==255&&img[i][79]==255&&Left_line[i]==0&&Right_line[i]==79)
       whiteline_num++;
   }
    return whiteline_num;
}
int Shizi(int a,int b)
{
  int c;
  if(a>=b)
  {c=a;a=b;b=c;}//a是最小值，B是最大值
  
  uint8 i=0,j=0;
  uint8 shizi_point=0;
   for(i=a;i<b;i++)
        { for(j=0;j<=79;j++)//320
          if(img[i][j]==255)
          {
          shizi_point++;
          }
        }
        if(shizi_point>((b-a)*79-5))return 1;
        else return 0;
        
}


void Shizi_buxian()
{
  uint i=0;
   uint8  zuoguaidian_flag=0,youguaidian_flag=0,zuoshangguaidian_flag=0,youshangguaidian_flag=0;
       //进十字补线
      for(i=55;i>15;i=i-1)
      {
          if(i<55)
         {
           if((Left_line[i+4]-Left_line[i+2]<=0)&&
              (Left_line[i+3]-Left_line[i]<=0)&&
                (Left_line[i+1]-Left_line[i]<=0)&&
                  (Left_line[i-1]-Left_line[i]<=0)&&
                    (Left_line[i-2]-Left_line[i]<0)&&
                      (Left_line[i]<30))
           {
               zuoguaidian_flag=1;
               zuoguaidian=i;
           }


           if((Right_line[i+4]-Right_line[i+2]>=0)&&
              (Right_line[i+3]-Right_line[i]>=0)&&
                (Right_line[i+1]-Right_line[i]>=0)&&
                  (Right_line[i-2]-Right_line[i]>0)&&
                    (Right_line[i-1]-Right_line[i]>=0)&&
                      (Right_line[i]>50))
           {
             youguaidian_flag=1;
               youguaidian=i;
           }
          }



          if(zuoguaidian_flag==1)
         {
           Left_line[i]=limitfun(Left_line[zuoguaidian]+(Left_line[zuoguaidian]-Left_line[55])*(zuoguaidian-i)/(55-zuoguaidian));//2*Left_line[zuoguaidian]-Left_line[2*zuoguaidian-i];//Left_line[i+2]+1;

           img[i][Left_line[i]]=0;

         }
         if(youguaidian_flag==1)
         {
           Right_line[i]=limitfun(Right_line[youguaidian]-
                                 (Right_line[55]-Right_line[youguaidian])
                                  *(youguaidian-i)/(55-youguaidian));//Right_line[i+2]-1;
           img[i][Right_line[i]]=0;
         }



         center[i]=limitfun((Left_line[i] + Right_line[i])/2); /*  */

       }

          if(Left_line[50]==0||Right_line[50]==79)
            guoguaidian_flag=1;


         //出十字补线
          if(guoguaidian_flag==1)
            for(i=20;i<50;i=i+1)
         {
            if((Left_line[i]-Left_line[i+2]>5)&&(Left_line[i-1]-Left_line[i]>=0)&&(Left_line[i-3]-Left_line[i-1]>=0)&&(Left_line[i-4]-Left_line[i-2]>=0)&&Left_line[i]<40)
            {
               zuoshangguaidian_flag=1;
               zuoshangguaidian=i;
            }
            if((Right_line[i+2]-Right_line[i]>5)&&(Right_line[i-1]-Right_line[i]<=0)&&(Right_line[i-3]-Right_line[i-1]<=0)&&(Right_line[i-4]-Right_line[i-2]<=0)&&Right_line[i]>40)
            {
                 youshangguaidian_flag=1;
               youshangguaidian=i;
            }

            if(zuoshangguaidian_flag==1)
            {
                 Left_line[i]=limitfun(Left_line[i-2]-1);
               img[i][Left_line[i]]=0;
            }
            if(youshangguaidian_flag==1)
           {
             Right_line[i]=limitfun(Right_line[i-2]+1);
             img[i][Right_line[i]]=0;
           }

            center[i]=limitfun((Left_line[i] + Right_line[i])/2);
         }
         
}
int Hjumpin()
{
  
   uint8 jump_point=0,i=0;
  for(i=0;i<59;i++)
  {
    if(img[i][0]==0&&img[i+1][0]==255)
      jump_point++;
  }
      if(jump_point>=2)
        return 1;
      else
        return 0;
  
}
int Rstra()
{
  uint8 stra_point=0,i=0;
  for(i=50;i>8;i--)
  {
    if((Right_line[i+2]-Right_line[i])<=2&&img[i][79]!=255&&(Right_line[i+3]-Right_line[i])>=0)
      stra_point++;
  }
      if(stra_point>32)
        return 1;
      else
        return 0;
}
int Hleftin()
{
  uint8 zero_point=0,i=0;
  for(i=50;i>30;i--)
  {
    if(Left_line[i]==0&&img[i][0]==255)
      zero_point++;
  }
      if(zero_point>=20)
        return 1;
      else
        return 0;
  
}
int Stra()
{
  uint8 stra_point=0,i=0;
  for(i=50;i>8;i--)
  {
    if(abs(center[i]-center[i+2])<=2)
      stra_point++;
  }
      if(stra_point>40)
        return 1;
      else
        return 0;
}
void Startline()
{
  int i=0,j=0;
  uint8 jump_point=0;
  for(i=32;i<=40;i++)//19到25是50-70cm左右能识别到
  {
          for(j=0;j<79;j++)
          {
                  if(img[i][j]==255&&img[i][j+1]==0)
                          jump_point++; 
                  if(jump_point>=8){stop_flag=1;break;}
          }
          jump_point=0;
                 
         
  }
}
void RLC()
{
	int i=0,j=0;
	switch(DSW_Scan())
	{

	case 1:
	{
                //参数显示
                LED_PrintValueI(80, 0,servo_duty );
                LED_PrintValueI(80, 1, servo_mid);//speed 
                 LED_PrintValueI(80, 2,Hlin_flag );// run_time
                  LED_PrintValueI(80, 3, error);
                  LED_PrintValueI(80, 4, error_last);
                  LED_PrintValueI(80, 5, Hdist1);
                  LED_PrintValueI(80, 6, distance);
                //图像显示 
                static uint8 key_cur=5;//按一下按键则改变图像，不能切换回原图
                if(DSW_Read(6)==DIP_UP)//按住按键改变图像，更新速度较慢
                key_cur=5;
		
		uint8 key_new=Key_Scan(1);
		if(key_new!=0)
			key_cur=key_new;
		switch(key_cur)
		{
		case KEY_UP:
			for(i=0; i<60; i++)
			{
				for(j=0; j<80; j++)
					img2[i][j]=255;

				img2[i][center[i]]=0;
				img2[i][Left_line[i]]=0;
				img2[i][Right_line[i]]=0;
			}

			LED_PrintImage((uint8*)img2,60, 80);
			break;
		case KEY_DOWN:
			for(i=0; i<60; i++)
			{
				for(j=0; j<80; j++)
					img2[i][j]=255;

				img2[i][center[i]]=0;
			}
			LED_PrintImage((uint8*)img2,60, 80);
			break;
		case KEY_LEFT:
			for(i=0; i<60; i++)
			{
				for(j=0; j<80; j++)
					img2[i][j]=255;

				img2[i][Left_line[i]]=0;

			}

			LED_PrintImage((uint8*)img2,60, 80);
			break;
		case KEY_RIGHT:
			for(i=0; i<60; i++)
			{
				for(j=0; j<80; j++)
					img2[i][j]=255;

				img2[i][Right_line[i]]=0;

			}

			LED_PrintImage((uint8*)img2,60, 80);
			break;
		case 5:
			LED_PrintImage((uint8*)img,60, 80);
			break;
		default:
			break;
		}

	}
	break;
	case 2: //img_sd_save(imgbuff,CAMERA_SIZE);//1.34ms
                break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
}
