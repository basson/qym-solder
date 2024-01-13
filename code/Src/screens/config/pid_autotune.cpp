#include "screens/config/pid_autotune.hpp"

namespace gui
{
    Screen ScreenPidAutoTune::_backScreenId = SCREEN_CONFIG;

    ScreenPidAutoTune::ScreenPidAutoTune()
    {
        _titleText.SetFont(&HellenicaRus8px);
        _titleText.SetText(_titleStr);

        _exmpText.SetFont(&HellenicaRus8px);
        _exmpText.SetText(_exmpStr);
        _exmpText.SetPosition({(uint16_t)(128 / 2 - _exmpText.GetWidth() / 2), 20, 0, 0});

        _textCurrent.SetFont(&HellenicaRus8px);
        _textCurrent.SetText(_strCurrent);
        _textCurrent.SetPosition({8, (uint16_t)(64 - 2 - _textCurrent.GetHeight()), 0, 0});

        _textSet.SetFont(&HellenicaRus8px);
        _textSet.SetText(_strSet);
        _textSet.SetPosition({(uint16_t)(128 - 8 - _textSet.GetWidth()), (uint16_t)(64 - 2 - _textSet.GetHeight()), 0, 0});


        _iconPidAutoTune.SetImage(&IconPid8px);

        _progress.SetPosition({8, 28+10, 112, 10});
        _progress.SetCount(100);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetPrimitive(&_exmpText);
        _layout.SetPrimitive(&_textCurrent);
        _layout.SetPrimitive(&_textSet);
        _layout.SetElement(&_progress);

        _window.SetTitle(&_titleText, &_iconPidAutoTune);
        _window.SetTitleHeight(12);
        _window.SetBody(&_layout);
        _window.SetPosition({0, 0, 128, 64});
    }

    void ScreenPidAutoTune::SetBackScreen(Screen screen)
    {
        _backScreenId = screen;
    }

    qymos::gui::IElement *ScreenPidAutoTune::GetPage()
    {
        return &_window;
    }
    void ScreenPidAutoTune::Process()
    {
        if (HAL_GetTick() > _millis + 20)
        {
            _load++;
            if (_load > 100)
                _load = 0;

            _millis = HAL_GetTick() + 20;

            _progress.SetProgress(_load);
        }
    }
    void ScreenPidAutoTune::OnEncoderDirection(bool direction)
    {
    }
    void ScreenPidAutoTune::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenPidAutoTune::OnButtonClick(uint16_t ButtonPin)
    {
        _hierarchy->SetSelectedItem(_backScreenId);
    }
    void ScreenPidAutoTune::OnButtonLongClick(uint16_t ButtonPin)
    {
    }
} // namespace gui
