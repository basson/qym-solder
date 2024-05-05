#pragma once


#include "stm32f1xx_hal.h"

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "icons/Logo15x22px.h"
#include "icons/Warning24x24px.h"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"

#include "gui/uip/text.hpp"
#include "gui/uip/bitmap.hpp"
#include "gui/uie/layout.hpp"

#include "control.hpp"

namespace gui
{
    class ScreenShutdown : public qymos::gui::IScreen
    {
    private:
        char _strBye[21] = "Выключение";
        char _strWarning[21] = "Охлаждение";

        qymos::gui::Text _textBye;

        qymos::gui::Bitmap _icon;

        qymos::gui::Layout _layout;

    public:
        ScreenShutdown();
        qymos::gui::IElement *GetPage();
        void Process();
        void OnButtonClick(uint16_t pin = 0);
        void OnButtonLongClick(uint16_t pin = 0);
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
        
    };

} // namespace gui