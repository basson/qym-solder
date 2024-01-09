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

        _textSelectCoolingNtc.SetFont(&HellenicaRus8px);
        _textSelectCoolingNtc.SetText(_strSelectCoolingNtc);

        _textSelectCoolingAlways.SetFont(&HellenicaRus8px);
        _textSelectCoolingAlways.SetText(_strSelectCoolingAlways);

        _textSelectNtcNone.SetFont(&HellenicaRus8px);
        _textSelectNtcNone.SetText(_strSelectNtcNone);

        _textSelectNtc10k.SetFont(&HellenicaRus8px);
        _textSelectNtc10k.SetText(_strSelectNtc10K);

        _textSelectNtc100k.SetFont(&HellenicaRus8px);
        _textSelectNtc100k.SetText(_strSelectNtc100k);

        _textResetCfgInputMessage.SetFont(&HellenicaRus8px);
        _textResetCfgInputMessage.SetText(_strResetCfgInputMessage);

        _textResetCfgInputOk.SetFont(&HellenicaRus8px);
        _textResetCfgInputOk.SetText(_strResetCfgInputOk);

        _textResetCfgInputCancel.SetFont(&HellenicaRus8px);
        _textResetCfgInputCancel.SetText(_strResetCfgInputCancel);

        _iconConfig.SetImage(&IconConfig8px);
        _iconBack.SetImage(&IconBack8px);
        _iconClock.SetImage(&IconClock8px);
        _iconSound.SetImage(&IconSound8px);

        _inputTime.SetFont(&HellenicaRus8px);
        _inputTime.SetPosition({20, 16, 88, 64 - 32});
        _inputTime.Visible(false);

        _inputSelectCooling.SetPosition({20, 16, 128 - 40, 28});
        _inputSelectCooling.SetItemHeight(12);
        _inputSelectCooling.AddItem(&_textSelectCoolingNtc, &_iconSound);
        _inputSelectCooling.AddItem(&_textSelectCoolingAlways, &_iconSound);
        _inputSelectCooling.Visible(false);

        _inputSelectNtc.SetPosition({30, 16, 128 - 60, 28});
        _inputSelectNtc.AddItem(&_textSelectNtcNone, &_iconConfig);
        _inputSelectNtc.AddItem(&_textSelectNtc10k, &_iconConfig);
        _inputSelectNtc.AddItem(&_textSelectNtc100k, &_iconConfig);
        _inputSelectNtc.SetItemHeight(12);
        _inputSelectNtc.Visible(false);

        _inputResetCfgConfirm.SetPosition({10, 16, 128 - 20, 32});
        _inputResetCfgConfirm.SetMessageText(&_textResetCfgInputMessage);
        _inputResetCfgConfirm.SetOkText(&_textResetCfgInputOk);
        _inputResetCfgConfirm.SetCancelText(&_textResetCfgInputCancel);
        _inputResetCfgConfirm.Visible(false);

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
        _layout.SetElement(&_inputSelectCooling);
        _layout.SetElement(&_inputSelectNtc);
        _layout.SetElement(&_inputResetCfgConfirm);

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
        if (_isInputShow[0] || _isInputShow[1])
        {
            if (!direction)
                _inputTime.Increase();
            else
                _inputTime.Decrease();
            return;
        }

        if (_isInputShow[2])
        {
            _inputSelectCooling.ChangeActiveByDirection(direction);
            return;
        }
        if (_isInputShow[3])
        {
            _inputSelectNtc.ChangeActiveByDirection(direction);
            return;
        }
        if (_isInputShow[4])
        {
            _inputResetCfgConfirm.Toggle();
            return;
        }

        _list.ChangeActiveByDirection(direction);
    }
    void ScreenConfigDefault::OnEncoderValue(uint32_t value)
    {
    }
    void ScreenConfigDefault::OnButtonClick(uint16_t ButtonPin)
    {
        if (_isInputShow[0] || _isInputShow[1])
        {
            _inputTime.Next();
            return;
        }

        switch (_list.GetActiveItem())
        {
        case 0:
            _hierarchy->SetSelectedItem(SCREEN_CONFIG);
            break;
        case 1:
            _isInputShow[0] = !_isInputShow[0];
            _inputTime.SetSeconds(5);
            _inputTime.SetMinutes(7);
            _inputTime.SetHours(1);
            _inputTime.Visible(_isInputShow[0]);
            break;
        case 2:
            _isInputShow[1] = !_isInputShow[1];
            _inputTime.SetSeconds(2);
            _inputTime.SetMinutes(3);
            _inputTime.SetHours(7);
            _inputTime.Visible(_isInputShow[1]);
            break;
        case 3:
            _soundState = !_soundState;
            if (_soundState)
                _textSound.SetText(_strSoundOn);
            else
                _textSound.SetText(_strSoundOff);
            break;
        case 4:
            _isInputShow[2] = !_isInputShow[2];
            _inputSelectCooling.Visible(_isInputShow[2]);
            break;
        case 5:
            _isInputShow[3] = !_isInputShow[3];
            _inputSelectNtc.Visible(_isInputShow[3]);
            break;
        case 6:
            _isInputShow[4] = !_isInputShow[4];
            _inputResetCfgConfirm.Visible(_isInputShow[4]);
        default:
            break;
        }
    }
    void ScreenConfigDefault::OnButtonLongClick(uint16_t ButtonPin)
    {
        switch (_list.GetActiveItem())
        {
        case 1:
        case 2:
            _isInputShow[0] = false;
            _isInputShow[1] = false;
            _inputTime.Visible(false);
            break;

        default:
            break;
        }
    }
} // namespace gui
