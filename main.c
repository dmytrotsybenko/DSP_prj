
#include <std.h>

#include <csl.h>
#include <csl_mcbsp.h>
#include "AIC.h"

int *ibuf;
int *obuf;
int FRAME = 128, i;

/*
 *  ======== main ========
 */

MCBSP_Config ConfigDSPsound= {
		0x0000,
		0x0100,
		0x0140,
		0x0000,
		0x0140,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0003,
		MCBSP_RCERA_DEFAULT,
		MCBSP_RCERB_DEFAULT,
		MCBSP_RCERC_DEFAULT,
		MCBSP_RCERD_DEFAULT,
		MCBSP_RCERE_DEFAULT,
		MCBSP_RCERF_DEFAULT,
		MCBSP_RCERG_DEFAULT,
		MCBSP_RCERH_DEFAULT,
		MCBSP_XCERA_DEFAULT,
		MCBSP_XCERB_DEFAULT,
		MCBSP_XCERC_DEFAULT,
		MCBSP_XCERD_DEFAULT,
		MCBSP_XCERE_DEFAULT,
		MCBSP_XCERF_DEFAULT,
		MCBSP_XCERG_DEFAULT,
		MCBSP_XCERH_DEFAULT
};
MCBSP_Config ConfigSPIsound= {
	0x1000,
	0x0100,
	0x0000,
	0x0000,
	0x0040,
	0x0000,
	0x0063,
	0x2013,
	0x0000,
	0x0000,
	0x1a0a,
	MCBSP_RCERA_DEFAULT,
	MCBSP_RCERB_DEFAULT,
	MCBSP_RCERC_DEFAULT,
	MCBSP_RCERD_DEFAULT,
	MCBSP_RCERE_DEFAULT,
	MCBSP_RCERF_DEFAULT,
	MCBSP_RCERG_DEFAULT,
	MCBSP_RCERH_DEFAULT,
	MCBSP_XCERA_DEFAULT,
	MCBSP_XCERB_DEFAULT,
	MCBSP_XCERC_DEFAULT,
	MCBSP_XCERD_DEFAULT,
	MCBSP_XCERE_DEFAULT,
	MCBSP_XCERF_DEFAULT,
	MCBSP_XCERG_DEFAULT,
	MCBSP_XCERH_DEFAULT
};

Void main()
{
    MCBSP_Handle spiMcbsp;
    MCBSP_Handle soundMcbsp;
    CSL_init();
    spiMcbsp = MCBSP_open(MCBSP_PORT1, MCBSP_OPEN_RESET);
    MCBSP_config(spiMcbsp, &ConfigSPIsound);

    /* Start Sample Rate Generator and Frame Sync */
    MCBSP_start(spiMcbsp,
      MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
      0x300
    );

    /* Enable MCBSP transmit and receive */
    MCBSP_start(spiMcbsp,
      MCBSP_RCV_START | MCBSP_XMIT_START,
      0
    );

    soundMcbsp = MCBSP_open(MCBSP_PORT2, MCBSP_OPEN_RESET);
    MCBSP_config(soundMcbsp, &ConfigDSPsound);

    /* Start Sample Rate Generator and Frame Sync */
    MCBSP_start(soundMcbsp,
      MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
      0x300
    );

    /* Enable MCBSP transmit and receive */
    MCBSP_start(soundMcbsp,
      MCBSP_RCV_START | MCBSP_XMIT_START,
      0
    );
   
	aicSetReg(spiMcbsp, RR, 0x000);
    aicSetReg(spiMcbsp, LLCIVC, 0x017);
	aicSetReg(spiMcbsp, RLCIVC, 0x017);
	aicSetReg(spiMcbsp, LCHVC, 0x1f9);
	aicSetReg(spiMcbsp, RCHVC, 0x1f9);
	aicSetReg(spiMcbsp, AAPC, 0x012);
	aicSetReg(spiMcbsp, DAPC, 0x000);
	aicSetReg(spiMcbsp, PDC, 0x002);
	aicSetReg(spiMcbsp, DAIF, 0x043);
	aicSetReg(spiMcbsp, SRC, 0x08D);//0x081
	aicSetReg(spiMcbsp, DIA, 0x001);


	while(1){
		for(i = 0; i < FRAME; i++){
			while (!MCBSP_rrdy(soundMcbsp));
				//Read input data
				ibuf[i] = MCBSP_read16(soundMcbsp); // div 2 to pretend the overflowing
				obuf[i]= ibuf[i];
				//Write output
			while (!MCBSP_xrdy(soundMcbsp));
				MCBSP_write16(soundMcbsp, obuf[i]); // restore the original magnitude
		}
	}
}
