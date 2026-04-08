/*
 * USART_Driver.h
 *
 *  Created on: 09-Apr-2026
 *      Author: Muhammad Rabeez
 */

#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include"STM32F401CCUx.h"

typedef struct
{
    uint8_t  USART_Mode;          // Select TX, RX, or TX+RX mode
    uint8_t  USART_NoOfStopBits;  // Number of stop bits used in frame
    uint8_t  USART_WordLength;    // Frame word length (8-bit or 9-bit)
    uint8_t  USART_ParityControl; // Parity configuration (None/Even/Odd)
    uint8_t  USART_HWFlowControl; // Hardware flow control (RTS/CTS)
    uint32_t USART_Baud;          // USART communication baud rate
} USART_Config_t;

typedef struct
{
    USART_RegDef_t   *pUSARTx;
    USART_Config_t   USART_Config;

}USART_Handle_t;
#endif /* USART_DRIVER_H_ */
