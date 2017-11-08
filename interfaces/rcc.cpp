#include "rcc.h"

RCC_RESULT rcc::set_cfg ( uint32_t number_cfg_set ) const {
    if ( number_cfg_set >= this->number_cfg ) return RCC_RESULT::ERROR_CFG_NUMBER;

    HAL_RCC_DeInit();

    if ( HAL_RCC_OscConfig( ( RCC_OscInitTypeDef* )&this->array_cfg_st[ number_cfg_set ].osc_cfg ) != HAL_OK )
        return RCC_RESULT::ERROR_OSC_INIT;

    if ( HAL_RCC_ClockConfig( ( RCC_ClkInitTypeDef* )&this->array_cfg_st[ number_cfg_set ].clk_cfg, this->array_cfg_st[ number_cfg_set ].f_latency ) != HAL_OK )
        return  RCC_RESULT::ERROR_CLK_INIT;

    return RCC_RESULT::OK;
}
