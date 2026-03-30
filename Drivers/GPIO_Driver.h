/*
 * GPIO_Driver.h
 *
 *  Created on: 30-Mar-2026
 *      Author: Muhammad Rabeez
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include"STM32F401CCUx.h"
//Clock enable or disable API

void GPIO_Clockcontrol(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

//GPIO init and GPIO deint

void GPIO_Init(void);
void GPIO_DeInit(void);

//Read write

void GPIO_ReadFromIn_Pin(void);
void GPIO_ReadFromIn_Port(void);

void GPIO_WriteToOut_Pin(void);
void GPIO_WriteToOut_Port(void);



#endif /* GPIO_DRIVER_H_ */
