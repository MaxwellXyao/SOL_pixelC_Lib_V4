#ifndef __USART_H
#define __USART_H

#include<stdarg.h> 						//支持变长参数

//###########################【API】###########################
void _myprintf(void (*myputc)(char),const char* str,va_list arp);		//自制printf底层


/*
【使用说明】
可以用于多串口使用的printf函数
这是一个底层，因此可以使用于多种不同的字符串发送场景（屏幕，串口）。

【1】如何嵌入到程序中：
0x01:添加支持变长函数的头文件

	#include<stdarg.h>

0x02:编写一个外壳函数用于调用，格式如下：
（其中只包含两个必须添加的参数，其他参数用户可自定义）

void XXX_printf(const char* str,...)
{
	va_list arp;
	va_start(arp,str);								//变长参数栈始点在str
	_myprintf(MYPUTC,str,arp);
	va_end(arp);	
}

其中的MYPUTC函数指针所指必须为void function(char)格式
	

【2】可以输出的格式:

0x01:格式符：
	%s,%S:字符串
	%c,%C:单个字符

	%f,%F:double浮点数
	（这里有个小bug，每个格式化字符串只能带有一个%f，否则后面的小数显示不正确，默认留3位小数）

	%b,%B:整型二进制
	%o,%O:整型八进制
	%d,%D:整型十进制（可有正负）
	%u,%U:整型十进制（可有正负）
	%x,%X:整型十六进制

0x02:参数（只有这三种）
	%07d：补零（数字最小显示长读7格，不足则用0在前面补齐）
	%-7d：左对齐（数字最小显示长度7格，不足则用空格在后面补齐）
	%.4f: 保留小数位数（保留4位小数，最多保留7位）

（程序内未对转义字符做处理，但是可以使用转义字符，可能存在未知的bug）
*/



#endif 
