"""
    BLG354E Project 1
    Mustafa Can Caliskan
    150200097
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import bode

numeratorFirst = [10, 10]
denominatorFirst = [1, 20, 100]

numeratorSecond = [1]
denominatorSecond = [1, 10]

numeratorCascade = [10, 10]
denominatorCascade = [1, 30, 200]

# Frequency range
w = np.logspace(-2, 2, 500)

# Bode plots
_, magFirst, phaseFirst = bode((numeratorFirst, denominatorSecond), w)

_, magSecond, phaseSecond = bode((numeratorFirst, denominatorSecond), w)

_, magCascade, phaseCascade = bode((numeratorCascade, denominatorCascade), w)

plt.figure(figsize=(14, 10))

plt.subplot(3, 2, 1)
plt.semilogx(w, magFirst, color='blue')
plt.title("Magnitude Plot for H_1(s)")
plt.xlabel("Frequency (rad/s)")
plt.ylabel("Magnitude (dB)")

plt.subplot(3, 2, 2)
plt.semilogx(w, phaseFirst, color='blue')
plt.title("Phase Plot for H_1(s)")
plt.xlabel("Frequency (rad/s)")
plt.ylabel("Phase (degrees)")

plt.subplot(3, 2, 3)
plt.semilogx(w, magSecond, color='green')
plt.title("Magnitude Plot for H_2(s)")
plt.xlabel("Frequency (rad/s)")
plt.ylabel("Magnitude (dB)")

plt.subplot(3, 2, 4)
plt.semilogx(w, phaseSecond, color='green')
plt.title("Phase Plot for H_2(s)")
plt.xlabel("Frequency (rad/s)")
plt.ylabel("Phase (degrees)")

plt.subplot(3, 2, 5)
plt.semilogx(w, magCascade, color='red')
plt.title("Magnitude Plot for Cascade H_1(s) * H_2(s)")
plt.xlabel("Frequency (rad/s)")
plt.ylabel("Magnitude (dB)")

plt.subplot(3, 2, 6)
plt.semilogx(w, phaseCascade, color='red')
plt.title("Phase Plot for Cascade H_1(s) * H_2(s)")
plt.xlabel("Frequency (rad/s)")
plt.ylabel("Phase (degrees)")

plt.tight_layout()

plt.savefig("q4Graphs.png")
plt.show()