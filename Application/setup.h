#ifndef __SETUP
#define __SETUP

#include "stm32f0xx_hal.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s8  int8_t
#define s16 int16_t
#define s32 int32_t
#define u64 uint64_t
#define s64 int64_t


#define bool u8
#define true 1
#define false 0


#define EE1024

#define EEPROM_TYPE_I2C 1
#define EEPROM_TYPE_SPI 2
#define __EEPROM_TYPE__ 2



#define SW_VERSION 21
//  21 2022-12-03 first version for locker system with LOCKER6 cards
// 221 2022-11-16 added enable/disable auto unlock with MSG_UNLK 252/253
// 220 2022-11-10 first version with M95M04 4Mb chip
// 212 2021-11-22 short on reader 4 middle pins on power up clears door 1 flags to get out of elevator mode
// 211 2021-11-13 fixed elevator software
// 210 2021-11-11 fixed USART2 interrupt problem
// 209 2021-09-25 fixed flash read/write functionality
// 207 2021-08-18 improved two-man + dual-reader operation. made TIM1 interrupt even faster
// 206 2021-08-13 changed system clock to 100MHz, 2nd reader sampled every 45uS
// 205 2021-08-09 fixed dual-reader mode on all 4 doors
// 204 2021-08-07 increased stored events to 4096
// 203 2021-08-07 dual reader mode working
// 202 2021-08-06 Fixed RTC reset problem 
// 201 2021-08-04 RDR2 working. forced door aux 30 seconds. DIP inverted
// 200 2021-07-31 first version for F411, based on 144 on older boards
// 136 2021-02-09 added post key processing pause per door to prevent multi-key break-in attempts
// 135 2021-02-04 added RDR2,RDR4 D0/D1 signal cleanup in NetQX_intr.c
// 134 - added EVT_RemoteLeaveDoorOpen = event 142 for UNLK 255. ignore extra UNLK commands.
// 133 - added event 140 - enable/disable door unlock
// 132 - changed event numbers according to Daniel's request


#define __LOCKER_SYSTEM__ 1






//========== STM32 housekeeping functions ===================================
// I/O pin functionality definitions for use with SetPinMode()

// port modes
#define PORTMODE_INPUT         0
#define PORTMODE_OUTPUT        1
#define PORTMODE_ALTERNATE     2
#define PORTMODE_ANALOG        3

// output modes
#define OUTMODE_PP    0x00
#define OUTMODE_OD    0x10

// output speed
#define OUTSPEED_400KHz        0x000
#define OUTSPEED_2MHz          0x100
#define OUTSPEED_10MHz         0x200
#define OUTSPEED_40MHz         0x300

// pullup/pulldown
#define PULL_NONE              0x0000
#define PULL_UP                0x1000
#define PULL_DOWN              0x2000

