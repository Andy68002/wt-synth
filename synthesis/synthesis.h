/*Open Source Synthesizer
 * Synthesis header file
 * Author:
 *  Andrew McLaurin
 */
#ifndef SYNTHESIS
#define SYNTHESIS

/* 1/44100s = 22675.737ns */
#define SAMPLE_RATE      22656
#define ONE_SECOND_NS    1000000000
#define NUM_NOTES        6
#define SAMPLE_WIDTH     (1)
#define WAVETABLE_LENGTH (48)
#define TRUE             1
#define FALSE            0

// 16 bit unsigned note_tuning_words
// 16 bit unsigned note_attenuation
// boolean enable/disable
// 32 bit pointer to LUT memory
void DDS(unsigned short *note_tuning_words,
         unsigned short *note_attenuation,
         char           *note_enable,
         int            *LUT);
void Send_Sample();


#endif /* ifndef SYNTHESIS */
