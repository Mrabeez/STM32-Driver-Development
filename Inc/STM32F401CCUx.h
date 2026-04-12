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
#define SET             	ENABLE
#define RESET           	DISABLE
#define GPIO_PIN_SET    	SET
#define GPIO_PIN_RESET  	RESET
#define FLAG_RESET      	RESET
#define FLAG_SET        	SET

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
#define USART1_BASE_ADDR   (APB2_BASE_ADDR + 0x1000)
#define USART6_BASE_ADDR   (APB2_BASE_ADDR + 0x1400)

//APB1
#define USART2_BASE_ADDR   (APB1_BASE_ADDR + 0x4400)

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


typedef struct
{
    __vo uint32_t SR;
    __vo uint32_t DR;
    __vo uint32_t BRR;
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t CR3;
    __vo uint32_t GTPR;
} USART_RegDef_t;


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
#define USART1  ((USART_RegDef_t*)USART1_BASE_ADDR)
#define USART2  ((USART_RegDef_t*)USART2_BASE_ADDR)
#define USART6  ((USART_RegDef_t*)USART6_BASE_ADDR)


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

//USART deinit()
#define USART1_REG_RESET() do{(RCC->APB2RSTR |= (1<<2));   (RCC->APB2RSTR &= ~(1<<2)); }while(0)
#define USART2_REG_RESET() do{(RCC->APB1RSTR |= (1<<17));  (RCC->APB1RSTR &= ~(1<<17)); }while(0)
#define USART6_REG_RESET() do{(RCC->APB2RSTR |= (1<<5));   (RCC->APB2RSTR &= ~(1<<5)); }while(0)


//--------usart-----------
//USART clock enable macros
#define USART1_Clk_En()   (RCC->APB2ENR |= (1 << 4))
#define USART6_Clk_En()   (RCC->APB2ENR |= (1 << 5))
#define USART2_Clk_En()   (RCC->APB1ENR |= (1 << 17))

//USART clock disable macro
#define USART1_Clk_Dis()   (RCC->APB2ENR &= ~(1 << 4))
#define USART6_Clk_Dis()   (RCC->APB2ENR &= ~(1 << 5))
#define USART2_Clk_Dis()   (RCC->APB1ENR &= ~(1 << 17))

//USAR peripheral reset macro
#define USART1_Reg_Reset()  do{ (RCC->APB2RSTR |= (1 << 4));  (RCC->APB2RSTR &= ~(1 << 4));} while(0)
#define USART2_Reg_Reset()  do{ (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); } while(0)
#define USART2_Reg_Reset()  do{ (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); } while()











/*
 * USART Control Register 1 (USART_CR1)
 */
#define USART_CR1_SBK            0   // Send Break
#define USART_CR1_RWU            1   // Receiver Wakeup
#define USART_CR1_RE             2   // Receiver Enable
#define USART_CR1_TE             3   // Transmitter Enable
#define USART_CR1_IDLEIE         4   // IDLE Interrupt Enable
#define USART_CR1_RXNEIE         5   // RXNE Interrupt Enable
#define USART_CR1_TCIE           6   // Transmission Complete Interrupt Enable
#define USART_CR1_TXEIE          7   // TXE Interrupt Enable
#define USART_CR1_PEIE           8   // Parity Error Interrupt Enable
#define USART_CR1_PS             9   // Parity Selection (0: Even, 1: Odd)
#define USART_CR1_PCE            10  // Parity Control Enable
#define USART_CR1_WAKE           11  // Wakeup Method (Idle / Address Mark)
#define USART_CR1_M              12  // Word Length (0: 8-bit, 1: 9-bit)
#define USART_CR1_UE             13  // USART Enable
#define USART_CR1_OVER8          15  // Oversampling Mode (1: By 8, 0: By 16)

/*
 * USART Control Register 2 (USART_CR2)
 */

#define USART_CR2_ADD            0   // Address of the USART (for multiprocessor mode)
#define USART_CR2_LBDL           5   // LIN Break Detection Length
#define USART_CR2_LBDIE          6   // LIN Break Detection Interrupt Enable
#define USART_CR2_LBCL           8   // Last Bit Clock Pulse
#define USART_CR2_CPHA           9   // Clock Phase
#define USART_CR2_CPOL           10  // Clock Polarity
#define USART_CR2_CLKEN          11  // Clock Enable (synchronous mode)
#define USART_CR2_STOP           12  // STOP Bits (12–13)
#define USART_CR2_LINEN          14  // LIN Mode Enable

/*
 * USART Control Register 3 (USART_CR3)
 */

#define USART_CR3_EIE            0   // Error Interrupt Enable (ORE/FE/NF)
#define USART_CR3_IREN           1   // IrDA Mode Enable
#define USART_CR3_IRLP           2   // IrDA Low-Power Mode
#define USART_CR3_HDSEL          3   // Half-Duplex Selection
#define USART_CR3_NACK           4   // Smartcard NACK Enable
#define USART_CR3_SCEN           5   // Smartcard Mode Enable
#define USART_CR3_DMAR           6   // DMA Enable Receiver
#define USART_CR3_DMAT           7   // DMA Enable Transmitter
#define USART_CR3_RTSE           8   // RTS Hardware Flow Control Enable
#define USART_CR3_CTSE           9   // CTS Hardware Flow Control Enable
#define USART_CR3_CTSIE          10  // CTS Interrupt Enable
#define USART_CR3_ONEBIT         11  // One Sample Bit Method Enable

/*
 * USART Status Register (USART_SR)
 */
#define USART_SR_PE              0   // Parity Error
#define USART_SR_FE              1   // Framing Error
#define USART_SR_NF              2   // Noise Flag
#define USART_SR_ORE             3   // Overrun Error
#define USART_SR_IDLE            4   // IDLE Line Detected
#define USART_SR_RXNE            5   // Read Data Register Not Empty
#define USART_SR_TC              6   // Transmission Complete
#define USART_SR_TXE             7   // Transmit Data Register Empty
#define USART_SR_LBD             8   // LIN Break Detection Flag
#define USART_SR_CTS             9   // CTS Flag (if CTS enabled)
#endif /* STM32F401CCUX_H_ */

