#include"pixelC_Hardware_include.h"

//##############################������ҳ�桿##############################
MENU_PAGE index;

__M_PAGE(index,"test",PAGE_NULL,{
	 SOLGUI_Cursor(0,6,5);
	 SOLGUI_Widget_OptionText(0,"1");
	 SOLGUI_Widget_OptionText(1,"12");
	 SOLGUI_Widget_OptionText(2,"123");
	 SOLGUI_Widget_OptionText(3,"1234");
	 SOLGUI_Widget_OptionText(4,"12345");
});

//##############################����������##############################
int main()
{
	u8 kv=0;
	Stm32_Clock_Init();					//ϵͳʱ�ӳ�ʼ��
	delay_init(72);						//72MHz�ڲ�Ƶ��

	pixelC_HW_flagLight_Init();
	pixelC_HW_Key_Init();

	SOLGUI_Init(&index);

	while(1)
	{
		kv=pixelC_HW_Key_GetValue();
		SOLGUI_InputKey(kv);
		SOLGUI_Menu_PageStage();
	
		SOLGUI_Refresh();				//������Ļ
	}
}





