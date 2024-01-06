#include "screens/main/hair_gun.hpp"

namespace gui
{
    ScreenHAirGun::ScreenHAirGun()
    {
        _textTempCurrent.SetFont(&HellenicaRus12px);
        _textTempCurrent.SetText(_strTempCurrent);
        _textTempCurrent.SetPosition({(uint16_t)(128 / 2 - _textTempCurrent.GetWidth() / 2), 18, 0, 0});
        _textTempCurrent.SetInvert(false);

        _textFlowCurrent.SetFont(&HellenicaRus12px);
        _textFlowCurrent.SetText(_strFlowCurrent);
        _textFlowCurrent.SetPosition({(uint16_t)(128 / 2 - _textFlowCurrent.GetWidth() / 2), 36, 0, 0});
        _textFlowCurrent.SetInvert(false);

        _textTempSet.SetFont(&HellenicaRus8px);
        _textTempSet.SetText(_strTempSet);
        _textTempSet.SetPosition({(uint16_t)(128 - 4 - _textTempSet.GetWidth()), (uint16_t)(64 - 2 - _textTempSet.GetHeight()), 0, 0});
        _textTempSet.SetInvert(false);

        _textFlowSet.SetFont(&HellenicaRus8px);
        _textFlowSet.SetText(_strFlowSet);
        _textFlowSet.SetPosition({4, (uint16_t)(64 - 2 - _textFlowSet.GetHeight()), 0, 0});
        _textFlowSet.SetInvert(false);

        _iconHeat.SetImage(&IconHeat12px);
        _iconHeat.SetPosition({20, 18, 0, 0});

        _iconFan.SetImage(&IconFan12px);
        _iconFan.SetPosition({20, 36, 0, 0});

        _tabPage.SetElement(&_textFlowCurrent);
        _tabPage.SetElement(&_textTempCurrent);
        _tabPage.SetElement(&_textTempSet);
        _tabPage.SetElement(&_textFlowSet);
        _tabPage.SetElement(&_iconHeat);
        _tabPage.SetElement(&_iconFan);
    }
    qymos::gui::TabPage *ScreenHAirGun::GetPage()
    {
        return &_tabPage;
    }

    void ScreenHAirGun::OnEncoderDirection(bool direction)
    {
    }
    void ScreenHAirGun::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenHAirGun::Process()
    {
    }
    void ScreenHAirGun::OnButtonClick()
    {
    }
    void ScreenHAirGun::OnButtonLongClick()
    {
    }
} // namespace gui
