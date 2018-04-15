#include "timer.h"

// Включаем тактирование SPI.
static void init_clk_tim ( TIM_TypeDef* tim ) {
	switch ( ( uint32_t )tim ) {
#ifdef TIM
		case	TIM_BASE:		__HAL_RCC_TIM_CLK_ENABLE();			break;
#endif
#ifdef TIM1
		case	TIM1_BASE:		__HAL_RCC_TIM1_CLK_ENABLE();		break;
#endif
#ifdef TIM2
		case	TIM2_BASE:		__HAL_RCC_TIM2_CLK_ENABLE();		break;
#endif
#ifdef TIM3
		case	TIM3_BASE:		__HAL_RCC_TIM3_CLK_ENABLE();		break;
#endif
#ifdef TIM4
		case	TIM4_BASE:		__HAL_RCC_TIM4_CLK_ENABLE();		break;
#endif
#ifdef TIM5
		case	TIM5_BASE:		__HAL_RCC_TIM5_CLK_ENABLE();		break;
#endif
#ifdef TIM6
		case	TIM6_BASE:		__HAL_RCC_TIM6_CLK_ENABLE();		break;
#endif
#ifdef TIM7
		case	TIM7_BASE:		__HAL_RCC_TIM7_CLK_ENABLE();		break;
#endif
#ifdef TIM8
		case	TIM8_BASE:		__HAL_RCC_TIM8_CLK_ENABLE();		break;
#endif
#ifdef TIM9
		case	TIM9_BASE:		__HAL_RCC_TIM9_CLK_ENABLE();		break;
#endif
#ifdef TIM10
		case	TIM10_BASE:		__HAL_RCC_TIM10_CLK_ENABLE();		break;
#endif
#ifdef TIM11
		case	TIM11_BASE:		__HAL_RCC_TIM11_CLK_ENABLE();		break;
#endif
#ifdef TIM12
		case	TIM12_BASE:		__HAL_RCC_TIM12_CLK_ENABLE();		break;
#endif
#ifdef TIM13
		case	TIM13_BASE:		__HAL_RCC_TIM13_CLK_ENABLE();		break;
#endif
#ifdef TIM14
		case	TIM14_BASE:		__HAL_RCC_TIM14_CLK_ENABLE();		break;
#endif
#ifdef TIM15
		case	TIM15_BASE:		__HAL_RCC_TIM15_CLK_ENABLE();		break;
#endif
#ifdef TIM16
		case	TIM16_BASE:		__HAL_RCC_TIM16_CLK_ENABLE();		break;
#endif
	};
}

//**********************************************************************
// tim_comp_one_channel
//**********************************************************************
TimCompOneChannel::TimCompOneChannel ( const timCompOneChannelCfg* const cfg ) : cfg( cfg ) {
	this->hal_tim_cfg.Instance						= this->cfg->tim;

	this->hal_tim_cfg.Channel						= this->cfg->timChannel;
	this->hal_tim_cfg.Init.AutoReloadPreload		= TIM_AUTORELOAD_PRELOAD_ENABLE;
	this->hal_tim_cfg.Init.ClockDivision			= TIM_CLOCKDIVISION_DIV1;
	this->hal_tim_cfg.Init.CounterMode				= TIM_COUNTERMODE_UP;

	/// reinit настраивает эти параметры.
	this->hal_tim_cfg.Init.Period					= 0;
	this->hal_tim_cfg.Init.Prescaler				= 0;

	this->hal_tim_ch_cfg.OCMode						= TIM_OCMODE_TOGGLE;
	this->hal_tim_ch_cfg.OCPolarity					= this->cfg->polarity;
	this->hal_tim_ch_cfg.Pulse						= 0;
}

bool TimCompOneChannel::reinit ( uint32_t cfg_number ) const {
	if ( cfg_number >= this->cfg->countCfg ) return false;

	this->hal_tim_cfg.Init.Period					= this->cfg->cfg[ cfg_number ].period;
	this->hal_tim_cfg.Init.Prescaler				= this->cfg->cfg[ cfg_number ].prescaler;
	this->hal_tim_ch_cfg.Pulse						= this->cfg->cfg[ cfg_number ].pulse;

	init_clk_tim( this->cfg->tim );
	if ( HAL_TIM_OC_DeInit( &this->hal_tim_cfg ) != HAL_OK ) return false;
	if ( HAL_TIM_OC_Init( &this->hal_tim_cfg ) != HAL_OK ) return false;
	if ( HAL_TIM_OC_ConfigChannel( &this->hal_tim_cfg, &this->hal_tim_ch_cfg, this->cfg->outChannel ) != HAL_OK ) return false;

	return true;
}

