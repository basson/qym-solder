#include "screens/config/default.hpp"

namespace gui
{
    ScreenConfigDefault::ScreenConfigDefault()
    {
        _titleText.SetFont(&HellenicaRus8px);
        _titleText.SetText(_titleStr);

        _textBack.SetFont(&HellenicaRus8px);
        _textBack.SetText(_strBack);

        _textTimeOff.SetFont(&HellenicaRus8px);
        _textTimeOff.SetText(_strTimeOff);

        _textTimeShutdown.SetFont(&HellenicaRus8px);
        _textTimeShutdown.SetText(_strTimeShutdown);

        _textSound.SetFont(&HellenicaRus8px);
        _textSound.SetText(_strSoundOff);

        _textCooling.SetFont(&HellenicaRus8px);
        _textCooling.SetText(_strCooling);

        _textNtc.SetFont(&HellenicaRus8px);
        _textNtc.SetText(_strNtc);

        _textResetCfg.SetFont(&HellenicaRus8px);
        _textResetCfg.SetText(_strResetCfg);

        _iconConfig.SetImage(&IconConfig8px);
        _iconBack.SetImage(&IconBack8px);
        _iconClock.SetImage(&IconClock8px);
        _iconSound.SetImage(&IconSound8px);

        _inputTime.SetFont(&HellenicaRus8px);
        _inputTime.SetPosition({20, 16, 88, 64 - 32});
        _inputTime.Visible(false);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textTimeOff, &_iconClock);
        _list.AddItem(&_textTimeShutdown, &_iconClock);
        _list.AddItem(&_textSound, &_iconSound);
        _list.AddItem(&_textCooling, &_iconBack);
        _list.AddItem(&_textNtc, &_iconBack);
        _list.AddItem(&_textResetCfg, &_iconBack);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetElement(&_list);
        _layout.SetElement(&_inputTime);

        _window.SetTitle(&_titleText, &_iconConfig);
        _window.SetTitleHeight(12);
        _window.SetBody(&_layout);
        _window.SetPosition({0, 0, 128, 64});
    }

    qymos::gui::IElement *ScreenConfigDefault::GetPage()
    {
        return &_window;
    }
    void ScreenConfigDefault::Process()
    {
    }
    void ScreenConfigDefault::OnEncoderDirection(bool direction)
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
    void ScreenConfigDefault::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenConfigDefault::OnButtonClick(uint16_t ButtonPin)
    {
        switch (_activeItem)
        {
        case 0:
            _hierarchy->SetSelectedItem(SCREEN_CONFIG);
            break;
        default:
            break;
        }
    }
    void ScreenConfigDefault::OnButtonLongClick(uint16_t ButtonPin)
    {
    }
} // namespace gui
