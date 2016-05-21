#ifndef PIXELC_HW_PORT_H
#define PIXELC_HW_PORT_H

#include<stdarg.h> 						//֧�ֱ䳤����

#define bit_getH4(x) ((x&0xf0)>>4)
#define bit_getL4(x) (x&0x0f)

//#############################�����ſ��ٲ�����###############################

typedef enum _PIN_PXx{
	PA0=0x00,		
	PA1=0x01,
	PA2=0x02,
	PA3=0x03,
	PB12=0x1c,		
	PB13=0x1d,
	PB14=0x1e,
	PB15=0x1f	
}PIN_PXx; 	//���ű��:
/*
	��4λ������bit��0~15��	
	��4λ���Ĵ�������A~G:0~6��
*/

typedef enum _MODE{
	OUTPUT=0,	 	//�������������ٶ�50MHz
	INPUT,	 		//����\��������
	ADC_IN,			//ʹ��ADC����(ADC1������ģʽ)
	PWM_OUT			//ʹ��PWM���
}PIN_MODE; 			//����ģʽ


//#############################��Э����ٲ�����###############################
//-----------��SPIЭ����ٵ��á�
void pixelC_HW_Port_SPI2_Init(void);		//SPI2Э���ʼ��
void Port_SPI2_SetSpeed(u8 SpeedSet); 	//�ٶ����ú�����SpeedSet:0~7����SPI�ٶȣ�MHz��=36/2^(SpeedSet+1)
u8 Port_SPI2_ReadWriteByte(u8 TxData);	//��дһ���ֽ�

/*----------------------------------------------------
SPIЭ��ʹ������:
PB12	: CS
PB13	: SCK
PB14	: MISO
PB15	: MOSI
��Ҫ���PB12��ʹ��	
----------------------------------------------------*/

//-----------������Э����ٵ��á�
void pixelC_HW_Port_USART2_Init(u32 bound,u8 en_rx);	//����2��ʼ���������ʣ�1����������жϣ�
void USART2_printf(const char* str,...);				//����2��ʽ������
/*�������ж���Ҫ�û����б�д���жϵȼ�Ĭ����͡�*/


//#############################��API��###############################
//-----------�����ö˿ڿ��ٲ�����
void pixelC_HW_Port_PinInit(PIN_PXx PXx,PIN_MODE mode);		//��ʼ�����ţ�ģʽ��OUTPUT��INPUT��ADC��PWM�� 
/*----------------------------------------------------

����֧���б�
IO	:	PA0,PA1,PA2,PA3,PB12,PB13,PB14,PB15
ADC	:	PA0,PA1,PA2,PA3
PWM	:	PA0,PA1,PA2,PA3


���ŵ�ƽ����:ʹ��λ�������꣺
PAout(n)=1;
PBout(n)=0;
value1=PAin(n);
value2=PBin(n);
----------------------------------------------------*/
u16 pixelC_HW_Port_getADC(PIN_PXx PXx);		//��ȡ����ADֵ	  [֧�ֵ����ţ�PA0,PA1,PA2,PA3]
void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on);	//����PWMֵ	  [֧�ֵ����ţ�PA0,PA1,PA2,PA3]



#endif
