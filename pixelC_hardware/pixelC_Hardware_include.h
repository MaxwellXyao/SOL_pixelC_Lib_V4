#ifndef PIXELC_HARDWARE_INCLUDE_H
#define PIXELC_HARDWARE_INCLUDE_H

//###########################������ѡ��############################

/*----------------------------------------------------------------------		
	pixelC2		 ������8·GPIO��4·ADC��4·PWM��8·�ⲿ�жϣ�2·���ڣ�1·Ӳ��SPI������SD������FATFS����24c02�������3.3v��5v��ѹ��

��������IO�ڣ�������Դ����				
	PA0��GPIO���жϣ�PWM(TIM2)��ADC��
	PA1��GPIO���жϣ�PWM(TIM2)��ADC��
	PA2��GPIO���жϣ�PWM(TIM2)��ADC��UART2_TX��
	PA3��GPIO���жϣ�PWM(TIM2)��ADC��UART2_RX��
	PB12��GPIO���жϣ�SPI2_CS��
	PB13��GPIO���жϣ�SPI2_SCK��
	PB14��GPIO���жϣ�SPI2_MISO��
	PB15��GPIO���жϣ�SPI2_MOSI��
	PA9��System_UART1_TX��
	PA10��System_UART1_RX��

PS:	STM32F103C8T6	[	ROM:64k,RAM:20k		]
				
											
----------------------------------------------------------------------*/

//############################�����ؿ⡿############################
#include"stm32f10x_lib.h"
#include<stdio.h>
#include<stdarg.h> 						//֧�ֱ䳤����

//------------------��system��
#include"system.h"						//ϵͳʹ��
#include"delay.h"						//��ʱ
#include"malloc.h"	    				//��̬�ڴ�
#include"Usart.h"						//����ͨ��


//------------------��pixelC_HW��
#include"pixelC_HW_flagLight.h"		   	//����ָʾ��
#include"pixelC_HW_Key.h"			   	//����
#include"pixelC_HW_OLED.h"			   	//OLEDӲ������
#include"pixelC_HW_Port.h"				//����IO�ӿ�
#include"pixelC_HW_24C02.h"			   	//����24c02
#include"pixelC_HW_SDcard.h"		   	//����SD��


//------------------��SOLGUI��
#include"SOLGUI_Include.h"			

//------------------��FATFS��
#include"ff.h"						  


//############################���û���д��############################
//#include "indclude.h"



//############################�����ù��ܷ�����############################
/*
//============��FATFS���ٲ���������============
��1������ȫ�ֱ�����
FATFS FatFs;   				//����ļ�ϵͳ��Ϣ
FIL file;	   				//����ļ���Ϣ

��2����ʼ��
while(SD_Init()){
	�޿�����;
}

��3������sd��(�൱��FATFS��ʼ��)
f_mount(SD_CARD,&FatFs);	//�ȹ���SD��

��4�����ö�д����
��1���������ļ�
f_open(&file,"test\temp.txt",FA_CREATE_NEW);    //�������ļ�
f_close(&file); 
��2���������ļ�׷��д
f_open(&file,(const TCHAR*)"test\temp.txt", FA_OPEN_EXISTING|FA_WRITE);   //д��ʽ���ļ�
f_lseek(&file,file.fsize);  								//�ļ�ָ���Ƶ�ĩβ
f_printf(&file,"%d\r\n",123); 								//��ǰ���д��һ����ʽ���ַ���(\r\n����)
f_puts((char *)buf,&file);  								//��ǰ��괦д���ַ������˴������(char *)����ת����
f_close(&file); 	
��3�����ļ��ж�����\�ַ���
��ע�⣡�����������建��bufʱҪ����Ϊ������ʽbuf[n]����Ҫ����Ϊָ��ʽ*buf��ָ�벻�����ڴ棬��ȥд���ݣ��������Ľ��డ����ѭ��������������
f_open(&file,(const TCHAR*)"test\temp.txt", FA_READ);   	//�Զ���ʽ���ļ����ַ���Ҫ��(const TCHAR*)ת������
f_read(&file,buf,128,&num);  								//���ļ��ڶ�128�ֽڸ���buf����\���飨&num�Ƕ�ȡ�ɹ��ĸ�����num�������ж��壩
f_gets(buf,128,&file); 										//���ļ���ȡ�ַ�����β��'\0'����buf���飨����128���ַ�����\r\n�س����н�����
f_lseek(&file,5000);										//�ļ�ָ���Ƶ�5000���ֽں�
f_close(&file);
��4���ļ�����
f_sync(&file);      							//���̳�ϴ�����ڳ�ʱ��д������;���棩
f_unlink("test\temp.txt");   					//ɾ���ļ�
f_rename("test1\temp1.txt", "test2\temp2.txt");	//�������ļ���Ҳ���������ƶ��ļ���

-----------------------------------------*/


#endif
