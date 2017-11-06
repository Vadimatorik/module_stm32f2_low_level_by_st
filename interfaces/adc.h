#include "mc_hardware_interfaces_adc.h"

class adc_one_channel : public adc_one_channel_base {
public:
    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;
    void start_continuous_conversion( void ) const;
    SPI::FUNC_RESULT get_measurement ( uint32_t& channel_measurement ) const;
};
