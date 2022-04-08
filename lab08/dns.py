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
from dns_tools import dns, dns_header_bitfields  # Custom module for boilerplate code

import argparse
import ctypes
import random
import socket
import struct
import sys

def main():

    # Setup configuration
    parser = argparse.ArgumentParser(description='DNS client for ECPE 170')
    parser.add_argument('--type', action='store', dest='qtype',
                        required=True, help='Query Type (A or AAAA)')
    parser.add_argument('--name', action='store', dest='qname',
                        required=True, help='Query Name')
    parser.add_argument('--server', action='store', dest='server_ip',
                        required=True, help='DNS Server IP')

    args = parser.parse_args()
    qtype = args.qtype
    qname = args.qname
    server_ip = args.server_ip
    port = 53
    server_address = (server_ip, port)

    if qtype not in ("A", "AAAA"):
        print("Error: Query Type must be 'A' (IPv4) or 'AAAA' (IPv6)")
        sys.exit()

    # Create UDP socket
    # ---------
    # STUDENT TO-DO
    # ---------
    udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Generate DNS request message
    # ---------
    # STUDENT TO-DO
    # ---------
    dns_request = bytearray()
    # dns_request.append(struct.pack('!H', random.randint(0, 65535))) # Message id is is generated via random 16 byte input
    dns_request += struct.pack('!H', random.randint(0, 65535)) # Message id is is generated via random 16 byte input
    
    #* Setting flags 
    flags = dns_header_bitfields() 
    flags.qr = 0
    flags.opcode = 0
    flags.aa = 0
    flags.tc = 0
    flags.rd = 1 # set to one to recursively ask for reply
    flags.ra = 0 
    flags.reserved = 0
    flags.rcode = 0
    dns_request += bytes(flags)

    dns_request += struct.pack('!H', 1) # set to one since we are sending one query
    dns_request += struct.pack('!H', 0) # not passing any entries for ANCount
    dns_request += struct.pack('!H', 0) # not passing any entries for NSCount
    dns_request += struct.pack('!H', 0) # Not passing any entries for ARCount
    
    split_url = qname.split('.')
    for part_of_url in split_url:
        dns_request += struct.pack('!b', len(part_of_url))
        dns_request += part_of_url.encode() 
    
    dns_request += struct.pack('!b', 0)
    if qtype == 'A':
        dns_request += struct.pack('!H', 1)
    else:
        dns_request += struct.pack('!H', 28)
    
    dns_request += struct.pack('!h', 1)

    # Send request message to server
    # (Tip: Use sendto() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
    udp.sendto(dns_request, server_address) 

    # Receive message from server
    # (Tip: use recvfrom() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
    raw_bytes = udp.recvfrom(4096)[0]
    # Close socket
    # ---------
    # STUDENT TO-DO
    # ---------
    udp.close()

    # Decode DNS message and display to screen
    dns.decode_dns(raw_bytes)


if __name__ == "__main__":
    sys.exit(main())
