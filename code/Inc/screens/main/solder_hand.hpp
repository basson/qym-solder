#pragma once

#include <stdlib.h>
#include "string.h"

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "icons/IconHeat12px.h"

#include "emem.hpp"

#include "gui/types.hpp"

#include "gui/uip/text.hpp"
#include "gui/uip/bitmap.hpp"

#include "gui/uie/tab_page.hpp"

#include "control.hpp"

namespace gui
{
    class ScreenSolderHand
    {
    private:
        char _strCurrent[10] = "300°";
        char _strSet[10] = "set:280°";

        qymos::gui::Text _textCurrent;
        qymos::gui::Text _textSet;
        qymos::gui::Bitmap _iconHeat;

        qymos::gui::TabPage _tabPage;

        Emem *_emem = Emem::GetInstance();

        bool _isChangeSetTemp = false;
        bool _isInvert = false;
        uint32_t _millis = 0;

    public:
        ScreenSolderHand();

        qymos::gui::TabPage *GetPage();

        void Process();

        void OnEncoderDirection(bool direction);
        void OnButtonClick();
        void OnButtonLongClick();
        void OnEncoderValue(uint32_t value);
    };

} // namespace gui
