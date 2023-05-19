#include "Motor1TIM2Encoder.h"
#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"
#include "main.h"

#define CNTZERO 10000
#define ENCODERPLUSE 4096

extern TIM_HandleTypeDef htim2;

struct SMotor1Timer2Encoder
{
    int32_t cnt; // 编码器脉冲数 0-ENCODERPLUSE
    float angle; // 编码器角度 0-360°
};
typedef struct SMotor1Timer2Encoder Motor1Timer2Encoder; /* TimEnc 类型 */
typedef Motor1Timer2Encoder *PMotor1Timer2Encoder;       /* PTimEnc 指针类型 */

Motor1Timer2Encoder gMotor1Timer2Encoder = {
    .cnt = 0,
    .angle = 0,
};

/*************************************************************
** Function name:       Motor1TIM2EncoderInit
** Descriptions:        初始化定时器2
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void Motor1TIM2EncoderInit(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    __HAL_TIM_SET_COUNTER(&htim2, CNTZERO);
    gMotor1Timer2Encoder.angle = 0.0;
    gMotor1Timer2Encoder.cnt = 0;
}
/*************************************************************
** Function name:       Motor1TIM2EncoderReset
** Descriptions:        复位定时器2
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void Motor1TIM2EncoderReset(void)
{
    __HAL_TIM_SET_COUNTER(&htim2, CNTZERO);
    gMotor1Timer2Encoder.angle = 0.0;
    gMotor1Timer2Encoder.cnt = 0;
}
/*************************************************************
** Function name:       Motor1TIM2EncoderGetCnt
** Descriptions:        获取定时器2编码器模式CNT的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      Timer2->CNT的值
*************************************************************/
int32_t Motor1TIM2EncoderGetCnt(void)
{
    gMotor1Timer2Encoder.cnt += __HAL_TIM_GET_COUNTER(&htim2) - CNTZERO;
    __HAL_TIM_SET_COUNTER(&htim2, CNTZERO);
    if (gMotor1Timer2Encoder.cnt < 0)
    {
        gMotor1Timer2Encoder.cnt += ENCODERPLUSE;
    }
    gMotor1Timer2Encoder.cnt = gMotor1Timer2Encoder.cnt % ENCODERPLUSE;
    return gMotor1Timer2Encoder.cnt;
}
/*************************************************************
** Function name:       Motor1TIM2EncoderSetCnt
** Descriptions:        设置Timer2Cnt的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1TIM2EncoderSetCnt(int32_t cnt)
{
    gMotor1Timer2Encoder.cnt = cnt;
}
/*************************************************************
** Function name:       Motor1TIM2EncoderGetAngle
** Descriptions:        获取编码器角度
** Input parameters:    None
** Output parameters:   None
** Returned value:      编码器角度
*************************************************************/
float Motor1TIM2EncoderGetAngle(void)
{
    gMotor1Timer2Encoder.angle = (float)Motor1TIM2EncoderGetCnt() / (float)ENCODERPLUSE * 360.0f;
    if (gMotor1Timer2Encoder.angle < 0)
    {
        gMotor1Timer2Encoder.angle = gMotor1Timer2Encoder.angle + 360.0f;
    }
    return gMotor1Timer2Encoder.angle;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// 以下外部零点Z信号外部中断
struct SMotor1EncoderCalibration_Struct
{
    /* data */
    int calibrationValue;    // 校准值
    uint8_t calibrationFlag; // 第一次值
};

struct SMotor1EncoderCalibration_Struct gMotor1EncoderCal = {0};

/*************************************************************
** Function name:       Motor1EncoderZ_Init
** Descriptions:        电机1编码器中断中断初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1EncoderZ_Init(void)
{
    gMotor1EncoderCal.calibrationValue = 0;
    gMotor1EncoderCal.calibrationFlag = 0;
}
/*************************************************************
** Function name:       Motor1EncoderZ_DeInit
** Descriptions:        电机1编码器中断反初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1EncoderZ_DeInit(void)
{
    gMotor1EncoderCal.calibrationValue = 0;
    gMotor1EncoderCal.calibrationFlag = 0;
}

/*************************************************************
** Function name:       Motor1EncoderZEXITCallback
** Descriptions:        电机1编码器中断回调函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1EncoderZEXITCallback(void)
{
    if (gMotor1EncoderCal.calibrationFlag == 0)
    {
        gMotor1EncoderCal.calibrationValue = Motor1TIM2EncoderGetCnt();
        gMotor1EncoderCal.calibrationFlag = 1;
    }
    else
    {
        Motor1TIM2EncoderSetCnt(gMotor1EncoderCal.calibrationValue);
    }
    // printf("1:%d\r\n",gMotor1EncoderCal.calibrationValue);
}
