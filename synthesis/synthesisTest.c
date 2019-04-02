/*
   OPEN SOURCE WAVETABLE Synthesizer
   NCSU ECE Senior Design 2019
   Authors:
   Andrew McLaurin
 */
#include <stdio.h>
#include <stdlib.h>
#include "../synthesizer.h"
#include "synthesis.h"


int main() {
	/*MAIN*/
	//initialize two buffers for USB-synthesis pipeline
	USB_synthesizer_data usb_buffer1;
	USB_synthesizer_data usb_buffer2;
	//initialize global buffer pointer for USB-synthesis data passing
	void *USB_synthesis_data_pointer = &usb_buffer1;
	char usb_buffer_select = 1;

	//initialize two period-sized buffers for synthesis-filtering
	int dds_buffer1[PERIOD_SAMPLES];
	int dds_buffer2[PERIOD_SAMPLES];

	void *dds_filter_buffer_pointer = &dds_buffer1;
	char dds_buffer_select = 1;

	//flag gets set in the ALSA callback function,
	//Initiates calculation of next period
	char filter_next_period_flag = FALSE;
	//flag set after filtering is done
	char calculate_next_period_flag = TRUE;

	// initialize the memory for the lookup table
	short *LUT = malloc(SAMPLE_WIDTH * WAVETABLE_LENGTH);

	/* Reading in the LUT */
	// pointer to file stream
	FILE *LUT_File;

	LUT_File = fopen("../wavetable_sine.bin", "rb"); // open file stream
	//TODO: Add error handling for wave file read

	fread(LUT, SAMPLE_WIDTH, WAVETABLE_LENGTH, LUT_File);

	usb_buffer1 = (USB_synthesizer_data){.tuning_word = {90, 90, 90, 3, 4, 5},
		                             .attenuate = {65535, 65535, 32767, 9, 10, 11},
		                             .enable = {1, 1, 1, 1, 1, 1}};
	init_DDS(LUT);
	while (1) {
		if(filter_next_period_flag) {
			filter_next_period_flag = FALSE;
			//INSERT AUDIO FUNCTION HERE
		}
		if(calculate_next_period_flag) {
			DDS(USB_synthesis_data_pointer);
			calculate_next_period_flag = FALSE;
		}
	}

	free(LUT);
	return 0;
}
