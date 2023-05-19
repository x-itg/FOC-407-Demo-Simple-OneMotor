#include "PositionPID.h"
//位置PID
#include "PositionPID.h"
//电机1电流闭环
#include "FOC.h"
#include "SpeedPID.h"
#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

volatile uint32_t gPositionPID_TimeCNT;

#define M1_POSITION_KP  0.08f
#define M1_POSITION_KI  0.000f
#define M1_POSITION_KD  0.08f
float Motor1GetPosition(void);
void Motor1SetPosition(float position);
PositionPIDControl_Struct gMotor1PositionPID = {                                                                    
    .isEnable = 0,                                                                              
    .sysTimer = 0,                                                                              
    .pPID.kp = 0,                                                                               
    .pPID.kd = 0,                                                                               
    .pPID.ki = 0,                                                                               
    .pPID.tar = 0,                                                                              
    .pPID.pre = 0,                                                                              
    .pPID.bais = 0,                                                                             
    .pPID.last_bias = 0,                                                                        
    .pPID.err = 0,                                                                              
    .pPID.out = 0,                                                                              
    .pPID.outMax = 100.0,//xOutMax,                                                                     
    .pPID.cycle = 0.005,//xCycle,                                                                       
    .GetPrePosition = Motor1GetPosition,                                                     
    .SetMotorSpeed = Motor1SetPosition,                                                            
};

float Motor1GetPosition(void)
{ 
    return Motor1GetAngle() -  180;
}

void Motor1SetPosition(float position)
{
    Motor1SpeedPIDConfigSetTar(position);
}



/*************************************************************
** Function name:       Motor1PositionPIDConfig_Init
** Descriptions:        位置PID初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1PositionPIDConfig_Init(void)
{
  SetPositionPIDEnable(&gMotor1PositionPID,1);
  SetPositionPIDParams(&gMotor1PositionPID,M1_POSITION_KP,M1_POSITION_KI,M1_POSITION_KD);
	Motor1PositionPIDConfigSetTar(0.0f);
}

/*************************************************************
** Function name:       Motor1SetPositionPIDConfigTar
** Descriptions:        设置目标位置
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1PositionPIDConfigSetTar(float tarPosition)
{
    SetPositionPIDTar(&gMotor1PositionPID,tarPosition);
}

/*************************************************************
** Function name:       Motor1PositionPIDConfig_Init
** Descriptions:        位置PID初始化
*************************************************************/
void Motor1PositionPIDConfig_Loop(void)
{
    PositionPIDCycle(&gMotor1PositionPID);
}
/*************************************************************
** Function name:       Motor1PositionPIDConfig_Printf
** Descriptions:        位置PID信息打印
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1PositionPIDConfig_Printf(void)
{
	PositionPIDPrintf(&gMotor1PositionPID);
}


/*************************************************************
** Function name:       PositionPIDControl
** Descriptions:        位置PID控制
** Input parameters:    pPositionPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void PositionPIDControl(PPositionPIDControl_Struct pPositionPID)
{

	float pre;
    pPositionPID->pPID.pre = pPositionPID->GetPrePosition();
	
	//旋转坐标系
	pre = pPositionPID->pPID.pre - pPositionPID->pPID.tar;
	if(pre > 180) {
		pre -= 360;
	} else if (pre < -180) {
		pre += 360;
	}
	
    pPositionPID->pPID.bais = 0 - pre;
    pPositionPID->pPID.out = pPositionPID->pPID.kp* pPositionPID->pPID.bais + pPositionPID->pPID.kd * (pPositionPID->pPID.bais - pPositionPID->pPID.last_bias) +  pPositionPID->pPID.ki * pPositionPID->pPID.err;
    pPositionPID->pPID.last_bias = pPositionPID->pPID.bais;
    pPositionPID->pPID.err += pPositionPID->pPID.bais;

	if (pPositionPID->pPID.out > pPositionPID->pPID.outMax) {
		pPositionPID->pPID.out = pPositionPID->pPID.outMax;
	} else if (pPositionPID->pPID.out < -pPositionPID->pPID.outMax) {
		pPositionPID->pPID.out = -pPositionPID->pPID.outMax;
	}
    if(pPositionPID->isEnable == 0) {
        pPositionPID->pPID.out = 0;
    }
    pPositionPID->SetMotorSpeed(pPositionPID->pPID.out);
}

/*************************************************************
** Function name:       PositionPIDCycle
** Descriptions:        位置PID循环函数
** Input parameters:    pPositionPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void PositionPIDCycle(PPositionPIDControl_Struct pPositionPID)
{
    if(POSITIONPID_TIMEOUT(pPositionPID->pPID.cycle * 1000.0f,pPositionPID->sysTimer)) {
        pPositionPID->sysTimer = POSITIONPID_GETTIME();
        PositionPIDControl(pPositionPID);
    }
}
/*************************************************************
** Function name:       SetPositionPIDParams
** Descriptions:        设置位置PID参数
** Input parameters:    pPositionPID:结构体指针
**                      kp:比例
**                      ki:积分
**                      kd:微分
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetPositionPIDParams(PPositionPIDControl_Struct pPositionPID,float kp,float ki,float kd)
{
    pPositionPID->pPID.kp = kp;
    pPositionPID->pPID.ki = ki;
    pPositionPID->pPID.kd = kd;
}
/*************************************************************
** Function name:       SetPositionPIDTar
** Descriptions:        设置目标值
** Input parameters:    pPositionPID:结构体指针
**                      tar:目标位置
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetPositionPIDTar(PPositionPIDControl_Struct pPositionPID,float tar)
{
    pPositionPID->pPID.tar = tar;
}



/*************************************************************
** Function name:       SetPositionPIDEnable
** Descriptions:        设置位置PID使能
** Input parameters:    pPositionPID:结构体指针
**                      isEnable:1: 使能0：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetPositionPIDEnable(PPositionPIDControl_Struct pPositionPID,float isEnable)
{
    pPositionPID->isEnable = isEnable;
}




/*************************************************************
** Function name:       PositionPIDPrintf
** Descriptions:        位置PID信息打印
** Input parameters:    pPositionPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void PositionPIDPrintf(PPositionPIDControl_Struct pPositionPID)
{
	printf("5:%f\r\n",pPositionPID->pPID.pre);
	printf("6:%f\r\n",pPositionPID->pPID.tar);
}










