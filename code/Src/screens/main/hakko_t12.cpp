#include "screens/main/hakko_t12.hpp"

namespace gui
{
    ScreenHakkoT12::ScreenHakkoT12()
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

    qymos::gui::TabPage *ScreenHakkoT12::GetPage()
    {
        return &_tabPage;
    }

    void ScreenHakkoT12::OnEncoderDirection(bool direction)
    {
    }
    void ScreenHakkoT12::OnEncoderValue(uint32_t value)
    {
    }

    void ScreenHakkoT12::Process()
    {
        uint16_t temp = Control::GetCurrentTempHakkoT12();
        itoa(temp, _strCurrent, 10);
        strcat(_strCurrent, "°");
        if (temp < 100)
        {
            char buf[6] = "0";
            strcat(buf, _strCurrent);
            strcpy(_strCurrent, buf);
        }
        _textCurrent.SetText(_strCurrent);
    }
    void ScreenHakkoT12::OnButtonClick()
    {
    }
    void ScreenHakkoT12::OnButtonLongClick()
    {
    }
} // namespace gui
