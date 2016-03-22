#ifndef SOL_HWM_PT2262_H
#define SOL_HWM_PT2262_H 

//##########################���ṹ�塿##########################

typedef struct _TELECTRL_MSG{
//--------��ʱ�������
	s32 Time_Short;		//�̼��
	s32 Time_Long;		//�����
	s32 Time_Syn;		//ͬ�����
//--------����ַ������
	u16 Address;		//��ַ
}TELECTRL_MSG;

typedef struct _PT2262_MSG{
//--------�������
	TELECTRL_MSG *telectrl;		//ң����Ϣ
//--------��Ӳ����
	void (*OutPin_Init)(void);	//Ӳ����ʼ��
	void (*OutPin_Set)(void);	//��λ
	void (*OutPin_Reset)(void);	//���
}PT2262_MSG;

//##########################��API��##########################
void SOL_HWM_PT2262_Init(void);
void _send(PT2262_MSG *p,u16 addr,u8 d);
#endif
