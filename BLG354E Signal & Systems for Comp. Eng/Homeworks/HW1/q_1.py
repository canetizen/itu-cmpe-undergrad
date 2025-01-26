"""
    BLG354E Project 1
    Mustafa Can Caliskan
    150200097
"""

import librosa
import numpy as np
import soundfile as sf

audio, samplingRate = librosa.load('bayrakfm.wav', sr=None)

# Define the length of each frame.
frameLen = samplingRate

# Calculate the number of frames in the audio.
nOfFrames = int(len(audio) / frameLen)

messageFrames = []

i = 0
while i < nOfFrames:
    # Define the start and end indices for the current frame.
    startIndex = i * frameLen
    endIndex = startIndex + frameLen
    
    # Extract the current frame.
    frame = audio[startIndex:endIndex]
    
    # Apply Fourier transform to the frame.
    frameForierTransformed = np.fft.fft(frame)
    
    # Split the Fourier-transformed frame and discard the first half.
    halfLen = len(frameForierTransformed) // 2
    messageForrier = np.zeros_like(frameForierTransformed)
    messageForrier[:halfLen] = frameForierTransformed[halfLen:]
    
    # Apply inverse Fourier transform to the modified frame.
    message_frame = np.fft.ifft(messageForrier)
    
    # Append the real part of the inverse transformed frame to the message frames list.
    messageFrames.append(message_frame.real)
    i += 1

hidden_message = np.concatenate(messageFrames)

# Write the extracted message to a new audio file.
sf.write('extractedMessage.wav', hidden_message, samplingRate)
print("Hidden message extracted.")
