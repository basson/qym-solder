#pragma once

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"

#include "gui/uip/text.hpp"

#include "gui/uie/tab.hpp"
#include "gui/uie/tab_bar.hpp"
#include "gui/uie/tab_layout.hpp"
#include "gui/uie/tab_page.hpp"

#include "screens/main/hakko_t12.hpp"
#include "screens/main/solder_hand.hpp"
#include "screens/main/hair_gun.hpp"

namespace gui
{
    class ScreenMain : public qymos::gui::IScreen
    {
    private:
        char _strT12[4] = "T12";
        char _strHair[5] = "HAIR";
        char _strIron[5] = "IRON";

        qymos::gui::Text _textT12;
        qymos::gui::Text _textHair;
        qymos::gui::Text _textIron;

        qymos::gui::TabLayout _tabLayout;

        int8_t _activeTab = 0;
        bool _isActiveEdit = false;
        
        ScreenHakkoT12 _screenHakkoT12;
        ScreenSolderHand _screenIron;
        ScreenHAirGun _screenHair;

    public:
        ScreenMain();
        qymos::gui::IElement *GetPage();
        void Process();
        void OnButtonClick(uint16_t pin = 0);
        void OnButtonLongClick(uint16_t pin = 0);
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
    };

} // namespace gui
