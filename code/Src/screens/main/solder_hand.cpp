#include "screens/main/solder_hand.hpp"

namespace gui
{
    ScreenSolderHand::ScreenSolderHand()
    {
        _textCurrent.SetFont(&HellenicaRus16px);
        _textCurrent.SetText(_strCurrent);
        _textCurrent.SetPosition({(uint16_t)(128 / 2 - _textCurrent.GetWidth() / 2), (uint16_t)((64 - 12) / 2 - _textCurrent.GetHeight() / 2 + 10), 0, 0});
        _textCurrent.SetInvert(false);

        _textSet.SetFont(&HellenicaRus8px);
        _textSet.SetText(_strSet);
        _textSet.SetPosition({(uint16_t)(128 - 4 - _textSet.GetWidth()), (uint16_t)(64 - 2 - _textSet.GetHeight()), 0, 0});
        _textSet.SetInvert(false);

        _iconHeat.SetImage(&IconHeat12px);
        _iconHeat.SetPosition({16, ((64 - 12) / 2 - 12 / 2) + 10, 0, 0});

        _tabPage.SetElement(&_textCurrent);
        _tabPage.SetElement(&_textSet);
        _tabPage.SetElement(&_iconHeat);
    }

    qymos::gui::TabPage *ScreenSolderHand::GetPage()
    {
        return &_tabPage;
    }

    void ScreenSolderHand::Process()
    {
        uint16_t showTemp;
        char buf[8] = "";

        switch (Control::StateSolderHand())
        {
        case Control::CONTROL_STATE_ON:
            _iconHeat.Visible(true);
            break;
        case Control::CONTROL_STATE_OFF:
            _iconHeat.Visible(false);
        default:
            break;
        }

        if (_isChangeSetTemp)
        {
            showTemp = _emem->Param().ironSetTemp;
            if (HAL_GetTick() > _millis)
            {
                if (!_isInvert)
                    _millis = 100;
                else
                    _millis = 500;
                _isInvert = !_isInvert;
                _millis += HAL_GetTick();
            }
            _iconHeat.Visible(true);
        }
        else
            showTemp = Control::GetCurrentTempSolderHand() + _emem->Param().ironCalibration;

        itoa(showTemp, _strCurrent, 10);
        strcat(_strCurrent, "°");
        if (showTemp < 100)
        {
            buf[0] = '0';
            strcat(buf, _strCurrent);
            strcpy(_strCurrent, buf);
        }
        _textCurrent.SetText(_strCurrent);
        _textCurrent.SetInvert(_isInvert);

        if (_emem->Param().ironSetTemp < 100)
            strcpy(_strSet, "set:0");
        else
            strcpy(_strSet, "set:");
        itoa(_emem->Param().ironSetTemp, buf, 10);
        strcat(_strSet, buf);
        strcat(_strSet, "°");
        _textSet.SetText(_strSet);
    }

    void ScreenSolderHand::OnEncoderDirection(bool direction)
    {
        if (!direction)
            _emem->Param().ironSetTemp++;
        else
            _emem->Param().ironSetTemp--;

        if (_emem->Param().ironSetTemp > _emem->Param().ironMaxTemp)
            _emem->Param().ironSetTemp = _emem->Param().ironMaxTemp;
        if (_emem->Param().ironSetTemp < _emem->Param().ironMinTemp)
            _emem->Param().ironSetTemp = _emem->Param().ironMinTemp;
    }

    void ScreenSolderHand::OnButtonClick()
    {
        if (_isChangeSetTemp)
            return;
        Control::StateSolderHand(Control::State(!(bool)Control::StateSolderHand()));
    }
    void ScreenSolderHand::OnButtonLongClick()
    {
        _isChangeSetTemp = !_isChangeSetTemp;
        if (!_isChangeSetTemp)
        {
            _emem->Save();
            _isInvert = false;
        }
    }

    void ScreenSolderHand::OnEncoderValue(uint32_t value)
    {
    }
} // namespace gui
