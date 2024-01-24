#include "hui/buzzer.hpp"

namespace qymos
{
    namespace hui
    {
        void Buzzer::Initialize(qymos::driver::Buzzer *buzzer)
        {
            _buzzer = buzzer;
        }
        void Buzzer::Beep(uint32_t millis)
        {
            _buzzer->On();
            HAL_Delay(millis);
            _buzzer->Off();
        }
    } // namespace hui

} // namespace qymos
