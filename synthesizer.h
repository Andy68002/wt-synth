/*Open Source Synthesizer
 * Synthesis header file
 * Author:
 *  Andrew McLaurin
 */
#ifndef SYNTHESIS
#define SYNTHESIS
// create a struct to store the pointers
//booleans definitions for flags
#define TRUE             1
#define FALSE            0
/* 1/44100s = 22675.737ns */
#define SAMPLE_RATE      22656
#define ONE_SECOND_NS    1000000000
#define NUM_NOTES        (6)
#define SAMPLE_WIDTH     (2)  // number of bytes
#define WAVETABLE_LENGTH (16777216) // Length

#define SAMPLE_SIZE (2) //number of bytes
#define NUM_CHANNELS (1) //number of channels (mono/stereo)
#define FRAME_SIZE (SAMPLE_SIZE * NUM_CHANNELS)
#define PERIOD_SAMPLES (16) //number of samples per period, mono

typedef struct {
	unsigned short tuning_word[NUM_NOTES];    // 16 bit unsigned note_tuning_words
	unsigned short attenuate[NUM_NOTES]; // 16 bit unsigned note_attenuation
	char enable[NUM_NOTES];              // boolean enable/disable
} USB_synthesizer_data;


#endif /* ifndef SYNTHESIS */
