#pragma once

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "icons/Logo15x22px.h"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"


#include "gui/uip/text.hpp"
#include "gui/uip/bitmap.hpp"
#include "gui/uie/layout.hpp"

namespace gui
{
    class ScreenStartup : public qymos::gui::IScreen
    {
    private:
        char _strLogo[11] = "qumis.tech";

        qymos::gui::Text _textLogo;

        qymos::gui::Bitmap _iconLogo;

        qymos::gui::Layout _layout;

    public:
        ScreenStartup();
        qymos::gui::IElement *GetPage();
        void Process();
        void OnButtonClick(uint16_t pin = 0);
        void OnButtonLongClick(uint16_t pin = 0);
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
    };

} // namespace gui