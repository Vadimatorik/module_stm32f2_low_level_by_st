#include "timer.h"

tim_comp_one_channel::tim_comp_one_channel ( const tim_comp_one_channel_cfg* const cfg ) : cfg( cfg ) {
	this->hal_tim_cfg.Instance						= this->cfg->tim;

	this->hal_tim_cfg.Channel						= this->cfg->tim_channel;
	this->hal_tim_cfg.Init.AutoReloadPreload		= TIM_AUTORELOAD_PRELOAD_ENABLE;
	this->hal_tim_cfg.Init.ClockDivision			= TIM_CLOCKDIVISION_DIV1;
	this->hal_tim_cfg.Init.CounterMode				= TIM_COUNTERMODE_UP;
	this->hal_tim_cfg.Init.Period					= this->cfg->period;
	this->hal_tim_cfg.Init.Prescaler				= this->cfg->prescaler;

	this->hal_tim_ch_cfg.OCMode						= TIM_OCMODE_TOGGLE;
	this->hal_tim_ch_cfg.OCPolarity					= this->cfg->polarity;
	this->hal_tim_ch_cfg.Pulse						= this->cfg->pulse;
}

void tim_comp_one_channel::reinit ( void ) const {
	HAL_TIM_OC_DeInit( &this->hal_tim_cfg );
	HAL_TIM_OC_Init( &this->hal_tim_cfg );
	HAL_TIM_OC_ConfigChannel( &this->hal_tim_cfg, &this->hal_tim_ch_cfg, this->cfg->out_channel );
}

void tim_comp_one_channel::on ( void ) const {
	HAL_TIM_OC_Start( &this->hal_tim_cfg, this->cfg->out_channel );
}

void tim_comp_one_channel::off ( void ) const {
	HAL_TIM_OC_Stop( &this->hal_tim_cfg, this->cfg->out_channel );
}

tim_interrupt::tim_interrupt( const tim_interrupt_cfg* const cfg ) : cfg( cfg ) {
	this->hal_tim_cfg.Instance						= this->cfg->tim;

	this->hal_tim_cfg.Channel						= this->cfg->tim_channel;
	this->hal_tim_cfg.Init.AutoReloadPreload		= TIM_AUTORELOAD_PRELOAD_ENABLE;
	this->hal_tim_cfg.Init.ClockDivision			= TIM_CLOCKDIVISION_DIV1;
	this->hal_tim_cfg.Init.CounterMode				= TIM_COUNTERMODE_UP;
	this->hal_tim_cfg.Init.Period					= this->cfg->period;
	this->hal_tim_cfg.Init.Prescaler				= this->cfg->prescaler;
}

void tim_interrupt::reinit ( void ) const {
	HAL_TIM_Base_DeInit( &this->hal_tim_cfg );
	HAL_TIM_Base_Init( &this->hal_tim_cfg );
}

void tim_interrupt::on ( void ) const {
	HAL_TIM_Base_Start_IT( &this->hal_tim_cfg );
}

void tim_interrupt::off ( void ) const {
	HAL_TIM_Base_Stop_IT( &this->hal_tim_cfg );
}

void tim_interrupt::clear_interrupt_flag ( void ) const {
	HAL_TIM_IRQHandler( &this->hal_tim_cfg );
}
