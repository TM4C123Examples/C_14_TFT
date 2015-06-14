#include <string.h>
#include <stdio.h>
#include "tft_hal.h"

#define Lo(X) (((unsigned char *)(&X))[0])
#define Hi(X) (((unsigned char *)(&X))[1])
#define fabs(X) ((X)>0? (X) : (-1)*(X))

void  delay_ms(int delay);

const unsigned short Black = 0;
const unsigned short Red = 63488;
const unsigned short Green = 2016;
const unsigned short Blue = 31;
const unsigned short White = 65535;
const unsigned short Purple = 61727;
const unsigned short Yellow = 65504;
const unsigned short Cyan = 2047;
const unsigned short d_gray = 21130;
const unsigned short l_gray = 31727;


const char FONT_8x8[784] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // space 0x20
0x30,0x78,0x78,0x30,0x30,0x00,0x30,0x00, // !
0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00, // "
0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00, // #
0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00, // $
0x00,0x63,0x66,0x0C,0x18,0x33,0x63,0x00, // %
0x1C,0x36,0x1C,0x3B,0x6E,0x66,0x3B,0x00, // &
0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00, // '
0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00, // (
0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00, // )
0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00, // *
0x00,0x30,0x30,0xFC,0x30,0x30,0x00,0x00, // +
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30, // ,
0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00, // -
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00, // .
0x03,0x06,0x0C,0x18,0x30,0x60,0x40,0x00, // ' (forward slash)
0x3E,0x63,0x63,0x6B,0x63,0x63,0x3E,0x00, // 0 0x30
0x18,0x38,0x58,0x18,0x18,0x18,0x7E,0x00, // 1
0x3C,0x66,0x06,0x1C,0x30,0x66,0x7E,0x00, // 2
0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0x00, // 3
0x0E,0x1E,0x36,0x66,0x7F,0x06,0x0F,0x00, // 4
0x7E,0x60,0x7C,0x06,0x06,0x66,0x3C,0x00, // 5
0x1C,0x30,0x60,0x7C,0x66,0x66,0x3C,0x00, // 6
0x7E,0x66,0x06,0x0C,0x18,0x18,0x18,0x00, // 7
0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00, // 8
0x3C,0x66,0x66,0x3E,0x06,0x0C,0x38,0x00, // 9
0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00, // :
0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30, // ;
0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00, // <
0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00, // =
0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x00, // >
0x3C,0x66,0x06,0x0C,0x18,0x00,0x18,0x00, // ?
0x3E,0x63,0x6F,0x69,0x6F,0x60,0x3E,0x00, // @ 0x40
0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x00, // A
0x7E,0x33,0x33,0x3E,0x33,0x33,0x7E,0x00, // B
0x1E,0x33,0x60,0x60,0x60,0x33,0x1E,0x00, // C
0x7C,0x36,0x33,0x33,0x33,0x36,0x7C,0x00, // D
0x7F,0x31,0x34,0x3C,0x34,0x31,0x7F,0x00, // E
0x7F,0x31,0x34,0x3C,0x34,0x30,0x78,0x00, // F
0x1E,0x33,0x60,0x60,0x67,0x33,0x1F,0x00, // G
0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00, // H
0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00, // I
0x0F,0x06,0x06,0x06,0x66,0x66,0x3C,0x00, // J
0x73,0x33,0x36,0x3C,0x36,0x33,0x73,0x00, // K
0x78,0x30,0x30,0x30,0x31,0x33,0x7F,0x00, // L
0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00, // M
0x63,0x73,0x7B,0x6F,0x67,0x63,0x63,0x00, // N
0x3E,0x63,0x63,0x63,0x63,0x63,0x3E,0x00, // O
0x7E,0x33,0x33,0x3E,0x30,0x30,0x78,0x00, // P 0x50
0x3C,0x66,0x66,0x66,0x6E,0x3C,0x0E,0x00, // Q
0x7E,0x33,0x33,0x3E,0x36,0x33,0x73,0x00, // R
0x3C,0x66,0x30,0x18,0x0C,0x66,0x3C,0x00, // S
0x7E,0x5A,0x18,0x18,0x18,0x18,0x3C,0x00, // T
0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x00, // U
0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00, // V
0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00, // W
0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00, // X
0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00, // Y
0x7F,0x63,0x46,0x0C,0x19,0x33,0x7F,0x00, // Z
0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00, // [
0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x00, // \ (back slash)
0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00, // ]
0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00, // ^
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF, // _
0x18,0x18,0x0C,0x00,0x00,0x00,0x00,0x00, // ` 0x60
0x00,0x00,0x3C,0x06,0x3E,0x66,0x3B,0x00, // a
0x70,0x30,0x3E,0x33,0x33,0x33,0x6E,0x00, // b
0x00,0x00,0x3C,0x66,0x60,0x66,0x3C,0x00, // c
0x0E,0x06,0x3E,0x66,0x66,0x66,0x3B,0x00, // d
0x00,0x00,0x3C,0x66,0x7E,0x60,0x3C,0x00, // e
0x1C,0x36,0x30,0x78,0x30,0x30,0x78,0x00, // f
0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x7C, // g
0x70,0x30,0x36,0x3B,0x33,0x33,0x73,0x00, // h
0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00, // i
0x06,0x00,0x06,0x06,0x06,0x66,0x66,0x3C, // j
0x70,0x30,0x33,0x36,0x3C,0x36,0x73,0x00, // k
0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00, // l
0x00,0x00,0x66,0x7F,0x7F,0x6B,0x63,0x00, // m
0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x00, // n
0x00,0x00,0x3C,0x66,0x66,0x66,0x3C,0x00, // o
0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x78, // p 0x70
0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x0F, // q
0x00,0x00,0x6E,0x3B,0x33,0x30,0x78,0x00, // r
0x00,0x00,0x3E,0x60,0x3C,0x06,0x7C,0x00, // s
0x08,0x18,0x3E,0x18,0x18,0x1A,0x0C,0x00, // t
0x00,0x00,0x66,0x66,0x66,0x66,0x3B,0x00, // u
0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x00, // v
0x00,0x00,0x63,0x6B,0x7F,0x7F,0x36,0x00, // w
0x00,0x00,0x63,0x36,0x1C,0x36,0x63,0x00, // x
0x00,0x00,0x66,0x66,0x66,0x3E,0x06,0x7C, // y
0x00,0x00,0x7E,0x4C,0x18,0x32,0x7E,0x00, // z
0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00, // {
0x0C,0x0C,0x0C,0x00,0x0C,0x0C,0x0C,0x00, // |
0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00, // }
0x3B,0x6E,0x00,0x00,0x00,0x00,0x00,0x00, // ~
0x1C,0x36,0x36,0x1C,0x00,0x00,0x00,0x00, // DEL
0x60,0x90,0x90,0x60,0x00,0x00,0x00,0x00,  // DEGREE use:�
0x22,0x77,0x7f,0x7f,0x3e,0x1c,0x08,0x00         //HEART use:�
};

