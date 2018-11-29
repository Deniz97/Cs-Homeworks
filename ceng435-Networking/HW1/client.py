import socket
import time
import netprotocol

#Required Variables
UDP_IP = "10.10.1.2"
UDP_PORT = 5005
DATA = ""
SOURCE_IP="10.10.1.1"
DEST_IP="10.10.4.2"

#IP socket using UDP protocol
sock = socket.socket(socket.AF_INET, # Internet
                    socket.SOCK_DGRAM) # UDP
sock.bind(("",UDP_PORT))

#Let's send a thousan packet each having the data "Hello world for index"
for index in range(1,1001):
    
    DATA = "Hello world for " + str(index)

    #Create time stamp and the packet to send.
    time_stamp= time.time()
    sending_packet= netprotocol.makePacket(SOURCE_IP,DEST_IP,DATA,time_stamp)

    #Send the packet
    sock.sendto(sending_packet, (UDP_IP, UDP_PORT))
    #Recieve the packet
    incoming_packet, addr=sock.recvfrom(1024)
    
    #Print the recieved data, expecting ACKNOWLEDGE.
    #Since this is UDP we won't be resending packet in case of failure,
    #but it is still good to know.
    print "RECIEVED ", netprotocol.getData(incoming_packet)


