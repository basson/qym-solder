#include "app.hpp"

#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include "drivers/ssd1309.hpp"
#include "drivers/m24cxx.hpp"
#include "drivers/buzzer.hpp"

#include "emem.hpp"

#include "hui/buzzer.hpp"
#include "hui/button.hpp"
#include "hui/button_irq.hpp"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"
#include "gui/hierarchy.hpp"

#include "screens.hpp"

#include "screens/startup.hpp"
#include "screens/main.hpp"
#include "screens/config.hpp"
#include "screens/config/default.hpp"
#include "screens/config/hakko_t12.hpp"
#include "screens/config/solder_hand.hpp"
#include "screens/config/hair_gun.hpp"
#include "screens/config/pid_autotune.hpp"

#include "control.hpp"

qymos::driver::M24cxx m24cxx;
qymos::driver::Ssd1309 graphicalDriver;
qymos::driver::Buzzer buzzerDriver;

Emem *emem = Emem::GetInstance();

qymos::hui::Buzzer buzzer;
qymos::hui::Button buttonEncoder;
qymos::hui::Button buttonPower;
qymos::hui::ButtonIrq buttonIrq;

uint8_t buffer[1024] = {0x00};
qymos::gui::DisplayBuffer displayBuffer;

qymos::gui::Hierarchy *hierarchy = qymos::gui::Hierarchy::GetInstance();

gui::ScreenMain screenMain;
gui::ScreenConfig screenConfig;
gui::ScreenConfigDefault screenConfigDefault;
gui::ScreenConfigHakkoT12 screenConfigHakkoT12;
gui::ScreenConfigSolderHand screenConfigSolderHand;
gui::ScreenConfigHairGun screenConfigHairGun;
gui::ScreenPidAutoTune screenConfigPidAutotune;

Control control;

uint32_t lastEncoderValue = 1200 / 2;

volatile uint16_t adcValue[7];
volatile bool adcIrq = false;

volatile bool hakkoT12MoveIrq = false;
volatile uint32_t hakkoT12MoveMs = 0;
volatile bool solderHandMoveIrq = false;
volatile uint32_t solderHandMoveMs = 0;
volatile bool hairGunStandIrq = false;
volatile uint32_t hairGunStandMs = 0;

void CreateHierarchy()
{
    hierarchy->AddItem(SCREEN_MAIN, SCREEN_MAIN, &screenMain);
    hierarchy->AddItem(SCREEN_CONFIG, SCREEN_MAIN, &screenConfig);
    hierarchy->AddItem(SCREEN_CONFIG_DEFAULT, SCREEN_CONFIG, &screenConfigDefault);
    hierarchy->AddItem(SCREEN_CONFIG_HAKKO_T12, SCREEN_CONFIG, &screenConfigHakkoT12);
    hierarchy->AddItem(SCREEN_CONFIG_SOLDER_HAND, SCREEN_CONFIG, &screenConfigSolderHand);
    hierarchy->AddItem(SCREEN_CONFIG_HAIR_GUN, SCREEN_CONFIG, &screenConfigHairGun);
    hierarchy->AddItem(SCREEN_CONFIG_PID_AUTOTUNE, SCREEN_CONFIG, &screenConfigPidAutotune);
}

