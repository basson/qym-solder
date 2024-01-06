#include "screens/main/haccko_t12.hpp"

namespace gui
{
    ScreenHacckoT12::ScreenHacckoT12()
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

    qymos::gui::TabPage *ScreenHacckoT12::GetPage()
    {
        return &_tabPage;
    }

    void ScreenHacckoT12::OnEncoderDirection(bool direction)
    {
    }
    void ScreenHacckoT12::OnEncoderValue(uint32_t value)
    {
    }

    void ScreenHacckoT12::Process()
    {
    }
    void ScreenHacckoT12::OnButtonClick()
    {
    }
    void ScreenHacckoT12::OnButtonLongClick()
    {
    }
} // namespace gui
