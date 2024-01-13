
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconPid8px[8] = {
    0x00, 
    0x42, 
    0x66, 
    0x99, 
    0x66, 
    0x42, 
    0x18, 
    0xe7
};
const qymos::gui::tImage IconPid8px = { image_data_IconPid8px, 8, 8,
    8, 8 };