const char FONT_16x16[3040]  = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  <Space>
0x00,0x00,0x00,0x00,0x07,0x00,0x0F,0x80,0x0F,0x80,0x0F,0x80,0x0F,0x80,0x0F,0x80,0x07,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x00,0x00, // !
0x00,0x00,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x06,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // "
0x00,0x00,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x7F,0xFE,0x7F,0xFE,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x7F,0xFE,0x7F,0xFE,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x00,0x00, // #
0x00,0x00,0x02,0x40,0x02,0x40,0x0F,0xF8,0x1F,0xF8,0x1A,0x40,0x1A,0x40,0x1F,0xF0,0x0F,0xF8,0x02,0x58,0x02,0x58,0x1F,0xF8,0x1F,0xF0,0x02,0x40,0x02,0x40,0x00,0x00, // $
0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x10,0x0E,0x30,0x0E,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x70,0x0C,0x70,0x08,0x70,0x00,0x00,0x00,0x00,0x00,0x00, // %
0x00,0x00,0x00,0x00,0x0F,0x00,0x19,0x80,0x19,0x80,0x19,0x80,0x0F,0x00,0x0F,0x08,0x0F,0x98,0x19,0xF8,0x18,0xF0,0x18,0xE0,0x19,0xF0,0x0F,0x98,0x00,0x00,0x00,0x00, // &
0x00,0x00,0x00,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
0x00,0x00,0x00,0x00,0x00,0xF0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xF0,0x00,0x00,0x00,0x00, // (
0x00,0x00,0x00,0x00,0x0F,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x0F,0x00,0x00,0x00,0x00,0x00, // )
0x00,0x00,0x00,0x00,0x01,0x80,0x11,0x88,0x09,0x90,0x07,0xE0,0x07,0xE0,0x3F,0xFC,0x3F,0xFC,0x07,0xE0,0x07,0xE0,0x09,0x90,0x11,0x88,0x01,0x80,0x00,0x00,0x00,0x00, // *
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x01,0x80,0x01,0x80,0x0F,0xF0,0x0F,0xF0,0x01,0x80,0x01,0x80,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // +
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x0E,0x00,0x00,0x00, // ,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF8,0x1F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // -
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x00,0x00, // ,
0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x06,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x00,0x1C,0x00,0x00,0x00,0x00,0x00, // '/
0x00,0x00,0x00,0x00,0x0F,0xF0,0x1C,0x38,0x1C,0x78,0x1C,0xF8,0x1C,0xF8,0x1D,0xB8,0x1D,0xB8,0x1F,0x38,0x1F,0x38,0x1E,0x38,0x1C,0x38,0x0F,0xF0,0x00,0x00,0x00,0x00, // 0
0x00,0x00,0x00,0x00,0x01,0x80,0x01,0x80,0x03,0x80,0x1F,0x80,0x1F,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x1F,0xF0,0x00,0x00,0x00,0x00, // 1
0x00,0x00,0x00,0x00,0x0F,0xE0,0x1C,0x70,0x1C,0x38,0x00,0x38,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x38,0x1C,0x38,0x1F,0xF8,0x00,0x00,0x00,0x00, // 2
0x00,0x00,0x00,0x00,0x0F,0xE0,0x1C,0x70,0x1C,0x38,0x00,0x38,0x00,0x70,0x03,0xC0,0x03,0xC0,0x00,0x70,0x00,0x38,0x1C,0x38,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // 3
0x00,0x00,0x00,0x00,0x00,0xE0,0x01,0xE0,0x03,0xE0,0x06,0xE0,0x0C,0xE0,0x18,0xE0,0x1F,0xF8,0x1F,0xF8,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x03,0xF8,0x00,0x00,0x00,0x00, // 4
0x00,0x00,0x00,0x00,0x1F,0xF8,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1F,0xE0,0x1F,0xF0,0x00,0x78,0x00,0x38,0x1C,0x38,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // 5
0x00,0x00,0x00,0x00,0x03,0xE0,0x07,0x00,0x0E,0x00,0x1C,0x00,0x1C,0x00,0x1F,0xF0,0x1F,0xF8,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x0F,0xF0,0x00,0x00,0x00,0x00, // 6
0x00,0x00,0x00,0x00,0x1F,0xFC,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x03,0x80,0x03,0x80,0x00,0x00,0x00,0x00, // 7
0x00,0x00,0x00,0x00,0x0F,0xF0,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1F,0x38,0x07,0xE0,0x07,0xE0,0x1C,0xF8,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x0F,0xF0,0x00,0x00,0x00,0x00, // 8
0x00,0x00,0x00,0x00,0x0F,0xF0,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1F,0xF8,0x0F,0xF8,0x00,0x38,0x00,0x38,0x00,0x70,0x00,0xE0,0x07,0xC0,0x00,0x00,0x00,0x00, // 9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // :
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ;
0x00,0x00,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x00,0x1C,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x00, // <
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x3F,0xFC,0x00,0x00,0x00,0x00,0x3F,0xFC,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // =
0x00,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x00,0x1C,0x00,0x00,0x00, // >
0x00,0x00,0x03,0xC0,0x0F,0xF0,0x1E,0x78,0x18,0x38,0x00,0x38,0x00,0x70,0x00,0xE0,0x01,0xC0,0x01,0xC0,0x00,0x00,0x00,0x00,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x00,0x00, // ?
0x00,0x00,0x0F,0xF8,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0xFC,0x1C,0xFC,0x1C,0xFC,0x1C,0xFC,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1F,0xF0,0x07,0xF8,0x00,0x00, // @
0x00,0x00,0x00,0x00,0x03,0xC0,0x07,0xE0,0x0E,0x70,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1F,0xF8,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x00,0x00,0x00,0x00, // A
0x00,0x00,0x00,0x00,0x1F,0xF0,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0F,0xF0,0x0F,0xF0,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x1F,0xF0,0x00,0x00,0x00,0x00, // B
0x00,0x00,0x00,0x00,0x07,0xF0,0x0E,0x38,0x1C,0x38,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x38,0x0E,0x38,0x07,0xF0,0x00,0x00,0x00,0x00, // C
0x00,0x00,0x00,0x00,0x1F,0xE0,0x0E,0x70,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x70,0x1F,0xE0,0x00,0x00,0x00,0x00, // D
0x00,0x00,0x00,0x00,0x1F,0xF8,0x0E,0x18,0x0E,0x08,0x0E,0x00,0x0E,0x30,0x0F,0xF0,0x0F,0xF0,0x0E,0x30,0x0E,0x00,0x0E,0x08,0x0E,0x18,0x1F,0xF8,0x00,0x00,0x00,0x00, // E
0x00,0x00,0x00,0x00,0x1F,0xF8,0x0E,0x18,0x0E,0x08,0x0E,0x00,0x0E,0x30,0x0F,0xF0,0x0F,0xF0,0x0E,0x30,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x1F,0x00,0x00,0x00,0x00,0x00, // F
0x00,0x00,0x00,0x00,0x07,0xF0,0x0E,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0xF8,0x1C,0x38,0x1C,0x38,0x0E,0x38,0x07,0xF8,0x00,0x00,0x00,0x00, // G
0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1F,0xF0,0x1F,0xF0,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x00,0x00,0x00,0x00, // H
0x00,0x00,0x00,0x00,0x0F,0xE0,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x0F,0xE0,0x00,0x00,0x00,0x00, // I
0x00,0x00,0x00,0x00,0x01,0xFC,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x38,0x70,0x38,0x70,0x38,0x70,0x38,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // J
0x00,0x00,0x00,0x00,0x1E,0x38,0x0E,0x38,0x0E,0x70,0x0E,0xE0,0x0F,0xC0,0x0F,0x80,0x0F,0x80,0x0F,0xC0,0x0E,0xE0,0x0E,0x70,0x0E,0x38,0x1E,0x38,0x00,0x00,0x00,0x00, // K
0x00,0x00,0x00,0x00,0x1F,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x08,0x0E,0x18,0x0E,0x38,0x1F,0xF8,0x00,0x00,0x00,0x00, // L
0x00,0x00,0x00,0x00,0x1C,0x1C,0x1E,0x3C,0x1F,0x7C,0x1F,0xFC,0x1F,0xFC,0x1D,0xDC,0x1C,0x9C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00, // M
0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1E,0x1C,0x1F,0x1C,0x1F,0x9C,0x1D,0xDC,0x1C,0xFC,0x1C,0x7C,0x1C,0x3C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00, // N
0x00,0x00,0x00,0x00,0x03,0xE0,0x07,0xF0,0x0E,0x38,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x0E,0x38,0x07,0xF0,0x03,0xE0,0x00,0x00,0x00,0x00, // O
0x00,0x00,0x00,0x00,0x1F,0xF0,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0F,0xF0,0x0F,0xF0,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x1F,0x00,0x00,0x00,0x00,0x00, // P
0x00,0x00,0x00,0x00,0x03,0xE0,0x0F,0x78,0x0E,0x38,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x7C,0x1C,0xFC,0x0F,0xF8,0x0F,0xF8,0x00,0x38,0x00,0xFC,0x00,0x00, // Q
0x00,0x00,0x00,0x00,0x1F,0xF0,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0F,0xF0,0x0F,0xF0,0x0E,0x70,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x1E,0x38,0x00,0x00,0x00,0x00, // R
0x00,0x00,0x00,0x00,0x0F,0xF0,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x00,0x0F,0xE0,0x07,0xF0,0x00,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x0F,0xF0,0x00,0x00,0x00,0x00, // S
0x00,0x00,0x00,0x00,0x1F,0xFC,0x19,0xCC,0x11,0xC4,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x07,0xF0,0x00,0x00,0x00,0x00, // T
0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // U
0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0E,0xE0,0x07,0xC0,0x03,0x80,0x00,0x00,0x00,0x00, // V
0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x9C,0x1C,0x9C,0x1C,0x9C,0x0F,0xF8,0x0F,0xF8,0x07,0x70,0x07,0x70,0x00,0x00,0x00,0x00, // W
0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0E,0xE0,0x07,0xC0,0x03,0x80,0x03,0x80,0x07,0xC0,0x0E,0xE0,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x00,0x00,0x00,0x00, // X
0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0E,0xE0,0x07,0xC0,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x0F,0xE0,0x00,0x00,0x00,0x00, // Y
0x00,0x00,0x00,0x00,0x1F,0xF8,0x1C,0x38,0x18,0x38,0x10,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x08,0x1C,0x18,0x1C,0x38,0x1F,0xF8,0x00,0x00,0x00,0x00, // Z
0x00,0x00,0x00,0x00,0x07,0xF0,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0xF0,0x00,0x00,0x00,0x00, // [
0x00,0x00,0x00,0x00,0x10,0x00,0x18,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x07,0x00,0x00,0x00,0x00, // <Backslash>
0x00,0x00,0x00,0x00,0x07,0xF0,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x07,0xF0,0x00,0x00,0x00,0x00, // ]
0x00,0x00,0x01,0x80,0x03,0xC0,0x07,0xE0,0x0E,0x70,0x1C,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ^
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0x7F,0xFF, // _
0x00,0x00,0x00,0x00,0x1C,0x00,0x1C,0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x00,0x70,0x00,0x70,0x0F,0xF0,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0F,0xD8,0x00,0x00,0x00,0x00, // a
0x00,0x00,0x00,0x00,0x1E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0F,0xF0,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x1B,0xF0,0x00,0x00,0x00,0x00, // b
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1C,0x70,0x1C,0x70,0x1C,0x00,0x1C,0x00,0x1C,0x70,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // c
0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x70,0x00,0x70,0x00,0x70,0x0F,0xF0,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0F,0xD8,0x00,0x00,0x00,0x00, // d
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1C,0x70,0x1C,0x70,0x1F,0xF0,0x1C,0x00,0x1C,0x70,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // e
0x00,0x00,0x00,0x00,0x03,0xE0,0x07,0x70,0x07,0x70,0x07,0x00,0x07,0x00,0x1F,0xE0,0x1F,0xE0,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x1F,0xC0,0x00,0x00,0x00,0x00, // f
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xD8,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0F,0xF0,0x07,0xF0,0x00,0x70,0x1C,0x70,0x0F,0xE0, // g
0x00,0x00,0x00,0x00,0x1E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0xF0,0x0F,0x38,0x0F,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x1E,0x38,0x00,0x00,0x00,0x00, // h
0x00,0x00,0x00,0x00,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x00,0x00,0x0F,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x0F,0xF8,0x00,0x00,0x00,0x00, // i
0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x00,0x03,0xF0,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x1C,0x70,0x0C,0xF0,0x07,0xE0, // j
0x00,0x00,0x00,0x00,0x1E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x38,0x0E,0x70,0x0E,0xE0,0x0F,0xC0,0x0E,0xE0,0x0E,0x70,0x0E,0x38,0x1E,0x38,0x00,0x00,0x00,0x00, // k
0x00,0x00,0x00,0x00,0x0F,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x0F,0xF8,0x00,0x00,0x00,0x00, // l
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF8,0x1C,0x9C,0x1C,0x9C,0x1C,0x9C,0x1C,0x9C,0x1C,0x9C,0x1C,0x9C,0x1C,0x9C,0x00,0x00,0x00,0x00, // m
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x00,0x00,0x00,0x00, // n
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // o
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0xF0,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0F,0xF0,0x0E,0x00,0x0E,0x00,0x1F,0x00, // p
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xB0,0x38,0xE0,0x38,0xE0,0x38,0xE0,0x38,0xE0,0x38,0xE0,0x1F,0xE0,0x00,0xE0,0x00,0xE0,0x01,0xF0, // q
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0xF0,0x0F,0xF8,0x0F,0x38,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x1F,0x00,0x00,0x00,0x00,0x00, // r
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1C,0x30,0x1C,0x30,0x0F,0x80,0x03,0xE0,0x18,0x70,0x18,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00, // s
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x03,0x00,0x07,0x00,0x1F,0xF0,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x70,0x07,0x70,0x03,0xE0,0x00,0x00,0x00,0x00, // t
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0F,0xD8,0x00,0x00,0x00,0x00, // u
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x0E,0xE0,0x07,0xC0,0x03,0x80,0x00,0x00,0x00,0x00, // v
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x9C,0x1C,0x9C,0x0F,0xF8,0x07,0x70,0x07,0x70,0x00,0x00,0x00,0x00, // w
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0xE0,0x1C,0xE0,0x0F,0xC0,0x07,0x80,0x07,0x80,0x0F,0xC0,0x1C,0xE0,0x1C,0xE0,0x00,0x00,0x00,0x00, // x
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x07,0xF0,0x03,0xE0,0x00,0xE0,0x01,0xC0,0x1F,0x80, // y
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x18,0xE0,0x11,0xC0,0x03,0x80,0x07,0x00,0x0E,0x20,0x1C,0x60,0x1F,0xE0,0x00,0x00,0x00,0x00, // z
0x00,0x00,0x00,0x00,0x01,0xF8,0x03,0x80,0x03,0x80,0x03,0x80,0x07,0x00,0x1C,0x00,0x1C,0x00,0x07,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x01,0xF8,0x00,0x00,0x00,0x00, // {
0x00,0x00,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x00,0x00, // |
0x00,0x00,0x00,0x00,0x1F,0x80,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x00,0xE0,0x00,0x38,0x00,0x38,0x00,0xE0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x1F,0x80,0x00,0x00,0x00,0x00, // }
0x00,0x00,0x00,0x00,0x1F,0x1C,0x3B,0x9C,0x39,0xDC,0x38,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  // ~
};



