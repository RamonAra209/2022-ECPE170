import socket
import struct
import sys

def main():
    # Setup configuration
    server_ip = "54.148.163.48"
    port = 3456 
    server_address = (server_ip, port)

    # Create UDP socket
    udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        #? socket.AF_INET = Internet family of internet protocals v4 addresses
        #? socket.SOCK_DGRAM: Allows us to send packets via datagrams

    # Generate UDP request message
    num_A, num_B = 5, 10
    udp_request = bytearray()
    udp_request += struct.pack('!B', 1)     # B=unsigned char (1 byte), val = 1 is version 
    udp_request += struct.pack('!I', num_A) # I=unsigned int (4 byte), val = 5 is # of choice
    udp_request += struct.pack('!I', num_B) # I=unsigned int (4 byte), val = 10 is # of choice
    udp_request += struct.pack('!I', 5)     # I=unsigned int (4 byte), val = num chars in name, ie 5
    udp_request += struct.pack('!B', 82)    # B=unsigned char (1 byte), val = R 
    udp_request += struct.pack('!B', 97)    # B=unsigned char (1 byte), val = a
    udp_request += struct.pack('!B', 109)   # B=unsigned char (1 byte), val = m
    udp_request += struct.pack('!B', 111)   # B=unsigned char (1 byte), val = o
    udp_request += struct.pack('!B', 110)   # B=unsigned char (1 byte), val = n

    # Send request message to server
    udp.sendto(udp_request, server_address) 

    # Receive message from server
    raw_bytes = udp.recvfrom(4096)[0]
    reply = struct.unpack('!BHI', raw_bytes) # returns list of elements = [B, H, I] #? !H = unsigned short
    if reply[1] == 0:
        print("Failure")
    else:
        print(f"Success: {num_A} + {num_B} = {reply[2]}")   # Server status = Success, i.e. print sum

    # Close socket
    udp.close()

if __name__ == "__main__":
    sys.exit(main())
