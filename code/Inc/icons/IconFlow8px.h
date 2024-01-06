
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconFlow8px[8] = {
    0x08, 0xb2, 0xc2, 0x9c, 0x80, 0xe4, 0x92, 0x20
};
const qymos::gui::tImage IconFlow8px = { image_data_IconFlow8px, 8, 8,
    8, 8 };
