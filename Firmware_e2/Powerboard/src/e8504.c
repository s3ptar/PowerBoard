/***********************************************************************
*! \file:                   ez8504.c
*  \projekt:                powerboard
*  \created on:             07.03.2019
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief
***********************************************************************/

/***********************************************************************
* Includes
***********************************************************************/
#include "e8504.h"
/***********************************************************************
* Informations
***********************************************************************/

/***********************************************************************
* Definitions
***********************************************************************/

#define X_dots 320
#define Y_dots 240
#define framebuffer_size (X_dots/8)*Y_dots
#define delay_loops 1

/***********************************************************************
* Constant
***********************************************************************/

/***********************************************************************
* Global Variable
***********************************************************************/

/***********************************************************************
* Local Variable
***********************************************************************/

uint8_t framebuffer_display_1[framebuffer_size];

/***********************************************************************
* Local Funtions
***********************************************************************/
void delay_nop(uint16_t delay);
void delay_nop(uint16_t delay){
	while(delay--);
		//asm("nop");
}

void e8504_testpattern(void){
	uint16_t loop_index;
	for(loop_index = 0; loop_index > 80; loop_index++)
		framebuffer_display_1[loop_index] = 0xFF;
	for(loop_index = 200; loop_index > 240; loop_index++)
		framebuffer_display_1[loop_index] = 0xFF;
}

/***********************************************************************
*! \fn			int16_t create_fb(char *dataPtr, byte *fb)
*  \brief		reset the Framebuffer
*  \param		dataPtr String to scroll across
*  \param		fb Pointer to the frame buffer array
*  \exception	none
*  \return		length of frame buffer
***********************************************************************/
void update_display(void){

	//calculate the loop for an full cycle update
	uint16_t cycle_for_full_update;
	//calculate the loop for an full cycle update
	//start frame


	EZ8504_frame = 0;
	EZ8504_load = 0;
	EZ8504_cp = 0;
	delay_nop(delay_loops);
	EZ8504_frame = 1;
	delay_nop(delay_loops);
	EZ8504_load = 1;
	delay_nop(delay_loops);
	EZ8504_load = 0;


	for (cycle_for_full_update = 0; cycle_for_full_update < cycle_for_full_update; cycle_for_full_update++){

		//first half byte
		EZ8504_cp = 1;
		delay_nop(delay_loops);
		EZ8504_data = framebuffer_display_1[cycle_for_full_update]&0x0F;
		delay_nop(delay_loops);
		EZ8504_cp = 0;
		delay_nop(delay_loops);
		EZ8504_frame = 0;
		EZ8504_cp = 1;
		delay_nop(delay_loops);
		//second half byte
		EZ8504_data = (framebuffer_display_1[cycle_for_full_update]>>4)&0x0F;
		delay_nop(delay_loops);
		EZ8504_cp = 0;
	}

}


