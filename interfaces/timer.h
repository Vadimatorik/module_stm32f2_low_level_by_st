#pragma once

#include "mc_hardware_interfaces_timer.h"
#include "stm32f2xx_hal_tim.h"
#include "stm32f2xx_hal_rcc.h"

//**********************************************************************
// tim_comp_one_channel
//**********************************************************************
struct tim_comp_one_channel_cfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	// Параметры таймера.
	HAL_TIM_ActiveChannel		tim_channel;
	uint16_t					period;					// 0..0xFFFF.
	uint16_t					prescaler;				// 0..0xFFFF.

	// Параметры выходного канала.
	uint8_t						out_channel;			// TIM_CHANNEL_x.
	uint32_t					polarity;				// TIM_OCPOLARITY_LOW  / TIM_OCPOLARITY_HIGH.
	uint16_t					pulse;					// 0..0xFFFF.

};

class tim_comp_one_channel : public tim_comp_one_channel_base {
public:
    tim_comp_one_channel( const tim_comp_one_channel_cfg* const cfg );
    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;

private:
    const tim_comp_one_channel_cfg*		const cfg;
    mutable TIM_HandleTypeDef			hal_tim_cfg;
    mutable	TIM_OC_InitTypeDef			hal_tim_ch_cfg;
};

//**********************************************************************
// tim_pwm_one_channel
//**********************************************************************
struct tim_pwm_one_channel_cfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	// Параметры таймера.
	HAL_TIM_ActiveChannel		tim_channel;
	uint16_t					period;					// 0..0xFFFF.
	uint16_t					prescaler;				// 0..0xFFFF.

	// Параметры выходного канала.
	uint8_t						out_channel;			// TIM_CHANNEL_x.
	uint32_t					polarity;				// TIM_OCPOLARITY_LOW  / TIM_OCPOLARITY_HIGH.
};

class tim_pwm_one_channel : public tim_pwm_one_channel_base {
public:
	tim_pwm_one_channel( const tim_pwm_one_channel_cfg* const cfg );
    void reinit ( void ) 			const;
    void on ( void ) 				const;
    void off ( void ) 				const;
    void duty_set ( float duty ) 	const;

private:
    const tim_pwm_one_channel_cfg*		const cfg;
    mutable TIM_HandleTypeDef			hal_tim_cfg;
    mutable	TIM_OC_InitTypeDef			hal_tim_ch_cfg;
};

//**********************************************************************
// tim_interrupt
//**********************************************************************
struct tim_interrupt_cfg {
	TIM_TypeDef*				tim;

	HAL_TIM_ActiveChannel		tim_channel;
	uint16_t					period;
	uint16_t					prescaler;
};

class tim_interrupt : public tim_interrupt_base {
public:
    tim_interrupt( const tim_interrupt_cfg* const cfg );

    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;
    void clear_interrupt_flag ( void ) const;

private:
    const tim_interrupt_cfg*		const cfg;
    mutable TIM_HandleTypeDef		hal_tim_cfg;
};
