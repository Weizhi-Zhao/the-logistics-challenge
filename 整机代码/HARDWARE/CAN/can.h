#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    

//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.

extern u8 CAN_RX_BUF[40];
extern u8 CAN_TX_BUF1[8];
extern u8 CAN_TX_BUF2[8];

										 							 				    
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 Can_Send_Msg(u8* msg,u8 len, u16 stdId);						//��������

u8 Can_Receive_Msg(u8 *buf);							//��������

void canInit(void);
#endif

















