#pragma once

#include "fonts/HellenicaRus8px.h"

#include "icons/IconConfig8px.h"
#include "icons/IconBack8px.h"
#include "icons/IconClock8px.h"
#include "icons/IconSound8px.h"

#include "types.hpp"
#include "iscreen.hpp"
#include "hierarchy.hpp"

#include "screens.hpp"

#include "uip/include/text.hpp"

#include "uie/include/window.hpp"
#include "uie/include/layout.hpp"
#include "uie/include/list.hpp"
#include "uie/include/input_time.hpp"

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

        qymos::gui::Text _titleText;
        qymos::gui::Text _textBack;
        qymos::gui::Text _textTimeOff;
        qymos::gui::Text _textTimeShutdown;
        qymos::gui::Text _textSound;
        qymos::gui::Text _textCooling;
        qymos::gui::Text _textNtc;
        qymos::gui::Text _textResetCfg;

        qymos::gui::Bitmap _iconConfig;
        qymos::gui::Bitmap _iconBack;
        qymos::gui::Bitmap _iconClock;
        qymos::gui::Bitmap _iconSound;

        qymos::gui::InputTime _inputTime;

        qymos::gui::Window _window;

        qymos::gui::Layout _layout;
        qymos::gui::List _list;

        qymos::gui::Hierarchy *_hierarchy = qymos::gui::Hierarchy::GetInstance();

        int8_t _activeItem = 0;

        bool _isInputShow[5] = {
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