typedef enum
{ GPIO_FMode_AIN         = ( PORTMODE_ANALOG  ),       // analog input or DAC output
  GPIO_FMode_IN_FLOATING = ( PORTMODE_INPUT  ),       // digital input, no pull-up/down resistor
  GPIO_FMode_IPD         = ( PORTMODE_INPUT | PULL_DOWN  ),       // digital input, pull-up resistor
  GPIO_FMode_IPU         = ( PORTMODE_INPUT | PULL_UP    ),       // digital input, pull-down resistor

  GPIO_FMode_p4_Out_PP   = ( PORTMODE_OUTPUT    | OUTSPEED_400KHz | OUTMODE_PP  ),       // 400KHz digital output, push-pull output
  GPIO_FMode_p4_Out_OD   = ( PORTMODE_OUTPUT    | OUTSPEED_400KHz | OUTMODE_OD  ),       // 400KHz digital output, open drain output
  GPIO_FMode_p4_AF_PP    = ( PORTMODE_ALTERNATE | OUTSPEED_400KHz | OUTMODE_PP  ),       // 400KHz digital output, push-pull alternate function output
  GPIO_FMode_p4_AF_OD    = ( PORTMODE_ALTERNATE | OUTSPEED_400KHz | OUTMODE_OD  ),       // 400KHz digital output, open drain alternate function output

  GPIO_FMode_2_Out_PP    = ( PORTMODE_OUTPUT    | OUTSPEED_2MHz   | OUTMODE_PP  ),       // 2MHz digital output, push-pull output
  GPIO_FMode_2_Out_OD    = ( PORTMODE_OUTPUT    | OUTSPEED_2MHz   | OUTMODE_OD  ),       // 2MHz digital output, open drain output
  GPIO_FMode_2_AF_PP     = ( PORTMODE_ALTERNATE | OUTSPEED_2MHz   | OUTMODE_PP  ),       // 2MHz digital output, push-pull alternate function output
  GPIO_FMode_2_AF_OD     = ( PORTMODE_ALTERNATE | OUTSPEED_2MHz   | OUTMODE_OD  ),       // 2MHz digital output, open drain alternate function output

  GPIO_FMode_10_Out_PP   = ( PORTMODE_OUTPUT    | OUTSPEED_10MHz  | OUTMODE_PP  ),       // 10MHz digital output, push-pull output
  GPIO_FMode_10_Out_OD   = ( PORTMODE_OUTPUT    | OUTSPEED_10MHz  | OUTMODE_OD  ),       // 10MHz digital output, open drain output
  GPIO_FMode_10_AF_PP    = ( PORTMODE_ALTERNATE | OUTSPEED_10MHz  | OUTMODE_PP  ),       // 10MHz digital output, push-pull alternate function output
  GPIO_FMode_10_AF_OD    = ( PORTMODE_ALTERNATE | OUTSPEED_10MHz  | OUTMODE_OD  ),       // 10MHz digital output, open drain alternate function output

  GPIO_FMode_40_Out_PP   = ( PORTMODE_OUTPUT    | OUTSPEED_40MHz  | OUTMODE_PP  ),       // 50MHz digital output, push-pull output
  GPIO_FMode_40_Out_OD   = ( PORTMODE_OUTPUT    | OUTSPEED_40MHz  | OUTMODE_OD  ),       // 50MHz digital output, open drain output
  GPIO_FMode_40_AF_PP    = ( PORTMODE_ALTERNATE | OUTSPEED_40MHz  | OUTMODE_PP  ),       // 50MHz digital output, push-pull alternate function output
  GPIO_FMode_40_AF_OD    = ( PORTMODE_ALTERNATE | OUTSPEED_40MHz  | OUTMODE_OD  )        // 50MHz digital output, open drain alternate function output
} GPIOModeFunc_TypeDef;


#define SetOutputHigh(PORTx, Pin) PORTx->BSRR = (uint32_t)1L << Pin
#define SetOutputLow(PORTx, Pin) PORTx->BSRR = (uint32_t)1L << (Pin+16)

#define SetOutputPin(PORTx, Pin, value) \
  if (value)                            \
    SetOutputHigh(PORTx, Pin);          \
  else                                  \
    SetOutputLow(PORTx, Pin)

#define InputPin(PORTx, Pin) ((PORTx->IDR & (1 << Pin)) != 0)

#define OutputToggle(PORTx, Pin) \
    if (InputPin(PORTx, Pin))     \
    { \
    SetOutputLow(PORTx, Pin); \
    } \
    else                         \
    { \
    SetOutputHigh(PORTx, Pin); \
    }

#define EnableEXTI(Pin) EXTI->IMR |= 1 << Pin
#define DisableEXTI(Pin) EXTI->IMR &= ~(1 << Pin)

#define output_drive(x) SetPinMode(x, GPIO_FMode_10_Out_PP)
#define output_float(x) SetPinMode(x, GPIO_FMode_IN_FLOATING);
#define output_od(x) SetPinMode(x, GPIO_FMode_10_Out_OD)
#define input_pullup(x) SetPinMode(x, GPIO_FMode_IPU);
#define input_pulldown(x) SetPinMode(x, GPIO_FMode_IPD);

#define output_low(x)        SetOutputLow(x)
#define output_high(x)       SetOutputHigh(x)
#define output_toggle(x)     OutputToggle(x)
#define output_pin(x, value) SetOutputPin(x, value)
    
#define input(x)        InputPin(x)

#define enable_ext_interrupt(x) EnableEXTI(x)
#define disable_ext_interrupt(x) DisableEXTI(x)
#define clear_tim_interrupt(htim) __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE)

#define make32(x3,x2,x1,x0) (((u32)x3 << 24) | ((u32)x2 << 16) | ((u32)x1 << 8) | (u32)x0)
#define make16(x1,x0) (((u32)x1 << 8) | (u32)x0)
#define make8(data, byte) ((data >> (byte * 8)) & 0xFF)


void SetPinMode(GPIO_TypeDef* GPIOx, u16 Pin, GPIOModeFunc_TypeDef PortMode);

void NVIC_Configuration(void);
void SysTickConfig(void);

#endif