#include    "common.h"
#include    "include.h"
#include    "bsp.h"




void BSP_init()
{
	/************************ ���� K60 �����ȼ�  ***********************/
	//K60 ��Ĭ�����ȼ� ��Ϊ 0
	//�ο����ӣ������ж�Ƕ�׵����� - ���ܳ������� - ɽ����̳
	//          http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270
	NVIC_SetPriorityGrouping(4);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�

	NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�
	NVIC_SetPriority(DMA0_IRQn,1);          //�������ȼ�
	NVIC_SetPriority(PIT0_IRQn,2);          //�������ȼ�
	DisableInterrupts;
	//OLED��ʼ��
	OLED_Init();
	LED_Fill(0x00);
	//IO�ڳ�ʼ��
	IO_Init();
	//����ͷ��ʼ��
#if CAMERA_MODE
	camera_init(imgbuff);
#endif
	//���ڳ�ʼ��
	uart_init (UART4, 9600);
        //SD����ʼ��
        img_sd_init();
	//set_vector_handler(UART4_RX_TX_VECTORn ,UART4_IRQHandler);    //���� UART4 ���жϷ�����Ϊ UART4_IRQHandler
	//uart_rx_irq_en (UART4);	
	//�����жϷ�����
#if CAMERA_MODE
	set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //����LPTMR���жϷ�����Ϊ PORTA_IRQHandler
	set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //����LPTMR���жϷ�����Ϊ PORTA_IRQHandler
#endif
	//�����ʼ��
	ftm_pwm_init(SD5_FTM, SD5_CH,SD5_HZ,4620);
	//�����ʼ��
	ftm_pwm_init(FTM0, FTM_CH2,20000,1600);
	ftm_pwm_init(FTM0, FTM_CH1,20000,0);
	/*********************** ���� ��ʼ��  ***********************/       //��ʼ���������������LPT0_ALT1����PTA19���룬ÿ��INT_COUNT�����жϣ���Ҫ���жϲ��ܲ����жϣ��������ش���
	//lptmr_pulse_init(LPT0_ALT2, 0xFFFF, LPT_Rising); 
        ftm_quad_init(FTM2);                                    //FTM2 ���������ʼ�������õĹܽſɲ� port_cfg.h ��
	port_init_NoALT(FTM2_QDPHA_PIN,IRQ_RISING | PF | PULLUP);       //���ùܽ��������������ģ�����Ѿ������ˣ���˴˴�����Ҫ����������
	port_init_NoALT(FTM2_QDPHB_PIN,IRQ_RISING | PF | PULLUP);
	
	/*********************** pit0 ��ʼ��  ***********************/
	pit_init_ms(PIT0, 10);                                 //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
	set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
	enable_irq (PIT0_IRQn);  //ʹ��PIT0�ж�
        
        gpio_init (PTC7, GPO,0 );
        gpio_set(PTC7,1);
        beep_ms(200);
	EnableInterrupts;
}