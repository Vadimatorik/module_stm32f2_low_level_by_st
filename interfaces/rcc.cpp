#include "rcc.h"

RCC_RESULT rcc::setCfg ( const uint32_t numberCfg ) const {
    if ( numberCfg >= this->cfgCount ) return RCC_RESULT::ERROR_CFG_NUMBER;

    HAL_RCC_DeInit();

	if ( HAL_RCC_OscConfig( ( RCC_OscInitTypeDef* )&this->cfg[ numberCfg ].osc ) != HAL_OK )
		return RCC_RESULT::ERROR_OSC_INIT;

	if ( HAL_RCC_ClockConfig( ( RCC_ClkInitTypeDef* )&this->cfg[ numberCfg ].clk, this->cfg[ numberCfg ].f_latency ) != HAL_OK )
		return  RCC_RESULT::ERROR_CLK_INIT;

    return RCC_RESULT::OK;
}
