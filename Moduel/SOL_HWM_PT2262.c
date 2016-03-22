#include"pixelC_Hardware_include.h"
#include"SOL_HWM_PT2262.h"


void _Outpin_Init(void);
void _Outpin_Set(void);
void _Outpin_Reset(void);

TELECTRL_MSG _teleC={
	492,
	1488,
	15378,
	0xaaaa
};
TELECTRL_MSG *teleC=&_teleC;


PT2262_MSG _PT2262={
	&_teleC,
	_Outpin_Init,
	_Outpin_Set,
	_Outpin_Reset
};
PT2262_MSG *PT2262=&_PT2262;

//##########################【硬件测试页面】##########################
MENU_PAGE index,simple,multiple,set,address_set,time_set,advance,a_addrzone;

//==========================【主页】==========================
__M_PAGE(index,"315_TeleCtrl",PAGE_NULL,
{
	SOLGUI_Cursor(6,0,4);	
	SOLGUI_Widget_GotoPage(0,&simple);		//简单模式
	SOLGUI_Widget_GotoPage(1,&multiple);	//多从机模式
	SOLGUI_Widget_GotoPage(2,&set);	//多从机模式
	SOLGUI_Widget_GotoPage(3,&advance);	//多从机模式
});

//==========================【简单模式】==========================

void _key_A()
{
	pixelC_HW_flagLight_Twinkle();
	_send(PT2262,PT2262->telectrl->Address,0x01);	
}

void _key_B()
{
	pixelC_HW_flagLight_Twinkle();
	_send(PT2262,PT2262->telectrl->Address,0x02);	
}

void _key_C()
{
	pixelC_HW_flagLight_Twinkle();
	_send(PT2262,PT2262->telectrl->Address,0x04);	
}

void _key_D()
{
	pixelC_HW_flagLight_Twinkle();
	_send(PT2262,PT2262->telectrl->Address,0x08);	
}

__M_PAGE(simple,"Simple",&index,
{
	SOLGUI_Cursor(6,0,4);	
	SOLGUI_Widget_Button(0,"A",_key_A);
	SOLGUI_Widget_Button(1,"B",_key_B);
	SOLGUI_Widget_Button(2,"C",_key_C);
	SOLGUI_Widget_Button(3,"D",_key_D);
});

//==========================【多从机模式】==========================
u32 dat;

void _key_multi()
{
	pixelC_HW_flagLight_Twinkle();
	_send(PT2262,PT2262->telectrl->Address,dat);	
}

__M_PAGE(multiple,"Multiple",&index,
{
	SOLGUI_Cursor(6,0,5);	
	SOLGUI_Widget_Switch(0,"A",&dat,0);
	SOLGUI_Widget_Switch(1,"B",&dat,1);
	SOLGUI_Widget_Switch(2,"C",&dat,2);
	SOLGUI_Widget_Switch(3,"D",&dat,3);
	SOLGUI_Widget_Button(4,"Send",_key_multi);
});

//==========================【设置】==========================
int a0=2,a1=2,a2=2,a3=2,a4=2,a5=2,a6=2,a7=2;

void _SetAddress()
{
	pixelC_HW_flagLight_Twinkle();
	PT2262->telectrl->Address=a0|a1<<2|a2<<4|a3<<6|a4<<8|a5<<10|a6<<12|a7<<14;
}

__M_PAGE(address_set,"Address",&set,
{
	SOLGUI_Cursor(5,0,10);
	SOLGUI_Widget_Text(0,48,F6X8," 0:0,1:1,2:F  [%04x]   ",PT2262->telectrl->Address);	
	SOLGUI_Widget_Spin(0,"A0",INTEGRAL,2,0,&a0);	//数字旋钮
	SOLGUI_Widget_Spin(1,"A1",INTEGRAL,2,0,&a1);	//数字旋钮
	SOLGUI_Widget_Spin(2,"A2",INTEGRAL,2,0,&a2);	//数字旋钮
	SOLGUI_Widget_Spin(3,"A3",INTEGRAL,2,0,&a3);	//数字旋钮
	SOLGUI_Widget_Spin(4,"A4",INTEGRAL,2,0,&a4);	//数字旋钮
	SOLGUI_Widget_Spin(5,"A5",INTEGRAL,2,0,&a5);	//数字旋钮
	SOLGUI_Widget_Spin(6,"A6",INTEGRAL,2,0,&a6);	//数字旋钮
	SOLGUI_Widget_Spin(7,"A7",INTEGRAL,2,0,&a7);	//数字旋钮
	SOLGUI_Widget_Spin(8,"AddressSet",INTEGRAL,0xffff,0,&PT2262->telectrl->Address);	//数字旋钮
	SOLGUI_Widget_Button(9,"SetAddress",_SetAddress);
});

__M_PAGE(time_set,"Time",&set,
{
	SOLGUI_Cursor(5,2,3);
	SOLGUI_Widget_Text(0,48,F6X8,"Set Flame(time in us)");	
	SOLGUI_Widget_Spin(0,"Time_long",INTEGRAL,100000,0,&PT2262->telectrl->Time_Long);	//数字旋钮
	SOLGUI_Widget_Spin(1,"Time_Short",INTEGRAL,100000,0,&PT2262->telectrl->Time_Short);	//数字旋钮
	SOLGUI_Widget_Spin(2,"Time_Syn",INTEGRAL,100000,0,&PT2262->telectrl->Time_Syn);	//数字旋钮
	SOLGUI_Widget_Text(0,8,F6X8,"Flame_Data");
	SOLGUI_Widget_Bar(66,8,60,6,PT2262->telectrl->Time_Long+PT2262->telectrl->Time_Short,0,PT2262->telectrl->Time_Short,SCALEBAR|DIREC_X);
	SOLGUI_Widget_Text(0,0,F6X8,"Flame_ALL");
	SOLGUI_Widget_Bar(66,0,60,6,PT2262->telectrl->Time_Long+PT2262->telectrl->Time_Short+PT2262->telectrl->Time_Syn,0,PT2262->telectrl->Time_Long+PT2262->telectrl->Time_Short,SCALEBAR|DIREC_X);
});

