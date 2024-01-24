#pragma once
#include "stdint.h"
#include "stm32f1xx_hal.h"

namespace qymos
{
    namespace driver
    {
        class Buzzer
        {
        private:
            GPIO_TypeDef *_port;
            uint16_t _pin;
            bool _direction = true;
        public:
            void Initialize(GPIO_TypeDef *port, uint16_t pin, bool direction = true);
            void On();
            void Off();
        };
        
    } // namespace driver
    
} // namespace qymos
