import socket
import time
import netprotocol
import os

#Required variables
UDP_IP="10.10.4.1"
UDP_PORT = 5005

#Open a file to write delay values in to
if not os.path.isfile("./DelayData.txt"):
    os.system("touch DelayData.txt")
try :
    delay_file = open("DelayData.txt","w")
except Exception:
    print "Could not open file DelayData.txt"


#IP socket using UDP protocol
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind(("", UDP_PORT))

while True:
    #Recieve the packet
    try: 
        sock.settimeout(15)
        packet, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    except socket.timeout:
        print "Closing socket"
        delay_file.close()
        sock.close()
        exit()
   
    #Get time stamp immideatly after recieving packet.
    server_time_stamp=time.time()
    delay = server_time_stamp - netprotocol.getTimeStamp(packet)
    print "Received data:", netprotocol.getData(packet)
    print " End-to-end delay: ", delay
   
    #Write delay to file
    try:
        delay_file.write(str(delay))
    except Exception as error:
        print "Could not write to file, exiting"
        print error
        exit()
   
    #Switch the source and destination IPs for reply packet.
    SOURCE_IP=netprotocol.getDestinationIp(packet)
    DEST_IP=netprotocol.getSourceIp(packet)
    DATA = "ACKNOWLEDGED"

    #Make the reply packet to send
    sending_packet = netprotocol.makePacket(SOURCE_IP,DEST_IP,DATA)
    #Send the packet
    try:
        sock.sendto(sending_packet,(UDP_IP, UDP_PORT))
    except Exception as error:
        print error
        exit()
