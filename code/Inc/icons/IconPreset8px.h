
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconPreset8px[8] = {
    0xfe, 0xb5, 0xb5, 0xbd, 0x81, 0xbd, 0xc3, 0xff
};
const qymos::gui::tImage IconPreset8px = { image_data_IconPreset8px, 8, 8,
    8, 8 };