void Initialize()
{
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc2);

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adcValue, 7); // стартуем АЦП

    __HAL_TIM_SET_COUNTER(&htim1, lastEncoderValue);

    m24cxx.SetPort(&hi2c2);
    m24cxx.SetAddress(0xA0);

    buzzerDriver.Initialize(BUZZER_GPIO_Port, BUZZER_Pin, true);

    buzzer.Initialize(&buzzerDriver);

    emem->Initialize(&m24cxx);

    control.Initialize();

    displayBuffer.data = buffer;
    displayBuffer.size = 1024;
    displayBuffer.width = 128;
    displayBuffer.height = 64;

    graphicalDriver.SetAddress(0x78);
    graphicalDriver.SetPort(&hi2c2);
    graphicalDriver.SetResetPin(DSP_RST_GPIO_Port, DSP_RST_Pin);
    graphicalDriver.Initialize();
    CreateHierarchy();

    hierarchy->SetSelectedItem(SCREEN_MAIN);
    // hierarchy->SetSelectedItem(SCREEN_CONFIG_PID_AUTOTUNE);

    HAL_Delay(200);
    HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, GPIO_PIN_SET);



    buttonEncoder.port = ENC_SW_GPIO_Port;
    buttonEncoder.pin = ENC_SW_Pin;
    buttonEncoder.edge = true;
    buttonEncoder.longClickMs = 500;
    buttonEncoder.OnClick = ButtonEncoderOnClick;
    buttonEncoder.OnLongClick = ButtonEncoderOnLongClick;

    buttonPower.port = POWER_BTN_MCU_GPIO_Port;
    buttonPower.pin = POWER_BTN_MCU_Pin;
    buttonPower.edge = true;
    buttonPower.longClickMs = 500;
    buttonPower.OnClick = ButtonPowerOnClick;
    buttonPower.OnLongClick = ButtonPowerOnLongClick;

    
    buttonIrq.Add(&buttonEncoder);
    buttonIrq.Add(&buttonPower);
    

    // HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, GPIO_PIN_SET);

    // TIM2->CCR1 = 3999/2;
    // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void Main()
{

    if (adcIrq)
    {
        control.SetAdcNtcHakkoT12(adcValue[3]);

        control.SetAdcCoupleHairGun(adcValue[2]);
        control.SetAdcNtcHairGun(adcValue[5]);

        control.SetAdcCoupleSolderHand(adcValue[1]);
        control.SetAdcNtcSolderHand(adcValue[4]);

        // 6 - это NTC в корпусе
        // 0 - это опорное на tl431 (2.5в)

        adcIrq = false;
    }

    if (hakkoT12MoveIrq)
    {
        if (!HAL_GPIO_ReadPin(T12_MOVE_GPIO_Port, T12_MOVE_Pin) && HAL_GetTick() - hakkoT12MoveMs > 1)
            control.CallbackHakkoT12Move();
        hakkoT12MoveIrq = false;
    }
    if (solderHandMoveIrq)
    {
        if (!HAL_GPIO_ReadPin(T12_MOVE_GPIO_Port, T12_MOVE_Pin) && HAL_GetTick() - solderHandMoveMs > 1)
            control.CallbackSolderHandMove();
        solderHandMoveIrq = false;
    }
    if (hairGunStandIrq)
    {
        if (!HAL_GPIO_ReadPin(T12_MOVE_GPIO_Port, T12_MOVE_Pin) && HAL_GetTick() - hairGunStandMs > 1)
            control.CallbackHairGunStand(HAL_GPIO_ReadPin(T12_MOVE_GPIO_Port, T12_MOVE_Pin));
        hairGunStandIrq = false;
    }

    control.Process();
    buttonIrq.Process();

    if (lastEncoderValue / 4 != __HAL_TIM_GET_COUNTER(&htim1) / 4)
    {
        bool direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1);
        lastEncoderValue = __HAL_TIM_GET_COUNTER(&htim1);
        hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnEncoderDirection(direction);
        hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnEncoderValue(lastEncoderValue);
        buzzer.Beep(2);
    }

    hierarchy->GetItem(hierarchy->GetSelectedItemId())->Process();
    hierarchy->GetItem(hierarchy->GetSelectedItemId())->GetPage()->Render(&displayBuffer);

    graphicalDriver.SendFrame(&displayBuffer, 0, 0);
}

void ButtonEncoderOnClick(GPIO_TypeDef *port, uint16_t pin, bool state)
{
    hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnButtonClick(ENC_SW_Pin);
    buzzer.Beep(4);
}

void ButtonEncoderOnLongClick(GPIO_TypeDef *port, uint16_t pin, bool state)
{
    hierarchy->GetItem(hierarchy->GetSelectedItemId())->OnButtonLongClick(ENC_SW_Pin);
    buzzer.Beep(100);
}

void ButtonPowerOnClick(GPIO_TypeDef *port, uint16_t pin, bool state)
{
    if (hierarchy->GetSelectedItemId() == SCREEN_MAIN)
        hierarchy->SetSelectedItem(SCREEN_CONFIG);
    else
        hierarchy->SetSelectedItem(SCREEN_MAIN);
    buzzer.Beep(100);
}

void ButtonPowerOnLongClick(GPIO_TypeDef *port, uint16_t pin, bool state)
{
    if(HAL_GPIO_ReadPin(POWER_ON_GPIO_Port, POWER_ON_Pin) == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, GPIO_PIN_SET);
        buzzer.Beep(1000);
    }
    else
    {
        HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, GPIO_PIN_RESET);
        buzzer.Beep(200);
    }
    
}

void PinCallback(uint16_t GPIO_Pin)
{
    buttonIrq.Irq(GPIO_Pin);

    switch (GPIO_Pin)
    {
    case T12_MOVE_Pin:
        hakkoT12MoveMs = HAL_GetTick();
        hakkoT12MoveIrq = true;
        break;
    case IRON_MOVE_Pin:
        solderHandMoveMs = HAL_GetTick();
        solderHandMoveIrq = true;
        break;
    case HAIR_MOVE_Pin:
        hairGunStandMs = HAL_GetTick();
        hairGunStandIrq = true;
        break;
    default:
        break;
    }
}

void AdcCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
        adcIrq = true;
}

void SysTickInterrupt()
{
}