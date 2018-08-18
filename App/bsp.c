#include    "common.h"
#include    "include.h"
#include    "bsp.h"




void BSP_init()
{
	/************************ 配置 K60 的优先级  ***********************/
	//K60 的默认优先级 都为 0
	//参考帖子：急求中断嵌套的例程 - 智能车讨论区 - 山外论坛
	//          http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270
	NVIC_SetPriorityGrouping(4);            //设置优先级分组,4bit 抢占优先级,没有亚优先级

	NVIC_SetPriority(PORTA_IRQn,0);         //配置优先级
	NVIC_SetPriority(DMA0_IRQn,1);          //配置优先级
	NVIC_SetPriority(PIT0_IRQn,2);          //配置优先级
	DisableInterrupts;
	//OLED初始化
	OLED_Init();
	LED_Fill(0x00);
	//IO口初始化
	IO_Init();
	//摄像头初始化
#if CAMERA_MODE
	camera_init(imgbuff);
#endif
	//串口初始化
	uart_init (UART4, 9600);
        //SD卡初始化
        img_sd_init();
	//set_vector_handler(UART4_RX_TX_VECTORn ,UART4_IRQHandler);    //设置 UART4 的中断服务函数为 UART4_IRQHandler
	//uart_rx_irq_en (UART4);	
	//配置中断服务函数
#if CAMERA_MODE
	set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置LPTMR的中断服务函数为 PORTA_IRQHandler
	set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置LPTMR的中断服务函数为 PORTA_IRQHandler
#endif
	//舵机初始化
	ftm_pwm_init(SD5_FTM, SD5_CH,SD5_HZ,4620);
	//电机初始化
	ftm_pwm_init(FTM0, FTM_CH2,20000,1600);
	ftm_pwm_init(FTM0, FTM_CH1,20000,0);
	/*********************** 测速 初始化  ***********************/       //初始化脉冲计数器，用LPT0_ALT1，即PTA19输入，每隔INT_COUNT产生中断（需要开中断才能产生中断），上升沿触发
	//lptmr_pulse_init(LPT0_ALT2, 0xFFFF, LPT_Rising); 
        ftm_quad_init(FTM2);                                    //FTM2 正交解码初始化（所用的管脚可查 port_cfg.h ）
	port_init_NoALT(FTM2_QDPHA_PIN,IRQ_RISING | PF | PULLUP);       //配置管脚上拉（电机驱动模块上已经上拉了，因此此处不需要配置上拉）
	port_init_NoALT(FTM2_QDPHB_PIN,IRQ_RISING | PF | PULLUP);
	
	/*********************** pit0 初始化  ***********************/
	pit_init_ms(PIT0, 10);                                 //初始化PIT0，定时时间为： 1000ms
	set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断服务函数为 PIT0_IRQHandler
	enable_irq (PIT0_IRQn);  //使能PIT0中断
        
        gpio_init (PTC7, GPO,0 );
        gpio_set(PTC7,1);
        beep_ms(200);
	EnableInterrupts;
}