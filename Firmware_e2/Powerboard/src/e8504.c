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
#define display_row (X_dots/8)
#define display_colum (Y_dots)
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

uint8_t framebuffer_display_1[display_colum][display_row];

/***********************************************************************
* Local Funtions
***********************************************************************/
void delay_nop(uint16_t delay);
void delay_nop(uint16_t delay){
	while(delay--);
		//asm("nop");
}

void e8504_testpattern(void){
	/*uint16_t loop_index;
	for(loop_index = 0; loop_index > 80; loop_index++)
		framebuffer_display_1[loop_index] = 0xFF;
	for(loop_index = 200; loop_index > 240; loop_index++)
		framebuffer_display_1[loop_index] = 0xFF;*/
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
	uint16_t row_count, colum_count;
	//calculate the loop for an full cycle update
	//start frame


	EZ8504_frame = 0;
	EZ8504_load = 0;
	EZ8504_cp = 0;
	//***************************
	delay_nop(delay_loops);
	EZ8504_frame = 1;
	delay_nop(delay_loops);
	EZ8504_load = 0;

    //print out colum
	for (colum_count = 0; colum_count < display_colum; colum_count++){

        //print row
        for(colum_row = 0; colum_row < display_row; colum_row++){

           //first half byte
		  EZ8504_cp = 1;
		  delay_nop(delay_loops); 
		  EZ8504_data = framebuffer_display_1[colum_count][colum_row]&0x0F;
		  delay_nop(delay_loops);
		  EZ8504_cp = 0;
		  delay_nop(delay_loops);
		  EZ8504_frame = 0;
		  //second half byte
		  EZ8504_cp = 1;
		  delay_nop(delay_loops);
		  EZ8504_data = (framebuffer_display_1[colum_count][colum_row]>>4)&0x0F;
		  delay_nop(delay_loops);
		  EZ8504_cp = 0;
            
        }
        
        //set Frame end
        EZ8504_load = 1;
	    delay_nop(delay_loops);
	}

}


