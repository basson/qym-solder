#pragma once

#include "driver/buzzer.hpp"

namespace qymos
{
    namespace hui
    {
        class Buzzer
        {
        private:
            qymos::driver::Buzzer *_buzzer;

        public:
            void Initialize(qymos::driver::Buzzer *buzzer);
            void Beep(uint32_t millis);
        };

    } // namespace hui

} // namespace qymos
