import numpy as np
import matplotlib.pyplot as plt
from scipy.io.wavfile import read

Fs, data=read('test2.wav')
output=open("test.freqs",'w+b')

sample_size=1024
sample_interval=256
dS_factor=round(sample_size/512)
dS_interval=round(sample_interval/dS_factor)
dS_data=[]
print(len(data))
N=round(len(data)/dS_factor)

for i in range(0,N,dS_factor):
    sum=0
    if i+dS_factor<=N:
        for j in range(dS_factor):
            sum+=np.right_shift(data[i*dS_factor+j][0],dS_factor)+np.right_shift(data[i*dS_factor+j][1],dS_factor)
        dS_data.append(sum)

print(len(dS_data))

fig,ax = plt.subplots()
ax.set_xscale('log')
plt.ylabel('Amplitude')
plt.xlabel('Frequency [Hz]')

for s in range(0,N,512-dS_interval):
    if s+512>=N/2:
        break
    #print(s,N)
    Y_k = np.fft.fft(dS_data[s:s+512])[0:int(256)]/512 # FFT function from numpy
    Pxx = np.abs(Y_k) # be sure to get rid of imaginary part

    f = Fs*np.arange((256))/526; # frequency vector

    idx=np.argpartition(Pxx,5)
    for i in idx[:4]:
        if i>255:
            i=255
        output.write(int(i).to_bytes(1,'big'))
        

    # plotting
    plt.plot(f,Pxx,linewidth=5)
    #plt.show()
output.close()