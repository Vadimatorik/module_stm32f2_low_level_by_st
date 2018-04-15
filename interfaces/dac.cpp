#include "dac.h"

DacOneChannel::DacOneChannel( const DacOneChannelCfg* const cfg ) : chName( cfg->channel ) {
	this->dac.Instance = DAC;
	this->dacCh.DAC_Trigger						= DAC_TRIGGER_NONE;
	this->dacCh.DAC_OutputBuffer				= cfg->buffer;
}

bool DacOneChannel::reinit ( void )	const {
	this->clkEnable();
	HAL_DAC_DeInit( &this->dac );

	if ( HAL_DAC_Init( &this->dac ) != HAL_OK )
		return false;

	if ( HAL_DAC_ConfigChannel( &this->dac, &this->dacCh, this->chName ) != HAL_OK)
		return false;

	HAL_DAC_Start(  &this->dac, this->chName );
	return true;
}

void DacOneChannel::setValue ( uint32_t& value ) const {
	HAL_DAC_SetValue( &this->dac, this->chName,	DAC_ALIGN_12B_R, value );
}

void DacOneChannel::setValue ( const uint32_t value ) const {
	this->setValue( static_cast< uint32_t >( value ));
}

void DacOneChannel::clkEnable ( void ) const {
	__HAL_RCC_DAC_CLK_ENABLE();
}

void DacOneChannel::clkDisable ( void ) const {
	__HAL_RCC_DAC_CLK_DISABLE();
}
