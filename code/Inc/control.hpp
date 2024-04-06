#pragma once

#include "stdint.h"
#include "stm32f1xx_hal.h"

#include "tim.h"
#include "adc.h"

#include "pid.hpp"
#include "ema.hpp"
#include "median.hpp"
#include "soft_timer.hpp"

#include "emem.hpp"

class Control
{
public:
    enum State
    {
        CONTROL_STATE_OFF = 0,
        CONTROL_STATE_ON = 1,
        CONTROL_STATE_SLEEP,
        CONTROL_STATE_COOLING,
        
        CONTROL_STATE_MAX,
    };

    Control();
    void Initialize();

    void Process();

    void CallbackHakkoT12Move();
    void CallbackSolderHandMove();
    void CallbackHairGunStand(bool direction);

    void SetAdcNtcHakkoT12(uint16_t value);
    void SetAdcCoupleSolderHand(uint16_t value);
    void SetAdcNtcSolderHand(uint16_t value);
    void SetAdcCoupleHairGun(uint16_t value);
    void SetAdcNtcHairGun(uint16_t value);

    static uint16_t GetCurrentTempHakkoT12();
    static uint16_t GetCurrentTempSolderHand();
    static uint16_t GetCurrentTempHairGun();

    static State StateHakkoT12(State state = CONTROL_STATE_MAX);
    static State StateSolderHand(State state = CONTROL_STATE_MAX);
    static State StateHairGun(State state = CONTROL_STATE_MAX);

    

private:
    static uint16_t _adcCoupleHacckoT12;
    static uint16_t _adcNtcHacckoT12;

    static uint16_t _adcCoupleSolderHand;
    static uint16_t _adcNtcSolderHand;

    static uint16_t _adcCoupleHairGun;
    static uint16_t _adcNtcHairGun;

    static uint16_t _currentTempHakkoT12;
    static uint16_t _currentTempSolderHand;
    static uint16_t _currentTempHairGun;


    static State _stateHakkoT12;
    static State _stateSolderHand;
    static State _stateHairGun;

    struct Trigger {
        bool hakkoT12 = false;
        bool solderHand = false;
        bool hairGun = false;
    };

    static Trigger _trigger;

    Emem *_emem;

    qymos::common::PidData _pidDataHakkoT12;
    qymos::common::PidData _pidDataSolderHand;
    qymos::common::PidData _pidDataHairGun;

    qymos::common::filter::Ema _emaHakkoT12;
    qymos::common::filter::Ema _emaSolderHand;
    qymos::common::filter::Ema _emaHairGun;

    qymos::common::filter::Median _medianHakkoT12;
    qymos::common::filter::Median _medianSolderHand;
    qymos::common::filter::Median _medianHairGun;

    qymos::common::time::SoftTimer _timerHakkoT12;
    qymos::common::time::SoftTimer _timerSolderHand;

    void ProcessHakktoT12();
    void ProcessSolderHand();
    void ProcessHairGun();

    void GetAdcCoupleHakkoT12();
};