void Write_Command(unsigned short Wcommand)
{
  TFT_HAL_RD(1);
  TFT_HAL_RS(0);
  TFT_HAL_DP_Hi(Wcommand >> 8);
  TFT_HAL_DP_Lo(Wcommand) ;
  TFT_HAL_WR(0);
  TFT_HAL_WR(1);
}

void Write_Data(unsigned short Wdata)
{
  TFT_HAL_RD(1);
  TFT_HAL_RS(1) ;
  TFT_HAL_DP_Hi(Wdata >>8);
  TFT_HAL_DP_Lo(Wdata);
  TFT_HAL_WR(0);
  TFT_HAL_WR(1);
}

void Write_Command_Data(unsigned short Wcommand,unsigned short Wdata)
{
   Write_Command(Wcommand);
   Write_Data(Wdata);
}

void TFT_Set_Address(unsigned short PX1,unsigned short PY1,unsigned short PX2,unsigned short PY2)
{
  Write_Command_Data(68,(PX2 << 8) + PX1 );  //Column address start2
  Write_Command_Data(69,PY1);      //Column address start1
  Write_Command_Data(70,PY2);  //Column address end2
  Write_Command_Data(78,PX1);      //Column address end1
  Write_Command_Data(79,PY1);  //Row address start2
  Write_Command(34);
}

