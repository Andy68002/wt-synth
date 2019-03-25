/*
Synthesis test code
*/
#include <stdio.h>
#include "synthesis.h"
//initialize arrays for frequency, attenuation, and enable
int32_t tuning[NUM_NOTES];
int32_t attenuate[NUM_NOTES];
bool enable[NUM_NOTES];
}
int main() {
	//initialize the memory for the lookup table
	int32_t *LUT = malloc(SAMPLE_WIDTH * WAVETABLE_LENGTH);
	DDS(tuning, attenuate, enable, LUT);

	free(LUT);
	return 0;
}
