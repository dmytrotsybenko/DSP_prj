/*
 * AIC.h
 *
 *  Created on: 23.12.2011
 *      Author: Taras
 */

#ifndef AIC_H_
#define AIC_H_

#include <csl.h>
#include <csl_mcbsp.h>

#define LLCIVC 0x0000
#define RLCIVC 0x0200
#define LCHVC 0x0400
#define RCHVC 0x0600
#define AAPC 0x0800
#define DAPC 0x0A00
#define PDC 0x0C00
#define DAIF 0x0E00
#define SRC 0x1000
#define DIA 0x1200
#define RR 0x1E00
void aicSetReg( MCBSP_Handle mhMcbsp, unsigned short int name, unsigned short int value);
#endif /* AIC_H_ */
