#pragma once

#include "fonts/HellenicaRus16px.h"
#include "fonts/HellenicaRus12px.h"
#include "fonts/HellenicaRus8px.h"

#include "icons/IconConfig8px.h"
#include "icons/IconBack8px.h"
#include "icons/IconMonitor8px.h"
#include "icons/IconT128px.h"
#include "icons/IconD8928px.h"
#include "icons/IconFan8px.h"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"
#include "gui/hierarchy.hpp"

#include "screens.hpp"

#include "gui/uip/text.hpp"

#include "gui/uie/window.hpp"
#include "gui/uie/layout.hpp"
#include "gui/uie/list.hpp"

namespace gui
{
    class ScreenConfig : public qymos::gui::IScreen
    {
    private:
        char _titleStr[19] = "Настройки";
        char _strBack[11] = "Назад";
        char _strDefault[17] = "Основные";
        char _strHacckoT12[10] = "Hakko t12";
        char _strSolderHand[12] = "Solder hand";
        char _strHiarGun[11] = "Hotair gun";
        

        qymos::gui::Text _titleText;
        qymos::gui::Text _textBack;
        qymos::gui::Text _textDefault;
        qymos::gui::Text _textHakkoT12;
        qymos::gui::Text _textSolderHand;
        qymos::gui::Text _textHairGun;

        qymos::gui::Bitmap _iconConfig;
        qymos::gui::Bitmap _iconBack;
        qymos::gui::Bitmap _iconDefault;
        qymos::gui::Bitmap _iconHakkoT12;
        qymos::gui::Bitmap _iconHiarGun;
        qymos::gui::Bitmap _iconSolderHand;

        qymos::gui::Window _window;

        qymos::gui::Layout _layout;
        qymos::gui::List _list;

        qymos::gui::Hierarchy *_hierarchy = qymos::gui::Hierarchy::GetInstance();

    public:
        ScreenConfig();
        qymos::gui::IElement *GetPage();
        void Process();
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
        void OnButtonClick(uint16_t ButtonPin = 0);
        void OnButtonLongClick(uint16_t ButtonPin = 0);
    };

} // namespace gui