void TFT_Init()
{
		TFT_HAL_init();
        TFT_HAL_RD(1);
        TFT_HAL_RST(1);
        delay_ms(5);
        TFT_HAL_RST(0);
        delay_ms(15);
        TFT_HAL_RST(1);
        delay_ms(15);
        TFT_HAL_CS(0);
        Write_Command_Data(0x0000,0x0001);
        Write_Command_Data(0x0003,0xA8A4);
        Write_Command_Data(0x000C,0x0000);
        Write_Command_Data(0x000D,0x800C);
        Write_Command_Data(0x000E,0x2B00);
        Write_Command_Data(0x001E,0x00B7);
        Write_Command_Data(0x0001,0x2B3F);
        Write_Command_Data(0x0002,0x0600);
        Write_Command_Data(0x0010,0x0000);
        Write_Command_Data(0x0011,0x6070);
        Write_Command_Data(0x0005,0x0000);
        Write_Command_Data(0x0006,0x0000);
        Write_Command_Data(0x0016,0xEF1C);
        Write_Command_Data(0x0017,0x0003);
        Write_Command_Data(0x0007,0x0233);
        Write_Command_Data(0x000B,0x0000);
        Write_Command_Data(0x000F,0x0000);
        Write_Command_Data(0x0041,0x0000);
        Write_Command_Data(0x0042,0x0000);
        Write_Command_Data(0x0048,0x0000);
        Write_Command_Data(0x0049,0x013F);
        Write_Command_Data(0x004A,0x0000);
        Write_Command_Data(0x004B,0x0000);
        Write_Command_Data(0x0044,0xEF95);
        Write_Command_Data(0x0045,0x0000);
        Write_Command_Data(0x0046,0x013F);
        Write_Command_Data(0x0030,0x0707);
        Write_Command_Data(0x0031,0x0204);
        Write_Command_Data(0x0032,0x0204);
        Write_Command_Data(0x0033,0x0502);
        Write_Command_Data(0x0034,0x0507);
        Write_Command_Data(0x0035,0x0204);
        Write_Command_Data(0x0036,0x0204);
        Write_Command_Data(0x0037,0x0502);
        Write_Command_Data(0x003A,0x0302);
        Write_Command_Data(0x003B,0x0302);
        Write_Command_Data(0x0023,0x0000);
        Write_Command_Data(0x0024,0x0000);
        Write_Command_Data(0x0025,0x8000);
        Write_Command_Data(0x004f,0x0000);
        Write_Command_Data(0x004e,0x0000);
        Write_Command(0x0022);
        TFT_HAL_CS(1);
}


