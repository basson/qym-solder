#pragma once

#include "stm32f1xx_hal.h"

#include "fonts/HellenicaRus8px.h"
#include "icons/IconPid8px.h"

#include "types.hpp"
#include "iscreen.hpp"
#include "hierarchy.hpp"

#include "screens.hpp"

#include "uip/include/text.hpp"

#include "uie/include/progress.hpp"

#include "uie/include/window.hpp"
#include "uie/include/layout.hpp"

namespace gui
{
    class ScreenPidAutoTune : public qymos::gui::IScreen
    {
    private:
        char *_titleStr = "PID Калибровка";
        char *_strCurrent = "Cur:200°";
        char *_strSet = "Set:200°";

        char *_exmpStr = "Идет калибровка...";
    

        qymos::gui::Text _titleText;
        qymos::gui::Text _textCurrent;
        qymos::gui::Text _textSet;
        qymos::gui::Text _exmpText;

        qymos::gui::Bitmap _iconPidAutoTune;

        qymos::gui::Progress _progress;

        qymos::gui::Window _window;

        qymos::gui::Layout _layout;

        qymos::gui::Hierarchy *_hierarchy = qymos::gui::Hierarchy::GetInstance();

        static Screen _backScreenId;

        uint32_t _millis;
        uint8_t _load = 0;

    public:
        ScreenPidAutoTune();

        static void SetBackScreen(Screen screen);

        qymos::gui::IElement *GetPage();
        void Process();
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
        void OnButtonClick(uint16_t ButtonPin = 0);
        void OnButtonLongClick(uint16_t ButtonPin = 0);
    };

} // namespace gui
