#include "screens/config.hpp"

namespace gui
{
    ScreenConfig::ScreenConfig()
    {
        _titleText.SetFont(&HellenicaRus8px);
        _titleText.SetText(_titleStr);

        _textBack.SetFont(&HellenicaRus8px);
        _textBack.SetText(_strBack);

        _textDefault.SetFont(&HellenicaRus8px);
        _textDefault.SetText(_strDefault);

        _textHakkoT12.SetFont(&HellenicaRus8px);
        _textHakkoT12.SetText(_strHacckoT12);

        _textSolderHand.SetFont(&HellenicaRus8px);
        _textSolderHand.SetText(_strSolderHand);

        _textHairGun.SetFont(&HellenicaRus8px);
        _textHairGun.SetText(_strHiarGun);

        _iconConfig.SetImage(&IconConfig8px);
        _iconBack.SetImage(&IconBack8px);
        _iconDefault.SetImage(&IconMonitor8px);
        _iconHakkoT12.SetImage(&IconT128px);
        _iconSolderHand.SetImage(&IconD8928px);
        _iconHiarGun.SetImage(&IconFan8px);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textDefault, &_iconDefault);
        _list.AddItem(&_textHakkoT12, &_iconHakkoT12);
        _list.AddItem(&_textSolderHand, &_iconSolderHand);
        _list.AddItem(&_textHairGun, &_iconHiarGun);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetElement(&_list);

        _window.SetTitle(&_titleText, &_iconConfig);
        _window.SetTitleHeight(12);
        _window.SetBody(&_layout);
        _window.SetPosition({0, 0, 128, 64});
    }
    qymos::gui::IElement *ScreenConfig::GetPage()
    {
        return &_window;
    }
    void ScreenConfig::Process()
    {
    }
    void ScreenConfig::OnEncoderDirection(bool direction)
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
    void ScreenConfig::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenConfig::OnButtonClick(uint16_t ButtonPin)
    {
        switch (_activeItem)
        {
        case 0:
            _hierarchy->SetSelectedItem(SCREEN_MAIN);
            break;
        case 1:
            _hierarchy->SetSelectedItem(SCREEN_CONFIG_DEFAULT);
            break;
        case 2:
            _hierarchy->SetSelectedItem(SCREEN_CONFIG_HAKKO_T12);
            break;
        case 3:
            _hierarchy->SetSelectedItem(SCREEN_CONFIG_SOLDER_HAND);
            break;
        case 4:
            _hierarchy->SetSelectedItem(SCREEN_CONFIG_HAIR_GUN);
            break;
        default:
            break;
        }
    }
    void ScreenConfig::OnButtonLongClick(uint16_t ButtonPin)
    {
    }
} // namespace gui
