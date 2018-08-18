#include "include.h"


void IO_Init(void)
{
	//����
        gpio_init(KEY_UP_PORT,GPI,1);//S1
	gpio_init(KEY_DOWN_PORT,GPI,1);//S2
	gpio_init(KEY_LEFT_PORT,GPI,1);//S3
	gpio_init(KEY_RIGHT_PORT,GPI,1);//S4


	gpio_init(PTC8 ,GPI,0);//���뿪��1
	gpio_init(PTC10,GPI,0);//���뿪��2
	gpio_init(PTC11,GPI,0);//���뿪��3
	gpio_init(PTC12,GPI,0);//���뿪��4
	gpio_init(PTC13,GPI,0);//���뿪��5
	gpio_init(PTC14,GPI,0);//���뿪��6

        gpio_init(BEEP,GPO,0);//������
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
//�����ȼ���������ֱ���жϲ��뿪��״̬
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

	case 1: //���뿪��1
		return gpio_get(PTC8);
		break;

	case 2: //���뿪��2
		return gpio_get(PTC10);
		break;

	case 3: //���뿪��3
		return gpio_get(PTC11);
		break;

	case 4: //���뿪��4
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
 *  * ��������  :  Key_Scan
 *  * ��    ��  ��mode:0֧��������1��֧������
 *  * ��    ��  : ����״̬���, û���κμ�����ʱ����0
 *  * ��   �� ��2018/04/13
 *  * ��   �� ��YZF
 *  * ע   �⣺�˺�������Ӧ���ȼ�
************************************************************/
unsigned char Key_Scan(unsigned char mode)
{
	static uint8 key_up=1;//�����ɿ�
	if(mode)key_up=1; 	//����ģʽ�£����ģ���ɿ�

	if(key_up&&
	        (//gpio_get(KEY_EXIT_PORT) == 0 ||
	            gpio_get(KEY_UP_PORT) == 0 ||
	            // gpio_get(KEY_OK_PORT) == 0 ||
	            gpio_get(KEY_LEFT_PORT) == 0 ||
	            gpio_get(KEY_DOWN_PORT) == 0 ||
	            gpio_get(KEY_RIGHT_PORT) == 0)) //���κ�һ����������
	{
		DELAY_MS(20);
		// if(gpio_get(KEY_EXIT_PORT) == 0) //EXIT����
		// {
		// DELAY_MS(35);
		// return KEY_EXIT;
		// }
		if(gpio_get(KEY_UP_PORT) == 0) //UP����
		{
			//DELAY_MS(5);
			return KEY_UP;
		}
		// if(gpio_get(KEY_OK_PORT) == 0) //OK����
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
	    gpio_get(KEY_RIGHT_PORT) == 1)key_up=1; 	//����̧��

	return 0;  //���κμ����·���0
}