unsigned short Set_color(unsigned short R,unsigned short G,unsigned short B)
{
  unsigned short temp;
  Hi(temp) = (R & 0xF8) | (G >> 5);
              G = (G & 0x1C);
  Lo(temp) = (G << 3) | (B >>3);
  return temp;
}


void TFT_Fill(unsigned short color)
{
  unsigned short i,j;
  TFT_HAL_CS(0);
  TFT_Set_Address(0,0,239,319);
  Write_Data(color);
  for(i = 0; i <= 319; i++)
  {
    for(j = 0; j <= 239; j++)
    {
        TFT_HAL_WR(0);
        TFT_HAL_WR(1);
    }
  }
  TFT_HAL_CS(1);
}


void TFT_Box(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color)
{
  unsigned short  i,j;
  TFT_HAL_CS(0);
  TFT_Set_Address(x1,y1,x2,y2);
  Write_Data(color);
  for(i = y1; i <= y2; i++)
  {
    for(j = x1; j <= x2; j++)
    {
        TFT_HAL_WR(0);
        TFT_HAL_WR(1);
    }
  }
  TFT_HAL_CS(1);
}


void TFT_Dot(unsigned short x,unsigned short y,unsigned short color)
{
  TFT_HAL_CS(0);
  TFT_Set_Address(x,y,x,y);
  Write_Data(color);
  TFT_HAL_CS(1);
}

