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


