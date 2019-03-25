/*
Open Source Synthesizer
Waveform Synthesis Code
Author:
  Andrew McLaurin
  24 March 2019
*/
#include <stdio.h>
#include <time.h>
#include "synthesis.h"


void DDS(int *note_tuning_words, int *note_attenuation, int *note_enable, int *LUT) {
	//Initialize the heartbeat

	// get the initial time

	int32_t last_beat; //LONG ns time of last beat
	int32_t elapsed_time; //LONG elapsed time in ns
	struct timespec time; //time struct
	bool calculate_next_sample = false; //flag to calculate the next sample
	uint32_t accumulator[NUM_NOTES];
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time); //High-res process timer
	last_beat = time.tv_nsec; // ns time of last beat

	//MAIN LOOP
	while(1) {
		//get the current time and calculate the elapsed time
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
		elapsed_time = time.tv_nsec - last_beat;
		//Check for 1s rollover
		if(elapsed_time < 0) {
			elapsed_time += ONE_SECOND_NS;
		}

		//check if the elapsed time is >= 1 sample period
		if (elapsed_time >= SAMPLE_RATE) {
			//SEND THE SAMPLE
			//Set flag to calculate next sample
			Send_Sample();
			calculate_next_sample = true;
		}

		//if we need to calculate the next sample, do it
		if(calculate_next_sample) {
			//CALCULATE THE NEW SAMPLES
			//Loop through every notes
			for(int i = 0; i < NUM_NOTES; i++) {
				//increment the accumulator and check for overflow
				accumulator[i] += note_tuning_words[i];
				if(accumulator[i] > WAVETABLE_LENGTH) accumulator[i]-= WAVETABLE_LENGTH;
			}
		}
	}

}
