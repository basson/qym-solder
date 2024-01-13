
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconReset8px[8] = {
    0x3e, 
    0x40, 
    0x42, 
    0xf7, 
    0xef, 
    0x42, 
    0x02, 
    0x7c
};
const qymos::gui::tImage IconReset8px = { image_data_IconReset8px, 8, 8,
    8, 8 };
