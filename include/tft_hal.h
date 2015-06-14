#ifndef TFT_HAL_H
#define TFT_HAL_H

void TFT_HAL_DP_Lo(unsigned char data);
void TFT_HAL_DP_Hi(unsigned char data);
void TFT_HAL_WR(unsigned char data);
void TFT_HAL_RD(unsigned char data);
void TFT_HAL_CS(unsigned char data);
void TFT_HAL_RS(unsigned char data);
void TFT_HAL_RST(unsigned char data);
void TFT_HAL_init();
#endif