#include"pixelC_Hardware_include.h"

//##############################【测试页面】##############################
MENU_PAGE index;

u32 pin_mem=0;
u16 adc0=0,adc1=0,adc2=0,adc3=0;

__M_PAGE(index,"test",PAGE_NULL,{
	 SOLGUI_Cursor(0,6,9);
	 SOLGUI_Widget_Switch(0,"PA0",&pin_mem,0);
	 SOLGUI_Widget_OptionText(1,"ADC0=%d",adc0);
	 SOLGUI_Widget_OptionText(2,"ADC1=%d",adc1);
	 SOLGUI_Widget_OptionText(3,"ADC2=%d",adc2);
	 SOLGUI_Widget_OptionText(4,"ADC3=%d",adc3);		
});

//##############################【主函数】##############################

int main()
{
	u8 kv=0;
	Stm32_Clock_Init();					//系统时钟初始化
	delay_init(72);						//72MHz内部频率

	pixelC_HW_flagLight_Init();
	pixelC_HW_Key_Init();

	SOLGUI_Init(&index);

	pixelC_HW_Port_PinInit(PA0,ADC_IN);
	pixelC_HW_Port_PinInit(PA1,ADC_IN);
	pixelC_HW_Port_PinInit(PA2,ADC_IN);	
	pixelC_HW_Port_PinInit(PA3,ADC_IN);
	while(1)
	{
		kv=pixelC_HW_Key_GetValue();
		SOLGUI_InputKey(kv);
		SOLGUI_Menu_PageStage();

//		PAout(0)=!bit_istrue(pin_mem,bit(0));
		adc0=pixelC_HW_Port_getADC(PA0);
		adc1=pixelC_HW_Port_getADC(PA1);
		adc2=pixelC_HW_Port_getADC(PA2);
		adc3=pixelC_HW_Port_getADC(PA3);

		SOLGUI_Refresh();				//更新屏幕
	}
}





