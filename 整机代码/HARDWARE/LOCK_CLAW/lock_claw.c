#include "lock_claw.h"

LockClaw lockClaw;
const float GEAR_R = 25;
const float CRITICAL_HEIGHT = 5;
const float MOVE_SPEED = 50;
const float _PI = 3.14159;
const float _REDUCTION_RATIO = 3581.0 / 187.0;	//����˺�ת�Ӷ�֮��ļ��ٱ�
const float _K = 8191.0 / 360.0;		//ת�Ӷ˱�������ʵ��ת���Ƕ�֮��ı�ֵ
const float LOCK_ACC = 500;
const float LOCK_HIGH_V = 300;
const float LOCK_LOW_V = 200;

void lockMoveAtSpeed(float speed){
	float rpm = speed / (2 * _PI * GEAR_R) * 60 * _REDUCTION_RATIO;
	run_at_rate(rpm, &lockClaw.motor);
}

u8 lockMovetoHeight(float startHeight, float endHeight){
	float angle = endHeight / GEAR_R / 2 / _PI * 360;
	float nowHeight = lockClaw.motor.realAngle / _K / _REDUCTION_RATIO / 360 * 2 * _PI * GEAR_R;
	if((nowHeight < endHeight - CRITICAL_HEIGHT) || (nowHeight > endHeight + CRITICAL_HEIGHT)){
		lockMoveAtSpeed(x_to_v(nowHeight, startHeight, endHeight, &lockClaw.sp));
	}
	else{
		u8 signal = run_to_angle(angle, &lockClaw.motor);
		if(signal) {
			lockClaw.timeCnt = 0;
			return 1;
		}
	}
	
	lockClaw.timeCnt++;
	if(lockClaw.timeCnt > 5000){
		lockClaw.timeCnt = 0;
		return 1;
	}
	return 0;
}

void lockHold(){
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
}

void lockRelease(){
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);
}

void lockClawInit(u8 id){
	motorInit(&lockClaw.motor, id);
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	
	lockHold();
	
	lockClaw.sp.acc = LOCK_ACC;
	lockClaw.sp.high_v = LOCK_HIGH_V;
	lockClaw.sp.low_v = LOCK_LOW_V;
}




