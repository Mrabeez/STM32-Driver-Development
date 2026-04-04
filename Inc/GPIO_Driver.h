/*
 * GPIO_Driver.h
 *
 *  Created on: 30-Mar-2026
 *      Author: Muhammad Rabeez
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include"STM32F401CCUx.h"

//GPIO pin configuration
typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinAltFunMode;
} GPIO_Init_t;


//GPIO Mode
#define GPIO_MODE_IN	       0
#define GPIO_MODE_OUT          1
#define GPIO_MODE_ALTFUN       2
#define GPIO_MODE_ANALOG       3

// GPIO Output Type
#define GPIO_OP_TYPE_PP   0
#define GPIO_OP_TYPE_OD   1


// GPIO Output Speed
#define GPIO_SPEED_LOW        0
#define GPIO_SPEED_MEDIUM     1
#define GPIO_SPEED_HIGH       2
#define GPIO_SPEED_VERYHIGH   3

// GPIO Pull-up Pull-down
#define GPIO_NO_PUPD     0
#define GPIO_PIN_PU      1
#define GPIO_PIN_PD      2

// GPIO Alternate Function
#define GPIO_AF0    0
#define GPIO_AF1    1
#define GPIO_AF2    2
#define GPIO_AF3    3
#define GPIO_AF4    4
#define GPIO_AF5    5
#define GPIO_AF6    6
#define GPIO_AF7    7
#define GPIO_AF8    8
#define GPIO_AF9    9
#define GPIO_AF10   10
#define GPIO_AF11   11
#define GPIO_AF12   12
#define GPIO_AF13   13
#define GPIO_AF14   14
#define GPIO_AF15   15



//Clock enable or disable API
void GPIO_Clockcontrol(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

//GPIO init and GPIO deint
void GPIO_Init(GPIO_RegDef_t *pGPIOx, GPIO_Init_t*pGPIOInit);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//Read write
uint8_t GPIO_ReadFromIn_Pin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromIn_Port(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOut_Pin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value);
void GPIO_WriteToOut_Port(GPIO_RegDef_t *pGPIOx,uint8_t value);



#endif /* GPIO_DRIVER_H_ */
