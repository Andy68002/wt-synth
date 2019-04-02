/*
 * Open Source Synthesizer
 * Waveform Synthesis Code
 * Author:
 * Andrew McLaurin
 * 24 March 2019
 */
#include <stdio.h>
#include "synthesis.h"
#include "../synthesizer.h"

//Accumulator registers
int accumulators[NUM_NOTES];
int samples[PERIOD_SAMPLES];
short *wavetable;
void init_DDS(short *LUT) {
	//Initialization function for DDS
	for (int i = 0; i < NUM_NOTES; i++) {
		accumulators[i] = 0;
		samples[i] = 0;
	}
	wavetable = LUT;
}

void DDS(void *data){
	USB_synthesizer_data dds_data = *(USB_synthesizer_data*)data;
	//Loop to calculate PERIOD_SAMPLES number of samples
	for(int i = 0; i < PERIOD_SAMPLES; i++) {
		int currentSample = 0;
		//loop through the accumulator register, calculating new lookup values
		//Calculate the current sample from looked up samples and attenuations
		for (int j = 0; j < NUM_NOTES; j++) {
			accumulators[j]+=dds_data.tuning_word[j];
			accumulators[j] = (accumulators[j] > WAVETABLE_LENGTH) ?
			                  accumulators[j]-=WAVETABLE_LENGTH : accumulators[j];
			if(dds_data.enable[j]) {
				//if note is enabled, currentSample += wavetable lookup
				//bitwise anded with attenuation factor
				currentSample += wavetable[accumulators[j]] / dds_data.attenuate[j];
			}
		}
		samples[i] = currentSample;
		//printf("sample %i: %i\n", i, samples[i]);
		printf("%i\n", samples[i]);
	}

} /* DDS */
