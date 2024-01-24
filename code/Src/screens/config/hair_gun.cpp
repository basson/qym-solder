#include "screens/config/hair_gun.hpp"

namespace gui
{

    ScreenConfigHairGun::ScreenConfigHairGun()
    {
        _titleText.SetFont(&HellenicaRus8px);
        _titleText.SetText(_titleStr);

        _textBack.SetFont(&HellenicaRus8px);
        _textBack.SetText(_strBack);

        _textTempCalibrate.SetFont(&HellenicaRus8px);
        _textTempCalibrate.SetText(_strTempCalibrate);

        _textTempMin.SetFont(&HellenicaRus8px);
        _textTempMin.SetText(_strTempMin);

        _textTempMax.SetFont(&HellenicaRus8px);
        _textTempMax.SetText(_strTempMax);

        _textFlowMin.SetFont(&HellenicaRus8px);
        _textFlowMin.SetText(_strFlowMin);

        _textFlowMax.SetFont(&HellenicaRus8px);
        _textFlowMax.SetText(_strFlowMax);

        _textSensor.SetFont(&HellenicaRus8px);
        _textSensor.SetText(_strSensorOff);

        _textPidTune.SetFont(&HellenicaRus8px);
        _textPidTune.SetText(_strPidTune);

        _textNtsResistens.SetFont(&HellenicaRus8px);
        _textNtsResistens.SetText(_strNtcResistens);

        _textSelectNtcNone.SetFont(&HellenicaRus8px);
        _textSelectNtcNone.SetText(_strSelectNtcNone);

        _textSelectNtc10k.SetFont(&HellenicaRus8px);
        _textSelectNtc10k.SetText(_strSelectNtc10K);

        _textSelectNtc100k.SetFont(&HellenicaRus8px);
        _textSelectNtc100k.SetText(_strSelectNtc100k);

        _iconHairGun.SetImage(&IconFan8px);
        _iconBack.SetImage(&IconBack8px);
        _iconCalibrate.SetImage(&IconCalibration8px);
        _iconSens.SetImage(&IconSens8px);
        _iconTemp.SetImage(&IconTemp8px);
        _iconFlow.SetImage(&IconCooling8px);
        _iconPid.SetImage(&IconPid8px);
        _iconNtc.SetImage(&IconNtc8px);
        _iconRadioBoxOn.SetImage(&IconRadioBoxOn8px);
        _iconRadioBoxOff.SetImage(&IconRadioBoxOff8px);

        _checkBox.SetImageCheck(&_iconRadioBoxOn);
        _checkBox.SetImageUncheck(&_iconRadioBoxOff);
        _checkBox.SetPosition({0, 0, 8, 8});

        _inputInt.SetFont(&HellenicaRus8px);
        _inputInt.SetPosition({20, 16, 88, 64 - 32});
        _inputInt.Visible(false);
        _inputInt.SetMax(350);
        _inputInt.SetMin(50);
        _inputInt.Visible(false);

        _inputSelectNtc.SetPosition({30, 16, 128 - 60, 28});
        _inputSelectNtc.AddItem(&_textSelectNtcNone, &_checkBox);
        _inputSelectNtc.AddItem(&_textSelectNtc10k, &_checkBox);
        _inputSelectNtc.AddItem(&_textSelectNtc100k, &_checkBox);
        _inputSelectNtc.SetItemHeight(12);
        _inputSelectNtc.Visible(false);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textTempCalibrate, &_iconCalibrate);
        _list.AddItem(&_textTempMin, &_iconTemp);
        _list.AddItem(&_textTempMax, &_iconTemp);
        _list.AddItem(&_textFlowMin, &_iconFlow);
        _list.AddItem(&_textFlowMax, &_iconFlow);
        _list.AddItem(&_textSensor, &_iconSens);
        _list.AddItem(&_textPidTune, &_iconPid);
        _list.AddItem(&_textNtsResistens, &_iconSens);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetElement(&_list);
        _layout.SetElement(&_inputInt);
        _layout.SetElement(&_inputSelectNtc);

