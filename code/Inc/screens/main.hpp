#pragma once

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "types.hpp"
#include "iscreen.hpp"

#include "uip/include/text.hpp"

#include "uie/include/tab.hpp"
#include "uie/include/tab_bar.hpp"
#include "uie/include/tab_layout.hpp"
#include "uie/include/tab_page.hpp"

#include "screens/main/haccko_t12.hpp"
#include "screens/main/soldering_iron.hpp"
#include "screens/main/hair_gun.hpp"

namespace gui
{
    class ScreenMain : public qymos::gui::IScreen
    {
    private:
        char *_strT12 = "T12";
        char *_strHair = "HAIR";
        char *_strIron = "IRON";

        qymos::gui::Text _textT12;
        qymos::gui::Text _textHair;
        qymos::gui::Text _textIron;

        qymos::gui::TabLayout _tabLayout;

        int8_t _activeTab = 0;
        
        ScreenHacckoT12 _screenHacckoT12;
        ScreenSolderingIron _screenIron;
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
