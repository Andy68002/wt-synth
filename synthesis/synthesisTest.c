/*
 * Synthesis test code
 */
#include <stdio.h>
#include <stdlib.h>
#include "synthesis.h"
#define FILE_BUFFER_SIZE 4
int main() {
    // initialize arrays for frequency, attenuation, and enable
    unsigned short tuning[NUM_NOTES];
    unsigned short attenuate[NUM_NOTES];
    char enable[NUM_NOTES];

    // initialize the memory for the lookup table
    char *LUT = malloc(SAMPLE_WIDTH * WAVETABLE_LENGTH);

    // Reading in the LUT
    FILE *LUT_File;                     // pointer to file stream

    LUT_File = fopen("test.bin", "rb"); // open file stream

    fread(LUT, 1, 48, LUT_File);
    printf("%X", LUT);

    for (int i = 0; i < WAVETABLE_LENGTH; i++) {
        printf("i: %i, LUT: %c, &LUT: %i\n", i, LUT[i], &LUT[i]);
    }

    // DDS(tuning, attenuate, enable, LUT);

    free(LUT);
    return 0;
}
