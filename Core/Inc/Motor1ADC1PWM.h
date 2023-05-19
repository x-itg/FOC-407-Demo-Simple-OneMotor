/***********************************************************************
* @file Motor1ADC1
* Description:
*
**********************************************************************
* File name:      Motor1ADC1.h
* Date:           2021-05-16
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __Motor1ADC1PWM_H__
#define __Motor1ADC1PWM_H__
#include "stdint.h"
void Motor1SetEnable(uint8_t isEnable);
void Motor1ADC1StartOnce(void);
void Motor1ADC1ValueStorage(void);
int32_t GetMotor1ADC1PhaseXValue(uint8_t Phase);
void Motor1TIM1_Init(void);
void SetMotor1ChannelAHighLeaveTime_us(float time);
void SetMotor1ChannelBHighLeaveTime_us(float time);
void SetMotor1ChannelCHighLeaveTime_us(float time);
#endif //__Motor1ADC1_H__

