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
    uint8_t USART_Enable;
} USART_Config_t;


typedef struct
{
    USART_RegDef_t   *pUSARTx;
    USART_Config_t   USART_Config;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
}USART_Handle_t;

//USART ENABLE or DISABLE
#define USART_CR1_UE_DISABLE    0
#define USART_CR1_UE_ENABLE     1

//flag
#define USART_FLAG_TXE          ( 1 << USART_SR_TXE)
#define USART_FLAG_RXNE         ( 1 << USART_SR_RXNE)
#define USART_FLAG_TC           ( 1 << USART_SR_TC)

//USART MODE
#define USART_MODE_ONLY_TX      0
#define USART_MODE_ONLY_RX      1
#define USART_MODE_TXRX         2

//word length
#define USART_WORDLEN_8BITS 0
#define USART_WORDLEN_9BITS 1

//parity
#define USART_PARITY_DISABLE        0
#define USART_PARITY_EN_EVEN        1
#define USART_PARITY_EN_ODD         2

//stop bit
#define USART_STOPBITS_1            0
#define USART_STOPBITS_0_5          1
#define USART_STOPBITS_2            2
#define USART_STOPBITS_1_5          3

//flow control
#define USART_HW_FLOW_CTRL_NONE     0
#define USART_HW_FLOW_CTRL_CTS      1
#define USART_HW_FLOW_CTRL_RTS      2
#define USART_HW_FLOW_CTRL_CTS_RTS  3

void USART_PeriClockControl(USART_RegDef_t* pUSARTx, uint8_t EnorDi);
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);






uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t FlagName);
#endif /* USART_DRIVER_H_ */
