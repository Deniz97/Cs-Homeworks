import socket
import os
from netprotocol import *
import threading


class MainSender(threading.Thread):
    def __init__(self, thread_name,ip,dest_ip, port, queue):
        self.thread_name = thread_name
        self.port = port
        self.ip = ip
        self.input_que=queue
        self.DEST_IP= ""
        self.DEST_PORT = port
        self.sock = socket.socket(socket.AF_INET, # Internet
                                            socket.SOCK_DGRAM) # UDP
                                            sock.bind((self.ip,self.port))
        threading.Thread.__init__(self)
        self.timer_function = threading.Timer(1,timeout,args= [self.sock] )
    def timeout(sock):
        sock.sendto(packet_array[window_base+1] ,(DEST_IP,DEST_PORT) )
        timer_function.start()

    def run(self):
        #timeout_array = []
        #ack_array = [0]*window_size #can be implemented as a long flag
        #timer_duration = 0.5
        window_size = 200
        packet_array = [0]*5000
        window_base =0
        next_seq_num = 0
        l#ast_unacked_num = 0
        last_ack_num=0
        curr_dup_acks=0
        #packet_to_retransmit = ""
        Reciever(self.sock).start()
         #This is to make packter_to_retransmit without need ot packet_array

         while(1)   
            
            while(next_seq_num-window_base<window_size):
                #read 1000-header_size byte from file
                #or from buffer[self.threadID] while buffer is not empty
                
                data = input_que.get()
                sending_packet= makePacket(next_seq_num, data)
                #packet_array[next_seq_num] = sending_packet
                self.sock.sendto(sending_packet, (DEST_IP, DEST_PORT))
                packet_array[next_seq_num]=sending_packet        
                #timeout_array[next_seq_num]=Time(timer_duration,timeout,args= [sending_packet, self.sock] )
                #timeout_array[next_seq_num].start()
                if( """timer_function not running""" ):
                    timer_function.start()
                next_seq_num+=1
            
    


class Reciever(threading.Thread):
    def __init__(self,sock):
        threading.Thread.__init__(self)
        self.sock = sock
    def run(self):
        ack_packet, addr = sock.recvfrom()
            if(notCorrupt(ack_packet) and getData(ack_packet)=="ACK"): 
                ack_num=getSeqNum(ack_packet)
            
            else: #packet corrupted
                ack_num=last_ack_num #Treat as a duplicate ack
            
            #succesfull cumulative ack
            if(ack_num>window_base):
                window_base=ack_num
                last_ack_num=ack_num
                if(last_ack_num<next_seq_num-1):
                    #START TIMER
                    timer_function.cancel()
                    timer_function.start()
            #duplicate ack
            elif(ack_num==last_ack_num):
                curr_dup_acks+=1
                
                if(curr_dup_acks==3):
                    sock.sendto(packet_array[last_ack_num+1] , (UDP_IP,UDP_PORT)) #packet_to_transmit is always last_ack_num+1(th) packet

            #timeout_array[ack_num].stop()
            #ack_array[ack_num-window_base] = 1
            


                




    