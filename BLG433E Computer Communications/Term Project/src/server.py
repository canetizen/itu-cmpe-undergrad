"""
    BLG433E Term Project - Selective Repeat Protocol Implementation
    A UDP server implementation that uses Selective Repeat protocol for reliable data transfer
    Author(s):
        Mustafa Can Caliskan, 150200097
        Yusuf Emir Sezgin, 150200066
"""

import socket
import random as rd
from time import time, sleep
import sys

class Server:
    def __init__(self, host='127.0.0.1', port=12345, window_size=10, err_rate=5):
        # Initialize server with configurable window size and error rate
        print("Server Initialization Started...")
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((host, port))
        self.window_size = window_size  # Size of the sliding window
        self.err_rate = err_rate        # Probability of packet loss in percentage
        self.timeout = 0.0001           # Timeout for packet retransmission
        self.sequence_base = 0          # Base sequence number of the window
        self.next_sequence = 0          # Next sequence number to be sent
        self.window = {}                # Dictionary to store unacknowledged packets
        self.timer = {}                 # Dictionary to track packet transmission times
        print(f"Selected Window Size: {self.window_size}, Selected Error Rate: {self.err_rate}%.")
        print("Server Initialization Completed.")
        
    def create_packet(self, packet_type, sequence=0, payload=b''):
        """
        Create packets with appropriate headers based on type:
        0: Handshake packet (Type + Length + Payload)
        1: ACK packet (Type + Sequence)
        2: Data packet (Type + Length + Sequence + Payload)
        3: FIN packet (Type + Sequence)
        """
        if packet_type == 0:  # Handshake
            return bytes([0]) + bytes([len(payload)]) + payload
        elif packet_type == 1:  # ACK
            return bytes([1]) + bytes([sequence])
        elif packet_type == 2:  # DATA
            return bytes([2]) + bytes([len(payload)]) + bytes([sequence]) + payload
        elif packet_type == 3:  # FIN
            return bytes([3]) + bytes([sequence])
            
    def unreliableSend(self, packet, userIP):
        """
        Simulate unreliable network by randomly dropping packets
        based on the specified error rate
        """
        if self.err_rate < rd.randint(0, 100):
            self.sock.sendto(packet, userIP)
            
    def handle_timeout(self, sequence, client_addr):
        """
        Retransmit packet and reset its timer when timeout occurs
        """
        if sequence in self.window:
            self.unreliableSend(self.window[sequence], client_addr)
            self.timer[sequence] = time()
            
    def handshake(self):
        """
        Perform three-way handshake with client:
        1. Receive client's connection request with filename
        2. Send acknowledgment
        3. Receive client's confirmation
        """
        print("Waiting for client connection...")
        while True:
            try:
                data, client_addr = self.sock.recvfrom(1024)
                if data[0] == 0:  # Handshake packet
                    filename = data[2:2+data[1]].decode()
                    print(f"Received request for file: {filename}")
                    
                    # Send ACK with sequence 0
                    ack_packet = self.create_packet(1, 0)
                    self.unreliableSend(ack_packet, client_addr)
                    
                    # Wait for client's ACK
                    data, _ = self.sock.recvfrom(1024)
                    if data[0] == 1 and data[1] == 0:
                        return filename, client_addr
            except socket.timeout:
                continue
                
    def send_file(self, filename, client_addr):
        """
        Implement Selective Repeat protocol to send file:
        1. Read and segment file
        2. Maintain sliding window of unacknowledged packets
        3. Handle packet timeouts and retransmissions
        4. Process acknowledgments and advance window
        5. Perform connection termination
        """
        try:
            with open(f"./data/{filename}", 'rb') as f:
                data = f.read()
                
            # Split file into segments of maximum 255 bytes
            segments = [data[i:i+255] for i in range(0, len(data), 255)]
            total_segments = len(segments)
            
            while self.sequence_base < total_segments:
                # Send new packets within window bounds
                while self.next_sequence < min(self.sequence_base + self.window_size, total_segments):
                    packet = self.create_packet(2, self.next_sequence, segments[self.next_sequence])
                    self.window[self.next_sequence] = packet
                    self.timer[self.next_sequence] = time()
                    self.unreliableSend(packet, client_addr)
                    self.next_sequence += 1
                    
                # Check for packet timeouts and retransmit if necessary
                current_time = time()
                for seq in list(self.timer.keys()):
                    if current_time - self.timer[seq] > self.timeout:
                        self.handle_timeout(seq, client_addr)
                        
                # Process incoming acknowledgments
                try:
                    self.sock.settimeout(self.timeout)
                    data, _ = self.sock.recvfrom(1024)
                    if data[0] == 1:  # ACK packet
                        ack_seq = data[1]
                        if ack_seq in self.window:
                            del self.window[ack_seq]
                            del self.timer[ack_seq]
                            # Advance window if base sequence is acknowledged
                            if ack_seq == self.sequence_base:
                                while self.sequence_base not in self.window and self.sequence_base < total_segments:
                                    self.sequence_base += 1
                except socket.timeout:
                    continue
                    
            # Initiate connection termination
            fin_packet = self.create_packet(3, total_segments)
            self.unreliableSend(fin_packet, client_addr)
            
            # Handle connection termination handshake
            while True:
                try:
                    data, _ = self.sock.recvfrom(1024)
                    if data[0] == 1:  # ACK
                        continue
                    elif data[0] == 3:  # FIN
                        # Send final ACK
                        ack_packet = self.create_packet(1, data[1])
                        self.unreliableSend(ack_packet, client_addr)
                        break
                except socket.timeout:
                    self.unreliableSend(fin_packet, client_addr)
                    
        except FileNotFoundError:
            print(f"File {filename} not found")
            exit(1)
            
    def start(self):
        """
        Main server loop:
        1. Accept new connections
        2. Transfer requested files
        3. Reset state for next transfer
        """
        try:
            while True:
                filename, client_addr = self.handshake()
                self.send_file(filename, client_addr)
                print(f"Finished sending {filename}")
                # Reset server state for next file transfer
                self.sequence_base = 0
                self.next_sequence = 0
                self.window.clear()
                self.timer.clear()
        except KeyboardInterrupt:
            print("\nServer shutting down...")
        finally:
            self.sock.close()

if __name__ == "__main__":
    server = Server(window_size=int(sys.argv[1]), err_rate=int(sys.argv[2]))
    server.start()