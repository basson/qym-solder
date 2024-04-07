#include "screens/startup.hpp"

namespace gui
{
    ScreenStartup::ScreenStartup()
    {
        _textLogo.SetFont(&HellenicaRus8px);
        _textLogo.SetText(_strLogo);
        _textLogo.SetPosition({(uint16_t)(128 / 2 - _textLogo.GetWidth() / 2), 15+22+4, 0, 0});

        _iconLogo.SetImage(&Logo15x22px);
        _iconLogo.SetPosition({(128-15)/2, 15, 0, 0});

        _layout.SetPosition({0, 0, 128, 64});

        _layout.SetPrimitive(&_textLogo);
        _layout.SetPrimitive(&_iconLogo);
    }

    qymos::gui::IElement *ScreenStartup::GetPage()
    {
        return &_layout;
    }

    void ScreenStartup::Process()
    {
    }
    void ScreenStartup::OnButtonClick(uint16_t pin)
    {
    }
    void ScreenStartup::OnButtonLongClick(uint16_t pin)
    {
    }
    void ScreenStartup::OnEncoderDirection(bool direction)
    {
    }
    void ScreenStartup::OnEncoderValue(uint32_t value)
    {
    }
} // namespace gui
