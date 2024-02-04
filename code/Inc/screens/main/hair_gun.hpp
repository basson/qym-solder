#pragma once

#include <stdlib.h>
#include "string.h"

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "icons/IconFan12px.h"
#include "icons/IconFlow12px.h"
#include "icons/IconHeat12px.h"

#include "emem.hpp"

#include "gui/types.hpp"

#include "gui/uip/text.hpp"
#include "gui/uip/bitmap.hpp"

#include "gui/uie/tab_page.hpp"

#include "control.hpp"

namespace gui
{
    class ScreenHAirGun
    {
    private:
        char _strTempCurrent[10] = "260°";
        char _strFlowCurrent[10] = "060%";
        char _strTempSet[10] = "set:280°";
        char _strFlowSet[10] = "set:60%";

        qymos::gui::Text _textTempCurrent;
        qymos::gui::Text _textFlowCurrent;
        qymos::gui::Text _textTempSet;
        qymos::gui::Text _textFlowSet;

        qymos::gui::Bitmap _iconHeat;
        qymos::gui::Bitmap _iconFlow;

        qymos::gui::TabPage _tabPage;

        Emem *_emem = Emem::GetInstance();

        bool _isChangeSetTemp = false;
        bool _isChangeSetFlow = false;
        bool _isChange = false;
        bool _isInvertTemp = false;
        bool _isInvertFlow = false;
        uint32_t _millis = 0;

    public:
        ScreenHAirGun();
        qymos::gui::TabPage *GetPage();

        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);

        void Process();
        void OnButtonClick();
        void OnButtonLongClick();
    };
} // namespace gui
