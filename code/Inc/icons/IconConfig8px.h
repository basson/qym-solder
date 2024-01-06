
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconConfig8px[8] = {
    0x18, 0x7e, 0x66, 0xdb, 0xdb, 0x66, 0x7e, 0x18
};
const qymos::gui::tImage IconConfig8px = { image_data_IconConfig8px, 8, 8,
    8, 8 };
