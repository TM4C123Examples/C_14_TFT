#ifndef TFT_HAL_H
#define TFT_HAL_H

void TFT_HAL_DP_Lo(unsigned char data);
void TFT_HAL_DP_Hi(unsigned char data);
void TFT_HAL_WR(unsigned char data);
void TFT_HAL_RD(unsigned char data);
void TFT_HAL_CS(unsigned char data);
void TFT_HAL_RS(unsigned char data);
void TFT_HAL_RST(unsigned char data);

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

#endif