#pragma once

#include "fonts/HellenicaRus8px.h"

#include "icons/IconT128px.h"
#include "icons/IconBack8px.h"
#include "icons/IconCalibration8px.h"
#include "icons/IconSens8px.h"
#include "icons/IconSleep8px.h"
#include "icons/IconTemp8px.h"

#include "types.hpp"
#include "iscreen.hpp"
#include "hierarchy.hpp"

#include "screens.hpp"

#include "uip/include/text.hpp"

#include "uie/include/input_time.hpp"
#include "uie/include/input_int.hpp"

#include "uie/include/window.hpp"
#include "uie/include/layout.hpp"
#include "uie/include/list.hpp"

namespace gui
{
    class ScreenConfigHakkoT12 : public qymos::gui::IScreen
    {
    private:
        char *_titleStr = "Hakko T12";

        char *_strBack = "Назад";
        char *_strTempCalibrate = "Калибровка темп.";
        char *_strTempMin = "Мин. Температура";
        char *_strTempMax = "Макс. Температура";
        char *_strSensorOn = "Сенсор Есть";
        char *_strSensorOff = "Сенсора Нет";
        char *_strTimeSleep = "Время погр в сон";
        char *_strTempSleep = "Темп во время сна";
        char *_strPidTune = "Калибровка PID";
        char *_strNtcResistens = "NTC термистр";

        qymos::gui::Text _titleText;
        qymos::gui::Text _textBack;
        qymos::gui::Text _textTempCalibrate;
        qymos::gui::Text _textTempMin;
        qymos::gui::Text _textTempMax;
        qymos::gui::Text _textSensor;
        qymos::gui::Text _textTimeSleep;
        qymos::gui::Text _textTempSleep;
        qymos::gui::Text _textPidTune;
        qymos::gui::Text _textNtsResistens;

        qymos::gui::Bitmap _iconT12;
        qymos::gui::Bitmap _iconCalibrate;
        qymos::gui::Bitmap _iconBack;
        qymos::gui::Bitmap _iconSens;
        qymos::gui::Bitmap _iconSleep;
        qymos::gui::Bitmap _iconTemp;

        qymos::gui::InputTime _inputTime;
        qymos::gui::InputInt _inputInt;

        qymos::gui::Window _window;

        qymos::gui::Layout _layout;
        qymos::gui::List _list;

        qymos::gui::Hierarchy *_hierarhy = qymos::gui::Hierarchy::GetInstance();

        int8_t _activeItem = 0;

    public:
        ScreenConfigHakkoT12();
        qymos::gui::IElement *GetPage();
        void Process();
        void OnEncoderDirection(bool direction);
        void OnEncoderValue(uint32_t value);
        void OnButtonClick(uint16_t ButtonPin = 0);
        void OnButtonLongClick(uint16_t ButtonPin = 0);
    };

} // namespace gui
