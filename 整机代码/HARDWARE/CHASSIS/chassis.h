#ifndef __CHASSIS
#define __CHASSIS

#include "motor.h"
#include "coco_claw.h"
#include "lock_claw.h"
#include "speed_planner.h"

//#define R 71.4;	//mm
//#define REDUCTION_RADIO 19.15;
//#define PI 3.14159;
	
	
typedef struct Chassis{
	Motor motor[3];
	float nowPos;
	float nowAngle;
	int timeCnt;
	int spinTimeCnt;
	SpeedPlanner sp_move;
	SpeedPlanner sp_spin;
}Chassis;

extern Chassis chassis;
//extern float PI;
//extern float REDUCTION_RATIO;
//extern float K;
//const float PI = 3.14159;
//const float REDUCTION_RATIO = 3581.0 / 187.0;	//����˺�ת�Ӷ�֮��ļ��ٱ�
//const float K = 8191.0 / 360.0;		//ת�Ӷ˱�������ʵ��ת���Ƕ�֮��ı�ֵ

void chassisInit(Chassis* chassis, u8 id1, u8 id2, u8 id3);
void chassisMoveAtSpeed(Chassis* chassis, float speed);
void getChassisInfo(Chassis* chassis);
void loadInitAngle(void);
u8 chassisMoveToPos(Chassis* chassis, float startPos, float endPos);
void chassisSpinAtRpm(Chassis* chassis, float rpm);
u8 chassisSpinToAngle(Chassis* chassis, float startAngle, float endAngle);


#endif