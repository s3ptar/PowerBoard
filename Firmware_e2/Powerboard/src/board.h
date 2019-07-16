/*
 * board.h
 *
 *  Created on: 31.10.2018
 *      Author: Besitzer
 */

#ifndef BOARD_H_
#define BOARD_H_



/*****************************************************************************
 * Includes
 ****************************************************************************/
#include "iodefine.h"
#include "stdint.h"


/*****************************************************************************
 * Definitions
 ****************************************************************************/
#define LED1_DDR	    PORTC.PDR.BIT.B5
#define LED1_Port	    PORTC.PODR.BIT.B5
#define LED1_Port	    PORTC.PODR.BIT.B5
#define EVE_CS_on  		PORT2.PODR.BIT.B2=0
#define EVE_CS_off 		PORT2.PODR.BIT.B2=1
#define EVE_Power_off  	PORT3.PODR.BIT.B3=0
#define EVE_Power_on   	PORT3.PODR.BIT.B3=1



/************************************************************************
 * Global Variable
 ***********************************************************************/

extern unsigned long int ms_counter,ms_counter2;

/*****************************************************************************
 * Functions
 ****************************************************************************/
void init_board( void );
void SysTick_Handler (void);
void delay_ms(uint32_t delay_time);
void init_IO(void);


#endif /* BOARD_H_ */
