/*
 * STM32F401CCUx.h
 *
 *  Created on: 28-Mar-2026
 *      Author: Muhammad Rabeez
 */

#ifndef STM32F401CCUX_H_
#define STM32F401CCUX_H_
#include <stdint.h>


/*****************************************************************************
 *                          Processor Specific Details                       *
 * Notes:These information you can get from ARM Cortex M4 Generic User Guide *
 *****************************************************************************/

/**
 * @brief NVIC ISER Registers (Interrupt Set Enable)
 * @note  Used to enable interrupt lines in NVIC.
 */
#define __vo volatile
#define NVIC_ISER0  ((__vo uint32_t *)0xE000E100)
#define NVIC_ISER1  ((__vo uint32_t *)0xE000E104)
#define NVIC_ISER2  ((__vo uint32_t *)0xE000E108)
#define NVIC_ISER3  ((__vo uint32_t *)0xE000E10C)

/**
 * @brief NVIC ICER Registers (Interrupt Clear Enable)
 * @note  Used to disable interrupt lines in NVIC.
 */
#define NVIC_ICER0  ((__vo uint32_t *)0XE000E180)
#define NVIC_ICER1  ((__vo uint32_t *)0XE000E184)
#define NVIC_ICER2  ((__vo uint32_t *)0XE000E188)
#define NVIC_ICER3  ((__vo uint32_t *)0XE000E18C)

/* ARM Cortex M4 Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR   ((__vo uint32_t *)0xE000E400)

/**
 * @brief NVIC Interrupt Priority Registers
 * @note  Each interrupt has 8-bit priority, but only upper 4 bits [7:4] are implemented.
 */



//some generic macros

#define ENABLE				1
#define DISABLE				0

#define APB1_BASE_ADDR     0x40000000U
#define APB2_BASE_ADDR     0x40010000U

#define AHB1_BASE_ADDR     0x40020000U
#define AHB2_BASE_ADDR     0x50000000U





//AHB1
#define GPIOA_BASE_ADDR    (AHB1_BASE_ADDR + 0x0000)
#define GPIOB_BASE_ADDR    (AHB1_BASE_ADDR + 0x0400)
#define GPIOC_BASE_ADDR    (AHB1_BASE_ADDR + 0x0800)
#define GPIOD_BASE_ADDR    (AHB1_BASE_ADDR + 0x0C00)
#define GPIOE_BASE_ADDR    (AHB1_BASE_ADDR + 0x1000)
#define GPIOH_BASE_ADDR    (AHB1_BASE_ADDR + 0x1C00)

#define RCC_BASE_ADDR 		0x40023800U


//APB2
#define EXTI_BASEADDR     (APB2_BASE_ADDR + 0x3C00)
#define SYSCFG_BASE_ADDR  (APB2_BASE_ADDR + 0x3800)

//Register Definition struct for GPIO port
typedef struct
{
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFR[2];

}GPIO_RegDef_t;


typedef struct
{
    uint32_t CR;
    uint32_t PLLCFGR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t AHB1RSTR;
    uint32_t AHB2RSTR;
    uint32_t RESERVED0[2];
    uint32_t APB1RSTR;
    uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    uint32_t AHB1ENR;
    uint32_t AHB2ENR;
    uint32_t RESERVED2[2];
    uint32_t APB1ENR;
    uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    uint32_t AHB1LPENR;
    uint32_t AHB2LPENR;
    uint32_t RESERVED4[2];
    uint32_t APB1LPENR;
    uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    uint32_t BDCR;
    uint32_t CSR;
    uint32_t RESERVED6[2];
    uint32_t SSCGR;
    uint32_t PLLI2SCFGR;
    uint32_t RESERVED7;
    uint32_t DCKCFGR;
} RCC_RegDef_t;


typedef struct {
     uint32_t IMR;
     uint32_t EMR;
     uint32_t RTSR;
     uint32_t FTSR;
     uint32_t SWIER;
     uint32_t PR;

}EXTI_RegDef_t;


//Pointers to hold base address of Regdef struct
#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASE_ADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASE_ADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOE   ((GPIO_RegDef_t*)GPIOE_BASE_ADDR)
#define GPIOH   ((GPIO_RegDef_t*)GPIOH_BASE_ADDR)

//Pointers for RCC base addr
#define RCC		((RCC_RegDef_t*)RCC_BASE_ADDR)
#define EXTI        ((EXTI_RegDef_t *) EXTI_BASEADDR)
#define SYSCFG      ((SYSCFG_RegDef_t *) SYSCFG_BASEADDR)



//GPIO Clock Enable Macros

#define GPIOA_Clk_En()   (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_Clk_En()   (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_Clk_En()   (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_Clk_En()   (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_Clk_En()   (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_Clk_En()   (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_Clk_En()   (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_Clk_En()   (RCC->AHB1ENR |= (1 << 7))

//GPIO Clock Disable Macros

#define GPIOA_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_Clk_Dis()   (RCC->AHB1ENR &= ~(1 << 7))


//GPIO deinit()
#define GPIOA_REG_RESET()  do{ (RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET()  do{ (RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()  do{ (RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()  do{ (RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()  do{ (RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOH_REG_RESET()  do{ (RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); }while(0)

#endif /* STM32F401CCUX_H_ */
