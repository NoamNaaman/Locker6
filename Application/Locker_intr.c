#include "main.h"

#include "setup.h"

u32 Timer_5mS_Flags;
u32 Timer_1ms_counter;
u32 Timer_1mS_Flags;
u32 Timer_10ms_count[4];
u32 Timer_10mS_Flags;
u32 Timer_10mS_Cnt;
u32 Timer_100mS_Flags;
u32 comm_timer;

//--------------------------------------------------------------------------
void UserSysTick_Handler(void) // 1ms
  {
//  u16 inp;
  Timer_1mS_Flags = 0xFFFFFFFF;
  comm_timer++;
  if (!Timer_1ms_counter || Timer_1ms_counter == 5)
    {
    Timer_5mS_Flags = 0xFFFFFFFF;
    }  
  if (++Timer_1ms_counter >= 10)
    {
    Timer_1ms_counter = 0;
    Timer_10ms_count[0]++;
    Timer_10ms_count[1]++;
    Timer_10mS_Flags = 0xFFFFFFFF;
    if (++Timer_10mS_Cnt >= 10)
      {
      Timer_10mS_Cnt = 0;
      Timer_100mS_Flags =  0xFFFFFFFF;
      }
    }
  }

////--------------------------------------------------------------
//
//void  RS485_receive_char(void)
//  {
//  u16 x;
//  x = U1RXREG;
//  COM1_rbuf[COM1_rxi & (COM1_RX_LEN-1)] = x;
//  if (++COM1_rxi >= COM1_RX_LEN)
//    COM1_rxi = 0;
//  if (COM1_rcnt < COM1_RX_LEN)
//    COM1_rcnt++;
//  characters++;
////  testbuf[tbx++] = x;
//  }
//
////--------------------------------------------------------------------------
///*
// * Ethernet module interface
// * Assumes that if ethernet is active, RS485 is not.
// * Uses same channel buffers as RS485.
// *
// */
//u16 prev_eth_char = 0;
//void  XPORT_receive_char(void)
//  {
//  u16 x;
//  x = U4RXREG;
//  COM1_rbuf[COM1_rxi & (COM1_RX_LEN-1)] = x;
//  if (++COM1_rxi >= COM1_RX_LEN)
//    COM1_rxi = 0;
//  if (COM1_rcnt < COM1_RX_LEN)
//    COM1_rcnt++;
//  characters++;
//  if (prev_eth_char == PREAMBLE0 && x == PREAMBLE1)
//    Ethernet_active = 12345;
//  prev_eth_char = x;
//  }
//
//

//=============================================================================================
void enable_interrupt_pin(u32 pin)
  {
  EXTI->IMR |= pin;
  }

//=============================================================================================
void disable_interrupt_pin(u32 pin)
  {
  EXTI->IMR &= ~pin;
  }

//=============================================================================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  {
  if (htim->Instance == TIM1)
    {
    }
  
  if (htim->Instance == TIM3)
    {
    }
  }

