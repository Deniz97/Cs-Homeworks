import socket
import netprotocol

#Required variables
UDP_IP = ""
UDP_PORT = 5005

#IP socket using UDP protocol
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind(("", UDP_PORT))

while(True):
    #Recieve the packet
    packet, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    
    #Get the target UDP ip
    UDP_IP = netprotocol.getTargetIp(packet,addr)

    #Send the packet
    sock.sendto(packet, (UDP_IP, UDP_PORT))
