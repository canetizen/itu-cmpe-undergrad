import soundcard as sc
import numpy as np
from scipy.fft import fft
import pyautogui
import time
from scipy.signal import find_peaks
import matplotlib.pyplot as plt
import random

def capture_audio():
    mics = sc.all_microphones(include_loopback=True)
    mic = mics[0]
    with mic.recorder(samplerate=100000) as mic:
        while True:
            data = mic.record(numframes=3000)
            yield np.mean(data, axis=1)

def analyze_heartbeat(signal):
    # Perform FFT to get frequency components
    N = len(signal)
    T = 1.0 / 50000.0
    yf = fft(signal)
    xf = np.fft.fftfreq(N, T)[:N//2]
    
    # Find peaks in the frequency domain
    peaks, _ = find_peaks(np.abs(yf[:N//2]))
    
    # Analyze the harmonic structure
    peak_freqs = xf[peaks]
    peak_magnitudes = np.abs(yf[:N//2][peaks])
    
    # Check for square wave characteristics (odd harmonics with significant magnitude)
    odd_harmonics = [freq for i, freq in enumerate(peak_freqs) if (i % 2) == 1]
    odd_harmonics_magnitudes = peak_magnitudes[::2]
    
    if len(odd_harmonics) > 0 and np.mean(odd_harmonics_magnitudes) > 0.1 * np.max(peak_magnitudes):
        print("square")
        return 'square'
    else:
        print("triangular")
        return 'triangular'
        
def control_monster(heartbeat_type):
    global currentMovement
    if heartbeat_type == 'square':
        pyautogui.keyUp(currentMovement)
    else:
        if currentMovement == "w":
            currentMovement = "d"
        elif currentMovement == "d":
            currentMovement = "s"
        elif currentMovement == "s":
            currentMovement = "a"
        elif currentMovement == "a":
            currentMovement = "w"
        pyautogui.keyDown(currentMovement)

time.sleep(3)
audio_stream = capture_audio()
currentMovement = "s"
for audio_data in audio_stream:
    control_monster(analyze_heartbeat(audio_data))
