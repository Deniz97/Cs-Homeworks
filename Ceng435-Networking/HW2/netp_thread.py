import socket
import os
from netprotocol import *

#Required Variables
UDP_IP = "10.10.1.2"
UDP_PORT = 5005
DATA = ""
SOURCE_IP="10.10.1.1"
DEST_IP="10.10.4.2"



class MainSender(threading.Thread):
    def __init__(self, thread_name,ip,dest_ip, port, queue):
        self.thread_name = thread_name
        self.port = port
        self.ip = ip
        self.input_que=queue
        self.DEST_IP= ""
        self.DEST_PORT =
        self.sock = socket.socket(socket.AF_INET, # Internet
                                            socket.SOCK_DGRAM) # UDP
                                            sock.bind((self.ip,self.port))
        threading.Thread.__init__(self)
    def run(self):
        #timeout_array = []
        ack_array = [0]*window_size #can be implemented as a long flag
        timer_duration = 0.5
        window_size = 100
        packet_array = [0]*window_size
        window_base =0
        current_seq_num = 0
        last_unacked_num = 0
        while(1):
            #read 1000-header_size byte from file
            #or from buffer[self.threadID] while buffer is not empty
            data = input_que.get()
            sending_packet= makePacket(current_seq_num, data)
            packet_array[current_seq_num-window_base] = sending_packet
            self.sock.sendto(sending_packet, (DEST_IP, DEST_PORT))
            ack_time = Time(timer_duration,timeout,args=[sending_packet] )
            
    def timeout(packet):



class Reciever(threading.Thread):
    def __init__(self,sock):
        threading.Thread.__init__(self)

    def run(self):
        ack_packet, addr = sock.recvfrom()
        if(notCorrupt(ack_packet)): #both can be implemented in the same function
            ack_num=getSeqNum(ack_packet)
            timeout_array[ack_num-window_base].stop()
            ack_array[ack_num-window_base] = 1
            flush(ack_array) #if contegious, move the window_base #DO TO reduce the timez

class Timer(threading.Thread):
    def __init__(self):



                




    