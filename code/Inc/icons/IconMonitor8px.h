
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconMonitor8px[8] = {
    0x7f, 0x81, 0x81, 0x81, 0xff, 0xff, 0x18, 0x7e
};
const qymos::gui::tImage IconMonitor8px = { image_data_IconMonitor8px, 8, 8,
    8, 8 };
