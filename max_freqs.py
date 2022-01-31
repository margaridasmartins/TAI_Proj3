import os, getopt, sys
from time import process_time_ns
import numpy as np
import matplotlib.pyplot as plt
from scipy.io.wavfile import read

def wav_signiture(f,filename):
    split_filename=filename.split(".")
    if split_filename[1]=="mp3":
        return
    if dir:
        output=open("comp_samples/{}.freqs".format(split_filename[0]),'w+b')
    else:
        output=open("../comp_test/{}.freqs".format(split_filename[0]),'w+b')
    print("Getting {} frequency signature".format(".".join(split_filename)))

    Fs, data=read(f)
    sample_size=1024
    freq_count=5

    dS_factor=round(sample_size/512)
    dS_data=[]
    N=round(len(data)/dS_factor)

    for i in range(0,N,dS_factor):
        sum=0
        if i+dS_factor<=N:
            for j in range(dS_factor):
                sum+=np.right_shift(data[i*dS_factor+j][0],dS_factor)+np.right_shift(data[i*dS_factor+j][1],dS_factor)
            dS_data.append(sum)

    #fig,ax = plt.subplots()
    #ax.set_xscale('log')
    #plt.ylabel('Amplitude')
    #plt.xlabel('Frequency [Hz]')

    for s in range(0,N,512-128):
        Y_k = np.fft.fft(dS_data[s:s+512])[0:int(256)]/512 # FFT function from numpy
        Pxx = np.abs(Y_k) # be sure to get rid of imaginary part

        f = Fs*np.arange((256))/526; # frequency vector

        idx=np.argpartition(Pxx,-freq_count)[-freq_count:]
        for i in idx:
            if i>255:
                i=255
            output.write(int(i).to_bytes(1,'big'))
            
        if len(dS_data[s::])<512:
            break
        # plotting
        #plt.plot(f,Pxx,linewidth=5)
        #plt.show()
    output.close()

###############################################################################

help_message="max_freqs.py (-f <filepath>|-d <directory>)\tFrequency signiture of file\n"
dir=2
directory='music_samples'
filepath=""

try:
    opts, args=getopt.getopt(sys.argv[1:],'hf:d:',['numberChar='])
except getopt.GetOptError:
    print(help_message)
    sys.exit(2)

for opt, arg in opts:
    if opt in ('-h'):
        print(help_message)    
        sys.exit(2)
    elif opt in ('-f'):
        if dir!=2:
            print("ERR: cannot receive parameters -f and -d simultaneously")
            sys.exit(3)
        dir=0
        filepath=arg
    elif opt in ('-d'):
        if dir!=2:
            print("ERR: cannot receive parameters -f and -d simultaneously")
            sys.exit(3)
        dir=1
        directory=arg

if dir:
    # assign directory
    
    # iterate over files in that directory
    for filename in os.listdir(directory):
        f = os.path.join(directory, filename)
        # checking if it is a file
        if os.path.isfile(f):
            wav_signiture(f,filename)
else:
    split_filepath=filepath.split("/")
    wav_signiture(filepath,split_filepath[-1])