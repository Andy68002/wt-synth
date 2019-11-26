
import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
from scipy.io import wavfile
import sys
import wave
from pydub import AudioSegment



numberofharmonics=8
midivalue=48
fundamental=440
amplitude=30000 #Too high will cause clipping!
fundamental_playback=fundamental #Changing this will alter the frequency of the sample wave. Set to 'fundamental' as default
amplitude_cutoff=.02 #any amplitude that is lower than cutoff*max_amplitude is filtered out
harmonic_cutoff=10 #any harmonic within cutoff hertz of another is skipped


sound = AudioSegment.from_wav("audio.wav")
sound = sound.set_channels(1)
sound.export("audio_mono.wav", format="wav")

spf = wave.open("audio_mono.wav", "r")

#Extract Raw Audio from Wav File
#signal = spf.readframes(-1)
#signal = np.fromstring(signal, "Int16")

#plt.figure(1)
#plt.title("Signal Wave...")
#plt.plot(signal)
#plt.show()





fs, data = scipy.io.wavfile.read('audio_mono.wav')


# Number of samplepoints
N = len(data)
if (N % 2) == 0:
    N=N
else:
    N=N-1





# sample spacing
T = 1.0 / fs
x = np.linspace(0.0, T*N, N)

y = data

yf = scipy.fftpack.fft(y)

xf = np.linspace(0.0, 1.0/(2.0*T), N/2)


#fig, ax = plt.subplots()
#ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
#plt.show()


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
co=0
while(n<numberofharmonics):
    io=co
    while((io!=-1 and co<N/2-1)):
        if(harmonic_cutoff<abs(harm[co]-harm[io-1])):
            io=io-1
        else:
            co=co+1
            io=co
        if(harm[co]==0):
            co=co+1
            io=co
        harmonics[n]=harm[co]
    n=n+1
    co=co+1
        
   
harmonics.sort()
amplitudes = np.empty(numberofharmonics, dtype=np.longdouble)
n=0
while(n<numberofharmonics):
    itemindex = np.where(xf==harmonics[n])
    while((len(itemindex[0])==0 and n<numberofharmonics)):
        n=n+1
        itemindex = np.where(xf==harmonics[n])  
    amplitudes[n]=dat[itemindex]
    n=n+1
n=0
while(n<numberofharmonics):
    if((max(amplitudes)*amplitude_cutoff)>amplitudes[n]):
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

TrueFundamental=min(harmonics, key=lambda x:abs(x-fundamental))
harmnorm = np.empty(numberofharmonics, dtype=np.longdouble)
harmnorm=harmonics.copy()

while(n<numberofharmonics):
    harmnorm[n]=harmonics[n]/TrueFundamental
    n=n+1

n=0

ampnorm_temp = np.empty(numberofharmonics, dtype=np.longdouble)
ampnorm_temp=ampnorm.copy()

harmnorm_temp = np.empty(numberofharmonics, dtype=np.longdouble)
harmnorm_temp=harmnorm.copy()

while(n<numberofharmonics):
    i=0
    ampnorm_temp=ampnorm.copy()
    harmnorm_temp=harmnorm.copy()
    if(ampnorm[0]==0):
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





wave=0
n=0
ratio=np.count_nonzero(ampnorm)
while(n<numberofharmonics):
    wave=(((amplitude/ratio)*ampnorm[n])*np.sin(harmnorm[n]*fundamental_playback*2*np.pi*x))+wave
    n=n+1

#fig, ax = plt.subplots()
#ax.plot(x,wave)
#plt.show()


wave=wave.astype('int16')



scipy.io.wavfile.write('audio_sample.wav',fs,wave)


print('\n\nPress ENTER to End')
input()







