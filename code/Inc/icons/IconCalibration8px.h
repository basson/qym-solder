
#pragma once
#include "../lib/qymos-stm32-gui-monochrome/types.hpp"



static uint8_t image_data_IconCalibration8px[8] = {
    0x66, 0xe7, 0xc3, 0x18, 0x18, 0xc3, 0xe7, 0x66
};
const qymos::gui::tImage IconCalibration8px = { image_data_IconCalibration8px, 8, 8,
    8, 8 };
