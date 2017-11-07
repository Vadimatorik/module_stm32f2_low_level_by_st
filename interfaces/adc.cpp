#include "adc.h"

void adc_one_channel::reinit ( void ) const {

}

void adc_one_channel::on ( void ) const {

}

void adc_one_channel::off ( void ) const {

}

void adc_one_channel::start_continuous_conversion ( void ) const {

}

SPI::FUNC_RESULT adc_one_channel::get_measurement ( uint32_t& channel_measurement ) const {
    ( void )channel_measurement;
    return SPI::FUNC_RESULT::OK;
}
