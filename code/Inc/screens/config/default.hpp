#pragma once

#include "fonts/HellenicaRus8px.h"

#include "icons/IconConfig8px.h"
#include "icons/IconBack8px.h"
#include "icons/IconClock8px.h"
#include "icons/IconSound8px.h"
#include "icons/IconNtc8px.h"
#include "icons/IconCooling8px.h"
#include "icons/IconReset8px.h"
#include "icons/IconRadioBoxOn8px.h"
#include "icons/IconRadioBoxOff8px.h"

#include "emem.hpp"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"
#include "gui/hierarchy.hpp"

#include "screens.hpp"

#include "gui/uip/text.hpp"

#include "gui/uie/window.hpp"
#include "gui/uie/layout.hpp"
#include "gui/uie/list.hpp"
#include "gui/uie/input_time.hpp"
#include "gui/uie/input_select.hpp"
#include "gui/uie/input_dialog.hpp"
#include "gui/uie/checkbox.hpp"
#include "gui/uie/message.hpp"

namespace gui
{
    class ScreenConfigDefault : public qymos::gui::IScreen
    {
    private:
        char *_titleStr = "Основные";

        char *_strBack = "Назад";
        char *_strTimeOff = "Время откл";
        char *_strTimeShutdown = "Время выкл";
        char *_strSoundOn = "Звук вкл";
        char *_strSoundOff = "Звук выкл";
        char *_strCooling = "Охлаждение";
        char *_strNtc = "NTC термистр";
        char *_strResetCfg = "Сбросить настройки";
        char *_strResetNotification = "Настройки сброшены!";


        char *_strSelectCoolingNtc = "Ntc";
        char *_strSelectCoolingAlways = "Постоянно";

        char *_strSelectNtcNone = "Нет";
        char *_strSelectNtc10K = "10К";
        char *_strSelectNtc100k = "100K";

        char *_strResetCfgInputMessage = "Вы уверены?";
        char *_strResetCfgInputOk = "Да";
        char *_strResetCfgInputCancel = "Нет";

        qymos::gui::Text _titleText;
        qymos::gui::Text _textBack;
        qymos::gui::Text _textTimeOff;
        qymos::gui::Text _textTimeShutdown;
        qymos::gui::Text _textSound;
        qymos::gui::Text _textCooling;
        qymos::gui::Text _textNtc;
        qymos::gui::Text _textResetCfg;

        qymos::gui::Text _textSelectCoolingNtc;
        qymos::gui::Text _textSelectCoolingAlways;

        qymos::gui::Text _textSelectNtcNone;
        qymos::gui::Text _textSelectNtc10k;
        qymos::gui::Text _textSelectNtc100k;

        qymos::gui::Text _textResetCfgInputMessage;
        qymos::gui::Text _textResetCfgInputOk;
        qymos::gui::Text _textResetCfgInputCancel;

        qymos::gui::Text _textResetNotification;

        qymos::gui::Bitmap _iconConfig;
        qymos::gui::Bitmap _iconBack;
        qymos::gui::Bitmap _iconClock;
        qymos::gui::Bitmap _iconSound;
        qymos::gui::Bitmap _iconNtc;
        qymos::gui::Bitmap _iconCooling;
        qymos::gui::Bitmap _iconReset;
        qymos::gui::Bitmap _iconRadioBoxOn;
        qymos::gui::Bitmap _iconRadioBoxOff;


        qymos::gui::CheckBox _checkBox;

        qymos::gui::InputTime _inputTime;
        qymos::gui::InputSelect _inputSelectCooling;
        qymos::gui::InputSelect _inputSelectNtc;
        qymos::gui::InputDialog _inputResetCfgConfirm;

        qymos::gui::Message _messageResetNotification;

        qymos::gui::Window _window;

        qymos::gui::Layout _layout;
        qymos::gui::List _list;

        qymos::gui::Hierarchy *_hierarchy = qymos::gui::Hierarchy::GetInstance();

        Emem *_emem = Emem::GetInstance();

        bool _isInputShow[6] = {
            false,
        };


    public:
        ScreenConfigDefault();

        qymos::gui::IElement *GetPage();
        void Process();
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
        void OnButtonClick(uint16_t ButtonPin = 0);
        void OnButtonLongClick(uint16_t ButtonPin = 0);
    };

} // namespace gui
