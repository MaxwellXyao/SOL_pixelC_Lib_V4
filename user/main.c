#include"pixelC_Hardware_include.h"

//##############################����������##############################
extern MENU_PAGE index;	//��menu.c�б�дҳ�溯��

int main()
{
	u8 kv=0;
	Stm32_Clock_Init();					//ϵͳʱ�ӳ�ʼ��
	delay_init(72);						//72MHz�ڲ�Ƶ��

	pixelC_HW_Key_Init();				//������ʼ��
	SOLGUI_Init(&index);				//SOLGUI��ʼ��

	
	while(1)
	{
		kv=pixelC_HW_Key_GetValue();
		SOLGUI_InputKey(kv);
		SOLGUI_Menu_PageStage();



		SOLGUI_Refresh();				//������Ļ
	}
}