void TFT_Line(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color)
{
int x,y,addx,addy,dx,dy;
long P;
unsigned short i;

  dx = fabs(x2-x1);
  dy = fabs(y2-y1);
  x = x1;
  y = y1;

   if(x1 > x2)
   {
       addx = -1;
   }
   else
   {
       addx = 1;
   }

   if(y1 > y2)
   {
      addy = -1;
   }
   else
   {
      addy = 1;
   }


 if(dx >= dy)
 {

  P = (2*dy) - dx;

   for(i = 1; i <= (dx +1); i++)
   {

     TFT_Dot(x,y,color);

     if(P < 0)
     {
         P = P + (2*dy);
         x = (x + addx);
     }
     else
     {
        P = P+(2*dy) - (2*dx);
        x = x + addx;
        y = y + addy;
     }
    }
  }
  else
  {
    P = (2*dx) - dy;

    for(i = 1; i <= (dy +1); i++)
    {

     TFT_Dot(x,y,color);

     if(P<0)
     {
       P = P + (2*dx);
       y = y + addy;
     }
     else
     {
        P = P + (2*dx) - (2*dy);
        x = x + addx;
        y = y + addy;
     }
    }
   }
}

void TFT_H_Line(char x1,char x2,unsigned short y_pos,unsigned short color)
{
  TFT_Box(x1,y_pos,x2,y_pos+1,color);
}

