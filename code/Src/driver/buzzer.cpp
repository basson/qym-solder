#include "driver/buzzer.hpp"

namespace qymos
{
    namespace driver
    {
        void Buzzer::Initialize(GPIO_TypeDef *port, uint16_t pin, bool direction)
        {
            _port = port;
            _pin = pin;
            _direction = direction;
            HAL_GPIO_WritePin(_port, _pin, (GPIO_PinState)!_direction);
        }
        void Buzzer::On()
        {
            HAL_GPIO_WritePin(_port, _pin, (GPIO_PinState)_direction);
        }
        void Buzzer::Off()
        {
            HAL_GPIO_WritePin(_port, _pin, (GPIO_PinState)!_direction);
        }
    } // namespace driver

} // namespace qymos
