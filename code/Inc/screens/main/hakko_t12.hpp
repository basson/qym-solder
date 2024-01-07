#pragma once

#include <stdlib.h>
#include "string.h"

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "icons/IconHeat12px.h"

#include "types.hpp"

#include "uip/include/text.hpp"
#include "uip/include/bitmap.hpp"

#include "uie/include/tab_page.hpp"

namespace gui
{
    class ScreenHakkoT12
    {
    private:
        char _strCurrent[10] = "120°";
        char _strSet[10] = "set:280°";

        qymos::gui::Text _textCurrent;
        qymos::gui::Text _textSet;
        qymos::gui::Bitmap _iconHeat;

        qymos::gui::TabPage _tabPage;

    public:
        ScreenHakkoT12();

        qymos::gui::TabPage *GetPage();

        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);

        void Process();
        void OnButtonClick();
        void OnButtonLongClick();
    };

} // namespace gui
