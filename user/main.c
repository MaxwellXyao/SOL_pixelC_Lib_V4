#include"pixelC_Hardware_include.h"

//##############################【测试页面】##############################



//##############################【主函数】##############################
extern MENU_PAGE index;	//在menu.c中编写页面

int main()
{
	u8 kv=0;
	Stm32_Clock_Init();					//系统时钟初始化
	delay_init(72);						//72MHz内部频率

	pixelC_HW_Key_Init();
	SOLGUI_Init(&index);

	
	while(1)
	{
		kv=pixelC_HW_Key_GetValue();
		SOLGUI_InputKey(kv);
		SOLGUI_Menu_PageStage();



		SOLGUI_Refresh();				//更新屏幕
	}
}





