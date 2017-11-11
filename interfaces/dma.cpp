#include "dma.h"

void dma::start ( void* src, void* dst, uint32_t l ) const {
    if (this->check_dma_handle() == false) return;                                    // Если структура не была указана - выходим.
    HAL_DMA_Start_IT( this->dma_handle, (uint32_t)src, (uint32_t)dst, l );
}

int dma::handler ( void )const {
    if (this->check_dma_handle() == false) return -1;                                        // Если структура не была указана - выходим.

    if(__HAL_DMA_GET_FLAG( this->dma_handle, __HAL_DMA_GET_TE_FLAG_INDEX(this->dma_handle))) {
        if(__HAL_DMA_GET_IT_SOURCE(this->dma_handle, DMA_IT_TE)) {
            __HAL_DMA_DISABLE_IT(this->dma_handle, DMA_IT_TE);
            __HAL_DMA_CLEAR_FLAG(this->dma_handle, __HAL_DMA_GET_TE_FLAG_INDEX(this->dma_handle));
        }
    }

    if(__HAL_DMA_GET_FLAG( this->dma_handle, __HAL_DMA_GET_TC_FLAG_INDEX(this->dma_handle))) {
        if(__HAL_DMA_GET_IT_SOURCE(this->dma_handle, DMA_IT_TC)) {
            __HAL_DMA_DISABLE_IT(this->dma_handle, DMA_IT_TC);
            __HAL_DMA_DISABLE_IT(this->dma_handle, DMA_IT_TE);
            __HAL_DMA_CLEAR_FLAG(this->dma_handle, __HAL_DMA_GET_TC_FLAG_INDEX(this->dma_handle));
            return 1;
        }
    }
    return 0;
}


/*
 * Проверка на то, указана ли структура инициализации.
 */
bool dma::check_dma_handle ( void ) const {
    if (this->dma_handle == nullptr) return false;
    return true;
}

/*
 * Запоминаем указатель на новую структуру.
 */
void dma::rewrite_dma_handle ( DMA_HandleTypeDef *dma_handle ) const {
    this->dma_handle = dma_handle;
}

// Включаем тактирование используемого DMA.
void dma::clock_enable ( void ) const {
    if (this->check_dma_handle() == false) return;                                        // Если структура не была указана - выходим.
    switch ((uint32_t)this->dma_handle->Instance) {
        // Для всех Stream нужно включить 1 DMA)))
#if defined(DMA1_Stream0) || defined(DMA1_Stream1) || defined(DMA1_Stream2) ||            \
        defined(DMA1_Stream3) || defined(DMA1_Stream4) || defined(DMA1_Stream5) ||        \
        defined(DMA1_Stream6) || defined(DMA1_Stream7)
        case DMA1_Stream0_BASE:
        case DMA1_Stream1_BASE:
        case DMA1_Stream2_BASE:
        case DMA1_Stream3_BASE:
        case DMA1_Stream4_BASE:
        case DMA1_Stream5_BASE:
        case DMA1_Stream6_BASE:
        case DMA1_Stream7_BASE:
        __HAL_RCC_DMA1_CLK_ENABLE(); break;
#endif
#if     defined(DMA2_Stream0) || defined(DMA2_Stream1) || defined(DMA2_Stream2) ||        \
        defined(DMA2_Stream3) || defined(DMA2_Stream4) || defined(DMA2_Stream5) ||        \
        defined(DMA2_Stream6) || defined(DMA2_Stream7)
        case DMA2_Stream0_BASE:
        case DMA2_Stream1_BASE:
        case DMA2_Stream2_BASE:
        case DMA2_Stream3_BASE:
        case DMA2_Stream4_BASE:
        case DMA2_Stream5_BASE:
        case DMA2_Stream6_BASE:
        case DMA2_Stream7_BASE:
            __HAL_RCC_DMA2_CLK_ENABLE(); break;
#endif
    }
}

int dma::init ( void ) const {
    if (this->check_dma_handle() == false) return -1;                                    // Если структура не была указана - выходим.
    return HAL_DMA_Init(this->dma_handle);
}

/*
 * Включаем прерыание от нужного stream.
 */
void dma::init_irq ( void ) const {
    if (this->check_dma_handle() == false) return;                                        // Если структура не была указана - выходим.
    switch ((uint32_t)this->dma_handle->Instance) {
#ifdef DMA1_Stream0
        case DMA1_Stream0_BASE:
            NVIC_SetPriority(DMA1_Stream0_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream0_IRQn);
        break;
#endif
#ifdef DMA1_Stream1
        case DMA1_Stream1_BASE:
            NVIC_SetPriority(DMA1_Stream1_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream1_IRQn);
        break;
#endif
#ifdef DMA1_Stream2
        case DMA1_Stream2_BASE:
            NVIC_SetPriority(DMA1_Stream2_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream2_IRQn);
        break;
#endif
#ifdef DMA1_Stream3
        case DMA1_Stream3_BASE:
            NVIC_SetPriority(DMA1_Stream3_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream3_IRQn);
        break;
#endif
#ifdef DMA1_Stream4
        case DMA1_Stream4_BASE:
            NVIC_SetPriority(DMA1_Stream4_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream4_IRQn);
        break;
#endif
#ifdef DMA1_Stream5
        case DMA1_Stream5_BASE:
            NVIC_SetPriority(DMA1_Stream5_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream5_IRQn);
        break;
#endif
#ifdef DMA1_Stream6
        case DMA1_Stream6_BASE:
            NVIC_SetPriority(DMA1_Stream6_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream6_IRQn);
        break;
#endif
#ifdef DMA1_Stream7
        case DMA1_Stream7_BASE:
            NVIC_SetPriority(DMA1_Stream7_IRQn, 5);
            NVIC_EnableIRQ(DMA1_Stream7_IRQn);
        break;
#endif
#ifdef DMA2_Stream0
        case DMA2_Stream0_BASE:
            NVIC_SetPriority(DMA2_Stream0_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream0_IRQn);
        break;
#endif
#ifdef DMA2_Stream1
        case DMA2_Stream1_BASE:
            NVIC_SetPriority(DMA2_Stream1_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream1_IRQn);
        break;
#endif
#ifdef DMA2_Stream2
        case DMA2_Stream2_BASE:
            NVIC_SetPriority(DMA2_Stream2_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream2_IRQn);
        break;
#endif
#ifdef DMA2_Stream3
        case DMA2_Stream3_BASE:
            NVIC_SetPriority(DMA2_Stream3_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream3_IRQn);
        break;
#endif
#ifdef DMA2_Stream4
        case DMA2_Stream4_BASE:
            NVIC_SetPriority(DMA2_Stream4_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream4_IRQn);
        break;
#endif
#ifdef DMA2_Stream5
        case DMA2_Stream5_BASE:
            NVIC_SetPriority(DMA2_Stream5_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream5_IRQn);
        break;
#endif
#ifdef DMA2_Stream6
        case DMA2_Stream6_BASE:
            NVIC_SetPriority(DMA2_Stream6_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream6_IRQn);
        break;
#endif
#ifdef DMA2_Stream7
        case DMA2_Stream7_BASE:
            NVIC_SetPriority(DMA2_Stream7_IRQn, 5);
            NVIC_EnableIRQ(DMA2_Stream7_IRQn);
        break;
#endif
    }
}
