#include "tft_hal.h"
#include "TM4C123.h"                    // Device header


/**
 * CS	PE0
 * RS	PE1
 * WR   PE2
 * RD	PE3
 * RST	PE4
 * DP_LO PB[0-7]
 * DP_HI_LO	PA[4-7]
 * DP_HI_HI PC[4-7]
 */

void TFT_HAL_init(){
	SYSCTL->RCGCGPIO|=(0x1<<0)|(0x1<<1)|(0x1<<2)|(0x1<<4);
	GPIOB->DEN|=0xFF;
	GPIOA->DEN|=0xF0;
	GPIOC->DEN|=0xF0;
	GPIOE->DEN|=0x1F;
	
	GPIOB->DIR|=0xFF;
	GPIOA->DIR|=0xF0;
	GPIOC->DIR|=0xF0;
	GPIOE->DIR|=0x1F;
	
	GPIOB->DATA&=~0xFF;
	GPIOA->DATA&=~0xF0;
	GPIOC->DATA&=~0xF0;
	GPIOE->DATA&=~0x1F;
}

void TFT_HAL_DP_Lo(unsigned char data){
	GPIOB->DATA=data;
}

void TFT_HAL_DP_Hi(unsigned char data){
	((uint32_t*)(GPIOA))[0xF0]=(data<<4)&(0xF0);
	((uint32_t*)(GPIOC))[0xF0]=(data<<0)&(0xF0);
}

void TFT_HAL_CS(unsigned char data){
	((uint32_t*)(GPIOE))[(0x1<<0)]=(data<<0);
}

void TFT_HAL_RS(unsigned char data){
	((uint32_t*)(GPIOE))[(0x1<<1)]=(data<<1);
}

void TFT_HAL_WR(unsigned char data){
	((uint32_t*)(GPIOE))[(0x1<<2)]=(data<<2);
}

void TFT_HAL_RD(unsigned char data){
	((uint32_t*)(GPIOE))[(0x1<<3)]=(data<<3);
}

void TFT_HAL_RST(unsigned char data){
	((uint32_t*)(GPIOE))[(0x1<<4)]=(data<<4);
}

