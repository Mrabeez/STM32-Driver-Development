/*
 * GPIO_Driver.c
 *
 *  Created on: 30-Mar-2026
 *      Author: Muhammad Rabeez
 */
#include"GPIO_Driver.h"

void GPIO_Clockcontrol(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_Clk_En();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_Clk_En();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_Clk_En();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_Clk_En();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_Clk_En();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_Clk_En();
        }
    }
    else if(EnorDi == DISABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_Clk_Dis();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_Clk_Dis();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_Clk_Dis();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_Clk_Dis();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_Clk_Dis();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_Clk_Dis();
        }
    }
}


void GPIO_Init(GPIO_RegDef_t *pGPIOx, GPIO_Init_t*pGPIOInit)
{
	//set mode of GPIO pin
	uint32_t temp = 0;
	temp |= (pGPIOInit->GPIO_PinMode <<( 2*pGPIOInit->GPIO_PinNumber));
	pGPIOx ->MODER &= ~(3 << (2*pGPIOInit->GPIO_PinNumber));
	pGPIOx ->MODER |=temp;

	//set GPIO output type
	temp = 0;
	temp |= (pGPIOInit->GPIO_PinOPType <<( pGPIOInit->GPIO_PinNumber ));
	pGPIOx ->OTYPER &= ~(1 << (pGPIOInit->GPIO_PinNumber));
	pGPIOx ->OTYPER |=temp;


	//set GPIO pin speed
	temp = 0;
	temp |= (pGPIOInit->GPIO_PinSpeed <<( 2*pGPIOInit->GPIO_PinNumber ));
	pGPIOx ->OSPEEDR &= ~(3 << (2*pGPIOInit->GPIO_PinNumber));
	pGPIOx ->OSPEEDR |=temp;

	//set GPIO Pull-up Pull-down
	temp = 0;
	temp |= (pGPIOInit->GPIO_PinPuPdControl << (2 * pGPIOInit->GPIO_PinNumber));
	pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOInit->GPIO_PinNumber));
	pGPIOx->PUPDR |=  temp;

	//set GPIO Alternate Function
	temp=0;
	uint8_t temp1;
	uint8_t temp2;
	if(pGPIOInit->GPIO_PinMode == 2)
	{
		temp1 = pGPIOInit->GPIO_PinNumber /8;
		temp2 = pGPIOInit->GPIO_PinNumber %8;

		temp |= (pGPIOInit->GPIO_PinAltFunMode<< (4 * temp2));
		pGPIOx->AFR[temp1] &= ~(15 << (4 * temp2));
		pGPIOx->AFR[temp1] |=temp;
	}

}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
}


uint8_t GPIO_ReadFromIn_Pin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber){
	uint8_t value;
	value=(uint8_t)(pGPIOx->IDR >>PinNumber & 0x1);
	return value;
}


uint16_t GPIO_ReadFromIn_Port(GPIO_RegDef_t *pGPIOx){
		uint16_t value;
		value=(uint16_t)(pGPIOx->IDR);
		return value;
}


void GPIO_WriteToOut_Pin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value)
{
	if(value ==1){
		pGPIOx->ODR |= (1<<PinNumber);
	}
	else{
		pGPIOx->ODR &=~(1<<PinNumber);
	}
}


void GPIO_WriteToOut_Port(GPIO_RegDef_t *pGPIOx,uint16_t value){
	pGPIOx->ODR = value;
}


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber){
	pGPIOx->ODR ^= (1<<PinNumber);

}


void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	uint8_t reg_index =IRQNumber /32;
	uint8_t bit_pos =IRQNumber %32;

	if (EnorDi == ENABLE)
	    {
	        if (reg_index == 0) *NVIC_ISER0 |= (1 << bit_pos);
	        else if (reg_index == 1) *NVIC_ISER1 |= (1 << bit_pos);
	        else if (reg_index == 2) *NVIC_ISER2 |= (1 << bit_pos);
	        else if (reg_index == 3) *NVIC_ISER3 |= (1 << bit_pos);
	    }
	    else
	    {
	        if (reg_index == 0) *NVIC_ICER0 |= (1 << bit_pos);
	        else if (reg_index == 1) *NVIC_ICER1 |= (1 << bit_pos);
	        else if (reg_index == 2) *NVIC_ICER2 |= (1 << bit_pos);
	        else if (reg_index == 3) *NVIC_ICER3 |= (1 << bit_pos);
	    }
}

void GPIO_IRQPriorityConfig (uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    uint8_t shift = (8 * iprx_section) + (8 - 4); // 4 bits implemented

    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift);
}
void GPIO_IRQHandling(uint8_t PinNumber){
	if (EXTI->PR & (1<<PinNumber)){
		EXTI->PR |=(1<<PinNumber);
	}
}
