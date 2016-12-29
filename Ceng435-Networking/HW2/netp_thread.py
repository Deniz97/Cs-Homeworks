import socket
import os
from netprotocol import *
import threading
import Queue

class Reciever(threading.Thread):
    def __init__(self,sock):
        self.sock = sock
        threading.Thread.__init__(self)

    def run(self):
        while(1)
            ack_packet, addr = sock.recvfrom()
                if(notCorrupt(ack_packet):
                    if(getData(ack_packet)=="break"):
                        break
                    if(getData(ack_packet)=="ACK"):  #reundant, can be just else
                        ack_num=getSeqNum(ack_packet))
                else: #packet corrupted
                    ack_num=last_ack_num #Treat as a duplicate ack
                
                #succesfull cumulative ack
                if(ack_num>window_base):
                    window_base=ack_num
                    last_ack_num=ack_num
                    if(last_ack_num<next_seq_num-1): #if there are any unacked packets start timer
                        #timer_function.cancel()
                        if(timer_function.isAlive()):
                            timer_function.cancel()
                        timer_function.start()
                
                #duplicate ack
                elif(ack_num==last_ack_num):
                    curr_dup_acks+=1
                    
                    if(curr_dup_acks==3):
                        sock.sendto(packet_array[last_ack_num+1] , (dest_ip,dest_port)) #packet_to_transmit is always last_ack_num+1(th) packet(also the windows base)                    
                

class MainSender(threading.Thread):
    def __init__(self, thread_name,ip,dest_ip, port, queue):
        self.thread_name = thread_name
        self.port = port
        self.ip = ip
        self.input_que=queue
        self.dest_ip= dest_ip
        self.dest_port = port
        self.sock = socket.socket(socket.AF_INET, # Internet
                                            socket.SOCK_DGRAM) # UDP
                                            sock.bind((self.ip,self.port))
        self.timer_function = threading.Timer(1,timeout,args= [self.sock] )
        threading.Thread.__init__(self)
        
    def timeout(sock):
        sock.sendto(packet_array[window_base+1] ,(dest_ip,dest_port) )
        timer_function.start()

    def run(self):
        
        #timer_duration = 0.5
        window_size = 200
        packet_array = [0]*5300
        window_base =-1
        next_seq_num = 0
        last_ack_num=0
        curr_dup_acks=0
        reciever_thread = Reciever(self.sock)
        reciever_thread.start()


         while(1) :
            
            while(next_seq_num-window_base<window_size):
                
                data = input_que.get()
                sending_packet= makePacket(ip,dest_ip,next_seq_num, data)
                self.sock.sendto(sending_packet, (DEST_IP, DEST_PORT))
                packet_array[next_seq_num]=sending_packet        
        
                if( !timer_function.isAlive() ):
                    timer_function.start()
                next_seq_num+=1
                if(data="break"):
                    break
            if(date=="break"):
                break
        reciever_thread.join()
    





                




    