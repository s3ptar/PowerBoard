/*
 * board.c
 *
 *  Created on: 31.10.2018
 *      Author: Besitzer
 */


/************************************************************************
 * Includes
 ***********************************************************************/
#include "board.h"
#include "gpio.h"

/************************************************************************
 * Informations
 ***********************************************************************/

/************************************************************************
 * Global Variable
 ***********************************************************************/
/* Uhr    */
unsigned long int ms_counter,ms_counter2, delay_counter;
/* Declare the simulated EEPROM data table */
/************************************************************************
 * Local Variable
 ***********************************************************************/

/************************************************************************
 * Constant
 ***********************************************************************/

/************************************************************************
 * Local Funtions
 ***********************************************************************/

/************************************************************************
*! \fn			init_clock( void )
*  \brief		cpu clock initialization
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void init_clock( void ){

	/*
    Clock Description              Frequency
	----------------------------------------
	Input Clock Frequency............  12 MHz
	PLL frequency (x16).............. 192 MHz
	Internal Clock Frequency.........  96 MHz
	Peripheral Clock Frequency.......  48 MHz
	USB Clock Frequency..............  48 MHz
	External Bus Clock Frequency.....  24 MHz */

	volatile unsigned int i;

	SYSTEM.PRCR.WORD = 0xA50B;			// Protect off.
	//SYSTEM.SOSCCR.BYTE = 0x01;        // stop sub-clock // Uncomment if not using sub-clock
	SYSTEM.SOSCCR.BYTE = 0x00;			// Enable sub-clock for RTC
	SYSTEM.MOSCWTCR.BYTE = 0x0D;		// Wait 131,072 cycles * 12 MHz = 10.9 ms
	SYSTEM.PLLWTCR.BYTE = 0x04;			// PLL wait is 4,194,304 cycles (default) * 192 MHz (12 MHz * 16) = 20.1 ms
	SYSTEM.PLLCR.WORD = 0x0F00;			// x16 @PLL */
	SYSTEM.MOSCCR.BYTE = 0x00;			// EXTAL ON
	SYSTEM.PLLCR2.BYTE = 0x00;			// PLL ON
    for(i = 0;i< 0x168;i++){
    	asm("nop");        					// Wait over 12ms
	}

	/* Setup system clocks
	SCKCR - System Clock Control Register
	b31:b28 FCK[3:0]  0x02 = Flash clock: PLL/4 = (192 / 4) = 48 MHz
	b27:b24 ICK[3:0]  0x01 = System clock: PLL/2 = (192 / 2) = 96 MHz
	b23     PSTOP1    0x00 = BCLK pin output is enabled
	b19:b16 BCK[3:0]  0x03 = BCLK: PLL/8 = 24 MHz
	b11:b8  PCKB[3:0] 0x02 = Peripheral clock B: PLL/4 = 48 MHz
	*/

	//	SYSTEM.SCKCR.LONG = 0x22862211;		//Mre 0x21031222;// ICK=PLL/4,BCK,FCK,PCK=PLL/4
	SYSTEM.SCKCR.LONG = 0x21862211;		//Mre 0x21031222;// ICK=PLL/2,BCK,FCK,PCK=PLL/4

	/* Setup IEBUS and USB clocks
	SCKCR2 - System Clock Control Register 2
	b7:b4 UCK[3:0]   0x03 = USB clock is PLL/4 = 48 MHz
	b3:b0 IEBCK[3:0] 0x01 = IE Bus clock is PLL/2 = 96 MHz
	*/

	SYSTEM.SCKCR2.WORD = 0x00;//Mre 0x0031;
	SYSTEM.SCKCR3.WORD = 0x0400;				// ICLK, PCLKB, FCLK, BCLK, IECLK, and USBCLK all come from PLL circuit
	SYSTEM.PRCR.WORD = 0xA500;					// Protect on.

}

/************************************************************************
*! \fn			Timer_MTU3_init(void)
*  \brief		Function configures the MTU2a's channel 3 using compare match method
*				  to generate a interrupt function to set the time for the Output.
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void Timer_MTU3_init(void){
    SYSTEM.PRCR.WORD 	= 0xA503;		// Protection off
	MSTP_MTU3 			= 0;			// Cancel the MTU0 module clock stop mode
	SYSTEM.PRCR.WORD 	= 0xA500;		// Protection on

	MTU3.TCR.BYTE 		= 0x4D;			// Clock PCLK/1024, count at falling edge, TCNT cleared by TRGB compare match
	MTU3.TMDR.BYTE 		= 0;			// Operate timers in normal mode
	MTU3.TIORH.BYTE 	= 0x00;			// Initial output is 0
	MTU.TRWER.BIT.RWE 	= 0x1;			// Enable access to protected MTU registers

	MTU3.TGRB	=0x28;

	IPR(MTU3,TGIB3) = 0x5;				// Set MTU3,TGIB3 interrupt priority level to 5
	IEN(MTU3,TGIB3) = 0x1;				// Enable MTU3,TGIB3 interrupts
	IR(MTU3,TGIB3) = 0x0;				// Clear MTU3,TGIB3 interrupt flag
   	MTU3.TIER.BYTE = 0x02;    			// Enable TGIEA interrupts
	MTU.TSTR.BIT.CST3 	= 0x1;			// Start MTU3 TCNT counter
}

/************************************************************************
 * Global Funtions
 ***********************************************************************/

/************************************************************************
*! \fn			void init_board( void )
*  \brief		initialization from cpu and peripheral
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void init_board( void ){

	init_clock();
	Timer_MTU3_init();		// Timer fpr SysTick
	//LED1_DDR = 1;
	//LED1_Port = 1;

	GPIO_output(C,5);
	GPIO_set(C,5);
	LED1_Port = 1;
	LED2_DDR = 1;
	LED2_Port = 1;

}


/************************************************************************
*! \fn			void delay_ms(uint32_t delay_time)
*  \brief		DelayRotine
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void delay_ms(uint32_t delay_time){

	delay_counter = delay_time;
	while(delay_counter){
		asm("nop");
	}

}

/************************************************************************
*! \fn			void SysTick_Handler (void)
*  \brief		System Tick Interrupt Service Routine
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void SysTick_Handler (void){

    ms_counter++;
	ms_counter2++;
	if(delay_counter)
		delay_counter--;


//       NVIC_ClearPendingIRQ(SysTick_IRQn);
}

/************************************************************************
*! \fn			void init_IO(void)
*  \brief		Init IOP
*
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void init_IO(void){

	PORT2.PDR.BIT.B2=1;		// Freigaben für PD und SS
	PORT3.PDR.BIT.B3=1;
}


