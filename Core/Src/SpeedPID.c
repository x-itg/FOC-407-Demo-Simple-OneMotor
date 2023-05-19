#include "SpeedPID.h"

#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

#define M1_SPEED_KP  0.25f
#define M1_SPEED_KI  0.0008f
#define M1_SPEED_KD  0.0f

volatile uint32_t gSpeedPID_TimeCNT;
float Motor1GetPreSpeed(void);
void  Motor1SetCurrent(float current);

SpeedPIDControl_Struct gMotor1SpeedPID = {                                                                    
    .isEnable = 0,                                                                              
    .sysTimer = 0,                                                                              
    .sPID.kp = 0,                                                                               
    .sPID.kd = 0,                                                                               
    .sPID.ki = 0,                                                                               
    .sPID.tar = 0,                                                                              
    .sPID.pre = 0,                                                                              
    .sPID.bais = 0,                                                                             
    .sPID.last_bias = 0,                                                                        
    .sPID.err = 0,                                                                              
    .sPID.out = 0,                                                                              
    .sPID.outMax = 10,//xOutMax,                                                                     
    .sPID.cycle = 0.002,//                                                                       
    .GetPreSpeed = Motor1GetPreSpeed,                                                      
    .SetOutCurrent = Motor1SetCurrent,                                                        
};



float Motor1GetPreSpeed(void)
{
    static float angle = 0.0;
    static float lastAngle = 0.0;
    float speed;
    angle = Motor1GetAngle();
    speed = angle - lastAngle;
    if (speed < -180) {
        speed = speed + 360;
    }
    if (speed > 180) {
        speed = speed - 360;
    }
		lastAngle = angle;
    return speed;
}

void  Motor1SetCurrent(float current)
{
    Motor1SetTarIDIQ(0,current);
}






/*************************************************************
** Function name:       Motor1SpeedPIDConfig_Init
** Descriptions:        电机1速度PID初始化

*************************************************************/
void Motor1SpeedPIDConfig_Init(void)
{
    SetSpeedPIDEnable(&gMotor1SpeedPID,1);
    SetSpeedPIDParams(&gMotor1SpeedPID,M1_SPEED_KP,M1_SPEED_KI,M1_SPEED_KD);
    SetSpeedPIDTar(&gMotor1SpeedPID,0.0f);
}

/*************************************************************
** Function name:       Motor1SpeedPIDConfigSetTar
** Descriptions:        电机1速度PID初始化

*************************************************************/
void Motor1SpeedPIDConfigSetTar(float tarSpeed)
{
    SetSpeedPIDTar(&gMotor1SpeedPID,tarSpeed);
}

/*************************************************************
** Function name:       Motor1SpeedPIDConfig_Init
** Descriptions:        电机1速度PID初始化

*************************************************************/
void Motor1SpeedPIDConfig_Loop(void)
{
    SpeedPIDCycle(&gMotor1SpeedPID);
}
/*************************************************************
** Function name:       Motor1SpeedPIDConfig_Printf
** Descriptions:        电机1速度PID信息打印

*************************************************************/
void Motor1SpeedPIDConfig_Printf(void)
{
	SpeedPIDPrintf(&gMotor1SpeedPID);
}
/*************************************************************
** Function name:       SpeedPIDControl
** Descriptions:        速度PID控制
** Input parameters:    pSpeedPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void SpeedPIDControl(PSpeedPIDControl_Struct pSpeedPID)
{

    pSpeedPID->sPID.pre = pSpeedPID->GetPreSpeed();
    pSpeedPID->sPID.bais = pSpeedPID->sPID.tar - pSpeedPID->sPID.pre;
    pSpeedPID->sPID.out += pSpeedPID->sPID.kp*(pSpeedPID->sPID.bais - pSpeedPID->sPID.last_bias) +  pSpeedPID->sPID.ki * pSpeedPID->sPID.bais;
    pSpeedPID->sPID.last_bias = pSpeedPID->sPID.bais;

	if (pSpeedPID->sPID.out > pSpeedPID->sPID.outMax) {
		pSpeedPID->sPID.out = pSpeedPID->sPID.outMax;
	} else if (pSpeedPID->sPID.out < -pSpeedPID->sPID.outMax) {
		pSpeedPID->sPID.out = -pSpeedPID->sPID.outMax;
	}
    if(pSpeedPID->isEnable == 0) {
        pSpeedPID->sPID.out = 0;
    }
    pSpeedPID->SetOutCurrent(pSpeedPID->sPID.out);
}

/*************************************************************
** Function name:       SpeedPIDCycle
** Descriptions:        速度PID循环函数
** Input parameters:    pSpeedPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDCycle(PSpeedPIDControl_Struct pSpeedPID)
{
    if(SPEEDPID_TIMEOUT(pSpeedPID->sPID.cycle * 1000.0f,pSpeedPID->sysTimer)) {
        pSpeedPID->sysTimer = SPEEDPID_GETTIME();
        SpeedPIDControl(pSpeedPID);
    }
}
/*************************************************************
** Function name:       SetSpeedPIDParams
** Descriptions:        设置速度PID参数
** Input parameters:    pSpeedPID:结构体指针
**                      kp:比例
**                      ki:积分
**                      kd:微分
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDParams(PSpeedPIDControl_Struct pSpeedPID,float kp,float ki,float kd)
{
    pSpeedPID->sPID.kp = kp;
    pSpeedPID->sPID.ki = ki;
    pSpeedPID->sPID.kd = kd;
}
/*************************************************************
** Function name:       SetSpeedPIDTar
** Descriptions:        设置目标值
** Input parameters:    pSpeedPID:结构体指针
**                      tar:目标速度
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDTar(PSpeedPIDControl_Struct pSpeedPID,float tar)
{
    pSpeedPID->sPID.tar = tar;
}



/*************************************************************
** Function name:       SetSpeedPIDEnable
** Descriptions:        设置速度PID使能
** Input parameters:    pSpeedPID:结构体指针
**                      isEnable:1: 使能0：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDEnable(PSpeedPIDControl_Struct pSpeedPID,float isEnable)
{
    pSpeedPID->isEnable = isEnable;
}




/*************************************************************
** Function name:       SpeedPIDPrintf
** Descriptions:        速度PID信息打印
** Input parameters:    pSpeedPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDPrintf(PSpeedPIDControl_Struct pSpeedPID)
{
	printf("2:%f\r\n",pSpeedPID->sPID.pre);
	printf("3:%f\r\n",pSpeedPID->sPID.tar);
}



























