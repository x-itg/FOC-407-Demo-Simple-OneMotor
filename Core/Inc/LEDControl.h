/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               LEDControl.h
** Latest modified date:    2020-07-20
** Latest version:          V1.0.0
** Description:             LED控制
**
**------------------------------------------------------------
** Created by:              liuxiang
** Created date:            2020-07-20
** Version:                 V1.0.0
** Descriptions:            LED控制
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#ifndef LEDControl_h
#define LEDControl_h
#include "stdint.h"
#include "stdint.h"
#include "main.h"
void LEDGPIOInit(void);
void SetLedLeave(uint8_t leave);
enum {
    LEDConfig_OFF = 0,
    LEDConfig_ON,
    LEDConfig_Toggle,
};


void LEDConfigSetSysLedStatus(uint8_t status, float cycle);
void LEDConfig_Init(void);
void LEDConfig_Loop(void);
enum {
    LEDState_OFF = 0,
    LEDState_ON,
    LEDState_Toggle,
};

struct SLEDControl_Struct {
    uint8_t state;//LED运行状态 0:LED常灭 1:LED常亮 2:闪烁
    uint8_t onoff;//当前LED状态
    float cycle;//闪烁周期(单位ms)
    uint8_t onLeave;//点亮电平
    uint32_t startTime;
    void(*SetLEDLeave)(uint8_t leave);//设置LED引脚电平函数
};
typedef struct SLEDControl_Struct LEDControl_Struct;
typedef LEDControl_Struct* PLEDControl_Struct;

/*************************************************************
** Function name:       LED_EXPORT
** Descriptions:        x:对象名字
**                      xonLeave:LED点亮电平
**                      xSetLEDLeave:设置LED引脚电平函数指针
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/

extern volatile uint32_t gLED_TimeCNT;

/*************************************************************
** Function name:       SysPower_TIMEBASE
** Descriptions:        时基,放在周期为1ms的函数里面执行
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
#define LED_TIMEBASE(ms)                \
        gLED_TimeCNT+= ms

/*************************************************************
** Function name:       SysPower_GETTIME
** Descriptions:        获取起始时间
** Input parameters:    None
** Output parameters:   None
** Returned value:      (uint32_t)起始时间
*************************************************************/
#define LED_GETTIME(void)                        \
    gLED_TimeCNT

/*************************************************************
** Function name:       SysPower_TIMEOUT
** Descriptions:        检查超时
** Input parameters:    timeOut：(uint32_t)超时时间
**                      startTime:(uint32_t)开始的时间
** Output parameters:   None
** Returned value:      false,未超时，true，超时
*************************************************************/
#define LED_TIMEOUT(timeOut,startTime)                \
    ((gLED_TimeCNT - startTime) >= timeOut ? 1 : 0)


void SetLedStatus(PLEDControl_Struct gLED,uint8_t status,float cycle);
void LEDRunCycle(PLEDControl_Struct gLED);
#endif /* LEDControl_h */