        _window.SetTitle(&_titleText, &_iconHairGun);
        _window.SetTitleHeight(12);
        _window.SetBody(&_layout);
        _window.SetPosition({0, 0, 128, 64});
    }
    qymos::gui::IElement *ScreenConfigHairGun::GetPage()
    {
        return &_window;
    }
    void ScreenConfigHairGun::Process()
    {
        if (_emem->Param().hairSensor)
            _textSensor.SetText(_strSensorOn);
        else
            _textSensor.SetText(_strSensorOff);
    }
    void ScreenConfigHairGun::OnEncoderDirection(bool direction)
    {
        if (_isInputShow[0] || _isInputShow[1] || _isInputShow[2] || _isInputShow[3] || _isInputShow[4])
        {
            if (!direction)
                _inputInt.Increase();
            else
                _inputInt.Decrease();
            return;
        }
        if (_isInputShow[5])
        {
            _inputSelectNtc.ChangeActiveByDirection(direction);
            return;
        }
        _list.ChangeActiveByDirection(direction);
    }
    void ScreenConfigHairGun::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenConfigHairGun::OnButtonClick(uint16_t ButtonPin)
    {
        switch (_list.GetActiveItem())
        {
        case 0:
            _hierarhy->SetSelectedItem(SCREEN_CONFIG);
            break;
        case 1:
            _isInputShow[0] = !_isInputShow[0];
            _inputInt.SetMax(10);
            _inputInt.SetMin(-10);
            if (_isInputShow[0])
                _inputInt.SetValue(_emem->Param().hairCalibration);
            else
            {
                _emem->Param().hairCalibration = _inputInt.GetValue();
                _emem->Save();
            }
            _inputInt.Visible(_isInputShow[0]);
            break;
        case 2:
            _isInputShow[1] = !_isInputShow[1];
            _inputInt.SetMax(100);
            _inputInt.SetMin(50);
            if (_isInputShow[1])
                _inputInt.SetValue(_emem->Param().hairMinTemp);
            else
            {
                _emem->Param().hairMinTemp = _inputInt.GetValue();
                _emem->Save();
            }
            _inputInt.Visible(_isInputShow[1]);
            break;
        case 3:
            _isInputShow[2] = !_isInputShow[2];
            _inputInt.SetMax(400);
            _inputInt.SetMin(_emem->Param().hairMinTemp);
            if (_isInputShow[2])
                _inputInt.SetValue(_emem->Param().hairMaxTemp);
            else
            {
                _emem->Param().hairMaxTemp = _inputInt.GetValue();
                _emem->Save();
            }
            _inputInt.Visible(_isInputShow[2]);
            break;
        case 4:
            _isInputShow[3] = !_isInputShow[3];
            _inputInt.SetMax(90);
            _inputInt.SetMin(10);
            if (_isInputShow[3])
                _inputInt.SetValue(_emem->Param().hairMinFlow);
            else
            {
                _emem->Param().hairMinFlow = _inputInt.GetValue();
                _emem->Save();
            }
            _inputInt.Visible(_isInputShow[3]);
            break;
        case 5:
            _isInputShow[4] = !_isInputShow[4];
            _inputInt.SetMax(100);
            _inputInt.SetMin(_emem->Param().hairMinFlow);
            if (_isInputShow[4])
                _inputInt.SetValue(_emem->Param().hairMaxFlow);
            else
            {
                _emem->Param().hairMaxFlow = _inputInt.GetValue();
                _emem->Save();
            }
            _inputInt.Visible(_isInputShow[4]);
            break;
        case 6:
            _emem->Param().t12Sensor = !_emem->Param().t12Sensor;
            _emem->Save();
            break;
        case 7:
            ScreenPidAutoTune::SetBackScreen(SCREEN_CONFIG_HAKKO_T12);
            _hierarhy->SetSelectedItem(SCREEN_CONFIG_PID_AUTOTUNE);
            break;
        case 8:
            if (!_isInputShow[5])
            {
                _inputSelectNtc.SetActiveItem(_emem->Param().hairNtc);
                _inputSelectNtc.SetAllItemCheck(false);
                _inputSelectNtc.SetItemCheck(_emem->Param().hairNtc, true);
                _isInputShow[5] = true;
            }
            else
            {
                _inputSelectNtc.SetAllItemCheck(false);
                _inputSelectNtc.SetItemCheck(_inputSelectNtc.GetActiveItem(), true);
                _emem->Param().hairNtc = _inputSelectNtc.GetActiveItem();
            }
            _inputSelectNtc.Visible(_isInputShow[5]);
        default:
            break;
        }
    }
    void ScreenConfigHairGun::OnButtonLongClick(uint16_t ButtonPin)
    {
        switch (_list.GetActiveItem())
        {
        case 8:
            _isInputShow[5] = false;
            _emem->Save();
            _inputSelectNtc.Visible(_isInputShow[3]);
            break;
        default:
            break;
        }
    }
} // namespace gui
