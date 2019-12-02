#include "wavesynth.h"
#include <stdio.h>
int accumulators[TOTAL_NUMBER_FREQUENCIES];
void init_DDS(short *samples)
{
    //Initialization function for DDS
    for (int i = 0; i < TOTAL_NUMBER_FREQUENCIES; i++)
    {
        accumulators[i] = 0;
        samples[i] = 0;
    }
}
float ATTENUATE_FACTOR = 0.125;
void DDS(void *DDS_data_array, void *USB_data_array, int numHarmonics, short *wavetable, short *samples, Envelope *envelope)
{
    DDS_data *dds_data = DDS_data_array;
    USB_data *usb_data = USB_data_array;
    //Loop to calculate PERIOD_SAMPLES number of samples
    for (int i = 0; i < PERIOD_SAMPLES; i++)
    {
        int currentSample = 0;
        //Loop through each note separately

        for (int current_note = 0; current_note < TOTAL_NUMBER_NOTES; current_note++)
        {
            int tempSample = 0;
            int note_done = 0;
            float x = 0;
            //get this notes attenuation vector
            //               usb_data[current_note].attenuation_vector
            float attenuation_multiple = 1.0;
            switch (usb_data[current_note].state)
            {
            case A:
                attenuation_multiple = usb_data[current_note].current_attenuation;
                if ((usb_data[current_note].current_attenuation += envelope->attack_speed) >= envelope->attack_level)
                {
                    usb_data[current_note].current_attenuation = envelope->attack_level;
                    usb_data[current_note].state = D;
                }
                break;

            case D:
                attenuation_multiple = usb_data[current_note].current_attenuation;
                if ((usb_data[current_note].current_attenuation -= envelope->decay_speed) <= envelope->decay_level)
                {
                    usb_data[current_note].current_attenuation = envelope->decay_level;
                    usb_data[current_note].state = S;
                }
                break;

            case S:
                attenuation_multiple = usb_data[current_note].current_attenuation;
                if(envelope->sustain_speed == 0.0) {}
                else if ((usb_data[current_note].current_attenuation -= envelope->sustain_speed) <= envelope->sustain_level)
                {
                    usb_data[current_note].current_attenuation = envelope->sustain_level;
                    usb_data[current_note].state = R;
                }
                break;
            case R:
                attenuation_multiple = usb_data[current_note].current_attenuation;
                if ((usb_data[current_note].current_attenuation -= envelope->release_speed) <= 0)
                {
                    usb_data[current_note].state = off;
                    note_done = 1;
                }
                break;
            }
            //Loop through the accumulators for those notes
            if (note_done)
            {
                for (int current_accumulator = (current_note * numHarmonics); current_accumulator < ((current_note + 1) * numHarmonics); current_accumulator++)
                {
                    dds_data[current_accumulator].enable = 0;
                }
            }
            else
            {
                for (int current_accumulator = (current_note * numHarmonics); current_accumulator < ((current_note + 1) * numHarmonics); current_accumulator++)
                {
                    if (dds_data[current_accumulator].enable)
                    {
                        accumulators[current_accumulator] += dds_data[current_accumulator].tuning_word;
                        accumulators[current_accumulator] = (accumulators[current_accumulator] > WAVETABLE_LENGTH) ? accumulators[current_accumulator] -= WAVETABLE_LENGTH : accumulators[current_accumulator];
                        //if note is enabled, currentSample += wavetable lookup
                        //bitwise anded with attenuation factor
                        tempSample += wavetable[accumulators[current_accumulator]] * dds_data[current_accumulator].attenuate;
                    }
                }
                tempSample = (int)((float)tempSample * attenuation_multiple) >> 3;
                currentSample = currentSample + tempSample;
            }
        }
        samples[i] = currentSample;
    }
}
