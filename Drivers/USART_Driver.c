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
        tempreg |= (1<<USART_CR3_RTSE);
    }else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS){
        //Enable both CTS and RTS Flow control
        tempreg |= ( ( 1 << USART_CR3_CTSE) | ( 1 << USART_CR3_RTSE) );
    }
    //update cr3
    pUSARTHandle->pUSARTx->CR3=tempreg;
    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
    USART_PeripheralControl(pUSARTHandle->pUSARTx, ENABLE);
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

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len){
	for(uint32_t i=0;i<Len;i++){
		while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_TXE));
		if(pUSARTHandle->USART_Config.USART_WordLength==USART_WORDLEN_9BITS){
			if(pUSARTHandle->USART_Config.USART_ParityControl==USART_PARITY_DISABLE){
				pUSARTHandle->pUSARTx->DR = (*((uint16_t*)pTxBuffer) & 0x01FF);
				pTxBuffer++;
				pTxBuffer++;
			}
			else {
				pUSARTHandle->pUSARTx->DR =*pTxBuffer & 0x00FF;
				pTxBuffer++;
			}
		}
		else{
			if(pUSARTHandle->USART_Config.USART_ParityControl==USART_PARITY_DISABLE){
				pUSARTHandle->pUSARTx->DR= *pTxBuffer & 0x0FF;
						pTxBuffer++;
			}
			else{
				pUSARTHandle->pUSARTx->DR= *pTxBuffer& 0x07F;
										pTxBuffer++;
			}


		}
	}
}


uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t flagname){
	if(pUSARTx->SR & flagname){
		return FLAG_SET;
	}
	return FLAG_RESET;
}


void USART_PeripheralControl(USART_RegDef_t *pUSARTx,uint8_t EnOrDi){
	if (EnOrDi==ENABLE){
		pUSARTx->CR1|=(1<<USART_CR1_UE);
	}
	else {
		pUSARTx->CR1&=~(1<<USART_CR1_UE);
	}
}




void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate){
	uint32_t PCLKx,usartdiv;
	uint32_t M_part,F_part,tempreg=0;

	if (pUSARTx==USART1|| pUSARTx==USART6){
		PCLKx=RCC_GetPCLK2Value();
	}
	else{
		PCLKx=RCC_GetPCLK1Value();
	}

//	if((RCC->CR>>15)&0x01){
	if((pUSARTx->CR1 >>USART_CR1_OVER8)&0x01){
		usartdiv = ((25 * PCLKx) / (2 *BaudRate));
	}
	else{
		usartdiv = ((25 * PCLKx) / (4 *BaudRate));
	}
//	Mantissa part
	M_part=usartdiv/100;
	tempreg|=M_part<<4;
// 	Fraction part
	F_part=usartdiv-(M_part*100);
	if((pUSARTx->CR1)&(1<<USART_CR1_OVER8)){
		F_part = ((( F_part * 8)+ 50) / 100)& (0x07);
	}
	else{
		 F_part = ((( F_part * 16)+ 50) / 100) & (0x0F);
	}

	tempreg|=F_part;
	pUSARTx->BRR=tempreg;
}



//interrupt
void USART_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnOrDi){

	uint8_t regindex=IRQNumber/32;
	uint8_t bit_pos=IRQNumber%32;

	if (EnOrDi==ENABLE){
		if (regindex==0) *NVIC_ISER0 |= (1 << bit_pos);
		else if (regindex==1) *NVIC_ISER1 |= (1 << bit_pos);
		else if (regindex==2) *NVIC_ISER2 |= (1 << bit_pos);
		else if (regindex==3) *NVIC_ISER3 |= (1 << bit_pos);
	}

	else{
		if (regindex==0) *NVIC_ICER0 |= (1 << bit_pos);
		else if (regindex==1) *NVIC_ICER1 |= (1 << bit_pos);
		else if (regindex==2) *NVIC_ICER2 |= (1 << bit_pos);
		else if (regindex==3) *NVIC_ICER3 |= (1 << bit_pos);
	}
}



void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;

	uint8_t shift = (8 * iprx_section) + (8 - 4);

	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift);
}


uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle ,uint8_t *pTxBuffer ,uint32_t Len){
	uint8_t txstate=pUSARTHandle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX){
		pUSARTHandle->TxLen=Len;
		pUSARTHandle->pTxBuffer=pTxBuffer;
		pUSARTHandle->TxBusyState= USART_BUSY_IN_TX;

		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);

		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);
	}
	return txstate;
}

uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle ,uint8_t *pTxBuffer ,uint32_t Len){
	uint8_t rxstate =pUSARTHandle->RxBusyState;

	if(rxstate !=USART_BUSY_IN_RX){
		pUSARTHandle->TxLen=Len;
		pUSARTHandle->pTxBuffer=pTxBuffer;
		pUSARTHandle->TxBusyState=USART_BUSY_IN_RX;

		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);
	}
}

static void usart_handle_tc(USART_Handle_t *pUSARTHandle);
static void usart_handle_txe(USART_Handle_t *pUSARTHandle);
static void usart_handle_rxne(USART_Handle_t *pUSARTHandle);
static void usart_handle_cts(USART_Handle_t *pUSARTHandle);
static void usart_handle_idle(USART_Handle_t *pUSARTHandle);
static void usart_handle_ore(USART_Handle_t *pUSARTHandle);
static void usart_handle_error_flags(USART_Handle_t *pUSARTHandle, uint32_t sr);

void USART_IRQHandling(USART_Handle_t *pUSARTHandle){
	uint32_t sr = pUSARTHandle->pUSARTx->SR;
	uint32_t cr1 = pUSARTHandle->pUSARTx->CR1;
	uint32_t cr3 = pUSARTHandle->pUSARTx->CR3;

	if ((sr & (1 << USART_SR_TC)) && (cr1 & (1 << USART_CR1_TCIE))){
	    usart_handle_tc(pUSARTHandle);
	}

	if ((sr & (1 << USART_SR_TXE)) && (cr1 & (1 << USART_CR1_TXEIE))){
	    usart_handle_txe(pUSARTHandle);
	}

	if ((sr & (1 << USART_SR_RXNE)) && (cr1 & (1 << USART_CR1_RXNEIE))){
	    usart_handle_rxne(pUSARTHandle);
	}

	if ((sr & (1 << USART_SR_CTS)) && (cr3 & (1 << USART_CR3_CTSIE))){
	    usart_handle_cts(pUSARTHandle);
	}

	if ((sr & (1 << USART_SR_IDLE)) && (cr1 & (1 << USART_CR1_IDLEIE))){
	    usart_handle_idle(pUSARTHandle);
	}

	if ((sr & (1 << USART_SR_ORE)) && (cr3 & (1 << USART_CR3_EIE))){
	    usart_handle_ore(pUSARTHandle);
	}
	if (cr3 & (1 << USART_CR3_EIE)){
	    usart_handle_error_flags(pUSARTHandle, sr);
	}
}


__weak USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv){
	 // This is a weak implementation. The application may override this function.
}


