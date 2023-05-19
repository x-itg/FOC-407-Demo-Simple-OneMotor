/***********************************************************************
* @file PositionPID
* Description:
*
**********************************************************************
* File name:      PositionPID.h
* Date:           2021-03-31
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __PositionPID_H__
#define __PositionPID_H__
#include "stdint.h"

extern volatile uint32_t gPositionPID_TimeCNT;


/******************************************************
 * 位置式PID结构体
 *****************************************************/
struct SPPID_Struct
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
typedef struct SPPID_Struct PPID_Struct;
typedef PPID_Struct *PPPID_Struct;

/******************************************************
 * 电机速度控制结构体
 *****************************************************/
struct SPositionPIDControl_Struct {
    uint8_t isEnable;   //使能
    uint32_t sysTimer;  //系统时钟
    PPID_Struct pPID;   //PID
    float (*GetPrePosition)(void);  //获取电机实际转速
    void(*SetMotorSpeed)(float speed);  //设置电机输出电流
};
typedef struct SPositionPIDControl_Struct PositionPIDControl_Struct;
typedef PositionPIDControl_Struct *PPositionPIDControl_Struct;

/*************************************************************
** Function name:       POSITION_PID_CONTROL_EXPORT
** Descriptions:        声明一个位置控制对象
** Input parameters:    x:对象名字
**                      xCycle：PID控制周期 单位秒
**                      xGetMotorPrePosition：获取实际位置
**                      xSetMotorSpeed：设置电流输出
*************************************************************/


/*************************************************************
** Function name:       MotorControl_TIMEBASE
** Descriptions:        时基,放在周期为1ms的函数里面执行
*************************************************************/
#define POSITIONPID_TIMEBASE(ms)                \
        gPositionPID_TimeCNT+= ms

/*************************************************************
** Function name:       MotorControl_GETTIME
** Descriptions:        获取起始时间
** Returned value:      (uint32_t)起始时间
*************************************************************/
#define POSITIONPID_GETTIME(void)                        \
    gPositionPID_TimeCNT

/*************************************************************
** Function name:       MotorControl_TIMEOUT
** Descriptions:        检查超时
** Input parameters:    timeOut：(uint32_t)超时时间
**                      startTime:(uint32_t)开始的时间
** Returned value:      false,未超时，true，超时
*************************************************************/
#define POSITIONPID_TIMEOUT(timeOut,startTime)                \
    ((gPositionPID_TimeCNT - startTime) >= timeOut ? 1 : 0)

void Motor1FOCConfig_Init(void);
void Motor1FOCConfig_Printf(void);
void Motor1FocControl(void);
void Motor1SetTarIDIQ(float id,float iq);
float Motor1GetAngle(void);
float Motor1TLE5012BReadAngel(void);
void PositionPIDCycle(PPositionPIDControl_Struct pPositionPID);
void SetPositionPIDParams(PPositionPIDControl_Struct pPositionPID,float kp,float ki,float kd);
void SetPositionPIDTar(PPositionPIDControl_Struct pPositionPID,float tar);
void SetPositionPIDEnable(PPositionPIDControl_Struct pPositionPID,float isEnable);
void PositionPIDPrintf(PPositionPIDControl_Struct pPositionPID);
void Motor1PositionPIDConfigSetTar(float tarPosition);
void Motor1PositionPIDConfig_Loop(void);
void Motor1PositionPIDConfig_Init(void);
#endif //__PositionPID_H__


