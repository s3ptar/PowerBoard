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
#define LED2_DDR	    PORT2.PDR.BIT.B4
#define LED2_Port	    PORT2.PODR.BIT.B4

//EZ8504CZZ
#define EZ8504_frame	PORTA.PODR.BIT.B0
#define EZ8504_load		PORTA.PODR.BIT.B1
#define EZ8504_cp		PORTA.PODR.BIT.B2
#define EZ8504_data		PORTE.PODR.BYTE



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
