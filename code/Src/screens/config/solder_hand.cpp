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
        _textSensor.SetText(_strSensorOn);

        _textTimeSleep.SetFont(&HellenicaRus8px);
        _textTimeSleep.SetText(_strTimeSleep);

        _textTempSleep.SetFont(&HellenicaRus8px);
        _textTempSleep.SetText(_strTempSleep);

        _textPidTune.SetFont(&HellenicaRus8px);
        _textPidTune.SetText(_strPidTune);

        _textNtsResistens.SetFont(&HellenicaRus8px);
        _textNtsResistens.SetText(_strNtcResistens);

        _iconSolderHand.SetImage(&IconD8928px);
        _iconBack.SetImage(&IconBack8px);
        _iconCalibrate.SetImage(&IconCalibration8px);
        _iconSens.SetImage(&IconSens8px);
        _iconSleep.SetImage(&IconSleep8px);
        _iconTemp.SetImage(&IconTemp8px);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textTempCalibrate, &_iconCalibrate);
        _list.AddItem(&_textTempMin, &_iconTemp);
        _list.AddItem(&_textTempMax, &_iconTemp);
        _list.AddItem(&_textSensor, &_iconSens);
        _list.AddItem(&_textTimeSleep, &_iconSleep);
        _list.AddItem(&_textTempSleep, &_iconTemp);
        _list.AddItem(&_textPidTune, &_iconCalibrate);
        _list.AddItem(&_textNtsResistens, &_iconSens);

        _inputTime.SetFont(&HellenicaRus8px);
        _inputTime.SetPosition({20, 16, 88, 64 - 32});
        _inputTime.Visible(false);

        _inputInt.SetFont(&HellenicaRus8px);
        _inputInt.SetPosition({20, 16, 88, 64 - 32});
        _inputInt.Visible(false);
        _inputInt.SetMax(350);
        _inputInt.SetMin(50);
        _inputInt.Visible(false);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetElement(&_list);
        _layout.SetElement(&_inputTime);
        _layout.SetElement(&_inputInt);

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
        if (!direction)
            _activeItem++;
        else
            _activeItem--;
        if (_activeItem > _list.GetSize())
            _activeItem = 0;
        if (_activeItem < 0)
            _activeItem = _list.GetSize();

        _list.SetActiveItem(_activeItem);
    }
    void ScreenConfigSolderHand::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenConfigSolderHand::OnButtonClick(uint16_t ButtonPin)
    {
        switch (_activeItem)
        {
        case 0:
            _hierarhy->SetSelectedItem(SCREEN_CONFIG);
            break;

        default:
            break;
        }
    }
    void ScreenConfigSolderHand::OnButtonLongClick(uint16_t ButtonPin)
    {
    }
} // namespace gui
