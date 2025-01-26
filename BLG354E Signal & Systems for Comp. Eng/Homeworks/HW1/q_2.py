"""
    BLG354E Project 1
    Mustafa Can Caliskan
    150200097
"""

import numpy as np
import scipy.signal as signal
import soundfile as sf

audio, samplingRate = sf.read('extractedMessage.wav')

# Filter coefficients.
b = [1, -7/4, -1/2]
a = [1, 1/4, -1/8]

# Linear filtering.
filteredAudio = signal.lfilter(b, a, audio)

sf.write('filteredMessage.wav', filteredAudio, samplingRate)
print("Extracted message filtered.")
