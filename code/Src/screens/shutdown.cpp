#include "screens/shutdown.hpp"

namespace gui
{
    ScreenShutdown::ScreenShutdown()
    {
        _textBye.SetFont(&HellenicaRus8px);
        _textBye.SetText(_strBye);
        _textBye.SetPosition({(uint16_t)(128 / 2 - _textBye.GetWidth() / 2), 15+22+4, 0, 0});

        _icon.SetImage(&Logo15x22px);
        _icon.SetPosition({(128-15)/2, 15, 0, 0});
        _icon.Visible(true);

        _layout.SetPosition({0, 0, 128, 64});

        _layout.SetPrimitive(&_textBye);
        _layout.SetPrimitive(&_icon);
    }

    qymos::gui::IElement *ScreenShutdown::GetPage()
    {
        return &_layout;
    }

    void ScreenShutdown::Process()
    {
        if (Control::StateHairGun() == Control::State::CONTROL_STATE_ON)
                Control::StateHairGun(Control::State::CONTROL_STATE_OFF);
        if (Control::StateHakkoT12() == Control::State::CONTROL_STATE_ON)
                Control::StateHakkoT12(Control::State::CONTROL_STATE_OFF);
        if (Control::StateSolderHand() == Control::State::CONTROL_STATE_ON)
        {
            Control::StateSolderHand(Control::State::CONTROL_STATE_OFF);
            return;
        }
        if (Control::StateHairGun() == Control::State::CONTROL_STATE_COOLING)
        {
            _textBye.SetText(_strWarning);
            _textBye.SetPosition({(uint16_t)(128 / 2 - _textBye.GetWidth() / 2), 15+22+4, 0, 0});
            _icon.SetImage(&Warning24x24px);
        }
        else
        {
            _textBye.SetText(_strBye);
            _textBye.SetPosition({(uint16_t)(128 / 2 - _textBye.GetWidth() / 2), 15+22+4, 0, 0});
            _icon.SetImage(&Logo15x22px);
            HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, GPIO_PIN_RESET);
        }

        
    }
    void ScreenShutdown::OnButtonClick(uint16_t pin)
    {
    }
    void ScreenShutdown::OnButtonLongClick(uint16_t pin)
    {
    }
    void ScreenShutdown::OnEncoderDirection(bool direction)
    {
    }
    void ScreenShutdown::OnEncoderValue(uint32_t value)
    {
    }
} // namespace gui
