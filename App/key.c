#include "include.h"


void IO_Init(void)
{
	//按键
        gpio_init(KEY_UP_PORT,GPI,1);//S1
	gpio_init(KEY_DOWN_PORT,GPI,1);//S2
	gpio_init(KEY_LEFT_PORT,GPI,1);//S3
	gpio_init(KEY_RIGHT_PORT,GPI,1);//S4


	gpio_init(PTC8 ,GPI,0);//拨码开关1
	gpio_init(PTC10,GPI,0);//拨码开关2
	gpio_init(PTC11,GPI,0);//拨码开关3
	gpio_init(PTC12,GPI,0);//拨码开关4
	gpio_init(PTC13,GPI,0);//拨码开关5
	gpio_init(PTC14,GPI,0);//拨码开关6

        gpio_init(BEEP,GPO,0);//蜂鸣器
	//gpio_init(RLED,GPO,1);//LED
	//gpio_init(YLED,GPO,1);//LED

}
void beep_ms(unsigned int time)
{
  	gpio_set(BEEP,1);
        DELAY_MS(time);
  	gpio_set(BEEP,0);

}
void beep_on()
{
	gpio_set(BEEP,1);
}
void beep_off()
{
	gpio_set(BEEP,0);
}
//有优先级，还不如直接判断拨码开关状态
uint8 DSW_Scan()
{
             if(DSW_Read(1)==DIP_DOWN)return 1;
	else if(DSW_Read(2)==DIP_DOWN)return 2;
	else if(DSW_Read(3)==DIP_DOWN)return 3;
	else if(DSW_Read(4)==DIP_DOWN)return 4;
	else if(DSW_Read(5)==DIP_DOWN)return 5;
	else if(DSW_Read(6)==DIP_DOWN)return 6;
	else return 0;
}
uint8  DSW_Read(uint8 keyno)
{
  
	switch(keyno)
	{

	case 1: //拨码开关1
		return gpio_get(PTC8);
		break;

	case 2: //拨码开关2
		return gpio_get(PTC10);
		break;

	case 3: //拨码开关3
		return gpio_get(PTC11);
		break;

	case 4: //拨码开关4
		return gpio_get(PTC12);
		break;

	case 5:
		return gpio_get(PTC13);
		break;

	case 6:
		return gpio_get(PTC14);
		break;

	default:
		return 0XFF;

	}
}

/***********************************************************
 *  * 函数名称  :  Key_Scan
 *  * 参    数  ：mode:0支持连按，1不支持连按
 *  * 功    能  : 按键状态检测, 没有任何键按下时返回0
 *  * 日   期 ：2018/04/13
 *  * 作   者 ：YZF
 *  * 注   意：此函数有响应优先级
************************************************************/
unsigned char Key_Scan(unsigned char mode)
{
	static uint8 key_up=1;//按键松开
	if(mode)key_up=1; 	//连按模式下，软件模拟松开

	if(key_up&&
	        (//gpio_get(KEY_EXIT_PORT) == 0 ||
	            gpio_get(KEY_UP_PORT) == 0 ||
	            // gpio_get(KEY_OK_PORT) == 0 ||
	            gpio_get(KEY_LEFT_PORT) == 0 ||
	            gpio_get(KEY_DOWN_PORT) == 0 ||
	            gpio_get(KEY_RIGHT_PORT) == 0)) //有任何一个按键按下
	{
		DELAY_MS(20);
		// if(gpio_get(KEY_EXIT_PORT) == 0) //EXIT按下
		// {
		// DELAY_MS(35);
		// return KEY_EXIT;
		// }
		if(gpio_get(KEY_UP_PORT) == 0) //UP按下
		{
			//DELAY_MS(5);
			return KEY_UP;
		}
		// if(gpio_get(KEY_OK_PORT) == 0) //OK按下
		// {

		// DELAY_MS(35);

		// return KEY_OK;
		// }
		if(gpio_get(KEY_LEFT_PORT) == 0) //LEFT
		{

			//DELAY_MS(5);

			return KEY_LEFT;
		}
		if(gpio_get(KEY_DOWN_PORT) == 0) //DOWN
		{
			//DELAY_MS(5);

			return KEY_DOWN;
		}
		if(gpio_get(KEY_RIGHT_PORT) == 0) //RIGHT
		{
			//DELAY_MS(5);
			return KEY_RIGHT;
		}
	}
	else if  (
	    //gpio_get(KEY_EXIT_PORT) == 0 ||
	    //gpio_get(KEY_OK_PORT) == 0 ||
	    gpio_get(KEY_UP_PORT) == 1 &&
	    gpio_get(KEY_LEFT_PORT) == 1 &&
	    gpio_get(KEY_DOWN_PORT) == 1 &&
	    gpio_get(KEY_RIGHT_PORT) == 1)key_up=1; 	//按键抬起

	return 0;  //无任何键按下返回0
}