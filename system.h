/**
  ******************************************************************************
  * @file    system.h
  * @author  Vu Ngoc Son
  * @version V1.0.0
  * @date    17-December-2019
  * @brief   This file provides functions control input, output for CortexM4-STM32F4
	*					 The CortexR-M3 memory map includes two bit-band regions. These regions map each word
	*					 in an alias region of memory to a bit in a bit-band region of memory. Writing to a 
	*					 word in the alias region has the same effect as a read-modify-write operation on the 
	*					 targeted bit in the bit-band region.
  *         
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================

    @endverbatim
  ******************************************************************************
  * @attention
  *				 								http://www.esatech.vn
  *        
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#ifndef __SYSTEM_H
#define __SYSTEM_H

#ifdef STM32F4XX
#include "stm32f4xx.h"
#else
#include "stm32f10x.h"
#endif
/*
 *	@note: bit_word_addr = bit_band_base + (byte_offset*32) + (bit_number*4)
 *				 where:
 *							 bit_word_addr is the address of the word in the alias memory region that maps 
 *							 to the targeted bit.
 *							 bit_band_base is the starting address of the alias region.
 *							 byte_offset is the number of the byte in the bit-band region that contains the 
 *							 targeted bit.
 *							 bit_number is the bit position (0-7) of the targeted bit.
 */

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 




#ifdef STM32F4XX

/*------------- Output address*/
//Address offset: 0x14
#define GPIOA_ODR_Addr    (GPIOA_BASE+0x14) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+0x14) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+0x14) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+0x14) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+0x14) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+0x14) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+0x14) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+0x14) //0x40021C14
#define GPIOI_ODR_Addr    (GPIOI_BASE+0x14) //0x40022014
#define GPIOJ_ODR_Addr    (GPIOJ_BASE+0x14) //0x40022414    
#define GPIOK_ODR_Addr    (GPIOK_BASE+0x14) //0x40022814

/*------------- Input address*/
//Address offset: 0x10
#define GPIOA_IDR_Addr    (GPIOA_BASE+0x10) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+0x10) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+0x10) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+0x10) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+0x10) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+0x10) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+0x10) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+0x10) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+0x10) //0x40022010 
#define GPIOJ_IDR_Addr    (GPIOJ_BASE+0x10) //0x40022410 
#define GPIOK_IDR_Addr    (GPIOK_BASE+0x10) //0x40022810 


#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n) 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n) 

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n) 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n) 

#define PJout(n)   BIT_ADDR(GPIOJ_ODR_Addr,n) 
#define PJin(n)    BIT_ADDR(GPIOJ_IDR_Addr,n) 

#define PKout(n)   BIT_ADDR(GPIOK_ODR_Addr,n) 
#define PKin(n)    BIT_ADDR(GPIOK_IDR_Addr,n) 

#else

#ifdef STM32F10x

/*------------- Output address*/
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

/*------------- Input address*/
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
#endif
#endif


#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n) 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)   
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n) 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n) 

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n) 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n) 

#endif
/************************************** END OF FILE **************************************/
