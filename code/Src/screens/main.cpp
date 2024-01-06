#include "screens/main.hpp"

namespace gui
{
    ScreenMain::ScreenMain()
    {
        _textT12.SetFont(&HellenicaRus8px);
        _textT12.SetText(_strT12);

        _textHair.SetFont(&HellenicaRus8px);
        _textHair.SetText(_strHair);

        _textIron.SetFont(&HellenicaRus8px);
        _textIron.SetText(_strIron);

        _tabLayout.SetPosition({0, 0, 128, 64});
        _tabLayout.SetTabBarHeight(12);
        _tabLayout.SetActiveTab(0);
        _tabLayout.AddTab(&_textT12, _screenHacckoT12.GetPage());
        _tabLayout.AddTab(&_textIron, _screenIron.GetPage());
        _tabLayout.AddTab(&_textHair, _screenHair.GetPage());
    }

    qymos::gui::IElement *ScreenMain::GetPage()
    {
        return &_tabLayout;
    }

    void ScreenMain::Process()
    {
        _screenHacckoT12.Process();
        _screenIron.Process();
        _screenHair.Process();
    }
    void ScreenMain::OnButtonClick(uint16_t pin)
    {
        switch (_tabLayout.GetActiveTab())
        {
        case 0:
            _screenHacckoT12.OnButtonClick();
            break;
        case 1:
            _screenIron.OnButtonClick();
            break;
        case 2:
            _screenHair.OnButtonClick();
            break;
        default:
            break;
        }
    }
    void ScreenMain::OnButtonLongClick(uint16_t pin)
    {
        switch (_tabLayout.GetActiveTab())
        {
        case 0:
            _screenHacckoT12.OnButtonLongClick();
            break;
        case 1:
            _screenIron.OnButtonLongClick();
            break;
        case 2:
            _screenHair.OnButtonLongClick();
            break;
        default:
            break;
        }
    }
    void ScreenMain::OnEncoderDirection(bool direction)
    {
        if (!direction)
            _activeTab++;
        else
            _activeTab--;
        if (_activeTab > _tabLayout.GetSize())
            _activeTab = 0;
        if (_activeTab < 0)
            _activeTab = _tabLayout.GetSize();

        _tabLayout.SetActiveTab(_activeTab);
    }
    void ScreenMain::OnEncoderValue(uint32_t value)
    {
    }
} // namespace gui
