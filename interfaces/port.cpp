#include "port.h"

#include "stm32f2xx_hal_gpio.h"

void GlobalPort::reinitAllPorts ( void ) const {
    for ( uint32_t l = 0; l < this->countCfg; l++ ) {
        gpio_clk_en( (const GPIO_TypeDef*)this->cfg[l].GPIOx );
        HAL_GPIO_Init( ( GPIO_TypeDef* )cfg[l].GPIOx, ( GPIO_InitTypeDef* ) ( &cfg[l].init ) );
    }
}
