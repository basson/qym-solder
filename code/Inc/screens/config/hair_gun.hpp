#pragma once

#include "fonts/HellenicaRus8px.h"

#include "icons/IconFan8px.h"
#include "icons/IconBack8px.h"
#include "icons/IconCalibration8px.h"
#include "icons/IconSens8px.h"
#include "icons/IconCooling8px.h"
#include "icons/IconTemp8px.h"
#include "icons/IconNtc8px.h"
#include "icons/IconPid8px.h"
#include "icons/IconRadioBoxOn8px.h"
#include "icons/IconRadioBoxOff8px.h"

#include "emem.hpp"

#include "gui/types.hpp"
#include "gui/iscreen.hpp"
#include "gui/hierarchy.hpp"

#include "screens.hpp"

#include "pid_autotune.hpp"

#include "gui/uip/text.hpp"

#include "gui/uie/checkbox.hpp"

#include "gui/uie/input_int.hpp"
#include "gui/uie/input_select.hpp"

#include "gui/uie/window.hpp"
#include "gui/uie/layout.hpp"
#include "gui/uie/list.hpp"

namespace gui
{
    class ScreenConfigHairGun : public qymos::gui::IScreen
    {
    private:
        char _titleStr[9] = "Hair Gun";

        char _strBack[11] = "Назад";
        char _strTempCalibrate[31] = "Калибровка темп.";
        char _strTempMin[31] = "Мин. Температура";
        char _strTempMax[33] = "Макс. Температура";
        char _strFlowMin[19] = "Мин. Поток";
        char _strFlowMax[21] = "Макс. Поток";
        char _strSensorOn[22] = "Сенсор Есть";
        char _strSensorOff[22] = "Сенсора Нет";
        char _strPidTune[25] = "Калибровка PID";
        char _strNtcResistens[21] = "NTC термистр";

        char _strSelectNtcNone[7] = "Нет";
        char _strSelectNtc10K[5] = "10К";
        char _strSelectNtc100k[5] = "100K";

        qymos::gui::Text _titleText;
        qymos::gui::Text _textBack;
        qymos::gui::Text _textTempCalibrate;
        qymos::gui::Text _textTempMin;
        qymos::gui::Text _textTempMax;
        qymos::gui::Text _textFlowMin;
        qymos::gui::Text _textFlowMax;
        qymos::gui::Text _textSensor;
        qymos::gui::Text _textPidTune;
        qymos::gui::Text _textNtsResistens;

        qymos::gui::Text _textSelectNtcNone;
        qymos::gui::Text _textSelectNtc10k;
        qymos::gui::Text _textSelectNtc100k;

        qymos::gui::Bitmap _iconHairGun;
        qymos::gui::Bitmap _iconCalibrate;
        qymos::gui::Bitmap _iconBack;
        qymos::gui::Bitmap _iconSens;
        qymos::gui::Bitmap _iconFlow;
        qymos::gui::Bitmap _iconTemp;
        qymos::gui::Bitmap _iconNtc;
        qymos::gui::Bitmap _iconPid;
        qymos::gui::Bitmap _iconRadioBoxOn;
        qymos::gui::Bitmap _iconRadioBoxOff;

        qymos::gui::CheckBox _checkBox;

        qymos::gui::InputInt _inputInt;
        qymos::gui::InputSelect _inputSelectNtc;

        qymos::gui::Window _window;

        qymos::gui::Layout _layout;
        qymos::gui::List _list;

        qymos::gui::Hierarchy *_hierarhy = qymos::gui::Hierarchy::GetInstance();

        Emem *_emem = Emem::GetInstance();

        bool _isInputShow[6]{
            false,
        };

    public:
        ScreenConfigHairGun();
        qymos::gui::IElement *GetPage();
        void Process();
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
        void OnButtonClick(uint16_t ButtonPin = 0);
        void OnButtonLongClick(uint16_t ButtonPin = 0);
    };

} // namespace gui
