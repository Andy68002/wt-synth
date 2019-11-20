import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
from scipy.io import wavfile
import sys
from pydub import AudioSegment

sound = AudioSegment.from_wav("audio.wav")
sound = sound.set_channels(1)
sound.export("audio_mono.wav", format="wav")

#spf = wave.open("audio_mono.wav", "r")

## Extract Raw Audio from Wav File
#signal = spf.readframes(-1)
#signal = np.fromstring(signal, "Int16")

#plt.figure(1)
#plt.title("Signal Wave...")
#plt.plot(signal)
#plt.show()


fs, data = wavfile.read('audio_mono.wav')


# Number of samplepoints
N = 22050
# sample spacing
T = 1.0 / 4410
x = np.linspace(0.0, T*N, N)

y = data

yf = scipy.fftpack.fft(y)

xf = np.linspace(0.0, 1.0/(2.0*T), N/2)


#fig, ax = plt.subplots()
#ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))

plt.show()
dat =2.0/N * np.abs(yf[:N//2])
datsort=2.0/N * np.abs(yf[:N//2])
datsort.sort()






harm = np.empty(datsort.shape, dtype=np.longdouble)
harmonics = np.empty(6, dtype=np.longdouble)
n=0
while(n<N/2):
    itemindex = np.where(dat==datsort[-(1+n)])
    harm[n]=xf[itemindex]
    n=n+1

n=0
c=0
while(n<6):
    i=c
    while(i!=-1):
        if(10<abs(harm[c]-harm[i-1])):
            i=i-1
        else:
            c=c+1
            i=c
        if(harm[c]==0):
            c=c+1
            i=c
        harmonics[n]=harm[c]
    n=n+1
    c=c+1
        
   
harmonics.sort()
amplitudes = np.empty(6, dtype=np.longdouble)
n=0
while(n<6):
    itemindex = np.where(xf==harmonics[n])
    amplitudes[n]=dat[itemindex]
    n=n+1
n=0
while(n<6):
    if((max(amplitudes)*.01)>amplitudes[n]):
        amplitudes[n]=0
        harmonics[n]=0
    n=n+1
    


n=0
ampnorm=[amplitudes[0],amplitudes[1],amplitudes[2],amplitudes[3],amplitudes[4],amplitudes[5]]

while(n<6):
    ampnorm[n]=amplitudes[n]/max(amplitudes)
    n=n+1
    
if(ampnorm[0]==0):
    ampnorm.sort(reverse=True)
    


n=0
harmnorm=[harmonics[0],harmonics[1],harmonics[2],harmonics[3],harmonics[4],harmonics[5]]

while(n<6):
    harmnorm[n]=harmonics[n]/(np.min(harmonics[np.nonzero(harmonics)]))
    n=n+1

if(harmnorm[0]==0):
    harmnorm.sort(reverse=True)


print('{\n  "sampled_instrument": {')
print('      "attenuationvector": 1,')
print('      "num_harmonics": 6,')
print('      "midiValue": 48,')   
print('      "harmonic_multiples": [')
print('      ',',\n       '.join(map(str, harmnorm))) 
#print('      ]\n    }\n  ]\n}')
print('      ],\n      "harmonic_attenuate": [')
print('      ',',\n       '.join(map(str, ampnorm))) 
print('    ]\n  }\n}')



print('\n\nPress ENTER to End')
input()




















