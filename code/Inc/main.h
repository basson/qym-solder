/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
void SysTick_interrupt(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define REF_Pin GPIO_PIN_0
#define REF_GPIO_Port GPIOA
#define SI_T12_Pin GPIO_PIN_1
#define SI_T12_GPIO_Port GPIOA
#define SI_IRON_Pin GPIO_PIN_2
#define SI_IRON_GPIO_Port GPIOA
#define SI_HAIR_Pin GPIO_PIN_3
#define SI_HAIR_GPIO_Port GPIOA
#define SI_T12_NTC_Pin GPIO_PIN_4
#define SI_T12_NTC_GPIO_Port GPIOA
#define SI_IRON_NTC_Pin GPIO_PIN_5
#define SI_IRON_NTC_GPIO_Port GPIOA
#define SI_HAIR_NTC_Pin GPIO_PIN_6
#define SI_HAIR_NTC_GPIO_Port GPIOA
#define SI_COOL_Pin GPIO_PIN_7
#define SI_COOL_GPIO_Port GPIOA
#define DSP_BCLK_Pin GPIO_PIN_1
#define DSP_BCLK_GPIO_Port GPIOB
#define DSP_RST_Pin GPIO_PIN_2
#define DSP_RST_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_10
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_11
#define SDA_GPIO_Port GPIOB
#define HAIR_MOVE_Pin GPIO_PIN_12
#define HAIR_MOVE_GPIO_Port GPIOB
#define HAIR_MOVE_EXTI_IRQn EXTI15_10_IRQn
#define IRON_MOVE_Pin GPIO_PIN_13
#define IRON_MOVE_GPIO_Port GPIOB
#define IRON_MOVE_EXTI_IRQn EXTI15_10_IRQn
#define T12_MOVE_Pin GPIO_PIN_14
#define T12_MOVE_GPIO_Port GPIOB
#define T12_MOVE_EXTI_IRQn EXTI15_10_IRQn
#define ENC_SW_Pin GPIO_PIN_15
#define ENC_SW_GPIO_Port GPIOB
#define ENC_SW_EXTI_IRQn EXTI15_10_IRQn
#define ENC_B_Pin GPIO_PIN_8
#define ENC_B_GPIO_Port GPIOA
#define ENC_A_Pin GPIO_PIN_9
#define ENC_A_GPIO_Port GPIOA
#define POWER_BTN_MCU_Pin GPIO_PIN_10
#define POWER_BTN_MCU_GPIO_Port GPIOA
#define POWER_BTN_MCU_EXTI_IRQn EXTI15_10_IRQn
#define PWM_COOL_Pin GPIO_PIN_15
#define PWM_COOL_GPIO_Port GPIOA
#define POWER_ON_Pin GPIO_PIN_3
#define POWER_ON_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_4
#define BUZZER_GPIO_Port GPIOB
#define PWM_HAIR_Pin GPIO_PIN_6
#define PWM_HAIR_GPIO_Port GPIOB
#define PWM_HFAN_Pin GPIO_PIN_7
#define PWM_HFAN_GPIO_Port GPIOB
#define PWM_D907_Pin GPIO_PIN_8
#define PWM_D907_GPIO_Port GPIOB
#define PWM_T12_Pin GPIO_PIN_9
#define PWM_T12_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
