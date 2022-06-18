import numpy as np
import matplotlib.pyplot as plt
from scipy.io.wavfile import read, write

def plot(x, y): 
	plt.figure()
	plt.plot(x, y, lw=10)
	plt.savefig("./data.png"); 
	plt.close('all')

if __name__=='__main__':
	file_name = "sample.wav"
	data = np.loadtxt("./data.txt")
	x = np.arange(0, len(data), 1)
	plot(x, data)
	write(file_name, rate=44100, data=data)
