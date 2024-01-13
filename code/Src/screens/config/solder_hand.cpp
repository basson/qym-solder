#include "screens/config/solder_hand.hpp"

namespace gui
{

    ScreenConfigSolderHand::ScreenConfigSolderHand()
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

        _textSensor.SetFont(&HellenicaRus8px);
        _textSensor.SetText(_strSensorOff);

        _textTimeSleep.SetFont(&HellenicaRus8px);
        _textTimeSleep.SetText(_strTimeSleep);

        _textTempSleep.SetFont(&HellenicaRus8px);
        _textTempSleep.SetText(_strTempSleep);

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

        _iconSolderHand.SetImage(&IconD8928px);
        _iconBack.SetImage(&IconBack8px);
        _iconCalibrate.SetImage(&IconCalibration8px);
        _iconSens.SetImage(&IconSens8px);
        _iconSleep.SetImage(&IconSleep8px);
        _iconTemp.SetImage(&IconTemp8px);
        _iconPid.SetImage(&IconPid8px);
        _iconNtc.SetImage(&IconNtc8px);

        _checkBoxSelected.SetPosition({0, 0, 8, 8});
        _checkBoxSelected.SetCheck(true);
        _checkBoxNotSelected.SetPosition({0, 0, 8, 8});
        _checkBoxNotSelected.SetCheck(false);

        _inputTime.SetFont(&HellenicaRus8px);
        _inputTime.SetPosition({20, 16, 88, 64 - 32});
        _inputTime.Visible(false);

        _inputInt.SetFont(&HellenicaRus8px);
        _inputInt.SetPosition({20, 16, 88, 64 - 32});
        _inputInt.SetMax(10);
        _inputInt.SetMin(-10);
        _inputInt.SetValue(0);
        _inputInt.Visible(false);

        _inputSelectNtc.SetPosition({30, 16, 128 - 60, 28});
        _inputSelectNtc.AddItem(&_textSelectNtcNone, &_checkBoxNotSelected);
        _inputSelectNtc.AddItem(&_textSelectNtc10k, &_checkBoxSelected);
        _inputSelectNtc.AddItem(&_textSelectNtc100k, &_checkBoxNotSelected);
        _inputSelectNtc.SetItemHeight(12);
        _inputSelectNtc.Visible(false);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textTempCalibrate, &_iconCalibrate);
        _list.AddItem(&_textTempMin, &_iconTemp);
        _list.AddItem(&_textTempMax, &_iconTemp);
        _list.AddItem(&_textSensor, &_iconSens);
        _list.AddItem(&_textTimeSleep, &_iconSleep);
        _list.AddItem(&_textTempSleep, &_iconTemp);
        _list.AddItem(&_textPidTune, &_iconPid);
        _list.AddItem(&_textNtsResistens, &_iconNtc);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetElement(&_list);
        _layout.SetElement(&_inputTime);
        _layout.SetElement(&_inputInt);
        _layout.SetElement(&_inputSelectNtc);

        _window.SetTitle(&_titleText, &_iconSolderHand);
        _window.SetTitleHeight(12);
        _window.SetBody(&_layout);
        _window.SetPosition({0, 0, 128, 64});
    }
    qymos::gui::IElement *ScreenConfigSolderHand::GetPage()
    {
        return &_window;
    }
    void ScreenConfigSolderHand::Process()
    {
    }
    void ScreenConfigSolderHand::OnEncoderDirection(bool direction)
    {
        if (_isInputShow[0] || _isInputShow[1] || _isInputShow[2] || _isInputShow[4])
        {
            if (!direction)
                _inputInt.Increase();
            else
                _inputInt.Decrease();
            return;
        }
        if (_isInputShow[3])
        {
            if (!direction)
                _inputTime.Increase();
            else
                _inputTime.Decrease();
            return;
        }
        if (_isInputShow[5])
        {
            _inputSelectNtc.ChangeActiveByDirection(direction);
            return;
        }
        _list.ChangeActiveByDirection(direction);
    }
    void ScreenConfigSolderHand::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenConfigSolderHand::OnButtonClick(uint16_t ButtonPin)
    {
        if (_isInputShow[3])
        {
            _inputTime.Next();
            return;
        }
        switch (_list.GetActiveItem())
        {
        case 0:
            _hierarhy->SetSelectedItem(SCREEN_CONFIG);
            break;
        case 1:
            _isInputShow[0] = !_isInputShow[0];
            _inputInt.SetMax(10);
            _inputInt.SetMin(-10);
            _inputInt.SetValue(0);
            _inputInt.Visible(_isInputShow[0]);
            break;
        case 2:
            _isInputShow[1] = !_isInputShow[1];
            _inputInt.SetMax(200);
            _inputInt.SetMin(50);
            _inputInt.SetValue(150);
            _inputInt.Visible(_isInputShow[1]);
            break;
        case 3:
            _isInputShow[2] = !_isInputShow[2];
            _inputInt.SetMax(400);
            _inputInt.SetMin(150);
            _inputInt.SetValue(200);
            _inputInt.Visible(_isInputShow[2]);
            break;
        case 4:
            _sensorState = !_sensorState;
            if (_sensorState)
                _textSensor.SetText(_strSensorOn);
            else
                _textSensor.SetText(_strSensorOff);
            break;
        case 5:
            _isInputShow[3] = !_isInputShow[3];
            _inputTime.SetSeconds(10);
            _inputTime.SetMinutes(10);
            _inputTime.SetHours(0);
            _inputTime.Visible(_isInputShow[3]);
            break;
        case 6:
            _isInputShow[4] = !_isInputShow[4];
            _inputInt.SetMax(200);
            _inputInt.SetMin(100);
            _inputInt.SetValue(110);
            _inputInt.Visible(_isInputShow[4]);
            break;
        case 7:
            ScreenPidAutoTune::SetBackScreen(SCREEN_CONFIG_SOLDER_HAND);
            _hierarhy->SetSelectedItem(SCREEN_CONFIG_PID_AUTOTUNE);
            break;
        case 8:
            _isInputShow[5] = !_isInputShow[5];
            _inputSelectNtc.Visible(_isInputShow[5]);
        default:
            break;
        }
    }
    void ScreenConfigSolderHand::OnButtonLongClick(uint16_t ButtonPin)
    {
        switch (_list.GetActiveItem())
        {
        case 5:
            _isInputShow[3] = false;
            _inputTime.Visible(false);
            break;

        default:
            break;
        }
    }
} // namespace gui
