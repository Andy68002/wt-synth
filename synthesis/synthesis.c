/*
 * Open Source Synthesizer
 * Waveform Synthesis Code
 * Author:
 * Andrew McLaurin
 * 24 March 2019
 */
#include <stdio.h>
#include <time.h>
#include "synthesis.h"
int TESTING = 0;
void Send_Sample(){
}

void DDS(unsigned short *note_tuning_words,
         unsigned short *note_attenuation,
         char           *note_enable,
         int            *LUT){


	// Initialize the heartbeat
	long last_beat;                    // LONG ns time of last beat
	long elapsed_time;                 // LONG elapsed time in ns
	struct timespec time;              // time struct
	char calculate_next_sample = FALSE; // flag to calculate the
	                                    // next sample
	unsigned long accumulator[NUM_NOTES];

	// get the initial time
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time); // High-res process timer
	last_beat = time.tv_nsec;          // ns time of last beat

	// MAIN LOOP
	while (1) {
		// get the current time and calculate the elapsed time
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time);
		elapsed_time = time.tv_nsec - last_beat;


		// Check for 1s rollover
		if (elapsed_time < 0) {
			elapsed_time += ONE_SECOND_NS;
		}

		// check if the elapsed time is >= 1 sample period
		if (elapsed_time >= SAMPLE_RATE) {
			// Set last_beat to new time and check for overflow
			if ((last_beat += SAMPLE_RATE) < 0) last_beat += ONE_SECOND_NS;

			// SEND THE SAMPLE
			// Set flag to calculate next sample
			Send_Sample();
			printf("%i, %li, \n", TESTING, elapsed_time);

			if (TESTING++ >= 2000) break;
			calculate_next_sample = TRUE;
		}

		// if we need to calculate the next sample, do it
		if (calculate_next_sample) {
			// CALCULATE THE NEW SAMPLES
			// Loop through every notes
			for (int i = 0; i < NUM_NOTES; i++) {
				// increment the accumulator and check for overflow
				accumulator[i] += note_tuning_words[i];

				if (accumulator[i] >
				    WAVETABLE_LENGTH) accumulator[i] -= WAVETABLE_LENGTH;
			}
		}
	}
} /* DDS */