__M_PAGE(set,"Set",&index,
{
	SOLGUI_Cursor(6,0,2);	
	SOLGUI_Widget_GotoPage(0,&address_set);
	SOLGUI_Widget_GotoPage(1,&time_set);
});

//==========================【高级模式】==========================

int addr_top=0;
int addr_bot=0;

void _Startaddrzone()
{
	static int k=0;
	for(k=addr_bot;k<addr_top;k++)
	{
		pixelC_HW_flagLight_Twinkle();
		_send(PT2262,k,dat);

		SOLGUI_Widget_Text(21,40,F6X8,"    Scanf   ");
		SOLGUI_Widget_Text(21,30,F6X8,"addr: [%04x]",k);
		SOLGUI_Widget_Bar(6,16,120,8,addr_bot,addr_top,k,PROGBAR|DIREC_X);
		SOLGUI_Refresh();				//更新屏幕
	}
		
}

__M_PAGE(a_addrzone,"AddrZone",&advance,		  			//地址段控制功能
{
	SOLGUI_Cursor(5,0,7);
	SOLGUI_Widget_Text(0,48,F6X8,"need more addr!");	
	SOLGUI_Widget_Spin(0,"Addr_max",INTEGRAL,0xffff,0,&addr_top);	//数字旋钮
	SOLGUI_Widget_Spin(1,"Addr_min",INTEGRAL,0xffff,0,&addr_bot);	//数字旋钮
	SOLGUI_Widget_Switch(2,"A",&dat,0);
	SOLGUI_Widget_Switch(3,"B",&dat,1);
	SOLGUI_Widget_Switch(4,"C",&dat,2);
	SOLGUI_Widget_Switch(5,"D",&dat,3);
	SOLGUI_Widget_Button(6,"Start!",_Startaddrzone);	

});

__M_PAGE(advance,"Advance",&index,
{
	SOLGUI_Cursor(6,0,2);	
	SOLGUI_Widget_GotoPage(0,&a_addrzone);
});

////==========================【RF315M_test_recieve】==========================
//
//__M_WMB_MALLOC(text_wave,128)
//
//__M_PAGE(RF315M_test_recieve,"recieve",&Index,
//{
//	SOLGUI_Cursor(6,6,1);
//	SOLGUI_Widget_Oscillogram(0,0,127,48,5000,0,text_wave);
//});
//
//
//
//
//
//
//
//



//##########################【全局变量定义】##########################


//##########################【内部】##########################

void _Outpin_Init(void)
{
	pixelC_HW_GPIO_Init(GPIO_PA2,GPIO_OUT);		//发射	
}

void _Outpin_Set(void)
{
	pixelC_HW_GPIO_Out(GPIO_PA2,1);
}

void _Outpin_Reset(void)
{
	pixelC_HW_GPIO_Out(GPIO_PA2,0);
}



//##########################【API】##########################

void SOL_HWM_PT2262_Init(void)
{
	
//	pixelC_HW_ADC_Init(ADC1,ADC_PA3);			//接收
//	pixelC_HW_Timer_Init(TIMER2,800,90);		//接收定时器
	PT2262->OutPin_Init();

}


void _PT2262_Data0(PT2262_MSG *p)
{
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Short);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Long);
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Short);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Long);
}

void _PT2262_Data1(PT2262_MSG *p)
{
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Long);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Short);
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Long);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Short);	
}

void _PT2262_DataF(PT2262_MSG *p)
{
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Short);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Long);
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Long);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Short);	
}

void _PT2262_DataSyn(PT2262_MSG *p)
{
	p->OutPin_Set();
	delay_us(p->telectrl->Time_Short);
	p->OutPin_Reset();
	delay_us(p->telectrl->Time_Syn);	
}

void _send(PT2262_MSG *p,u16 addr,u8 d)
{
	u8 i,j;         
    u16 temp;          

    for(i=0;i<4;i++)
	{     //发射相同的8组码 //发射相同的4组码？//发射相同的2组码  ????? 
		for(j=0;j<8;j++){        //先发射8位地址
		temp=addr;
		temp>>=((7-j)*2);        //将待发射的两位移到最低位
		temp&=3;
		
		if(temp==0)      _PT2262_Data0(p);
		else if (temp==1)_PT2262_Data1(p);
		else if (temp==2)_PT2262_DataF(p);
		}
		
		for(j=0;j<4;j++){        //再发4位数据
		temp=d;
		temp>>=(3-j);
		temp&=1;
		if(temp==0)		_PT2262_Data0(p);
		else if(temp==1)_PT2262_Data1(p);
		}        
		_PT2262_DataSyn(p); 	
    }
}

//##################################【定时器中断】#######################################
//------------【定时器2中断函数】
void TIM2_IRQHandler(void)
{
#ifdef Timer2_IRQ_Enable
//	unsigned int v;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
		/*------------此处编写TIM2中断中执行的语句------------*/
//		v=pixelC_HW_ADC_getValue(ADC1,ADC_PA3);
//		SOLGUI_Oscillogram_Probe(text_wave,v);
		/*----------------------------------------------------*/	
	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}
#endif
}






