/*
 * rcc_driver.c
 *
 *  Created on: 20-Sept-2026
 *      Author: Muhammad Rabeez
 */

#include"rcc_driver.h"



const uint16_t AHB_PreScaler[8] ={2, 4, 8, 16, 64, 128, 256, 512};


const uint8_t  APB_PreScaler[4] = { 2, 4 , 8, 16};

uint32_t RCC_GetPCLK1Value(void){
uint32_t SysClk, pclk1,ahbp;
uint8_t clksrc,temp,apb1p;

clksrc =((RCC->CFGR >>2)&0x03);

if (clksrc==0x00){
	SysClk=16000000U;
}
else if (clksrc==0x01){
	SysClk=8000000U;
}
else if (clksrc==0x02){
	SysClk=GetPLLOutputClk();
}


//for the  AHB prescaler
temp =((RCC->CFGR>>0x04)&0x0F);
if (temp <8){
	ahbp=1;
}
else {
	ahbp=AHB_PreScaler[temp-8];
}

//for APB1 prescaler
temp=((RCC->CFGR>>10)&0x07);
if (temp<4){
	apb1p=1;
}
else {
	apb1p=APB_PreScaler[temp-4];
}



pclk1 =  (SysClk / ahbp) /apb1p;

return pclk1;
}

uint32_t RCC_GetPCLK2Value(void){
	uint32_t SysClk,pclk2,ahbp ;
	uint8_t clksrc,temp,apb2p;

	clksrc=((RCC->CFGR >>2)&0x03);

	if (clksrc==0){
		SysClk=16000000U;
	}
	else if (clksrc==1){
		SysClk=8000000U;
	}else if(clksrc == 0x02){
        SysClk = GetPLLOutputClk();
	}

	temp=((RCC->CFGR >> 4)&0x0f);
	if (temp<8){
		ahbp=1;
	}
	else{
		ahbp=AHB_PreScaler[temp-8];
	}


	temp=((RCC->CFGR>> 13)&0x07);
	if (temp<4){
		apb2p=1;
	}
	else{
		apb2p=APB_PreScaler[temp-4];
	}
	pclk2 =  (SysClk / ahbp) /apb2p;

	return pclk2;
}



uint32_t GetPLLOutputClk(){
	/*TODO : implement PLL output calculation if your system uses PLL as SYSCLK ,
	 	 	 for now return 0 to show it is not implemented
	*/
	return 0;

}


