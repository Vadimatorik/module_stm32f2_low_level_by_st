#include "mc_hardware_interfaces_adc.h"
#include "stm32f2xx_hal_adc.h"
#include "stm32f2xx_hal_rcc.h"

struct adc_one_channel_cfg {
    ADC_TypeDef*        ADCx;
    uint32_t            clock_prescaler;                                // ADC_ClockPrescaler
    uint32_t            resolution;                                     // ADC_Resolution
    uint32_t            data_align;                                     // ADC_Data_align
    uint32_t            channel;                                        // ADC_channels
    uint32_t            sampling_time;                                  // ADC_sampling_times
};

class adc_one_channel : public adc_one_channel_base {
public:
    adc_one_channel( const adc_one_channel_cfg* const cfg );

    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;
    void start_continuous_conversion ( void ) const;
    SPI::FUNC_RESULT get_measurement ( uint32_t& channel_measurement ) const;

private:
    mutable ADC_HandleTypeDef               adc_st;
    mutable ADC_ChannelConfTypeDef          channel_cfg;
};
