#ifndef SOL_HWM_PT2262_H
#define SOL_HWM_PT2262_H 

//##########################【结构体】##########################

typedef struct _TELECTRL_MSG{
//--------【时间参数】
	s32 Time_Short;		//短间隔
	s32 Time_Long;		//长间隔
	s32 Time_Syn;		//同步间隔
//--------【地址参数】
	u16 Address;		//地址
}TELECTRL_MSG;

typedef struct _PT2262_MSG{
//--------【软件】
	TELECTRL_MSG *telectrl;		//遥控信息
//--------【硬件】
	void (*OutPin_Init)(void);	//硬件初始化
	void (*OutPin_Set)(void);	//置位
	void (*OutPin_Reset)(void);	//清除
}PT2262_MSG;

//##########################【API】##########################
void SOL_HWM_PT2262_Init(void);
void _send(PT2262_MSG *p,u16 addr,u8 d);
#endif
