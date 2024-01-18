#include "control.hpp"

uint16_t Control::_adcCoupleHacckoT12 = 0;
uint16_t Control::_adcNtcHacckoT12 = 0;

uint16_t Control::_adcCoupleSolderHand = 0;
uint16_t Control::_adcNtcSolderHand = 0;

uint16_t Control::_adcCoupleHairGun = 0;
uint16_t Control::_adcNtcHairGun = 0;

uint16_t Control::_currentTempHakkoT12 = 0;
uint16_t Control::_currentTempSolderHand = 0;
uint16_t Control::_currentTempHairGun = 0;

Control::State Control::_stateHakkoT12 = CONTROL_STATE_OFF;
Control::State Control::_stateSolderHand = CONTROL_STATE_OFF;
Control::State Control::_stateHairGun = CONTROL_STATE_OFF;

Control::Control()
{

}
void Control::Initialize()
{
    _emem = Emem::GetInstance();

    _emaHakkoT12.SetK(0.06);
    _emaSolderHand.SetK(0.06);
    _emaHairGun.SetK(0.06);

    _timerHakkoT12.SetRepeat(true);
    _timerSolderHand.SetRepeat(true);
    // _timerHairGun.SetRepeat(true);

    _pidDataHakkoT12.OutputMin = 0;
    _pidDataHakkoT12.OutputMax = 3999;
    _pidDataHakkoT12.SampleTimeMs = 4;

    _pidDataSolderHand.OutputMin = 0;
    _pidDataSolderHand.OutputMax = 3999;
    _pidDataSolderHand.SampleTimeMs = 4;

    _pidDataHairGun.OutputMin = 0;
    _pidDataHairGun.OutputMax = 3999;
    _pidDataHairGun.SampleTimeMs = 4;
}

void Control::Process()
{
    ProcessHakktoT12();
    ProcessSolderHand();
    ProcessHairGun();
}

void Control::SetAdcNtcHakkoT12(uint16_t value)
{
    _adcNtcHacckoT12 = value;
}
void Control::SetAdcCoupleSolderHand(uint16_t value)
{
    _adcCoupleSolderHand = value;
}
void Control::SetAdcNtcSolderHand(uint16_t value)
{
    _adcNtcSolderHand = value;
}
void Control::SetAdcCoupleHairGun(uint16_t value)
{
    _adcCoupleHairGun = value;
}
void Control::SetAdcNtcHairGun(uint16_t value)
{
    _adcNtcHairGun = value;
}

uint16_t Control::GetCurrentTempHakkoT12()
{
    return _currentTempHakkoT12;
}
uint16_t Control::GetCurrentTempSolderHand()
{
    return _currentTempSolderHand;
}
uint16_t Control::GetCurrentTempHairGun()
{
    return _currentTempHairGun;
}

Control::State Control::StateHakkoT12(Control::State state)
{
    if (state > 1)
        return _stateHakkoT12;
    _stateHakkoT12 = state;
    return _stateHakkoT12;
}
Control::State Control::StateSolderHand(Control::State state)
{
    if (state > 1)
        return _stateSolderHand;
    _stateSolderHand = state;
    return _stateSolderHand;
}
Control::State Control::StateHairGun(Control::State state)
{
    if (state > 1)
        return _stateHairGun;
    _stateHairGun = state;
    return _stateHairGun;
}

void Control::ProcessHakktoT12()
{
    uint16_t _filterAdc = 0;
    GetAdcCoupleHakkoT12();

    _medianHakkoT12.Set(_adcCoupleHacckoT12);
    _emaHakkoT12.Set(_medianHakkoT12.Get());
    _filterAdc = _emaHakkoT12.Get();
    _currentTempHakkoT12 = 0.1320134f * _filterAdc + 21.43212233f;

    if (_stateHakkoT12 == CONTROL_STATE_OFF && !_trigger.hakkoT12)
        return;

    _timerHakkoT12.Process();

    if (_stateHakkoT12 == CONTROL_STATE_SLEEP)
        _pidDataHakkoT12.Point = _emem->Param().t12TempSleep;
    else
        _pidDataHakkoT12.Point = _emem->Param().t12SetTemp;

    _pidDataHakkoT12.Kp = _emem->Param().ironKp;
    _pidDataHakkoT12.Ki = _emem->Param().ironKi;
    _pidDataHakkoT12.Kd = _emem->Param().ironKd;
    

    qymos::common::Pid::SetData(&_pidDataHakkoT12);
    qymos::common::Pid::Process();

    TIM4->CCR4 = _pidDataHakkoT12.Output;

    if (_trigger.hakkoT12)
    {
        if (_stateHakkoT12 == CONTROL_STATE_ON)
            HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
        else
        {
            _stateHakkoT12 = CONTROL_STATE_OFF;
            HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
        }
        _trigger.hakkoT12 = false;
    }
}
void Control::ProcessSolderHand()
{
    uint16_t _filterAdc = 0;

    _medianSolderHand.Set(_adcCoupleSolderHand);
    _emaSolderHand.Set(_medianSolderHand.Get());
    _filterAdc = _emaSolderHand.Get();
    _currentTempSolderHand = 0.1320134f * _filterAdc + 21.43212233f;

    if (_stateSolderHand == CONTROL_STATE_OFF && !_trigger.solderHand)
        return;

    _timerSolderHand.Process();

    if (_stateSolderHand == CONTROL_STATE_SLEEP)
        _pidDataSolderHand.Point = _emem->Param().t12TempSleep;
    else
        _pidDataSolderHand.Point = _emem->Param().t12SetTemp;

    _pidDataSolderHand.Kp = _emem->Param().ironKp;
    _pidDataSolderHand.Ki = _emem->Param().ironKi;
    _pidDataSolderHand.Kd = _emem->Param().ironKd;

    qymos::common::Pid::SetData(&_pidDataSolderHand);
    qymos::common::Pid::Process();

    TIM4->CCR3 = _pidDataSolderHand.Output;

    if (_trigger.solderHand)
    {
        if (_stateSolderHand == CONTROL_STATE_ON)
            HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
        else
        {
            _stateSolderHand = CONTROL_STATE_OFF;
            HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
        }
        _trigger.solderHand = false;
    }
}

void Control::ProcessHairGun()
{

}

void Control::GetAdcCoupleHakkoT12()
{

    if (_stateHakkoT12 == CONTROL_STATE_ON || _stateHakkoT12 == CONTROL_STATE_SLEEP)
        HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);

    HAL_Delay(15);
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 100);
    _adcCoupleHacckoT12 = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);

    if (_stateHakkoT12 == CONTROL_STATE_ON || _stateHakkoT12 == CONTROL_STATE_SLEEP)
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}