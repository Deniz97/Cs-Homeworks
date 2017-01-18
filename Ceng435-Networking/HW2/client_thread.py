import socket
import os
from netprotocol import *
import threading
import Queue
import time


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
        self.packet_array=[0]*6000
        self.window_base=[-1] 
        
        
        threading.Thread.__init__(self)
        
    

    def run(self):
         
        ip = self.ip
        input_que = self.input_que
        dest_ip=self.dest_ip
        dest_port = self.dest_port
        port=self.port
        
        window_size = 20
        next_seq_num = 0
        curr_dup_acks=0
        thread_name=self.thread_name
        #Flag to stop timer at the end of the execution
        timer_flag=[True]
        
        #Timer thread
        def timeout(thread_name, packet_array,window_base,dest_ip,dest_port,flag):
            sock = socket.socket(socket.AF_INET, # Internet
                                                socket.SOCK_DGRAM) # UDP
                      
            while(flag[0]):
                curr_base= window_base[0]
                try:
                    time.sleep(0.1)
                except Exception:
                    pass
                if(curr_base==window_base[0]):
                    try:
                        sock.sendto( packet_array[window_base[0]+1] ,(dest_ip,dest_port) ) 
                    except Exception:
                        pass
            sock.close()

        timer_function = threading.Thread(target=timeout, args = [self.thread_name, self.packet_array,self.window_base,self.dest_ip,self.dest_port,timer_flag] )

        timer_function.start()

        def reciever():

            curr_dup_acks=0
            last_ack_num=0
            ack_num=0
            
            sock = socket.socket(socket.AF_INET, # Internet
                                                socket.SOCK_DGRAM) # UDP
            
            sock.bind((ip,port))
            
            while(1):
                #recieve ack packet
                ack_packet, addr = sock.recvfrom(1024)
                
                if(notCorrupt(ack_packet)): #packet is not corrupted
                   
                   #Server signalled break, closing
                    if(getData(ack_packet)=="break"):
                        break

                    #Ack packet
                    if(getData(ack_packet)=="ACK"): 
                        ack_num=getSeqNum(ack_packet)
                        
                else: #packet corrupted
                     
                     ack_num=last_ack_num #Treat as a duplicate ack
                    
                    #succesfull cumulative ack
                if(ack_num>self.window_base[0]):
                    
                    #update window base
                    self.window_base[0]=ack_num
                    last_ack_num=ack_num
                    
                    #duplicate ack
                elif(ack_num==last_ack_num):
                    curr_dup_acks+=1
                    

                    if(curr_dup_acks==3):
                        curr_dup_acks=0
                        try:
                            sock.sendto(self.packet_array[last_ack_num+1] , (dest_ip,dest_port)) #packet_to_transmit is always last_ack_num+1(th) packet(also the windows base+1)                    
                        except Exception:
                            pass

        
        reciever_thread = threading.Thread(target=reciever)
        reciever_thread.start()
        
        data=""

        while(1) :   
            while(next_seq_num-self.window_base[0]<window_size):
                #get data from main process
                data = input_que.get()
                #make and send the packet
                sending_packet= makePacket(next_seq_num, data)                
                self.sock.sendto(sending_packet, (dest_ip, dest_port))
                self.packet_array[next_seq_num]=sending_packet        

                next_seq_num+=1
                #main process signaled break, closing
                if(data=="break"):
                    break

            if(data=="break"):
                break
        
        #wait for reciever before closing
        reciever_thread.join()

        #signal the timer to stop.
        timer_flag[0]=False
        timer_function.join()

