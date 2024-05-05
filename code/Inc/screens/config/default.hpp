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
        char _titleStr[17] = "Основные";

        char _strBack[11] = "Назад";
        char _strTimeOff[20] = "Время откл";
        char _strTimeShutdown[20] = "Время выкл";
        char _strSoundOn[16] = "Звук вкл";
        char _strSoundOff[18] = "Звук выкл";
        char _strCooling[21] = "Охлаждение";
        char _strNtc[21] = "NTC термистр";
        char _strResetCfg[36] = "Сбросить настройки";
        char _strResetNotification[37] = "Настройки сброшены!";


        char _strSelectCoolingNtc[4] = "Ntc";
        char _strSelectCoolingAlways[19] = "Постоянно";

        char _strSelectNtcNone[7] = "Нет";
        char _strSelectNtc10K[5] = "10К";
        char _strSelectNtc100k[5] = "100K";

        char _strResetCfgInputMessage[21] = "Вы уверены?";
        char _strResetCfgInputOk[5] = "Да";
        char _strResetCfgInputCancel[7] = "Нет";

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
