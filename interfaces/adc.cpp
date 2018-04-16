#include "adc.h"

AdcOneChannel::AdcOneChannel( const AdcOneChannelCfg* const cfg ) {
	this->adc.Instance					= cfg->ADCx;
	this->adc.Init.ClockPrescaler		= cfg->clockPrescaler;
	this->adc.Init.Resolution			= cfg->resolution;
	this->adc.Init.DataAlign			= cfg->dataAlign;
	this->adc.Init.ScanConvMode			= DISABLE;
	this->adc.Init.ContinuousConvMode	= ENABLE;
	this->adc.Init.DiscontinuousConvMode= DISABLE;
	this->adc.Init.ExternalTrigConv		= ADC_SOFTWARE_START;
	this->adc.Init.ExternalTrigConvEdge	= ADC_EXTERNALTRIGCONVEDGE_NONE;
	this->adc.Init.NbrOfConversion		= 1;
	this->adc.Init.DMAContinuousRequests= DISABLE;
	this->adc.Init.EOCSelection			= ADC_EOC_SEQ_CONV;

	this->channelCfg.Channel			= cfg->channel;
	this->channelCfg.Rank				= 1;
	this->channelCfg.SamplingTime		= cfg->samplingTime;
}

bool AdcOneChannel::reinit ( void ) const {
	this->clkEnable();
	HAL_ADC_DeInit( &this->adc );

	HAL_StatusTypeDef r;
	r = HAL_ADC_Init( &this->adc );
	if ( r != HAL_OK ) return false;
	r = HAL_ADC_ConfigChannel( &this->adc, &this->channelCfg );
	if ( r != HAL_OK ) return false;

	return true;
}

void AdcOneChannel::clkEnable ( void ) const {
	switch( ( uint32_t )this->adc.Instance ) {
		case ADC1_BASE: __HAL_RCC_ADC1_CLK_ENABLE(); break;
		case ADC2_BASE: __HAL_RCC_ADC2_CLK_ENABLE(); break;
		case ADC3_BASE: __HAL_RCC_ADC3_CLK_ENABLE(); break;
	}
}

void AdcOneChannel::clkDisable ( void ) const {
	switch( ( uint32_t )this->adc.Instance ) {
		case ADC1_BASE:	__HAL_RCC_ADC1_CLK_DISABLE(); break;
		case ADC2_BASE:	__HAL_RCC_ADC2_CLK_DISABLE(); break;
		case ADC3_BASE:	__HAL_RCC_ADC3_CLK_DISABLE(); break;
	}
}

bool AdcOneChannel::startContinuousConversion ( void ) const {
	HAL_StatusTypeDef r;
	r = HAL_ADC_Start( &this->adc );
	if ( r != HAL_OK ) return false;
	return true;
}

bool AdcOneChannel::stopContinuousConversion ( void ) const {
	HAL_StatusTypeDef r;
	r = HAL_ADC_Stop( &this->adc );
	if ( r != HAL_OK ) return false;
	return true;
}

void AdcOneChannel::getMeasurement ( uint32_t& channelMeasurement ) const {
	channelMeasurement = HAL_ADC_GetValue( &this->adc );
}

void AdcOneChannel::irqHandler ( void ) const {
	this->adc.Instance->SR = 0;
}
