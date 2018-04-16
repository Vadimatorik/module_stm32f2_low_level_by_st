#include "dac.h"

Dac::Dac( const DacCfg* const cfg ) {
	this->dac.Instance = DAC;
	this->dacCh.DAC_Trigger						= DAC_TRIGGER_NONE;
	this->dacCh.DAC_OutputBuffer				= cfg->buffer;
}

bool Dac::reinit ( void )	const {
	this->clkDisable();
	this->clkEnable();

	if ( HAL_DAC_DeInit( &this->dac ) != HAL_OK )
		return false;

	if ( HAL_DAC_Init( &this->dac ) != HAL_OK )
		return false;

	if ( HAL_DAC_ConfigChannel( &this->dac, &this->dacCh, DAC_CHANNEL_1 ) != HAL_OK)
		return false;

	if ( HAL_DAC_ConfigChannel( &this->dac, &this->dacCh, DAC_CHANNEL_2 ) != HAL_OK)
		return false;

	HAL_DAC_Start(  &this->dac, DAC_CHANNEL_1 );
	HAL_DAC_Start(  &this->dac, DAC_CHANNEL_2 );
	return true;
}

void Dac::setValue ( const uint32_t ch, const uint32_t value ) const {
	if ( ch == 0 ) {
		HAL_DAC_SetValue( &this->dac, DAC_CHANNEL_1,	DAC_ALIGN_12B_R, value );
	} else {
		HAL_DAC_SetValue( &this->dac, DAC_CHANNEL_2,	DAC_ALIGN_12B_R, value );
	}
}

void Dac::clkEnable ( void ) const {
	__HAL_RCC_DAC_CLK_ENABLE();
}

void Dac::clkDisable ( void ) const {
	__HAL_RCC_DAC_CLK_DISABLE();
}
