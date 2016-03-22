#include"SOL_SWM_RSA.h"



int _RSA_ModExp(int a, int b, int c)        //¿ìËÙÃÝÈ¡Óàa^b%c
{
    int res, t;
    res = 1 % c; 
    t = a % c;
    while (b)
    {
        if (b & 1)
        {
            res = res * t % c;
        }
        t = t * t % c;
        b >>= 1;
    }
    return res;
}

void SOL_SWM_RSA_Encrypt(unsigned char *TrsMsg,unsigned char *SecCode,unsigned int MsgNum,unsigned char e,unsigned char n)
{
	int i;
	for(i=0;i<MsgNum;i++)
	{
		SecCode[i]=_RSA_ModExp(TrsMsg[i],e,n);
	}
}

void SOL_SWM_RSA_Decrypt(unsigned char *SecCode,unsigned char *DeMsg,unsigned int MsgNum,unsigned char d,unsigned char n)
{
	int i;
	for(i=0;i<MsgNum;i++)
	{
		DeMsg[i]=(unsigned char)_RSA_ModExp(SecCode[i],d,n);
	}	
}


