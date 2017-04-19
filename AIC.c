/*
 * AIC.c
 *
 *  Created on: 23.12.2011
 *      Author: Taras
 */

# include "AIC.h"

void aicSetReg( MCBSP_Handle mhMcbsp, unsigned short int name, unsigned short int value)
{
	while (!MCBSP_xrdy(mhMcbsp));
		MCBSP_write16(mhMcbsp, name | value);
	return;
}
