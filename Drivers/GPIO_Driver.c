/*
 * GPIO_Driver.c
 *
 *  Created on: 30-Mar-2026
 *      Author: Muhammad Rabeez
 */


void GPIO_Clockcontrol(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx==GPIOA)
		{
			GPIOA_Clk_En();
		}
		else if(pGPIOx==GPIOB)
		{
			GPIOB_Clk_En();
		}
	}
}
