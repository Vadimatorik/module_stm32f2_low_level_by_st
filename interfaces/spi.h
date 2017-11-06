#pragma once

#include "mc_hardware_interfaces_spi.h"
#include "pin.h"
#include "stm32f2xx_hal_spi.h"
#include "stm32f2xx_hal_dma.h"

struct spi_cfg {
    SPI_TypeDef*                SPIx;
    pin_base*                   pin_cs;
    uint32_t                    clk_polarity;                   // SPI_Clock_Polarity.
    uint32_t                    clk_phase;                      // SPI_Clock_Phase.
    uint32_t                    allowed_baudrate;               // Разрешенная максимальная частота интерфейса.
                                                                // Код подберет prescaler как можно ближе к этой
                                                                // величине снизу.
// В случае, если DMA не используется (передача и прием на прерываниях),
// то следует указать nullptr.
    DMA_Stream_TypeDef*         dma_tx;                         // Из мерии DMAx_Streamx.
    DMA_Stream_TypeDef*         dma_rx;                         // Из мерии DMAx_Streamx.
    uint32_t                    dma_tx_ch;                      // Из серии DMA_CHANNEL_x.
    uint32_t                    dma_rx_ch;                      // Из серии DMA_CHANNEL_x.
};

class spi_master_8bit : public spi_master_8bit_base {
public:
    spi_master_8bit( const spi_cfg* const cfg ) : cfg( cfg ) {}
    void reinit ( void ) const;
    void on     ( void ) const;
    void off    ( void ) const;
    SPI::BASE_RESULT tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms, const SPI::STEP_MODE step_mode = SPI::STEP_MODE::INC ) const;
    SPI::BASE_RESULT tx ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const;
    SPI::BASE_RESULT tx_one_item ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const;
    SPI::BASE_RESULT rx ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value = 0xFF ) const;

private:
    const spi_cfg* const cfg;
};
