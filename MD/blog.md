4月14日
1.编码器测转速成功，因为我把A，B相接反了。但是名优科创的编码器比龙邱的编码器波形差很多，考虑买一个龙邱编码器
2.	使用PIT测试程序周期
PLL180Mhz,总线时钟90Mhz
2.1图像显示开启 time*1000/bus_clk_khz
				2400000*/90=26ms
2.2图像显示关闭    17ms
2.3图像显示占用26-17=9ms
2.4图像采集camera_get_img();//16ms，不是112帧吗？？？？不应该9ms一次吗？？
2.5剩下的程序0.62ms		
		img_extract(img, imgbuff,CAMERA_SIZE);
		get_center();
		servo_control();
        RLC();//OLED显示函数

