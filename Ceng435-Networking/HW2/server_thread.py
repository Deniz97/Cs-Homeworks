import socket
import os
from netprotocol import *
import threading
import Queue

class MainReciever(threading.Thread):
    def __init__(self, thread_name,ip,dest_ip,port, queue):
        self.thread_name = thread_name
        self.port = port
        self.ip = ip
        self.output_que=queue
        self.dest_port = port
        self.dest_ip=dest_ip
        self.sock = socket.socket(socket.AF_INET, # Internet
                                            socket.SOCK_DGRAM) # UDP
                                            sock.bind((self.ip,self.port))
        threading.Thread.__init__(self)
       
    def isContigious(array,suq_num):
        i=seq_num+1
        j=0
        while(j<len(array)):
            if(array[j]!=i):
                break
            i+=1
            j+=1
        return j

    def append(array,item):
        i =0
        retval=[]
        while(i<len(array)):
            if(array[i]>item):
                retval.append(item)
            retval.append(array[i] )
            i+=1
        return retval

    def Sender(sock, seq_num):
        sending_packet = makePacket(ip,dest_ip,seq_num,"ACK")
        sock.sendto(sending_packet,(dest_ip,dest_port))

    def run(self):
        expected_seq_num=0
        buffer_que=Queue.queue(1000)
        out_of_order_array=[]
        last_send_ack=0
        break_flag=false
        while(1):
            if(last_send_ack==expected_seq_num-1 and break_flag)
            incoming_packet, addr = sock.recvfrom()
        
            if(notCorrupt(incoming_packet)): #not corrupt
                recieved_data=getData(incoming_packet)
                recieved_ack=getSeqNum(incoming_packet)
                
                if(recieved_ack==expected_seq_num): #in-order packet
                    threading.Sender(sock,recieved_ack).start() #send ack
                    last_send_ack=recieved_ack
                    
                    i=isContigious(out_of_order_array,expected_seq_num)
                    out_of_order_array=out_of_order_array[i:]
                    while(i>0):
                        output_que.put(buffer_que.get())
                    output_que.put(recieved_data)
                    if(recieved_data=="break"):
                        break
                    expected_seq_num+=1
                    
                elif(recieved_ack>expected_seq_num): #out of order packet
                    recieved_data=getData(incoming_packet)
                    recieved_seq_num=getSeqNum(incoming_packet)

                    out_of_order_array = append(out_of_order_array, recieved_seq_num)
                    buffer_que.put(recieved_data)

                    threading.Sender(sock,last_send_ack).start() #send duplicate ack
                    if(recieved_data=="break"):
                        break_flag=true
                    
            else: #corrupt packet, send duplicate ack
                threading.Sender(sock,last_send_ack)






        
