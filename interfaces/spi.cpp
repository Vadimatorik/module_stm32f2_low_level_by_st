#include "spi.h"

void spi_master_8bit::reinit ( void ) const {

}

void spi_master_8bit::on ( void ) const {

}

void spi_master_8bit::off  ( void ) const {

}

SPI::BASE_RESULT spi_master_8bit::tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms, const SPI::STEP_MODE step_mode  ) const {
    (void)p_array_tx; (void)length; (void)timeout_ms; (void)step_mode;
    return SPI::BASE_RESULT::OK;
}

SPI::BASE_RESULT spi_master_8bit::tx ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const {
    (void)p_array_tx;(void)p_array_rx;(void)length ;(void)timeout_ms;
    return SPI::BASE_RESULT::OK;
}

SPI::BASE_RESULT spi_master_8bit::tx_one_item ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const {
 (void)p_item_tx;(void)count;(void)timeout_ms;
         return SPI::BASE_RESULT::OK;
}

SPI::BASE_RESULT spi_master_8bit::rx ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value ) const {
(void)p_array_rx;(void)length;(void)timeout_ms ;(void)out_value;
         return SPI::BASE_RESULT::OK;
}
