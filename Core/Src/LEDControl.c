#include "LEDControl.h"
void SetLedLeave(uint8_t leave)
{
    HAL_GPIO_WritePin(SYS_LED_GPIO_Port, SYS_LED_Pin, (GPIO_PinState)leave);
}
LEDControl_Struct gSysLed = {
    .state = LEDState_OFF,
    .onoff = 0,
    .cycle = 0.0,
    .onLeave = 1, // xonLeave:LED点亮电平
    .startTime = 0,
    .SetLEDLeave = SetLedLeave, // xSetLEDLeave:设置LED引脚电平函数指针
};

volatile uint32_t gLED_TimeCNT;

/*************************************************************
** Function name:       LEDON
** Descriptions:        LED常亮
** Input parameters:    gLED:SLEDControl_Struct结构体指针
*************************************************************/
void SetLEDON(PLEDControl_Struct gLED)
{
    gLED->state = LEDState_ON;
    gLED->SetLEDLeave(gLED->onLeave);
}
/*************************************************************
** Function name:       LEDFF
** Descriptions:        LED常灭
** Input parameters:    gLED:SLEDControl_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetLEDOFF(PLEDControl_Struct gLED)
{
    gLED->state = LEDState_OFF;
    gLED->SetLEDLeave(!(gLED->onLeave));
}
/*************************************************************
** Function name:       LEDToggle
** Descriptions:        LED闪烁
** Input parameters:    gLED:SLEDControl_Struct结构体指针
*************************************************************/
void LEDToggle(PLEDControl_Struct gLED)
{
    gLED->onoff = !gLED->onoff;
    gLED->SetLEDLeave(gLED->onoff);
}
/*************************************************************
** Function name:       LEdRunCycle
** Descriptions:        LED周期执行函数
** Input parameters:    gLED:SLEDControl_Struct结构体指针
*************************************************************/
void LEDRunCycle(PLEDControl_Struct gLED)
{
    if (LED_TIMEOUT(gLED->cycle * 1000, gLED->startTime))
    {
        gLED->startTime = LED_GETTIME();
        if (gLED->state == LEDState_Toggle)
        {
            LEDToggle(gLED);
        }
    }
}
/*************************************************************
** Function name:       LEDFlashing
** Descriptions:        LED闪烁
** Input parameters:    gLED:SLEDControl_Struct结构体指针
**                      cycle:闪烁周期(单位ms)
*************************************************************/
void SetLEDFlashing(PLEDControl_Struct gLED, float cycle)
{
    gLED->state = LEDState_Toggle;
    gLED->cycle = cycle;
}

/*************************************************************
** Function name:       SetLedStatus
** Descriptions:        设置LEDz状态
** Input parameters:    gLED:SLEDControl_Struct结构体指针
**                      status:LED状态
**                      cycle:闪烁周期(单位ms)
*************************************************************/
void SetLedStatus(PLEDControl_Struct gLED, uint8_t status, float cycle)
{
    switch (status)
    {
    case LEDState_OFF:
        SetLEDOFF(gLED);
        break;
    case LEDState_ON:
        SetLEDON(gLED);
        break;
    case LEDState_Toggle:
        SetLEDFlashing(gLED, cycle);
        break;
    }
}

/*************************************************************
** Function name:       LEDConfigSetYellowLedStatus
** Descriptions:        设置绿色LED状态
** Input parameters:    status：LED状态 0：熄灭 1：常亮 2：闪烁
**                      cycle：周期单位秒
*************************************************************/
void LEDConfigSetSysLedStatus(uint8_t status, float cycle)
{
    SetLedStatus(&gSysLed, status, cycle);
}
/*************************************************************
** Function name:       LEDConfig_Init
** Descriptions:        led初始化
*************************************************************/
void LEDConfig_Init(void)
{
    LEDConfigSetSysLedStatus(LEDConfig_Toggle, 1);
}
/*************************************************************
** Function name:       LEDConfig_Loop
** Descriptions:        led周期循环函数
*************************************************************/
void LEDConfig_Loop(void)
{
    LEDRunCycle(&gSysLed);
}
