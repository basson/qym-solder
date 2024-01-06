#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32f1xx_hal.h"

#include "main.h"

extern void Initialize();
extern void Main();
extern void PinCallback(uint16_t GPIO_Pin);
extern void TimerInterrupt();
extern void SysTickInterrupt();
extern void DmaInterrupt();
extern void AdcCallback(ADC_HandleTypeDef *hadc);
extern void Error();