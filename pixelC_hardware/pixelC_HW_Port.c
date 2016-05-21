#include"pixelC_Hardware_include.h"
//ʹ�üĴ�����Ҫstm32f10x_map.h�ļ�֧��




static void Port_PinInit_GPIO(PIN_PXx PXx,u8 mode)
{
	GPIO_TypeDef *gpoi_reg=(GPIO_TypeDef *)(GPIOA_BASE+bit_getH4((int)PXx)*0x400);
	u8 temp=(bit_getL4((int)PXx)%8)*4;
	RCC->APB2ENR|=1<<(2+bit_getH4((int)PXx));    		//ʹ��ʱ�� 
	if(bit_getL4((int)PXx)/8){
		gpoi_reg->CRH&=~((u32)0xf<<temp);		
		gpoi_reg->CRH|=(u32)mode<<temp;
	}
	else{
		gpoi_reg->CRL&=~((u32)0xf<<temp);
		gpoi_reg->CRL|=(u32)mode<<temp;
	}
}

static void Port_PinInit_ADC(PIN_PXx PXx)
{
	u8 pin_temp=bit_getL4((int)PXx);
//======��ADC���š�	
 	RCC->APB2ENR|=1<<(2+bit_getH4((int)PXx));    		//ʹ��ʱ�� 
	Port_PinInit_GPIO(PXx,0);	//anolog���루�üĴ�����0��	

//======��ADCʱ�����á�		 
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����

//======���ɼ��������á�		    
	RCC->CFGR&=~(3<<14);   	//��Ƶ��������	
	RCC->CFGR|=2<<14; 		//SYSCLK/DIV2=12M ADCʱ������Ϊ12M,ADC���ʱ�Ӳ��ܳ���14M!
	//���򽫵���ADC׼ȷ���½�!

//======��ADC���á�	     	 
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ  
	ADC1->CR1&=~(1<<8);    //��ɨ��ģʽ	  
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //�������ת��  
	ADC1->CR2|=1<<20;      //ʹ�����ⲿ����(SWSTART)!!!	����ʹ��һ���¼�������
	ADC1->CR2&=~(1<<11);   //�Ҷ���	 

//======��ADC����			  
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20; 		//����ͨ������1��

//======��ADC�ٶȡ�		
	ADC1->SMPR2&=~((u32)7<<(3*pin_temp));  //ͨ������ʱ�����	  
 	ADC1->SMPR2|=((u32)7<<(3*pin_temp));   //239.5���ڣ���߲���ʱ�������߾�ȷ��    		
	
//======��У׼��	 
	ADC1->CR2|=1<<0;	   		//����ADת����	 
	ADC1->CR2|=1<<3;       	//ʹ�ܸ�λУ׼  
	while(ADC1->CR2&1<<3); 	//�ȴ�У׼���� 			 
    //��λ��������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
	ADC1->CR2|=1<<2;        	//����ADУ׼	   
	while(ADC1->CR2&1<<2);  	//�ȴ�У׼����
	//��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����  
}

static void Port_PinInit_PWM(PIN_PXx PXx)
{
	Port_PinInit_GPIO(PXx,0xB);	//����������üĴ�����B��	  
	RCC->APB1ENR|=1<<0; 	//TIM2ʱ��ʹ�� 

	if((bit_getL4((int)PXx)/2)==0){
		TIM2->CCMR1|=7<<((bit_getL4((int)PXx)%2)*8+4);  	//CH1,CH2 PWM2ģʽ
		TIM2->CCMR1|=1<<((bit_getL4((int)PXx)%2)*8+3); 		//CH1,CH2 Ԥװ��ʹ��
	}
	else{
		TIM2->CCMR2|=7<<((bit_getL4((int)PXx)%2)*8+4);  	//CH3,CH4 PWM2ģʽ
		TIM2->CCMR2|=1<<((bit_getL4((int)PXx)%2)*8+3); 		//CH3,CH4 Ԥװ��ʹ��
	}
	TIM2->CR1=0x0080;   	//ARPEʹ��
	TIM2->CR1|=1<<0;    	//ʹ�ܶ�ʱ��2	  	   		
}

//#############################���ⲿ��###############################

void pixelC_HW_Port_PinInit(PIN_PXx PXx,PIN_MODE mode)
{
	switch(mode)
	{
		case OUTPUT:	Port_PinInit_GPIO(PXx,0x3);	break;
		case INPUT:		Port_PinInit_GPIO(PXx,0x8);	break;
		case ADC_IN:	Port_PinInit_ADC(PXx);		break;
		case PWM_OUT:	Port_PinInit_PWM(PXx);		break;
		default:;
	}	
}

