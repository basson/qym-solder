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
        _textSensor.SetText(_strSensorOn);

        _textPidTune.SetFont(&HellenicaRus8px);
        _textPidTune.SetText(_strPidTune);

        _textNtsResistens.SetFont(&HellenicaRus8px);
        _textNtsResistens.SetText(_strNtcResistens);

        _iconHairGun.SetImage(&IconFan8px);
        _iconBack.SetImage(&IconBack8px);
        _iconCalibrate.SetImage(&IconCalibration8px);
        _iconSens.SetImage(&IconSens8px);
        _iconTemp.SetImage(&IconTemp8px);
        _iconFlow.SetImage(&IconFlow8px);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textTempCalibrate, &_iconCalibrate);
        _list.AddItem(&_textTempMin, &_iconTemp);
        _list.AddItem(&_textTempMax, &_iconTemp);
        _list.AddItem(&_textFlowMin, &_iconFlow);
        _list.AddItem(&_textFlowMax, &_iconFlow);
        _list.AddItem(&_textSensor, &_iconSens);
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
    }
    void ScreenConfigHairGun::OnEncoderDirection(bool direction)
    {
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

        default:
            break;
        }
    }
    void ScreenConfigHairGun::OnButtonLongClick(uint16_t ButtonPin)
    {
    }
} // namespace gui
