//
// Created by AQin on 2022/11/29.
//

#ifndef AT24_PRAC_AT24CXX_H
#define AT24_PRAC_AT24CXX_H

#include "main.h"
#include "memory.h"

#define IIC         hi2c1
#define REST_TIME   5
#define AT_WRITEADDR   0xA0
#define AT_READADDR    0xA1
#define AT_TIMEOUT  1000

#define ENABLE_DELAY

/*ATC02XX Device type(total size)*/
/*The Memory Address of follow chips is 8 bits*/
#define AT24C01   128    /*16 pages 8-bytes each*/
#define AT24C02   256    /*32 pages 8-bytes each*/
#define AT24C04   512    /*32 pages 16-bytes each*/
#define AT24C08   1024   /*64 pages 16-bytes each*/
#define AT24C16   2048   /*128 pages 16-bytes each*/
/*The Memory Address of follow chips is 16 bits*/
#define AT24C32   4096   /*256 pages 32-bytes each*/
#define AT24C64   8192   /*256 pages 32-bytes each*/
#define AT24C128  16384  /*256 pages 64-bytes each*/
#define AT24C256  32768  /*512 pages 64-bytes each*/

/*Select type of chip*/
#define AT24CXX_TYPE AT24C256

void AT24C_ClearAll();
uint8_t AT24C_WriteByte(uint16_t add, uint8_t src_val);
uint8_t AT24C_ReadByte(uint16_t add, uint8_t* dst_val);
void AT24C_WriteArray(uint16_t add, uint8_t* src_array, uint16_t len);
void AT24C_ReadArray(uint16_t add, uint8_t* dst_array, uint16_t len);

#endif //AT24_PRAC_AT24CXX_H
