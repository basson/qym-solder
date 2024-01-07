#include "app.hpp"

#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include "ssd1309.hpp"

#include "types.hpp"
#include "iscreen.hpp"
#include "hierarchy.hpp"

#include "screens.hpp"

#include "screens/startup.hpp"
#include "screens/main.hpp"
#include "screens/config.hpp"
#include "screens/config/default.hpp"
#include "screens/config/hakko_t12.hpp"
#include "screens/config/solder_hand.hpp"
#include "screens/config/hair_gun.hpp"

qymos::driver::Ssd1309 graphicalDriver;

uint8_t buffer[1024] = {
    0x00,
};
qymos::gui::DisplayBuffer displayBuffer;

qymos::gui::Hierarchy *hierarchy = qymos::gui::Hierarchy::GetInstance();

gui::ScreenMain screenMain;
gui::ScreenConfig screenConfig;
gui::ScreenConfigDefault screenConfigDefault;
gui::ScreenConfigHakkoT12 screenConfigHakkoT12;
gui::ScreenConfigSolderHand screenConfigSolderHand;
gui::ScreenConfigHairGun screenConfigHairGun;

volatile bool btnEncoderIrq = false;
volatile uint32_t btnEncoderPushedMs = 0;

volatile bool btnPowerIrq = false;
volatile uint32_t btnPowerPushedMs = 0;

uint32_t lastEncoderValue = 1200 / 2;

void CreateHierarchy()
{
    hierarchy->AddItem(SCREEN_MAIN, SCREEN_MAIN, &screenMain);
    hierarchy->AddItem(SCREEN_CONFIG, SCREEN_MAIN, &screenConfig);
    hierarchy->AddItem(SCREEN_CONFIG_DEFAULT, SCREEN_CONFIG, &screenConfigDefault);
    hierarchy->AddItem(SCREEN_CONFIG_HAKKO_T12, SCREEN_CONFIG, &screenConfigHakkoT12);
    hierarchy->AddItem(SCREEN_CONFIG_SOLDER_HAND, SCREEN_CONFIG, &screenConfigSolderHand);
    hierarchy->AddItem(SCREEN_CONFIG_HAIR_GUN, SCREEN_CONFIG, &screenConfigHairGun);
}

void Initialize()
{

    displayBuffer.data = buffer;
    displayBuffer.size = 1024;
    displayBuffer.width = 128;
    displayBuffer.height = 64;

    graphicalDriver.SetAddress(0x78);
    graphicalDriver.SetPort(&hi2c2);
    graphicalDriver.SetResetPin(DSP_RST_GPIO_Port, DSP_RST_Pin);

    CreateHierarchy();

    hierarchy->SetSelectedItem(SCREEN_MAIN);
}

void Main()
{

    if (btnEncoderIrq)
    {
        if (HAL_GPIO_ReadPin(ENC_SW_GPIO_Port, ENC_SW_Pin))
        {
            if (HAL_GetTick() - btnEncoderPushedMs <= 500)
                hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnButtonClick(ENC_SW_Pin);
            else
                hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnButtonLongClick(ENC_SW_Pin);
            btnEncoderIrq = false;
        }
    }
    if (btnPowerIrq)
    {
        if (HAL_GPIO_ReadPin(POWER_BTN_MCU_GPIO_Port, POWER_BTN_MCU_Pin))
        {
            if (HAL_GetTick() - btnPowerPushedMs >= 500)
            {
                if (hierarchy->GetSelectedItemId() == SCREEN_MAIN)
                    hierarchy->SetSelectedItem(SCREEN_CONFIG);
                else if (hierarchy->GetSelectedItemId() == SCREEN_CONFIG)
                    hierarchy->SetSelectedItem(SCREEN_MAIN);
            }
            btnPowerIrq = false;
        }
    }

    if (lastEncoderValue / 4 != __HAL_TIM_GET_COUNTER(&htim1) / 4)
	{
		bool direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1);
		lastEncoderValue = __HAL_TIM_GET_COUNTER(&htim1);
		hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnEncoderDirection(direction);
		hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnEncoderValue(lastEncoderValue);
	}

    
    hierarchy->GetItem(hierarchy->GetSelectedItemId())->Process();
    hierarchy->GetItem(hierarchy->GetSelectedItemId())->GetPage()->Render(&displayBuffer);
    graphicalDriver.SendFrame(&displayBuffer, 0, 0);
}

void PinCallback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == ENC_SW_Pin)
    {
        btnEncoderPushedMs = HAL_GetTick();
        btnEncoderIrq = true;
    }
    if (GPIO_Pin == POWER_BTN_MCU_Pin)
    {
        btnPowerPushedMs = HAL_GetTick();
        btnPowerIrq = true;
    }
}

void AdcCallback(ADC_HandleTypeDef *hadc)
{
}

void SysTickInterrupt()
{
}