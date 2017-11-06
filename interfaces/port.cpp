#include "port.h"

#include "stm32f2xx_hal_gpio.h"

void global_port::init_all_port ( void ) const {
    for ( uint32_t l = 0; l < this->number_pin; l++ ) {
        gpio_clk_en( &cfg[l] );
        HAL_GPIO_Init( cfg[l].GPIOx, ( GPIO_InitTypeDef* ) ( &cfg[l].init ) );
    }
}
