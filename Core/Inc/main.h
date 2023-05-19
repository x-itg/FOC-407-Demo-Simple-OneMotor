/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M2_ADC_U_Pin GPIO_PIN_0
#define M2_ADC_U_GPIO_Port GPIOC
#define M2_ADC_V_Pin GPIO_PIN_1
#define M2_ADC_V_GPIO_Port GPIOC
#define M2_ADC_W_Pin GPIO_PIN_2
#define M2_ADC_W_GPIO_Port GPIOC
#define M1_Encoder_A_Pin GPIO_PIN_0
#define M1_Encoder_A_GPIO_Port GPIOA
#define M1_Encoder_B_Pin GPIO_PIN_1
#define M1_Encoder_B_GPIO_Port GPIOA
#define M1_Encoder_Z_Pin GPIO_PIN_2
#define M1_Encoder_Z_GPIO_Port GPIOA
#define M1_Encoder_Z_EXTI_IRQn EXTI2_IRQn
#define M1_SPI_CS_Pin GPIO_PIN_4
#define M1_SPI_CS_GPIO_Port GPIOA
#define M1_SPI_SCK_Pin GPIO_PIN_5
#define M1_SPI_SCK_GPIO_Port GPIOA
#define M1_SPI_MISO_Pin GPIO_PIN_6
#define M1_SPI_MISO_GPIO_Port GPIOA
#define M1_SPI_MOSI_Pin GPIO_PIN_7
#define M1_SPI_MOSI_GPIO_Port GPIOA
#define M1_ADC_U_Pin GPIO_PIN_4
#define M1_ADC_U_GPIO_Port GPIOC
#define M1_ADC_V_Pin GPIO_PIN_5
#define M1_ADC_V_GPIO_Port GPIOC
#define M1_ADC_W_Pin GPIO_PIN_0
#define M1_ADC_W_GPIO_Port GPIOB
#define M1_Enable_Pin GPIO_PIN_8
#define M1_Enable_GPIO_Port GPIOE
#define M1_PWM_U_Pin GPIO_PIN_9
#define M1_PWM_U_GPIO_Port GPIOE
#define M1_PWM_V_Pin GPIO_PIN_11
#define M1_PWM_V_GPIO_Port GPIOE
#define M1_PWM_W_Pin GPIO_PIN_13
#define M1_PWM_W_GPIO_Port GPIOE
#define M2_SPI_CS_Pin GPIO_PIN_12
#define M2_SPI_CS_GPIO_Port GPIOB
#define M2_SPI_CLK_Pin GPIO_PIN_13
#define M2_SPI_CLK_GPIO_Port GPIOB
#define M2_SPI_MISO_Pin GPIO_PIN_14
#define M2_SPI_MISO_GPIO_Port GPIOB
#define M2_SPI_MOSI_Pin GPIO_PIN_15
#define M2_SPI_MOSI_GPIO_Port GPIOB
#define M2_Encoder_Z_Pin GPIO_PIN_11
#define M2_Encoder_Z_GPIO_Port GPIOD
#define M2_Encoder_Z_EXTI_IRQn EXTI15_10_IRQn
#define M2_Encoder_A_Pin GPIO_PIN_12
#define M2_Encoder_A_GPIO_Port GPIOD
#define M2_Encoder_B_Pin GPIO_PIN_13
#define M2_Encoder_B_GPIO_Port GPIOD
#define M2_PWM_U_Pin GPIO_PIN_6
#define M2_PWM_U_GPIO_Port GPIOC
#define M2_PWM_V_Pin GPIO_PIN_7
#define M2_PWM_V_GPIO_Port GPIOC
#define M2_PWM_W_Pin GPIO_PIN_8
#define M2_PWM_W_GPIO_Port GPIOC
#define M2_Enable_Pin GPIO_PIN_9
#define M2_Enable_GPIO_Port GPIOC
#define CAN_ID_1_Pin GPIO_PIN_0
#define CAN_ID_1_GPIO_Port GPIOD
#define CAN_ID_2_Pin GPIO_PIN_1
#define CAN_ID_2_GPIO_Port GPIOD
#define CAN_ID_3_Pin GPIO_PIN_2
#define CAN_ID_3_GPIO_Port GPIOD
#define CAN_ID_4_Pin GPIO_PIN_3
#define CAN_ID_4_GPIO_Port GPIOD
#define SYS_LED_Pin GPIO_PIN_4
#define SYS_LED_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
