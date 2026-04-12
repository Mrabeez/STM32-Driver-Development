/*
 * USART_Driver.c
 *
 *  Created on: 09-Apr-2026
 *      Author: Muhammad Rabeez
 */


#include"USART_Driver.h"


void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pUSARTx == USART1)
        {
            USART1_Clk_En();
        }
        else if(pUSARTx == USART2)
        {
            USART2_Clk_En();
        }
        else if(pUSARTx == USART6)
        {
            USART6_Clk_En();
        }
    }
    else
    {
        if(pUSARTx == USART1)
        {
            USART1_Clk_Dis();
        }
        else if(pUSARTx == USART2)
        {
            USART2_Clk_Dis();
        }
        else if(pUSARTx == USART6)
        {
            USART6_Clk_Dis();
        }
    }
}


void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg=0;

	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);


	if (pUSARTHandle->USART_Config.USART_Mode==USART_MODE_ONLY_RX){
		tempreg|=(1<<USART_CR1_RE);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode==USART_MODE_ONLY_TX){
		tempreg|=(1<<USART_CR1_TE);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode==USART_MODE_TXRX){
		tempreg|=(1<<USART_CR1_RE)|(1<<USART_CR1_TE);
	}
	tempreg|=(pUSARTHandle->USART_Config.USART_WordLength<<USART_CR1_M);

	//parity
	if (pUSARTHandle->USART_Config.USART_ParityControl==USART_PARITY_EN_EVEN){
		tempreg|=(1<<USART_CR1_PCE);
		//no need of enabling PS
	}
	else if (pUSARTHandle->USART_Config.USART_ParityControl==USART_PARITY_EN_ODD){
		tempreg|=(1<<USART_CR1_PCE);
		tempreg|=(1<<USART_CR1_PS);
	}
	//update cr1
	pUSARTHandle->pUSARTx->CR1=tempreg;

	//cr2
	tempreg=0;
	tempreg|=(pUSARTHandle->USART_Config.USART_NoOfStopBits <<USART_CR2_STOP);
	//update cr2
	pUSARTHandle->pUSARTx->CR2=tempreg;

	//cr3
	tempreg=0;
    if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS){
        //Enable CTS flow control
        tempreg |= ( 1 << USART_CR3_CTSE);
    }else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS){
        //Enable RTS flow control
        tempreg |= USART_CR3_RTSE;
    }else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS){
        //Enable both CTS and RTS Flow control
        tempreg |= ( ( 1 << USART_CR3_CTSE) | ( 1 << USART_CR3_RTSE) );
    }
    //update cr3
    pUSARTHandle->pUSARTx->CR3=tempreg;
    //USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
}


void USART_DeInit(USART_RegDef_t *pUSARTx){
	 if (pUSARTx==USART1){
		 USART1_REG_RESET();
	 }
	 else if (pUSARTx==USART2){
		 USART2_REG_RESET();
	 }
	 else if (pUSARTx==USART6){
		 USART6_REG_RESET();
	 }
}


void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len){
	for(uint32_t i=0;i<Len;i++){
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_RXNE));

		if(pUSARTHandle->USART_Config.USART_WordLength==USART_WORDLEN_9BITS){
			if(pUSARTHandle->USART_Config.USART_ParityControl==USART_PARITY_DISABLE){
				*((uint16_t*)pRxBuffer)=pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF;
				pRxBuffer++;
				pRxBuffer++;
			}
			else {
				*pRxBuffer=pUSARTHandle->pUSARTx->DR & (uint8_t)0x00FF;
				pRxBuffer++;
			}
		}
		else{
			if(pUSARTHandle->USART_Config.USART_ParityControl==USART_PARITY_DISABLE){
				*pRxBuffer=(uint8_t) (pUSARTHandle->pUSARTx->DR & (uint8_t)0x00FF);
			}
			else{
				*pRxBuffer=(uint8_t) (pUSARTHandle->pUSARTx->DR & (uint8_t)0x007F);
			}
		}pRxBuffer++;
	}
}

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t flagname){
	if(pUSARTx->SR & flagname){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

