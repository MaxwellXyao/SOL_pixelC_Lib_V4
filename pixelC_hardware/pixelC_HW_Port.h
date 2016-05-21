#ifndef PIXELC_HW_PORT_H
#define PIXELC_HW_PORT_H

#include<stdarg.h> 						//支持变长参数

#define bit_getH4(x) ((x&0xf0)>>4)
#define bit_getL4(x) (x&0x0f)

//#############################【引脚快速操作】###############################

typedef enum _PIN_PXx{
	PA0=0x00,		
	PA1=0x01,
	PA2=0x02,
	PA3=0x03,
	PB12=0x1c,		
	PB13=0x1d,
	PB14=0x1e,
	PB15=0x1f	
}PIN_PXx; 	//引脚编号:
/*
	低4位：引脚bit（0~15）	
	高4位：寄存器名（A~G:0~6）
*/

typedef enum _MODE{
	OUTPUT=0,	 	//推挽输出，最大速度50MHz
	INPUT,	 		//上拉\下拉输入
	ADC_IN,			//使用ADC输入(ADC1，单次模式)
	PWM_OUT			//使用PWM输出
}PIN_MODE; 			//功能模式


//#############################【协议快速操作】###############################
//-----------【SPI协议快速调用】
void pixelC_HW_Port_SPI2_Init(void);		//SPI2协议初始化
void Port_SPI2_SetSpeed(u8 SpeedSet); 	//速度设置函数（SpeedSet:0~7），SPI速度（MHz）=36/2^(SpeedSet+1)
u8 Port_SPI2_ReadWriteByte(u8 TxData);	//读写一个字节

/*----------------------------------------------------
SPI协议使用引脚:
PB12	: CS
PB13	: SCK
PB14	: MISO
PB15	: MOSI
需要配合PB12来使用	
----------------------------------------------------*/

//-----------【串口协议快速调用】
void pixelC_HW_Port_USART2_Init(u32 bound,u8 en_rx);	//串口2初始化（波特率，1：允许接收中断）
void USART2_printf(const char* str,...);				//串口2格式化发送
/*【接收中断需要用户自行编写，中断等级默认最低】*/


//#############################【API】###############################
//-----------【常用端口快速操作】
void pixelC_HW_Port_PinInit(PIN_PXx PXx,PIN_MODE mode);		//初始化引脚（模式：OUTPUT，INPUT，ADC，PWM） 
/*----------------------------------------------------

引脚支持列表：
IO	:	PA0,PA1,PA2,PA3,PB12,PB13,PB14,PB15
ADC	:	PA0,PA1,PA2,PA3
PWM	:	PA0,PA1,PA2,PA3


引脚电平控制:使用位带操作宏：
PAout(n)=1;
PBout(n)=0;
value1=PAin(n);
value2=PBin(n);
----------------------------------------------------*/
u16 pixelC_HW_Port_getADC(PIN_PXx PXx);		//获取引脚AD值	  [支持的引脚：PA0,PA1,PA2,PA3]
void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on);	//设置PWM值	  [支持的引脚：PA0,PA1,PA2,PA3]



#endif
