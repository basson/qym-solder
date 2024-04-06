#include "screens/main/hair_gun.hpp"

namespace gui
{
    ScreenHAirGun::ScreenHAirGun()
    {
        _textTempCurrent.SetFont(&HellenicaRus12px);
        _textTempCurrent.SetText(_strTempCurrent);
        _textTempCurrent.SetPosition({(uint16_t)(128 / 2 - _textTempCurrent.GetWidth() / 2), 18, 0, 0});
        _textTempCurrent.SetInvert(false);

        _textFlowCurrent.SetFont(&HellenicaRus12px);
        _textFlowCurrent.SetText(_strFlowCurrent);
        _textFlowCurrent.SetPosition({(uint16_t)(128 / 2 - _textFlowCurrent.GetWidth() / 2), 36, 0, 0});
        _textFlowCurrent.SetInvert(false);

        _textTempSet.SetFont(&HellenicaRus8px);
        _textTempSet.SetText(_strTempSet);
        _textTempSet.SetPosition({(uint16_t)(128 - 4 - _textTempSet.GetWidth()), (uint16_t)(64 - 2 - _textTempSet.GetHeight()), 0, 0});
        _textTempSet.SetInvert(false);

        _textFlowSet.SetFont(&HellenicaRus8px);
        _textFlowSet.SetText(_strFlowSet);
        _textFlowSet.SetPosition({4, (uint16_t)(64 - 2 - _textFlowSet.GetHeight()), 0, 0});
        _textFlowSet.SetInvert(false);

        _iconHeat.SetImage(&IconHeat12px);
        _iconHeat.SetPosition({20, 18, 0, 0});

        _iconFlow.SetImage(&IconFlow12px);
        _iconFlow.SetPosition({20, 36, 0, 0});

        _tabPage.SetElement(&_textFlowCurrent);
        _tabPage.SetElement(&_textTempCurrent);
        _tabPage.SetElement(&_textTempSet);
        _tabPage.SetElement(&_textFlowSet);
        _tabPage.SetElement(&_iconHeat);
        _tabPage.SetElement(&_iconFlow);
    }
    qymos::gui::TabPage *ScreenHAirGun::GetPage()
    {
        return &_tabPage;
    }

    void ScreenHAirGun::Process()
    {
        uint16_t showTemp;
        uint16_t showFlow;
        char buf[8] = "";

        switch (Control::StateHairGun())
        {
        case Control::CONTROL_STATE_ON:
            _iconHeat.Visible(true);
            break;
        case Control::CONTROL_STATE_OFF:
            _iconHeat.Visible(false);
        default:
            break;
        }

        if (_isChange)
            _iconHeat.Visible(true);

        if (_isChangeSetTemp)
        {
            showTemp = _emem->Param().hairSetTemp;
            if (HAL_GetTick() > _millis)
            {
                if (!_isInvertTemp)
                    _millis = 100;
                else
                    _millis = 500;
                _isInvertTemp = !_isInvertTemp;
                _millis += HAL_GetTick();
            }
        }
        else
            showTemp = Control::GetCurrentTempHairGun() + _emem->Param().hairCalibration;

        itoa(showTemp, _strTempCurrent, 10);
        strcat(_strTempCurrent, "°");
        if (showTemp < 100)
        {
            buf[0] = '0';
            strcat(buf, _strTempCurrent);
            strcpy(_strTempCurrent, buf);
        }
        _textTempCurrent.SetText(_strTempCurrent);
        _textTempCurrent.SetInvert(_isInvertTemp);

        if (_emem->Param().hairSetTemp < 100)
            strcpy(_strTempSet, "set:0");
        else
            strcpy(_strTempSet, "set:");
        itoa(_emem->Param().hairSetTemp, buf, 10);
        strcat(_strTempSet, buf);
        strcat(_strTempSet, "°");
        _textTempSet.SetText(_strTempSet);

        memset(buf, 0, 8);
        if (_isChangeSetFlow)
        {
            showFlow = _emem->Param().hairSetFlow;
            if (HAL_GetTick() > _millis)
            {
                if (!_isInvertFlow)
                    _millis = 100;
                else
                    _millis = 500;
                _isInvertFlow = !_isInvertFlow;
                _millis += HAL_GetTick();
            }
        }
        else
        {
            if (Control::StateHairGun() == Control::CONTROL_STATE_ON)
                showFlow = _emem->Param().hairSetFlow;
            else if (Control::StateHairGun() == Control::CONTROL_STATE_COOLING)
                showFlow = 100;
            else
                showFlow = 0;
        }

        itoa(showFlow, _strFlowCurrent, 10);
        strcat(_strFlowCurrent, "%");
        if (showFlow < 100)
            buf[0] = '0';
        if (showFlow < 10)
            buf[1] = '0';
        strcat(buf, _strFlowCurrent);
        strcpy(_strFlowCurrent, buf);

        _textFlowCurrent.SetText(_strFlowCurrent);
        _textFlowCurrent.SetInvert(_isInvertFlow);

        if (_emem->Param().hairSetFlow < 100)
            strcpy(_strFlowSet, "set:0");
        else
            strcpy(_strFlowSet, "set:");
        itoa(_emem->Param().hairSetFlow, buf, 10);
        strcat(_strFlowSet, buf);
        strcat(_strFlowSet, "%");
        itoa((int)Control::StateHairGun(), _strFlowSet, 10);
        _textFlowSet.SetText(_strFlowSet);
    }

    void ScreenHAirGun::OnEncoderDirection(bool direction)
    {

        if (!direction)
        {
            if (_isChangeSetTemp)
                _emem->Param().hairSetTemp++;
            if (_isChangeSetFlow)
                _emem->Param().hairSetFlow++;
        }
        else
        {
            if (_isChangeSetTemp)
                _emem->Param().hairSetTemp--;
            if (_isChangeSetFlow)
                _emem->Param().hairSetFlow--;
        }

        if (_emem->Param().hairSetTemp > _emem->Param().hairMaxTemp)
            _emem->Param().hairSetTemp = _emem->Param().hairMaxTemp;
        if (_emem->Param().hairSetTemp < _emem->Param().hairMinTemp)
            _emem->Param().hairSetTemp = _emem->Param().hairMinTemp;

        if (_emem->Param().hairSetFlow > _emem->Param().hairMaxFlow)
            _emem->Param().hairSetFlow = _emem->Param().hairMaxFlow;
        if (_emem->Param().hairSetFlow < _emem->Param().hairMinFlow)
            _emem->Param().hairSetFlow = _emem->Param().hairMinFlow;
    }
    void ScreenHAirGun::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenHAirGun::OnButtonClick()
    {
        if (_isChange)
        {
            _isChangeSetFlow = _isChangeSetTemp;
            _isChangeSetTemp = !_isChangeSetTemp;
            _isInvertTemp = false;
            _isInvertFlow = false;
        }
        else
        {
            if (Control::StateHairGun() == Control::State::CONTROL_STATE_ON)
                Control::StateHairGun(Control::State::CONTROL_STATE_OFF);
            else
                Control::StateHairGun(Control::State::CONTROL_STATE_ON);

            // Control::StateHairGun(Control::State(!(bool)Control::StateHairGun()));
        }
    }
    void ScreenHAirGun::OnButtonLongClick()
    {
        _isChange = !_isChange;
        if (!_isChange)
        {
            _isChangeSetFlow = false;
            _isChangeSetTemp = false;
            _emem->Save();
            _isInvertTemp = false;
            _isInvertFlow = false;
        }
        else
            _isChangeSetTemp = true;
    }
} // namespace gui