void TFT_V_Line(unsigned short y1,unsigned short y2,char x_pos,unsigned short color)
{
  TFT_Box(x_pos,y1,x_pos+1,y2,color);
}

void TFT_Rectangle(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color)
{
  TFT_H_Line(x1,x2,y1,color);
  TFT_H_Line(x1,x2,y2,color);
  TFT_V_Line(y1,y2,x1,color);
  TFT_V_Line(y1,y2,x2,color);
}

void TFT_Circle(unsigned short x,unsigned short y,char radius,char fill,unsigned short color)
{
int a_,b_,P;
 a_ = 0;
 b_ = radius;
 P = 1 - radius;
 while (a_ <= b_)
 {
    if(fill == 1)
    {
         TFT_Box(x-a_,y-b_,x+a_,y+b_,color);
         TFT_Box(x-b_,y-a_,x+b_,y+a_,color);
    }
    else
    {
         TFT_Dot(a_+x, b_+y, color);
         TFT_Dot(b_+x, a_+y, color);
         TFT_Dot(x-a_, b_+y, color);
         TFT_Dot(x-b_, a_+y, color);
         TFT_Dot(b_+x, y-a_, color);
         TFT_Dot(a_+x, y-b_, color);
         TFT_Dot(x-a_, y-b_, color);
         TFT_Dot(x-b_, y-a_, color);
    }
    if (P < 0 )
    {
        P = (P + 3) + (2* a_);
        a_ ++;
    }
    else
    {
        P = (P + 5) + (2* (a_ - b_));
        a_ ++;
        b_ --;
    }
  }
}

