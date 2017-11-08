#include "spi.h"

SPI::BASE_RESULT  spi_master_8bit::reinit ( void ) const {
    if ( this->init_clk_spi() == false )    return SPI::BASE_RESULT::ERROR_INIT;      // Включаем тактирование SPI.
    if ( this->init_spi() == false )        return SPI::BASE_RESULT::ERROR_INIT;      // Инициализируем UART (и DMA, внутри тактирование DMA включается).
    this->init_spi_irq();                                      // Включаем IRQ SPI (если DMA не вызывается для используемого функционала).
    this->init_dma_irq();                                      // Включаем IRQ DMA, если DMA используется.

    return SPI::BASE_RESULT::OK;
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

/*******************************************************************************************************
 * Прикладные функции.
 *******************************************************************************************************/
// Включаем тактирование SPI.
bool spi_master_8bit::init_clk_spi () const {
    switch ((uint32_t)this->cfg->SPIx) {
#ifdef SPI
        case    SPI_BASE:     __SPI_CLK_ENABLE();     break;
#endif
#ifdef SPI1
        case    SPI1_BASE:    __SPI1_CLK_ENABLE();    break;
#endif
#ifdef SPI2
        case    SPI2_BASE:    __SPI2_CLK_ENABLE();    break;
#endif
#ifdef SPI3
        case    SPI3_BASE:    __SPI3_CLK_ENABLE();    break;
#endif
#ifdef SPI4
        case    SPI4_BASE:    __SPI4_CLK_ENABLE();    break;
#endif
#ifdef SPI5
        case    SPI5_BASE:    __SPI5_CLK_ENABLE();    break;
#endif
#ifdef SPI6
        case    SPI6_BASE:    __SPI6_CLK_ENABLE();    break;
#endif
    };
    return true;
}

// Включаем тактирование DMA (если используется).
bool spi_master_8bit::init_clk_dma ( void ) const {
    bool result = false;
    if (this->cfg->dma_tx != nullptr) {
        this->dma_tx.rewrite_dma_handle(&this->hdma_tx);
        this->dma_tx.clock_enable();
        result = true;
    }
    if (this->cfg->dma_rx != nullptr) {
        this->dma_rx.rewrite_dma_handle(&this->hdma_rx);
        this->dma_rx.clock_enable();
        result = true;
    }
    return result;
}


bool spi_master_8bit::init_spi_irq ( void ) const {
    // Если и TX и RX по DMA, то SPI прерывание не включается.
    if ((this->cfg->dma_tx != nullptr) && (this->cfg->dma_rx != nullptr)) {
        return false;
    }
    switch ((uint32_t)this->cfg->SPIx)    {
#ifdef SPI
        case    SPI_BASE:    NVIC_SetPriority(SPI_IRQn, 5);    NVIC_EnableIRQ(SPI_IRQn);    break;
#endif
#ifdef SPI1
        case    SPI1_BASE:    NVIC_SetPriority(SPI1_IRQn, 5);    NVIC_EnableIRQ(SPI1_IRQn);    break;
#endif
#ifdef SPI2
        case    SPI2_BASE:    NVIC_SetPriority(SPI2_IRQn, 5);    NVIC_EnableIRQ(SPI2_IRQn);    break;
#endif
#ifdef SPI3
        case    SPI3_BASE:    NVIC_SetPriority(SPI3_IRQn, 5);    NVIC_EnableIRQ(SPI3_IRQn);    break;
#endif
#ifdef SPI4
        case    SPI4_BASE:    NVIC_SetPriority(SPI4_IRQn, 5);    NVIC_EnableIRQ(SPI4_IRQn);    break;
#endif
#ifdef SPI5
        case    SPI5_BASE:    NVIC_SetPriority(SPI5_IRQn, 5);    NVIC_EnableIRQ(SPI5_IRQn);    break;
#endif
#ifdef SPI6
        case    SPI6_BASE:    NVIC_SetPriority(SPI6_IRQn, 5);    NVIC_EnableIRQ(SPI6_IRQn);    break;
#endif
};
    return true;
}

// Включаем прерывание канала DMA, если используется DMA.
bool spi_master_8bit::init_dma_irq ( void ) const {
    bool result = false;
    if (this->cfg->dma_tx != nullptr) {
        this->dma_tx.init_irq();                    // Включаем прерывание по выбранному каналу.
        result = true;
    }
    if (this->cfg->dma_rx != nullptr) {
        this->dma_rx.init_irq();                    // Включаем прерывание по выбранному каналу.
        result = true;
    }
    return result;
}

bool spi_master_8bit::init_spi ( void ) const {
    this->handle.Instance			= this->cfg->SPIx;
    this->handle.Init.Mode			= SPI_MODE_MASTER;
    this->handle.Init.Direction		= SPI_DIRECTION_2LINES;
    this->handle.Init.DataSize		= SPI_DATASIZE_8BIT;
    this->handle.Init.CLKPolarity   = this->cfg->clk_polarity;
    this->handle.Init.CLKPhase      = this->cfg->clk_phase;
    this->handle.Init.BaudRatePrescaler = this->cfg->baud_rate_prescaler;

    this->handle.Init.NSS					= SPI_NSS_SOFT;
    this->handle.Init.FirstBit				= SPI_FIRSTBIT_MSB;
    this->handle.Init.TIMode				= SPI_TIMODE_DISABLED;
    this->handle.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLED;
    this->handle.Init.CRCPolynomial			= 0xFF;

    HAL_SPI_Init ( &this->handle );

    if ( this->cfg->dma_tx != NULL ) {
        this->handle.hdmatx = &this->hdma_tx;			// Указываем, что структура инициализации канала DMA находится внутри объекта SPI.
        this->handle.hdmatx->Instance					= this->cfg->dma_tx;
        this->handle.hdmatx->Init.Channel				= this->cfg->dma_tx_ch;
        this->handle.hdmatx->Init.Direction				= DMA_MEMORY_TO_PERIPH;
        this->handle.hdmatx->Init.PeriphInc				= DMA_PINC_DISABLE;
        this->handle.hdmatx->Init.MemInc				= DMA_MINC_ENABLE;
        this->handle.hdmatx->Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
        this->handle.hdmatx->Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;
        this->handle.hdmatx->Init.Mode					= DMA_NORMAL;
        this->handle.hdmatx->Init.Priority				= DMA_PRIORITY_HIGH;
        this->handle.hdmatx->Init.FIFOMode				= DMA_FIFOMODE_DISABLE;
        if ( this->init_clk_dma() == false )	return false;
        this->dma_tx.init();
    }

    if ( this->cfg->dma_rx != NULL ) {		// Нам не всегда нужно, чтобы RX затерал данные. Для тех случаев, когда мы только передаем!
        this->handle.hdmarx = &this->hdma_rx;
        this->handle.hdmarx->Instance					= this->cfg->dma_rx;
        this->handle.hdmarx->Init.Channel				= this->cfg->dma_rx_ch;
        this->handle.hdmarx->Init.Direction				= DMA_PERIPH_TO_MEMORY;
        this->handle.hdmarx->Init.PeriphInc				= DMA_PINC_DISABLE;
        this->handle.hdmarx->Init.MemInc				= DMA_MINC_ENABLE;
        this->handle.hdmarx->Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
        this->handle.hdmarx->Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;
        this->handle.hdmarx->Init.Mode					= DMA_NORMAL;
        this->handle.hdmarx->Init.Priority				= DMA_PRIORITY_HIGH;
        this->handle.hdmarx->Init.FIFOMode				= DMA_FIFOMODE_DISABLE;
        if ( this->init_clk_dma() == false )	return false;
        this->dma_rx.init();
    }

    __HAL_SPI_ENABLE(&this->handle);

    if ( this->cfg->pin_cs != nullptr ) {
         this->cfg->pin_cs->set( 1 );
    }

    this->semaphore = xSemaphoreCreateBinary ();
    return true;

    return true;
}