bool TimCompOneChannel::on ( void ) const {
	if ( HAL_TIM_OC_Start( &this->hal_tim_cfg, this->cfg->outChannel ) != HAL_OK ) return false;
	return true;
}

bool TimCompOneChannel::off ( void ) const {
	if ( HAL_TIM_OC_Stop( &this->hal_tim_cfg, this->cfg->outChannel ) != HAL_OK ) return false;
	return true;
}

//**********************************************************************
// tim_pwm_one_channel
//**********************************************************************
TimPwmOneChannel::TimPwmOneChannel ( const timPwmOneChannelCfg* const cfg ) : cfg( cfg ) {
	this->tim.Instance						= this->cfg->tim;

	this->tim.Channel						= this->cfg->timChannel;
	this->tim.Init.AutoReloadPreload		= TIM_AUTORELOAD_PRELOAD_ENABLE;
	this->tim.Init.ClockDivision			= TIM_CLOCKDIVISION_DIV1;
	this->tim.Init.CounterMode				= TIM_COUNTERMODE_UP;

	/// reinit настраивает эти параметры.
	this->tim.Init.Period					= 0;
	this->tim.Init.Prescaler				= 0;

	this->timCh.OCMode						= TIM_OCMODE_PWM2;
	this->timCh.OCPolarity					= this->cfg->polarity;
}

bool TimPwmOneChannel::reinit ( uint32_t cfg_number ) const {
	if ( cfg_number >= this->cfg->countCfg ) return false;

	this->tim.Init.Period					= this->cfg->cfg[ cfg_number ].period;
	this->tim.Init.Prescaler				= this->cfg->cfg[ cfg_number ].prescaler;

	init_clk_tim( this->cfg->tim );
	if ( HAL_TIM_PWM_DeInit( &this->tim ) != HAL_OK ) return false;
	if ( HAL_TIM_PWM_Init( &this->tim ) != HAL_OK ) return false;
	if ( HAL_TIM_PWM_ConfigChannel( &this->tim, &this->timCh, this->cfg->outChannel ) != HAL_OK ) return false;

	return true;
}

bool TimPwmOneChannel::on ( void ) const {
	if ( HAL_TIM_PWM_Start( &this->tim, this->cfg->outChannel ) != HAL_OK ) return false;
	return true;
}

bool TimPwmOneChannel::off ( void ) const {
	if ( HAL_TIM_PWM_Stop( &this->tim, this->cfg->outChannel ) != HAL_OK ) return false;
	return true;
}

void TimPwmOneChannel::setDuty ( float duty ) const {
	__HAL_TIM_SET_COMPARE( &this->tim, this->cfg->outChannel, this->cfg->tim->ARR * duty );
}

//**********************************************************************
// tim_interrupt
//**********************************************************************
TimInterrupt::TimInterrupt( const timInterruptCfg* const cfg ) : cfg( cfg ) {
	this->tim.Instance						= this->cfg->tim;

	this->tim.Channel						= this->cfg->timChannel;
	this->tim.Init.AutoReloadPreload		= TIM_AUTORELOAD_PRELOAD_ENABLE;
	this->tim.Init.ClockDivision			= TIM_CLOCKDIVISION_DIV1;
	this->tim.Init.CounterMode				= TIM_COUNTERMODE_UP;

	/// reinit настраивает эти параметры.
	this->tim.Init.Period					= 0;
	this->tim.Init.Prescaler				= 0;
}

bool TimInterrupt::reinit ( uint32_t cfg_number ) const {
	if ( cfg_number >= this->cfg->countCfg ) return false;

	this->tim.Init.Period					= this->cfg->cfg[ cfg_number ].period;
	this->tim.Init.Prescaler				= this->cfg->cfg[ cfg_number ].prescaler;

	if ( HAL_TIM_Base_DeInit( &this->tim ) != HAL_OK ) return false;
	if ( HAL_TIM_Base_Init( &this->tim ) != HAL_OK ) return false;
	return true;
}

bool TimInterrupt::on ( void ) const {
	if ( HAL_TIM_Base_Start_IT( &this->tim ) != HAL_OK ) return false;
	return true;
}

bool TimInterrupt::off ( void ) const {
	if ( HAL_TIM_Base_Stop_IT( &this->tim ) != HAL_OK ) return false;
	return true;
}

void TimInterrupt::clearInterruptFlag ( void ) const {
	HAL_TIM_IRQHandler( &this->tim );
}
