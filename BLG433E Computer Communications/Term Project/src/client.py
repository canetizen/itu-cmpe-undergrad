"""
    BLG433E Term Project - Selective Repeat Protocol Implementation
    UDP client that implements reliable data transfer using Selective Repeat
    Author(s):
        Mustafa Can Caliskan, 150200097
        Yusuf Emir Sezgin, 150200066
"""

import socket
import random as rd
from time import time
import sys

class Client:
    def __init__(self, host='127.0.0.1', port=12345, window_size=10, err_rate=5):
        # Initialize client with configurable parameters
        print("Client Initialization Started...")
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_addr = (host, port)
        self.window_size = window_size      # Size of receiving window
        self.err_rate = err_rate           # Packet loss probability
        self.timeout = 0.0001              # Timeout for packet reception
        self.received_buffer = {}          # Buffer for out-of-order packets
        self.expected_sequence = 0         # Next expected sequence number
        print(f"Selected Window Size: {self.window_size}, Selected Error Rate: {self.err_rate}%.")
        print("Client Initialization Completed...")
        
    def create_packet(self, packet_type, sequence=0, payload=b''):
        """
        Create packets with appropriate headers based on type:
        0: Handshake (Type + Length + Payload)
        1: ACK (Type + Sequence)
        2: Data (Type + Length + Sequence + Payload)
        3: FIN (Type + Sequence)
        """
        if packet_type == 0:  # Handshake
            return bytes([0]) + bytes([len(payload)]) + payload
        elif packet_type == 1:  # ACK
            return bytes([1]) + bytes([sequence])
        elif packet_type == 2:  # DATA
            return bytes([2]) + bytes([len(payload)]) + bytes([sequence]) + payload
        elif packet_type == 3:  # FIN
            return bytes([3]) + bytes([sequence])
            
    def unreliableSend(self, packet):
        """Simulate unreliable network with random packet loss"""
        if self.err_rate < rd.randint(0, 100):
            self.sock.sendto(packet, self.server_addr)
            
    def handshake(self, filename):
        """
        Three-way handshake process:
        1. Send connection request with filename
        2. Wait for server ACK
        3. Send confirmation ACK
        """
        handshake_packet = self.create_packet(0, payload=filename.encode())
        self.unreliableSend(handshake_packet)
        
        while True:
            try:
                self.sock.settimeout(self.timeout)
                data, _ = self.sock.recvfrom(1024)
                if data[0] == 1 and data[1] == 0:  # ACK packet with sequence 0
                    ack_packet = self.create_packet(1, 0)
                    self.unreliableSend(ack_packet)
                    return True
            except socket.timeout:
                self.unreliableSend(handshake_packet)
                
    def receive_file(self):
        """
        Implement Selective Repeat receiver:
        1. Accept packets within window
        2. Buffer out-of-order packets
        3. Send ACKs for received packets
        4. Deliver in-order data to application
        5. Handle connection termination
        """
        while True:
            try:
                self.sock.settimeout(self.timeout)
                data, _ = self.sock.recvfrom(1024)
                
                if data[0] == 2:  # DATA packet
                    payload_length = data[1]
                    sequence = data[2]
                    payload = data[3:3+payload_length]
                    
                    # Accept if within receiving window
                    if self.expected_sequence <= sequence < self.expected_sequence + self.window_size:
                        self.received_buffer[sequence] = payload
                        
                    # Always acknowledge received packets
                    ack_packet = self.create_packet(1, sequence)
                    self.unreliableSend(ack_packet)
                    
                    # Deliver consecutive packets to application
                    while self.expected_sequence in self.received_buffer:
                        yield self.received_buffer.pop(self.expected_sequence)
                        self.expected_sequence += 1
                        
                elif data[0] == 3:  # FIN packet
                    # Handle connection termination
                    ack_packet = self.create_packet(1, data[1])
                    self.unreliableSend(ack_packet)
                    
                    fin_packet = self.create_packet(3, data[1] + 1)
                    self.unreliableSend(fin_packet)
                    
                    try:
                        self.sock.settimeout(self.timeout * 2)
                        data, _ = self.sock.recvfrom(1024)
                        if data[0] == 1:
                            break
                    except socket.timeout:
                        break
                        
            except socket.timeout:
                continue
                
    def start(self, filename):
        """
        Main client operation:
        1. Establish connection
        2. Receive file data
        3. Handle cleanup
        """
        try:
            if self.handshake(filename):
                print(f"Connected to server, requesting {filename}")
                received_data = b''
                for data in self.receive_file():
                    received_data += data
                print(f"Received {len(received_data)} bytes")
                return received_data
        except KeyboardInterrupt:
            print("\nClient shutting down...")
        finally:
            self.sock.close()

if __name__ == "__main__":
    client = Client(window_size=int(sys.argv[1]), err_rate=int(sys.argv[2]))
    received_data = client.start(sys.argv[3])
    if received_data:
        print("File contents:", received_data.decode())