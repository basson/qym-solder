
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconClock8px[8] = {
    0x18, 0x66, 0x42, 0x89, 0x99, 0x42, 0x66, 0x18
};
const qymos::gui::tImage IconClock8px = { image_data_IconClock8px, 8, 8,
    8, 8 };
