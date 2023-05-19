#include "Motor1ADC1PWM.h"
#include "main.h"

#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

// 一介低通滤波系数
#define FILTER_KP 0.9f

extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;

void Motor1SetEnable(uint8_t isEnable)
{
    HAL_GPIO_WritePin(M1_Enable_GPIO_Port, M1_Enable_Pin, (GPIO_PinState)isEnable);
}

struct SMotor1ADC1_Struct
{
    uint32_t adDmaValue[3]; // DMA原始数据
    int adValue[3];         // 电流实际AD值
    int lastAdValue[3];     // 上次电流实际AD值
};
struct SMotor1ADC1_Struct gMotor1ADC1 = {0};
/*************************************************************
** Function name:       Motor1ADC1StartOnce
** Descriptions:        Motor1ADC开始一次DMA转换
*************************************************************/
void Motor1ADC1StartOnce(void)
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)gMotor1ADC1.adDmaValue, 3);
}

/*************************************************************
** Function name:       Motor1ADCValueStorage
** Descriptions:        Motor1存储DMA获取到的数据
*************************************************************/
void Motor1ADC1ValueStorage(void)
{
    gMotor1ADC1.adValue[0] = gMotor1ADC1.adDmaValue[0] - 2048;
    gMotor1ADC1.adValue[1] = gMotor1ADC1.adDmaValue[1] - 2048;
    gMotor1ADC1.adValue[2] = gMotor1ADC1.adDmaValue[2] - 2048;
}
/*************************************************************
** Function name:       GetMotor1ADC1PhaseXValue
** Descriptions:        获取 Motor13相电流
** Input parameters:    Phase：1：A相 2：B相 3：C相
*************************************************************/
int32_t GetMotor1ADC1PhaseXValue(uint8_t Phase)
{
    if (Phase >= 3)
    {
        return 0;
    }
    int32_t value;
    value = (int32_t)(FILTER_KP * (float)gMotor1ADC1.adValue[Phase] + (1 - FILTER_KP) * (float)gMotor1ADC1.lastAdValue[Phase]);
    gMotor1ADC1.lastAdValue[Phase] = value;
    return value;
}

/*************************************************************
** Function name:       Motor1TIM1_Init
** Descriptions:        电机1定时器初始化
*************************************************************/
void Motor1TIM1_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

    SetMotor1ChannelAHighLeaveTime_us(0);
    SetMotor1ChannelBHighLeaveTime_us(0);
    SetMotor1ChannelCHighLeaveTime_us(0);
}

/*************************************************************
** Function name:       SetMotor1ChannelAHighLeaveTime_us
** Descriptions:        设置电机1通道A高电平时间（中央对齐模式二）
** Input parameters:    time：高电平时间 单位us 范围 0-100
*************************************************************/
void SetMotor1ChannelAHighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0)
    {
        time = 0;
    }
    if (time > 100)
    {
        time = 100;
    }
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccr);
}
/*************************************************************
** Function name:       SetMotor1ChannelBHighLeaveTime_us
** Descriptions:        设置电机1通道B高电平时间（中央对齐模式二）
** Input parameters:    time：高电平时间 单位us 范围 0-100
*************************************************************/
void SetMotor1ChannelBHighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0)
    {
        time = 0;
    }
    if (time > 100)
    {
        time = 100;
    }
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, ccr);
}
/*************************************************************
** Function name:       SetMotor1ChannelCHighLeaveTime_us
** Descriptions:        设置电机1通道C高电平时间（中央对齐模式二）
** Input parameters:    time：高电平时间 单位us 范围 0-100
*************************************************************/
void SetMotor1ChannelCHighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0)
    {
        time = 0;
    }
    if (time > 100)
    {
        time = 100;
    }
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, ccr);
}
