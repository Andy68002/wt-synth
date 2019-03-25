
/*Open Source Synthesizer
  Synthesis header file
  Author:
	Andrew McLaurin
*/
#ifndef SYNTHESIS
#define SYNTHESIS

/* 1/44100s = 22675.737ns */
#define SAMPLE_RATE 22656
#define ONE_SECOND_NS 1000000000
#define NUM_NOTES 6
#define SAMPLE_WIDTH (16)
#define WAVETABLE_LENGTH (2^24)

//16 bit unsigned note_tuning_words
//16 bit unsigned note_attenuation
//boolean enable/disable
//32 bit pointer to LUT memory
void DDS(uint16_t *note_tuning_words, uint16_t *note_attenuation, bool *note_enable, int32_t *LUT);
void Send_Sample();


#endif
