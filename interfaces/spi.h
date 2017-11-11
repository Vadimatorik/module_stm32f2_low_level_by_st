#pragma once

#include "user_os.h"
#include "mc_hardware_interfaces_spi.h"
#include "pin.h"
#include "dma.h"
#include "stm32f2xx_hal_spi.h"
#include "stm32f2xx_hal_dma.h"

struct spi_master_8bit_cfg {
    SPI_TypeDef*                SPIx;
    const pin_base*             pin_cs;
    uint32_t                    clk_polarity;                   // SPI_Clock_Polarity.
    uint32_t                    clk_phase;                      // SPI_Clock_Phase.
    uint32_t                    baud_rate_prescaler;            // SPI_BaudRate_Prescaler
// В случае, если DMA не используется (передача и прием на прерываниях),
// то следует указать nullptr.
    DMA_Stream_TypeDef*         dma_tx;                         // Из мерии DMAx_Streamx.
    DMA_Stream_TypeDef*         dma_rx;                         // Из мерии DMAx_Streamx.
    uint32_t                    dma_tx_ch;                      // Из серии DMA_CHANNEL_x.
    uint32_t                    dma_rx_ch;                      // Из серии DMA_CHANNEL_x.
};

class spi_master_8bit : public spi_master_8bit_base {
public:
    spi_master_8bit( const spi_master_8bit_cfg* const cfg );
    SPI::BASE_RESULT  reinit ( void ) const;
    void on     ( void ) const;
    void off    ( void ) const;
    SPI::BASE_RESULT tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms, const SPI::STEP_MODE step_mode = SPI::STEP_MODE::INC ) const;
    SPI::BASE_RESULT tx ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const;
    SPI::BASE_RESULT tx_one_item ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const;
    SPI::BASE_RESULT rx ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value = 0xFF ) const;

    void	handler ( void );
private:
    bool    init_clk_spi        ( void ) const;            // Включаем тактирование SPI и DMA (если используется).
    bool    init_spi            ( void ) const;            // Инициализируем только SPI (считается, что он уже затактирован).
    bool    init_clk_dma        ( void ) const;
    bool    init_spi_irq        ( void ) const;            // Включаем нужные прерывания (по SPI (если нет DMA) иначе DMA).
    bool    init_dma_irq        ( void ) const;

    uint8_t                             num_cfg;                   // Колличество структур переинициализации.

    mutable SPI_HandleTypeDef               handle;
    mutable USER_OS_STATIC_BIN_SEMAPHORE               semaphore        = nullptr;
    uint8_t                     runtime_flags    = 0;
    dma                         dma_tx;
    mutable DMA_HandleTypeDef           hdma_tx;
    dma                         dma_rx;
    mutable DMA_HandleTypeDef           hdma_rx;

    const spi_master_8bit_cfg* const cfg;
};
