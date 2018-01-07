#include "uart.h"

uart::uart( const uart_cfg* const cfg ) : cfg(cfg) {
	this->handle.Instance							= cfg->UARTx;

	this->handle.Init.BaudRate						= cfg->baudrate;
	this->handle.Init.HwFlowCtl						= UART_HWCONTROL_NONE;
	this->handle.Init.Mode							= cfg->mode;
	this->handle.Init.OverSampling					= UART_OVERSAMPLING_8;
	this->handle.Init.Parity						= UART_PARITY_NONE;
	this->handle.Init.StopBits						= UART_STOPBITS_1;
	this->handle.Init.WordLength					= UART_WORDLENGTH_8B;

	if ( cfg->dma_tx != nullptr ) {
		this->handle.hdmatx = &this->hdma_tx;
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

		this->handle.hdmatx                             = &this->hdma_tx;
		this->handle.hdmatx->Parent                     = &this->handle;
	}

	// Грязный хак. Сохраняем в структуру HAL-uart-а указатель на объект.
	this->handle.obj = this;

    this->s = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &this->sb );
}

void uart::reinit ( void ) const {
	init_clk();

	if ( cfg->dma_tx != nullptr ) {
		dma_clk_on( this->cfg->dma_tx );
		dma_irq_on( this->cfg->dma_tx );
	}

	HAL_UART_DeInit( &this->handle );
	HAL_UART_Init( &this->handle );
}

void uart::on ( void ) const {
	__HAL_UART_ENABLE( &this->handle );
}

void uart::off ( void ) const {
	__HAL_UART_DISABLE( &this->handle );
}

BASE_RESULT uart::tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms ) const {
	xSemaphoreTake ( this->s, 0 );

	if ( cfg->dma_tx != nullptr ) {												// Если передача идет по DMA.
		HAL_UART_Transmit_DMA( &this->handle, (uint8_t*)p_array_tx, length );
	} else {																	// Если по прерываниям.
		HAL_UART_Transmit_IT( &this->handle, (uint8_t*)p_array_tx, length );
	}

	volatile BASE_RESULT rv = BASE_RESULT::TIME_OUT;
	if ( xSemaphoreTake ( this->s, timeout_ms ) == pdTRUE ) {
		rv = BASE_RESULT::OK;
	}

	return rv;
}

BASE_RESULT uart::get_byte ( uint8_t* data ) const {
	*data = this->handle.Instance->DR;
	return BASE_RESULT::OK;
}

void uart::irq_handler ( void ) const {
	HAL_UART_IRQHandler( &this->handle );
}

void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart ) {
	((uart*)huart->obj)->give_semaphore();
}

// Private.
void uart::give_semaphore ( void ) const {
    if ( this->s ) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR ( this->s, &xHigherPriorityTaskWoken);
    }
}

bool uart::init_clk ( void ) const {
    switch ( ( uint32_t )this->cfg->UARTx ) {
#ifdef USART1
        case    USART1_BASE:     __USART1_CLK_ENABLE();     break;
#endif
#ifdef USART2
        case    USART2_BASE:     __USART2_CLK_ENABLE();     break;
#endif
#ifdef USART3
        case    USART3_BASE:     __USART3_CLK_ENABLE();     break;
#endif
#ifdef UART4
        case	UART4_BASE:		__UART4_CLK_ENABLE();		break;
#endif
#ifdef UART5
        case	UART5_BASE:		__UART5_CLK_ENABLE();		break;
#endif
#ifdef UART6
        case	UART6_BASE:		__UART6_CLK_ENABLE();		break;
#endif
#ifdef UART7
        case	UART7_BASE:		__UART7_CLK_ENABLE();		break;
#endif
#ifdef UART8
        case	UART8_BASE:		__UART8_CLK_ENABLE();		break;
#endif
    };
    return true;
}
