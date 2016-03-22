#ifndef SOL_SWM_RSA_H
#define	SOL_SWM_RSA_H

/* RSA�㷨�м��ܷ���������Կ��N��E�����ܷ�ʹ��N��D���� */
#define P   11   /* P��Q����Ϊ��������ʵ��������ͨ��Ϊ�ܴ���� */
#define Q   13
 
#define N   (P*Q)  		//143	//��Կ(��������ֵС��143)
#define Z   ((P - 1)*(Q - 1))	//120
 
#define E   11       /* ���ܷ�ѡ��E��E�����Zֻ��һ����Լ�� */
#define D   11       /* (E * D - 1)�����ܹ���Z���� */
                    /* ����long int�޷���ʾ��������֣�����Dȡ5 */

//��Կ(143,11)
//˽Կ(143,11)


void SOL_SWM_RSA_Encrypt(unsigned char *TrsMsg,unsigned char *SecCode,unsigned int MsgNum,unsigned char e,unsigned char n);
void SOL_SWM_RSA_Decrypt(unsigned char *SecCode,unsigned char *DeMsg,unsigned int MsgNum,unsigned char d,unsigned char n);

#endif
