/***********************************************************************
* @file SpeedPID
* Description:
*
**********************************************************************
* File name:      SpeedPID.h
* Date:           2021-03-24
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __SpeedPID_H__
#define __SpeedPID_H__
#include "stdint.h"
void Motor1SpeedPIDConfigSetTar(float tarSpeed);
void Motor1SpeedPIDConfig_Loop(void);
void Motor1SpeedPIDConfig_Init(void);
void Motor1FOCConfig_Init(void);
void Motor1FOCConfig_Printf(void);
void Motor1FocControl(void);
void Motor1SetTarIDIQ(float id,float iq);
float Motor1GetAngle(void);
float Motor1TLE5012BReadAngel(void);
void Motor1SpeedPIDConfig_Loop(void);
void Motor1SpeedPIDConfig_Init(void);
extern volatile uint32_t gSpeedPID_TimeCNT;


/******************************************************
 * 增量式PID结构体
 *****************************************************/
struct SSPID_Struct
{
    float kp;           //比例
    float kd;           //微分
    float ki;           //积分
    float tar;          //目标
    float pre;          //实际
    float bais;         //目标与实际之前差值（目标-实际）
    float last_bias;    //上次差值
    float err;          //累计差值
    float out;          //输出
	float outMax;       //输出限幅
	float cycle;      //周期，单位秒
};
typedef struct SSPID_Struct SPID_Struct;
typedef SPID_Struct *PSPID_Struct;

/******************************************************
 * 电机速度控制结构体
 *****************************************************/
struct SSpeedPIDControl_Struct {
    uint8_t isEnable;   //使能
    uint32_t sysTimer;  //系统时钟
    SPID_Struct sPID;   //PID
    float (*GetPreSpeed)(void);  //获取电机实际转速
    void(*SetOutCurrent)(float current);  //设置电机输出电流
};
typedef struct SSpeedPIDControl_Struct SpeedPIDControl_Struct;
typedef SpeedPIDControl_Struct *PSpeedPIDControl_Struct;
/*************************************************************
** Function name:       SPEED_PID_CONTROL_EXPORT
** Descriptions:        声明一个速度控制对象
** Input parameters:    x:对象名字
**                      xCycle：PID控制周期
**                      xGetMotorPreSpeed：获取实际速度
**                      xSetMotorCurrent：设置电流输出
*************************************************************/
/*************************************************************
** Function name:       MotorControl_TIMEBASE
** Descriptions:        时基,放在周期为1ms的函数里面执行
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
#define SPEEDPID_TIMEBASE(ms)                \
        gSpeedPID_TimeCNT+= ms

/*************************************************************
** Function name:       MotorControl_GETTIME
** Descriptions:        获取起始时间
** Input parameters:    None
** Output parameters:   None
** Returned value:      (uint32_t)起始时间
*************************************************************/
#define SPEEDPID_GETTIME(void)                        \
    gSpeedPID_TimeCNT

/*************************************************************
** Function name:       MotorControl_TIMEOUT
** Descriptions:        检查超时
** Input parameters:    timeOut：(uint32_t)超时时间
**                      startTime:(uint32_t)开始的时间
** Output parameters:   None
** Returned value:      false,未超时，true，超时
*************************************************************/
#define SPEEDPID_TIMEOUT(timeOut,startTime)                \
    ((gSpeedPID_TimeCNT - startTime) >= timeOut ? 1 : 0)



void SpeedPIDCycle(PSpeedPIDControl_Struct pSpeedPID);
void SetSpeedPIDParams(PSpeedPIDControl_Struct pSpeedPID,float kp,float ki,float kd);
void SetSpeedPIDTar(PSpeedPIDControl_Struct pSpeedPID,float tar);
void SetSpeedPIDEnable(PSpeedPIDControl_Struct pSpeedPID,float isEnable);
void SpeedPIDPrintf(PSpeedPIDControl_Struct pSpeedPID);
#endif //__SpeedPID_H__

















