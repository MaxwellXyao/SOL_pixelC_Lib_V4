#ifndef PIXELC_HARDWARE_INCLUDE_H
#define PIXELC_HARDWARE_INCLUDE_H

//###########################【机型选择】############################

/*----------------------------------------------------------------------		
	pixelC2		 【引出8路GPIO，4路ADC，4路PWM，8路外部中断，2路串口，1路硬件SPI，板载SD卡（带FATFS）和24c02，可输出3.3v和5v电压】

【引出的IO口（可用资源）】				
	PA0（GPIO，中断，PWM(TIM2)，ADC）
	PA1（GPIO，中断，PWM(TIM2)，ADC）
	PA2（GPIO，中断，PWM(TIM2)，ADC，UART2_TX）
	PA3（GPIO，中断，PWM(TIM2)，ADC，UART2_RX）
	PB12（GPIO，中断，SPI2_CS）
	PB13（GPIO，中断，SPI2_SCK）
	PB14（GPIO，中断，SPI2_MISO）
	PB15（GPIO，中断，SPI2_MOSI）
	PA9（System_UART1_TX）
	PA10（System_UART1_RX）

PS:	STM32F103C8T6	[	ROM:64k,RAM:20k		]
				
											
----------------------------------------------------------------------*/

//############################【加载库】############################
#include"stm32f10x_lib.h"
#include<stdio.h>
#include<stdarg.h> 						//支持变长参数

//------------------【system】
#include"system.h"						//系统使用
#include"delay.h"						//延时
#include"malloc.h"	    				//动态内存
#include"Usart.h"						//串口通用


//------------------【pixelC_HW】
#include"pixelC_HW_flagLight.h"		   	//板载指示灯
#include"pixelC_HW_Key.h"			   	//按键
#include"pixelC_HW_OLED.h"			   	//OLED硬件驱动
#include"pixelC_HW_Port.h"				//对外IO接口
#include"pixelC_HW_24C02.h"			   	//板载24c02
#include"pixelC_HW_SDcard.h"		   	//板载SD卡


//------------------【SOLGUI】
#include"SOLGUI_Include.h"			

//------------------【FATFS】
#include"ff.h"						  


//############################【用户编写】############################
//#include "indclude.h"



//############################【常用功能范例】############################
/*
//============【FATFS快速操作范例】============
【1】定义全局变量：
FATFS FatFs;   				//存放文件系统信息
FIL file;	   				//存放文件信息

【2】初始化
while(SD_Init()){
	无卡操作;
}

【3】挂载sd卡(相当于FATFS初始化)
f_mount(SD_CARD,&FatFs);	//先挂载SD卡

【4】常用读写操作
（1）创建新文件
f_open(&file,"test\temp.txt",FA_CREATE_NEW);    //创建新文件
f_close(&file); 
（2）打开已有文件追加写
f_open(&file,(const TCHAR*)"test\temp.txt", FA_OPEN_EXISTING|FA_WRITE);   //写方式打开文件
f_lseek(&file,file.fsize);  								//文件指针移到末尾
f_printf(&file,"%d\r\n",123); 								//当前光标写入一个格式化字符串(\r\n换行)
f_puts((char *)buf,&file);  								//当前光标处写入字符串（此处必须加(char *)类型转换）
f_close(&file); 	
（3）从文件中读数组\字符串
【注意！！！！！定义缓存buf时要定义为数组形式buf[n]，不要定义为指针式*buf；指针不申请内存，就去写数据，是作死的节奏啊（死循环）！！！！】
f_open(&file,(const TCHAR*)"test\temp.txt", FA_READ);   	//以读方式打开文件，字符串要加(const TCHAR*)转换类型
f_read(&file,buf,128,&num);  								//从文件内读128字节赋给buf变量\数组（&num是读取成功的个数，num变量自行定义）
f_gets(buf,128,&file); 										//从文件内取字符串并尾加'\0'赋给buf数组（读够128个字符读到\r\n回车换行结束）
f_lseek(&file,5000);										//文件指针移到5000个字节后
f_close(&file);
（4）文件操作
f_sync(&file);      							//立刻冲洗（用于长时间写数据中途保存）
f_unlink("test\temp.txt");   					//删除文件
f_rename("test1\temp1.txt", "test2\temp2.txt");	//重命名文件（也可以用于移动文件）

-----------------------------------------*/


#endif