void TFT_Char(char C,unsigned short x,unsigned short y,char DimFont,unsigned short Fcolor,unsigned short Bcolor)
{
const char *ptrfont;
unsigned short Cptrfont;
unsigned short font8x8[8];
unsigned short font16x16[16];
char k,i,print1,print2;
unsigned short print3,print4;

if(DimFont == 8)
{
     ptrfont = FONT_8x8;
     Cptrfont = (C-32)*8;
     ptrfont = ptrfont + Cptrfont;

     for(k = 0; k <= 7; k++)
     {
      font8x8[k] = *ptrfont;
      ptrfont++;
     }
     
     TFT_HAL_CS(0);
     TFT_Set_Address(x,y,x+7,y+7);
     for(i = 0; i <= 7; i++)
     {
       for(k = 0; k <= 7; k++)
       {
          print1 = (font8x8[i] & 0x80);
          print2 = print1 >>7;
          if(print2 == 1)
          {
             Write_Data(Fcolor);
          }
          else
          {
             Write_Data(Bcolor);
          }
          font8x8[i] = font8x8[i] << 1;
       }
     }
     TFT_HAL_CS(1);
}

else if(DimFont == 16)
{
     ptrfont = FONT_16x16;
     Cptrfont = (C-32)*32;
     ptrfont = ptrfont + Cptrfont;

     for(k = 0; k <= 15; k++)
     {
      font16x16[k] = *ptrfont;
      ptrfont++;
      font16x16[k] = (font16x16[k] << 8);
      font16x16[k] = font16x16[k] + *ptrfont;
      ptrfont++;
     }

     TFT_HAL_CS(0);
     TFT_Set_Address(x,y,x+15,y+15);
     for(i = 0; i <= 15; i++)
     {
       for(k = 0; k <= 15; k++)
       {
        print3 = (font16x16[i] & 0x8000);
        print4 = print3 >>15;

        if(print4 == 1)
        {
           Write_Data(Fcolor);
        }
        else
        {
           Write_Data(Bcolor);
        }

        font16x16[i] = font16x16[i] << 1;
       }
     }
     TFT_HAL_CS(1);
}

}


void TFT_Text(char * S,unsigned short x,unsigned short y,char DimFont,unsigned short Fcolor,unsigned short Bcolor)
{
  int lenght,cnt;
  char buffer[24];
  lenght = strlen(S);

  for(cnt = 0; cnt <= (lenght - 1); cnt++)
  {
    buffer[cnt] = S[cnt];
  }

  if(DimFont == 8)
  {
      for(cnt = 0; cnt <= (lenght - 1); cnt++)
      {
        TFT_Char(buffer[cnt],x,y,DimFont,Fcolor,Bcolor);
        x = x + 8;
      }
  }
  else if(DimFont == 16)
  {
      for(cnt = 0; cnt <= (lenght - 1); cnt++)
      {
        TFT_Char(buffer[cnt],x,y,DimFont,Fcolor,Bcolor);
        x = x + 16;
      }
  }
}


void TFT_Image(unsigned short pos_x,unsigned short pos_y,unsigned short dim_x,unsigned short dim_y,const unsigned short *picture){
    unsigned short x, y;

    TFT_HAL_CS(0);
    TFT_Set_Address(pos_x, pos_y, pos_x + dim_x - 1, pos_y + dim_y - 1);
    for(y = pos_y; y < (pos_y + dim_y); y++ ) {
        for(x = pos_x; x < (pos_x + dim_x); x++ ) {
            Write_Data(*picture++);
        }
    }
    TFT_HAL_CS(1);
}
