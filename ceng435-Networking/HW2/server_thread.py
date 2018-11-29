import socket
import os
from netprotocol import *
import threading
import Queue


#Main Reciever Thread
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
        self.sock.bind((self.ip,self.port))
        threading.Thread.__init__(self)

    

    

    def run(self):
        #Check how many contigious element does out_of_order array has at it's head.
        def isContigious(array,seq_num):
            i=seq_num+1
            j=0
            while(j<len(array)):
                if(array[j]!=i):
                    break
                i+=1
                j+=1
            return j

        #append an item into a sorted array at correct position.
        def ekle(array,item):
            i =0
            retval=[]
            appended = False
            while(i<len(array)):
                if(array[i]>item and not appended):
                    retval.append(item)
                    appended = True
                retval.append(array[i] )
                i+=1
            if(not appended):
                retval.append(item)
            return retval

        #Send Ack Packets with given sequence number.
        def Sender(sock, seq_num,ip,dest_ip,dest_port):
            sending_packet = makePacket(seq_num,"ACK")
            sock.sendto(sending_packet,(dest_ip,dest_port))

        #define object variables for local use
        ip=self.ip
        dest_ip=self.dest_ip
        port=self.port
        dest_port=self.dest_port
        thread_name=self.thread_name

        #Required variables
        ending_seq_num = 31000 #arbitary until the break packet is recieved
        expected_seq_num=0
        #buffer que to hold out-of-order segments
        buffer_que=Queue.PriorityQueue(3000)
        out_of_order_array=[]
        last_send_ack=-1

        dupp_packet_count=0

        while(expected_seq_num<ending_seq_num):
            
            incoming_packet, addr = self.sock.recvfrom(1024)
            
            if( notCorrupt(incoming_packet) ): #not corrupt
                
                recieved_data=getData(incoming_packet)
                recieved_ack=getSeqNum(incoming_packet)
                
                if(recieved_ack==expected_seq_num): #in-order packet

                    #number of contigious out of order packets with respect to recieved seq num
                    i=isContigious(out_of_order_array,expected_seq_num)
                    
                    out_of_order_array=out_of_order_array[i:]
                    last_send_ack=recieved_ack+i

                    #send cumulatif ack
                    threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start() #send ack
                    expected_seq_num+=1+i

                    self.output_que.put(recieved_data)
                    #empty the buffer_que for correct (i) number of elements
                    while(i>0):
                        self.output_que.put(buffer_que.get()[1])
                        i-=1
                    
                    #client signalled end of data, set the ending_seq_num
                    if(recieved_data=="break"):
                        ending_seq_num = recieved_ack

                
                elif(recieved_ack>expected_seq_num): #out of order packet

                    #duplicate out of order packet
                    if(recieved_ack in out_of_order_array):
                        continue
                    
                    out_of_order_array = ekle(out_of_order_array, recieved_ack)
                    buffer_que.put((recieved_ack, recieved_data))
                    threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start() #send duplicate ack

                    #client signalled end of data, set the ending_seq_num
                    if(recieved_data=="break"):
                        ending_seq_num = recieved_ack
                
                #duplicate packet with sequence number smaller than last acked packet, may need to send a duplicate ack at times.
                else:
                    dupp_packet_count+=1
                    if(dupp_packet_count==8):
                        dupp_packet_count=0
                        threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start()   


                    
            else: #corrupt packet, send duplicate ack

                threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start()

        sending_packet = makePacket(last_send_ack,"break")
        self.sock.sendto(sending_packet,(dest_ip,dest_port))
        self.sock.sendto(sending_packet,(dest_ip,dest_port))
        self.sock.sendto(sending_packet,(dest_ip,dest_port))
        self.sock.sendto(sending_packet,(dest_ip,dest_port))
        self.sock.sendto(sending_packet,(dest_ip,dest_port))

