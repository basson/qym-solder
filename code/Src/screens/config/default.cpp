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

        _textResetNotification.SetFont(&HellenicaRus8px);
        _textResetNotification.SetText(_strResetNotification);

        _iconConfig.SetImage(&IconConfig8px);
        _iconBack.SetImage(&IconBack8px);
        _iconClock.SetImage(&IconClock8px);
        _iconSound.SetImage(&IconSound8px);
        _iconNtc.SetImage(&IconNtc8px);
        _iconCooling.SetImage(&IconCooling8px);
        _iconReset.SetImage(&IconReset8px);
        _iconRadioBoxOn.SetImage(&IconRadioBoxOn8px);
        _iconRadioBoxOff.SetImage(&IconRadioBoxOff8px);

        _checkBox.SetImageCheck(&_iconRadioBoxOn);
        _checkBox.SetImageUncheck(&_iconRadioBoxOff);
        _checkBox.SetPosition({0, 0, 8, 8});

        _inputTime.SetFont(&HellenicaRus8px);
        _inputTime.SetPosition({20, 16, 88, 64 - 32});
        _inputTime.Visible(false);

        _inputSelectCooling.SetPosition({20, 16, 128 - 40, 28});
        _inputSelectCooling.SetItemHeight(12);
        _inputSelectCooling.AddItem(&_textSelectCoolingAlways, &_checkBox);
        _inputSelectCooling.AddItem(&_textSelectCoolingNtc, &_checkBox);
        _inputSelectCooling.Visible(false);

        _inputSelectNtc.SetPosition({30, 16, 128 - 60, 28});
        _inputSelectNtc.AddItem(&_textSelectNtcNone, &_checkBox);
        _inputSelectNtc.AddItem(&_textSelectNtc10k, &_checkBox);
        _inputSelectNtc.AddItem(&_textSelectNtc100k, &_checkBox);
        _inputSelectNtc.SetItemHeight(12);
        _inputSelectNtc.Visible(false);

        _inputResetCfgConfirm.SetPosition({10, 16, 128 - 20, 32});
        _inputResetCfgConfirm.SetMessageText(&_textResetCfgInputMessage);
        _inputResetCfgConfirm.SetOkText(&_textResetCfgInputOk);
        _inputResetCfgConfirm.SetCancelText(&_textResetCfgInputCancel);
        _inputResetCfgConfirm.Visible(false);

        _messageResetNotification.SetPosition({0, 16, 128, 32});
        _messageResetNotification.SetMessageText(&_textResetNotification);
        _messageResetNotification.Visible(false);

        _list.SetPosition({2, 13, 124, 49});
        _list.SetItemHeight(12);
        _list.AddItem(&_textBack, &_iconBack);
        _list.AddItem(&_textTimeOff, &_iconClock);
        _list.AddItem(&_textTimeShutdown, &_iconClock);
        _list.AddItem(&_textSound, &_iconSound);
        _list.AddItem(&_textCooling, &_iconCooling);
        _list.AddItem(&_textNtc, &_iconNtc);
        _list.AddItem(&_textResetCfg, &_iconReset);

        _layout.SetPosition({2, 13, 124, 49});
        _layout.SetElement(&_list);
        _layout.SetElement(&_inputTime);
        _layout.SetElement(&_inputSelectCooling);
        _layout.SetElement(&_inputSelectNtc);
        _layout.SetElement(&_inputResetCfgConfirm);
        _layout.SetElement(&_messageResetNotification);

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
        if (_emem->Param().defaultSound)
            _textSound.SetText(_strSoundOn);
        else
            _textSound.SetText(_strSoundOff);
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
        if (_isInputShow[4] && !_isInputShow[5])
        {
            _inputResetCfgConfirm.Toggle();
            return;
        }
        if(_isInputShow[5])
        {
            _isInputShow[5] = false;
            _messageResetNotification.Visible(_isInputShow[5]);
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
            _inputTime.SetSeconds(_emem->Param().defaultTimeOff[2]);
            _inputTime.SetMinutes(_emem->Param().defaultTimeOff[1]);
            _inputTime.SetHours(_emem->Param().defaultTimeOff[0]);
            _inputTime.Visible(_isInputShow[0]);
            break;
        case 2:
            _isInputShow[1] = !_isInputShow[1];
            _inputTime.SetSeconds(_emem->Param().defaultTimeShutdown[2]);
            _inputTime.SetMinutes(_emem->Param().defaultTimeShutdown[1]);
            _inputTime.SetHours(_emem->Param().defaultTimeShutdown[0]);
            _inputTime.Visible(_isInputShow[1]);
            break;
        case 3:
            _emem->Param().defaultSound = !_emem->Param().defaultSound;
            _emem->Save();
            break;
        case 4:
            if (!_isInputShow[2])
            {
                _inputSelectCooling.SetActiveItem(_emem->Param().defualtCooling);
                _inputSelectCooling.SetAllItemCheck(false);
                _inputSelectCooling.SetItemCheck(_emem->Param().defualtCooling, true);
                _isInputShow[2] = true;
            }
            else
            {
                _inputSelectCooling.SetAllItemCheck(false);
                _inputSelectCooling.SetItemCheck(_inputSelectCooling.GetActiveItem(), true);
                _emem->Param().defualtCooling = _inputSelectCooling.GetActiveItem();
            }
            _inputSelectCooling.Visible(_isInputShow[2]);
            break;
        case 5:
            if (!_isInputShow[3])
            {
                _inputSelectNtc.SetActiveItem(_emem->Param().defaultNtc);
                _inputSelectNtc.SetAllItemCheck(false);
                _inputSelectNtc.SetItemCheck(_emem->Param().defaultNtc, true);
                _isInputShow[3] = true;
            }
            else
            {
                _inputSelectNtc.SetAllItemCheck(false);
                _inputSelectNtc.SetItemCheck(_inputSelectNtc.GetActiveItem(), true);
                _emem->Param().defaultNtc = _inputSelectNtc.GetActiveItem();
            }
            _inputSelectNtc.Visible(_isInputShow[3]);
            break;
        case 6:
            if (!_isInputShow[4] && !_isInputShow[5])
            {
                _inputResetCfgConfirm.SetVariant(qymos::gui::InputDialog::VARIANT_CANCEL);
                _isInputShow[4] = true;
            }
            else if(_isInputShow[4] && !_isInputShow[5])
            {
                if (_inputResetCfgConfirm.GetResult())
                {
                    _emem->WriteDefault();
                    _isInputShow[5] = true;
                }
                
                _isInputShow[4] = false;
            }
            else
                _isInputShow[5] = false;
            _inputResetCfgConfirm.Visible(_isInputShow[4]);
            _messageResetNotification.Visible(_isInputShow[5]);
            break;
        default:
            break;
        }
    }
    void ScreenConfigDefault::OnButtonLongClick(uint16_t ButtonPin)
    {
        switch (_list.GetActiveItem())
        {
        case 1:
            _isInputShow[0] = false;
            _emem->Param().defaultTimeOff[2] = _inputTime.GetSeconds();
            _emem->Param().defaultTimeOff[1] = _inputTime.GetMinutes();
            _emem->Param().defaultTimeOff[0] = _inputTime.GetHours();
            _emem->Save();
            _inputTime.Visible(_isInputShow[0]);
            break;
        case 2:
            _isInputShow[1] = false;
            _emem->Param().defaultTimeShutdown[2] = _inputTime.GetSeconds();
            _emem->Param().defaultTimeShutdown[1] = _inputTime.GetMinutes();
            _emem->Param().defaultTimeShutdown[0] = _inputTime.GetHours();
            _emem->Save();
            _inputTime.Visible(_isInputShow[1]);
            break;
        case 4:
            _isInputShow[2] = false;
            _emem->Save();
            _inputSelectCooling.Visible(_isInputShow[2]);
            break;
        case 5:
            _isInputShow[3] = false;
            _emem->Save();
            _inputSelectNtc.Visible(_isInputShow[3]);
            break;
        default:
            break;
        }
    }
} // namespace gui
