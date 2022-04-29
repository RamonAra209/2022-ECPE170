#!/usr/bin/env python3

# Python DNS query client
#
# Example usage:
#   ./dns.py --type=A --name=www.pacific.edu --server=8.8.8.8
#   ./dns.py --type=AAAA --name=www.google.com --server=8.8.8.8

# Should provide equivalent results to:
#   dig www.pacific.edu A @8.8.8.8 +noedns
#   dig www.google.com AAAA @8.8.8.8 +noedns
#   (note that the +noedns option is used to disable the pseduo-OPT
#    header that dig adds. Our Python DNS client does not need
#    to produce that optional, more modern header)


from posixpath import split
#! Ethan better show me that toxic ass youtuber 
import argparse
import ctypes
import random
import socket
import struct
import sys

def main():

    # Setup configuration
    server_ip = "54.148.163.48"
    port = 3456 
    server_address = (server_ip, port)


    # Create UDP socket
    # ---------
    # STUDENT TO-DO
    # ---------
    udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Generate DNS request message
    # ---------
    # STUDENT TO-DO
    # ---------
    num_A, num_B = 5, 10
    udp_request = bytearray()
    udp_request += struct.pack('!B', 1)     # B=unsigned int (1 byte), val = 1 is version 
    udp_request += struct.pack('!I', num_A)     # I=unsigned int (4 byte), val = 5 is # of choice
    udp_request += struct.pack('!I', num_B)    # I=unsigned int (4 byte), val = 10 is # of choice
    udp_request += struct.pack('!I', 5)     # I=unsigned int (4 byte), val = num chars in name, ie 5
    udp_request += struct.pack('!B', 82)    # B=unsigned int (1 byte), val = R 
    udp_request += struct.pack('!B', 97)    # B=unsigned int (1 byte), val = a
    udp_request += struct.pack('!B', 109)   # B=unsigned int (1 byte), val = m
    udp_request += struct.pack('!B', 111)   # B=unsigned int (1 byte), val = o
    udp_request += struct.pack('!B', 110)   # B=unsigned int (1 byte), val = n
    print(udp_request)

    # Send request message to server
    # (Tip: Use sendto() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
    udp.sendto(udp_request, server_address) 

    # Receive message from server
    # (Tip: use recvfrom() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
    raw_bytes = udp.recvfrom(4096)[0]
    reply = struct.unpack('!BHI', raw_bytes) # returns list of elements = [B, H, I]
    if reply[1] == 0:
        print("Failure")
    else:
        print("Success: ", end='')
    print(f"{num_A} + {num_B} = {reply[2]}")   

    # Close socket
    # ---------
    # STUDENT TO-DO
    # ---------
    udp.close()

    # Decode DNS message and display to screen


if __name__ == "__main__":
    sys.exit(main())
