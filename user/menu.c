#include"pixelC_Hardware_include.h"

/*-----------------------------------------------------------------------
//============【SOLGUI快速操作范例】============
【1】字符串的格式化输出:
格式用法和PC的prinf一样：

0x01:格式符：
	%s,%S:字符串
	%c,%C:单个字符

	%f,%F:double浮点数（每个格式化字符串只能带有一个，默认留3位小数）

	%b,%B:整型二进制
	%o,%O:整型八进制
	%d,%D:整型十进制（可有正负）
	%u,%U:整型十进制（可有正负）
	%x,%X:整型十六进制

0x02:参数（只有这三种）
	%07d：补零（数字最小显示长读7格，不足则用0在前面补齐）
	%-7d：左对齐（数字最小显示长度7格，不足则用空格在后面补齐）
	%.4f: 保留小数位数（保留4位小数，最多保留7位）

【2】页面框架部署:

	SOLGUI_Init(&index);			//初始化
	...
	while(1)
	{
		...
		kv=pixelC_HW_Key_GetValue();	//键值获取
		SOLGUI_InputKey(kv);			//键值输入
		SOLGUI_Menu_PageStage();	 	//前台
		SOLGUI_Refresh();				//更新屏幕
		...
	}


【3】页面创建:
MENU_PAGE index;						//页面声明
 __M_PAGE(index,"test",PAGE_NULL,{		//宏方式创建页面
	//////////////添加控件//////////////
});

【4】添加控件:
//---------------------------------【页面控制】------------------------------------
SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);					
//光标（上边界行，下边界行，选项个数）

//---------------------------------【选项式控件】------------------------------------
SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);										
页面跳转（显示序号，页面指针）

SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);
数字旋钮（显示序号，显示名，变量类型，调整上限，调整下限，变量指针）
<变量类型>:INT8，UINT8，INT16，INT32，FLT16，FLT32

SOLGUI_Widget_OptionText(u8 USN,const u8* str,...);									
选项文本（显示序号，格式化字符串，变长参数）
(太长的文字str会遮盖滚动条)

SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));						
按键（显示序号，显示名，牵连函数）

SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift);				
变量开关（显示序号，显示名，u32型变量指针，控制的位）

SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf);						
文本编辑器（显示序号，显示名，可修改长度，字符串指针）

//-------------------------------------【自由式控件】------------------------
SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...);										
文字（参考点x坐标，参考点y坐标，字体，格式化字符串，变长参数）
<字体>:F6X8，R6X8，F4X6，R4X6，F8X8，R8X8，F8X10，R8X10 (F为正常，R为反白)

SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);				
条（参考点x坐标，参考点y坐标，长，高，上限值，下限值，输入值，显示模式）
<显示模式>:		使用例：DIREC_X|SCALEBAR
mode[0]：DIREC_X(x方向生长,默认)，DIREC_Y(y方向生长)
mode[2:1]：PROGBAR(进度条,默认)，SCALEBAR(刻度条)

SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	
谱（参考点x坐标，参考点y坐标，长，高，上限值，下限值，显示点数，输入数组）

SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb);  		
波（参考点x坐标，参考点y坐标，长，高，上限值，下限值，波数据储存块指针）
要通过波探针SOLGUI_Oscillogram_Probe()输入数据

SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode); 
图片（参考点x坐标，参考点y坐标，显示长，显示高，图片指针，原图长，原图高，显示模式）
<显示模式>:	NML(正常无附加)，FRM(边框开关)，REV(反白开关)


//---------------------------------------【附件】------------------------------
SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value);												
波探针(波数据储存块指针,变量输入);

-----------------------------------------------------------------------*/


//##############################【声明页面变量】##############################
MENU_PAGE index;

//##############################【编写页面函数】##############################




//=================【主页面】=================

__M_PAGE(index,"index",PAGE_NULL,{
	SOLGUI_Widget_Text(0,0,F6X8,"Helloworld!");		
});









