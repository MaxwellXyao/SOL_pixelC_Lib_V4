#ifndef SOL_SWM_RSA_H
#define	SOL_SWM_RSA_H

/* RSA算法中加密方公布的密钥是N和E，解密方使用N和D解密 */
#define P   11   /* P和Q必须为素数，在实际运用中通常为很大的数 */
#define Q   13
 
#define N   (P*Q)  		//143	//公钥(输入数据值小于143)
#define Z   ((P - 1)*(Q - 1))	//120
 
#define E   11       /* 加密方选择E，E必须和Z只有一个公约数 */
#define D   11       /* (E * D - 1)必须能够被Z整除 */
                    /* 由于long int无法表示过大的数字，所以D取5 */

//公钥(143,11)
//私钥(143,11)


void SOL_SWM_RSA_Encrypt(unsigned char *TrsMsg,unsigned char *SecCode,unsigned int MsgNum,unsigned char e,unsigned char n);
void SOL_SWM_RSA_Decrypt(unsigned char *SecCode,unsigned char *DeMsg,unsigned int MsgNum,unsigned char d,unsigned char n);

#endif
