/*
 * rcc_driver.h
 *
 *  Created on: 20-Sept-2026
 *      Author: Muhammad Rabeez
 */

#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_

#include"STM32F401CCUx.h"

uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);

uint32_t GetPLLOutputClk();
#endif /* RCC_DRIVER_H_ */
