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
        self.packet_array=[0]*5300
        self.window_base=[-1] 
        
        
        threading.Thread.__init__(self)
        
    

    def run(self):
         
        ip = self.ip
        input_que = self.input_que
        dest_ip=self.dest_ip
        dest_port = self.dest_port
        port=self.port
        
        
        #timer_duration = 0.5
        window_size = 10
        #packet_array = self.packet_array
        #window_base = self.window_base
        next_seq_num = 0
        
        curr_dup_acks=0
        thread_name=self.thread_name

        def timeout(thread_name, packet_array,window_base,dest_ip,dest_port):
            sock = socket.socket(socket.AF_INET, # Internet
                                                socket.SOCK_DGRAM) # UDP
            
            
            while(1):
                curr_base= window_base[0]
                time.sleep(0.1)
                if(curr_base==window_base[0]):
                    sock.sendto( packet_array[window_base[0]+1] ,(dest_ip,dest_port) ) 
                    print "TIMER SEND from "+str(thread_name)+ " "+str(getSeqNum( packet_array[ window_base[0]+1 ] ))


            sock.close()


        timer_function = threading.Thread()
        timer_function = threading.Thread(target=timeout, args = [self.thread_name, self.packet_array,self.window_base,self.dest_ip,self.dest_port] )
        timer_function.daemon = True
        timer_function.start()

        def reciever():

            
            curr_dup_acks=0
            last_ack_num=0
            ack_num=0
            
            sock = socket.socket(socket.AF_INET, # Internet
                                                socket.SOCK_DGRAM) # UDP
            
            sock.bind((ip,port))
            
            while(1):
                ack_packet, addr = sock.recvfrom(1024)
                debug= " From " + str(thread_name) +"got ack for= "+str(getSeqNum(ack_packet))+" "
                if(notCorrupt(ack_packet)):
                    debug+= " Not Corrupt,  "
                    if(getData(ack_packet)=="break"):
                        debug+= " got break exiting "

                        print debug
                        break

                    if(getData(ack_packet)=="ACK"):  #reundant, can be just else
                        ack_num=getSeqNum(ack_packet)
                        
                else: #packet corrupted
                     debug+= " Is Corrupt,  "
                     ack_num=last_ack_num #Treat as a duplicate ack
                    
                    #succesfull cumulative ack
                if(ack_num>self.window_base[0]):
                    debug+= "  succesfull cumulative ack,  "
                    self.window_base[0]=ack_num
                    last_ack_num=ack_num
                    
                    #duplicate ack
                elif(ack_num==last_ack_num):
                    curr_dup_acks+=1
                    debug+="  duplicate ack no. "+str(curr_dup_acks)+"  "

                    if(curr_dup_acks==3):
                        debug+= " SENDING " +str(getSeqNum(self.packet_array[last_ack_num+1]))
                        curr_dup_acks=0
                        sock.sendto(self.packet_array[last_ack_num+1] , (dest_ip,dest_port)) #packet_to_transmit is always last_ack_num+1(th) packet(also the windows base)                    
                print
                print debug
                print
        
        reciever_thread = threading.Thread(target=reciever)
        reciever_thread.start()
        
        data=""
        s_debug =""
        while(1) :   
            while(next_seq_num-self.window_base[0]<window_size):
                s_debug =""
                data = input_que.get()

                sending_packet= makePacket(ip,dest_ip,next_seq_num, data)
                s_debug += "Sending from "+str(self.thread_name)+" num= "+str(next_seq_num)+", "
                
                self.sock.sendto(sending_packet, (dest_ip, dest_port))

                self.packet_array[next_seq_num]=sending_packet        

                next_seq_num+=1
                
                if(data=="break"):
                    s_debug += " GOT BREAK "
                    break
                #print s_debug
            if(data=="break"):
                break
        print s_debug
        reciever_thread.join()
        print "EXITING "+thread_name    
