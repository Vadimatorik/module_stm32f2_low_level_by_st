#include "adc.h"

adc_one_channel::adc_one_channel( const adc_one_channel_cfg* const cfg ) {
    this->adc_st.Instance                     = cfg->ADCx;
    this->adc_st.Init.ClockPrescaler          = cfg->clock_prescaler;
    this->adc_st.Init.Resolution              = cfg->resolution;
    this->adc_st.Init.DataAlign               = cfg->data_align;
    this->adc_st.Init.ScanConvMode            = DISABLE;
    this->adc_st.Init.EOCSelection            = ADC_EOC_SINGLE_CONV;
    this->adc_st.Init.ContinuousConvMode      = DISABLE;
    this->adc_st.Init.NbrOfConversion         = 1;
    this->adc_st.Init.ExternalTrigConv        = ADC_SOFTWARE_START;
    this->adc_st.Init.DMAContinuousRequests   = DISABLE;

    this->channel_cfg.Channel               = cfg->channel;
    this->channel_cfg.Rank                  = 1;
    this->channel_cfg.SamplingTime          = cfg->sampling_time;
}

void adc_one_channel::reinit ( void ) const {
    HAL_ADC_DeInit( &this->adc_st );
    HAL_ADC_Init( &this->adc_st );
    HAL_ADC_ConfigChannel( &this->adc_st, &this->channel_cfg );
}

void adc_one_channel::on ( void ) const {
    switch( ( uint32_t )this->adc_st.Instance ) {
        case ADC1_BASE: __HAL_RCC_ADC1_CLK_ENABLE(); break;
        case ADC2_BASE: __HAL_RCC_ADC2_CLK_ENABLE(); break;
        case ADC3_BASE: __HAL_RCC_ADC3_CLK_ENABLE(); break;
    }
}

void adc_one_channel::off ( void ) const {
    switch( ( uint32_t )this->adc_st.Instance ) {
        case ADC1_BASE: __HAL_RCC_ADC1_CLK_DISABLE(); break;
        case ADC2_BASE: __HAL_RCC_ADC2_CLK_DISABLE(); break;
        case ADC3_BASE: __HAL_RCC_ADC3_CLK_DISABLE(); break;
    }
}

void adc_one_channel::start_continuous_conversion ( void ) const {
    HAL_ADC_Start( &this->adc_st );
}

SPI::FUNC_RESULT adc_one_channel::get_measurement ( uint32_t& channel_measurement ) const {
    channel_measurement = HAL_ADC_GetValue( &this->adc_st );
    return SPI::FUNC_RESULT::OK;
}
