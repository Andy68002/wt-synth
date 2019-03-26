/*
 * Synthesis test code
 */
#include <stdio.h>
#include <stdlib.h>
#include "synthesis.h"
#include <pthread.h>
#define FILE_BUFFER_SIZE 4

// create a struct to store the pointers
typedef struct {
	unsigned short *tuning_ptr;
	unsigned short *attenuate_ptr;
	char           *enable_ptr;
	int            *LUT_ptr;
} passed_variables;

// thread function to break out synthesis to its own thread
// passed a single struct containing the variables needed
void* synthesis_thread(void *args) {
	passed_variables *dds_args = args;

	DDS(dds_args->tuning_ptr,
	    dds_args->attenuate_ptr,
	    dds_args->enable_ptr,
	    dds_args->LUT_ptr);
}

int main() {
	// initialize arrays for frequency, attenuation, and enable
	unsigned short tuning[NUM_NOTES];
	unsigned short attenuate[NUM_NOTES];
	char enable[NUM_NOTES];

	// initialize the memory for the lookup table
	int *LUT = malloc(SAMPLE_WIDTH * WAVETABLE_LENGTH);

// initialize the passed variable struct;
	passed_variables passed_args;

	passed_args.tuning_ptr    = tuning;
	passed_args.attenuate_ptr = attenuate;
	passed_args.enable_ptr    = enable;
	passed_args.LUT_ptr       = LUT;

	// Create a void pointer to the passed variables struct
	void *args = &passed_args;

	// Reading in the LUT
	FILE *LUT_File;                 // pointer to file stream

	LUT_File = fopen("test.bin", "rb"); // open file stream
//TODO: Add error handling for wave file read
	fread(LUT, SAMPLE_WIDTH, WAVETABLE_LENGTH, LUT_File);

	pthread_t thread_id;
	pthread_create(&thread_id, NULL, synthesis_thread, args);
//	DDS(tuning, attenuate, enable, LUT);
	while(1);
	free(LUT);
	return 0;
}
