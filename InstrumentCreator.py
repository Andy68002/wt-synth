import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
from scipy.io import wavfile
import sys
from pydub import AudioSegment



numberofharmonics=8
midivalue=48




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
harmonics = np.empty(numberofharmonics, dtype=np.longdouble)
n=0
while(n<N/2):
    itemindex = np.where(dat==datsort[-(1+n)])
    harm[n]=xf[itemindex]
    n=n+1

n=0
c=0
while(n<8):
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
amplitudes = np.empty(numberofharmonics, dtype=np.longdouble)
n=0
while(n<numberofharmonics):
    itemindex = np.where(xf==harmonics[n])
    amplitudes[n]=dat[itemindex]
    n=n+1
n=0
while(n<numberofharmonics):
    if((max(amplitudes)*.02)>amplitudes[n]):
        amplitudes[n]=0
        harmonics[n]=0
    n=n+1
    


n=0

ampnorm = np.empty(numberofharmonics, dtype=np.longdouble)
ampnorm=amplitudes.copy()

while(n<numberofharmonics):
    ampnorm[n]=amplitudes[n]/max(amplitudes)
    n=n+1




n=0

harmnorm = np.empty(numberofharmonics, dtype=np.longdouble)
harmnorm=harmonics.copy()

while(n<numberofharmonics):
    harmnorm[n]=harmonics[n]/(np.min(harmonics[np.nonzero(harmonics)]))
    n=n+1

n=0

ampnorm_temp = np.empty(numberofharmonics, dtype=np.longdouble)
ampnorm_temp=ampnorm.copy()

harmnorm_temp = np.empty(numberofharmonics, dtype=np.longdouble)
harmnorm_temp=harmnorm.copy()

while(n<numberofharmonics):
    i=0
    if(ampnorm[n]==0):
        while(i<numberofharmonics-1):
            ampnorm[i]=ampnorm_temp[1+i]
            harmnorm[i]=harmnorm_temp[1+i]
            i=i+1
        ampnorm[i]=0
        harmnorm[i]=0
    n=n+1


print('{\n  "sampled_instrument": {')
print('      "attenuationvector": 1,')
print('      "num_harmonics":',numberofharmonics,end=',\n')
print('      "midiValue":',midivalue,end=',\n')   
print('      "harmonic_multiples": [')
print('      ',',\n       '.join(map(str, harmnorm))) 
#print('      ]\n    }\n  ]\n}')
print('      ],\n      "harmonic_attenuate": [')
print('      ',',\n       '.join(map(str, ampnorm))) 
print('    ]\n  }\n}')



print('\n\nPress ENTER to End')
input()






















