#include "screens/main/soldering_iron.hpp"

namespace gui
{
    ScreenSolderingIron::ScreenSolderingIron()
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

    qymos::gui::TabPage *ScreenSolderingIron::GetPage()
    {
        return &_tabPage;
    }

    void ScreenSolderingIron::OnEncoderDirection(bool direction)
    {
    }
    void ScreenSolderingIron::OnEncoderValue(uint32_t value)
    {
    }

    void ScreenSolderingIron::Process()
    {
    }
    void ScreenSolderingIron::OnButtonClick()
    {
    }
    void ScreenSolderingIron::OnButtonLongClick()
    {
    }
} // namespace gui