u16 pixelC_HW_Port_getADC(PIN_PXx PXx)   
{	   
	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
	ADC1->SQR3|=bit_getL4((int)PXx);				  			    
	ADC1->CR2|=1<<22;       //��������ת��ͨ�� 
	while(!(ADC1->SR&1<<1));//�ȴ�ת������	 	   
	return ADC1->DR;		//����adcֵ		
}

void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on)
{
	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ����Ƶ����
	switch(bit_getL4((int)PXx))
	{
		case 0:TIM2->CCR1=ccr;break;
		case 1:TIM2->CCR2=ccr;break;
		case 2:TIM2->CCR3=ccr;break;
		case 3:TIM2->CCR4=ccr;break;
		default:;
	}
	TIM2->CCER|=((u32)pwm_on)<<((bit_getL4((int)PXx)*4));   	//OC1 ���ʹ��			 
}

//-------------------------��Э����ٲ�����
//-----------��SPI��


//SPI2�ٶ����ú���
//SpeedSet:0~7
//SPI�ٶ�=fAPB1/2^(SpeedSet+1)
//APB1ʱ��һ��Ϊ36Mhz
void Port_SPI2_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//���Ʒ�Χ
	SPI2->CR1&=0XFFC7; 
	SPI2->CR1|=SpeedSet<<3;	//����SPI2�ٶ�  
	SPI2->CR1|=1<<6; 		//SPI�豸ʹ��	  
} 

//SPI2 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 Port_SPI2_ReadWriteByte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI2->SR&1<<1)==0)		//�ȴ���������	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//��ʱ�˳�
	}			  
	SPI2->DR=TxData;	 	  		//����һ��byte 
	retry=0;
	while((SPI2->SR&1<<0)==0) 		//�ȴ�������һ��byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//��ʱ�˳�
	}	  						    
	return SPI2->DR;          		//�����յ�������				    
}

void pixelC_HW_Port_SPI2_Init(void)	   //ʹ��SPI2��
{
	RCC->APB2ENR|=1<<3;  	//PORTBʱ��ʹ�� 	 
	RCC->APB1ENR|=1<<14;   	//SPI2ʱ��ʹ�� 
	//����ֻ���SPI�ڳ�ʼ��
	GPIOB->CRH&=0X000FFFFF; 
	GPIOB->CRH|=0XBBB00000;	//PB13/14/15���� 	    
	GPIOB->ODR|=0X7<<13;   	//PB13/14/15����
	SPI2->CR1|=0<<10;		//ȫ˫��ģʽ	
	SPI2->CR1|=1<<9; 		//���nss����
	SPI2->CR1|=1<<8;  

	SPI2->CR1|=1<<2; 		//SPI����
	SPI2->CR1|=0<<11;		//8bit���ݸ�ʽ	
	SPI2->CR1|=1<<1; 		//����ģʽ��SCKΪ1 CPOL=1
	SPI2->CR1|=1<<0; 		//���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1  
	//��SPI2����APB1������.ʱ��Ƶ�����Ϊ36M.
	SPI2->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPI2->CR1|=0<<7; 		//MSBfirst   
	SPI2->CR1|=1<<6; 		//SPI�豸ʹ��
	Port_SPI2_ReadWriteByte(0xff);//��������			
}

//-----------��USART��


static void _myfputc(char ch)
{
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	USART2->DR = (u8) ch;      
}

void USART2_printf(const char* str,...)
{
	va_list arp;
	va_start(arp,str);								//�䳤����ջʼ����str
	_myprintf(_myfputc,str,arp);
	va_end(arp);
}

void pixelC_HW_Port_USART2_Init(u32 bound,u8 en_rx)	//����2��ʼ��
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(72000000)/(bound*32);//�õ�USARTDIV��ע�⣺����2��ʱ���Ǵ���1��һ�룡����
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 

	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���2ʱ��
	 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO״̬����
		  
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
	//����������
 	USART2->BRR=mantissa; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
	if(en_rx==1)
	{
		//ʹ�ܽ����ж�
		USART2->CR1|=1<<8;    //PE�ж�ʹ��
		USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
		System_NVIC_Init(3,3,USART2_IRQChannel,2);//��2��������ȼ� 
	}
}



