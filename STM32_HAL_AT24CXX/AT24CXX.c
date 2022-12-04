//
// Created by AQin on 2022/11/29.
//
#include "AT24CXX.h"

#if AT24CXX_TYPE == 128 || AT24CXX_TYPE == 256
#define AT_PAGESIZE 8
#elif AT24CXX_TYPE == 512 || AT24CXX_TYPE == 1024 || AT24CXX_TYPE == 2048
#define AT_PAGESIZE 16
#elif AT24CXX_TYPE == 4096 || AT24CXX_TYPE == 8192
#define AT_PAGESIZE 32
#elif AT24CXX_TYPE == 16384 || AT24CXX_TYPE == 32768
#define AT_PAGESIZE 64
#endif

uint8_t page_white[AT_PAGESIZE]; //Blank Page


static uint8_t Write(uint16_t add, uint8_t* src_val, uint16_t len)
{
  return HAL_I2C_Mem_Write(&IIC,
                           AT_WRITEADDR,
                           add,
                           AT24CXX_TYPE <= AT24C16 ? I2C_MEMADD_SIZE_8BIT : I2C_MEMADD_SIZE_16BIT,
                           src_val,
                           len,
                           AT_TIMEOUT);
}

static uint8_t Read(uint16_t add, uint8_t* dst_val, uint16_t len)
{
  return HAL_I2C_Mem_Read(&IIC,
                          AT_READADDR,
                          add,
                          AT24CXX_TYPE <= AT24C16 ? I2C_MEMADD_SIZE_8BIT : I2C_MEMADD_SIZE_16BIT,
                          dst_val,
                          len,
                          AT_TIMEOUT);
}

void AT24C_ClearAll()
{
  uint16_t pages = AT24CXX_TYPE / AT_PAGESIZE;
  while (pages--)
  {
    Write(pages, page_white, AT_PAGESIZE);
  }
#ifdef ENABLE_DELAY
  HAL_Delay(REST_TIME);
#endif
}

uint8_t AT24C_WriteByte(uint16_t add, uint8_t src_val)
{
  uint8_t state;
  state = Write(add, &src_val, 1);
#ifdef ENABLE_DELAY
  HAL_Delay(REST_TIME);
#endif
  return state == HAL_OK;
}

uint8_t AT24C_ReadByte(uint16_t add, uint8_t* dst_val)
{
  uint8_t state;
  state = Read(add, dst_val, 1);
#ifdef ENABLE_DELAY
  HAL_Delay(REST_TIME);
#endif
  return state == HAL_OK;
}

void AT24C_WriteArray(uint16_t add, uint8_t* src_array, uint16_t len)
{
  uint8_t* p_src = src_array;
  uint8_t last_len = AT_PAGESIZE - add % AT_PAGESIZE;

  if (last_len >= len)
  {
    Write(add, p_src, len);
  }
  else
  {
    Write(add, p_src, last_len);
    add += last_len;
    p_src+=last_len;
    len -= last_len;

    while (len >= AT_PAGESIZE)
    {
      Write(add, p_src, AT_PAGESIZE);
      add += last_len;
      p_src += AT_PAGESIZE;
      len -= AT_PAGESIZE;
    }
    HAL_Delay(REST_TIME);
    if (len != 0)
    {
      Write(add, p_src, len);
    }

  }
#ifdef ENABLE_DELAY
  HAL_Delay(REST_TIME);
#endif
  return;
}

void AT24C_ReadArray(uint16_t add, uint8_t* dst_array, uint16_t len)
{
  uint8_t* p_src = dst_array;
  uint8_t last_len = AT_PAGESIZE - add % AT_PAGESIZE;

  if (last_len >= len)
  {
    Read(add, p_src, len);
  }
  else
  {
    Read(add, p_src, last_len);
    add += last_len;
    p_src+=last_len;
    len -= last_len;

    while (len >= AT_PAGESIZE)
    {
      Read(add, p_src, AT_PAGESIZE);
      add += last_len;
      p_src += AT_PAGESIZE;
      len -= AT_PAGESIZE;
    }
    HAL_Delay(REST_TIME);
    if (len != 0)
    {
      Read(add, p_src, len);
    }

  }
  p_src -= len;
#ifdef ENABLE_DELAY
  HAL_Delay(REST_TIME);
#endif
  return;
}
