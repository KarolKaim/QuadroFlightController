#ifndef _STABILIZATION_H_
#define _STABILIZATION_H_

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

void PitchPID(	float * SetValue, float  *CurrnetValue);
void PitchInit(void);

void rollPID(	float * SetValue, float  *CurrnetValue);
void RollInit(void);

#endif