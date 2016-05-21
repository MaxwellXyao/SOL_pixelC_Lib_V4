#include"pixelC_Hardware_include.h"

/*-----------------------------------------------------------------------
//============��SOLGUI���ٲ���������============
��1���ַ����ĸ�ʽ�����:
��ʽ�÷���PC��prinfһ����

0x01:��ʽ����
	%s,%S:�ַ���
	%c,%C:�����ַ�

	%f,%F:double��������ÿ����ʽ���ַ���ֻ�ܴ���һ����Ĭ����3λС����

	%b,%B:���Ͷ�����
	%o,%O:���Ͱ˽���
	%d,%D:����ʮ���ƣ�����������
	%u,%U:����ʮ���ƣ�����������
	%x,%X:����ʮ������

0x02:������ֻ�������֣�
	%07d�����㣨������С��ʾ����7�񣬲�������0��ǰ�油�룩
	%-7d������루������С��ʾ����7�񣬲������ÿո��ں��油�룩
	%.4f: ����С��λ��������4λС������ౣ��7λ��

��2��ҳ���ܲ���:

	SOLGUI_Init(&index);			//��ʼ��
	...
	while(1)
	{
		...
		kv=pixelC_HW_Key_GetValue();	//��ֵ��ȡ
		SOLGUI_InputKey(kv);			//��ֵ����
		SOLGUI_Menu_PageStage();	 	//ǰ̨
		SOLGUI_Refresh();				//������Ļ
		...
	}


��3��ҳ�洴��:
MENU_PAGE index;						//ҳ������
 __M_PAGE(index,"test",PAGE_NULL,{		//�귽ʽ����ҳ��
	//////////////��ӿؼ�//////////////
});

��4����ӿؼ�:
//---------------------------------��ҳ����ơ�------------------------------------
SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);					
//��꣨�ϱ߽��У��±߽��У�ѡ�������

//---------------------------------��ѡ��ʽ�ؼ���------------------------------------
SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);										
ҳ����ת����ʾ��ţ�ҳ��ָ�룩

SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);
������ť����ʾ��ţ���ʾ�����������ͣ��������ޣ��������ޣ�����ָ�룩
<��������>:INT8��UINT8��INT16��INT32��FLT16��FLT32

SOLGUI_Widget_OptionText(u8 USN,const u8* str,...);									
ѡ���ı�����ʾ��ţ���ʽ���ַ������䳤������
(̫��������str���ڸǹ�����)

SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));						
��������ʾ��ţ���ʾ����ǣ��������

SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift);				
�������أ���ʾ��ţ���ʾ����u32�ͱ���ָ�룬���Ƶ�λ��

SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf);						
�ı��༭������ʾ��ţ���ʾ�������޸ĳ��ȣ��ַ���ָ�룩

//-------------------------------------������ʽ�ؼ���------------------------
SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...);										
���֣��ο���x���꣬�ο���y���꣬���壬��ʽ���ַ������䳤������
<����>:F6X8��R6X8��F4X6��R4X6��F8X8��R8X8��F8X10��R8X10 (FΪ������RΪ����)

SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);				
�����ο���x���꣬�ο���y���꣬�����ߣ�����ֵ������ֵ������ֵ����ʾģʽ��
<��ʾģʽ>:		ʹ������DIREC_X|SCALEBAR
mode[0]��DIREC_X(x��������,Ĭ��)��DIREC_Y(y��������)
mode[2:1]��PROGBAR(������,Ĭ��)��SCALEBAR(�̶���)

SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	
�ף��ο���x���꣬�ο���y���꣬�����ߣ�����ֵ������ֵ����ʾ�������������飩

SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb);  		
�����ο���x���꣬�ο���y���꣬�����ߣ�����ֵ������ֵ�������ݴ����ָ�룩
Ҫͨ����̽��SOLGUI_Oscillogram_Probe()��������

SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode); 
ͼƬ���ο���x���꣬�ο���y���꣬��ʾ������ʾ�ߣ�ͼƬָ�룬ԭͼ����ԭͼ�ߣ���ʾģʽ��
<��ʾģʽ>:	NML(�����޸���)��FRM(�߿򿪹�)��REV(���׿���)


//---------------------------------------��������------------------------------
SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value);												
��̽��(�����ݴ����ָ��,��������);

-----------------------------------------------------------------------*/


//##############################������ҳ�������##############################
MENU_PAGE index;

//##############################����дҳ�溯����##############################




//=================����ҳ�桿=================

__M_PAGE(index,"index",PAGE_NULL,{
	SOLGUI_Widget_Text(0,0,F6X8,"Helloworld!");		
});









