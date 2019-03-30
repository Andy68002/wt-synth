/*Open Source Synthesizer
 * Synthesis header file
 * Author:
 *  Andrew McLaurin
 */
#ifndef DDS_h
#define DDS_h
// 16 bit unsigned note_tuning_words
// 16 bit unsigned note_attenuation
// boolean enable/disable
// 32 bit pointer to LUT memory
void DDS(void *data);
void init_DDS(short *LUT);
void Send_Sample();


#endif /* ifndef SYNTHESIS */
