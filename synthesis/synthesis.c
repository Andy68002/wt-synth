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
void DDS(int* note_tuning_words, int* note_attenuation, int* note_enable) {
	//set up heartbeat timer
	long last_beat;
	long time_change;
	struct timespec current_time;
	char beat_10ms_timer = 0;

	clock_gettime(CLOCK_REALTIME, &current_time);
	last_beat = current_time.tv_nsec;

	//timer
	clock_gettime(CLOCK_REALTIME, &current_time);
	time_change = current_time.tv_nsec - last_beat;
	if (time_change < 0) time_change += 1000000000;
	if (time_change > 1000000) {
		last_beat += 1000000;
		if (last_beat > 1000000000) last_beat -=1000000000;

		beat_10ms_timer++;
		if(beat_10ms_timer == 10) {
			beat_10ms_timer = 0;
			printf("time: %b", current_time.tv_nsec);
		}
	}
}
