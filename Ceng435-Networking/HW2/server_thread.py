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
        self.sock.bind((self.ip,self.port))
        threading.Thread.__init__(self)

    

    

    def run(self):
        def isContigious(array,seq_num):
            i=seq_num+1
            j=0
            while(j<len(array)):
                if(array[j]!=i):
                    break
                i+=1
                j+=1
            return j

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

        def Sender(sock, seq_num,ip,dest_ip,dest_port):
            sending_packet = makePacket(ip,dest_ip,seq_num,"ACK")
            sock.sendto(sending_packet,(dest_ip,dest_port))

        ip=self.ip
        dest_ip=self.dest_ip
        port=self.port
        dest_port=self.dest_port
        thread_name=self.thread_name

        ending_seq_num = 31000
        expected_seq_num=0
        buffer_que=Queue.PriorityQueue(3000)
        out_of_order_array=[]
        last_send_ack=0

        while(expected_seq_num<ending_seq_num):
            debug=""
            
            
            incoming_packet, addr = self.sock.recvfrom(1024)
            
            debug+= " Exp seq num = " + str(expected_seq_num)
            debug+= " From "+ self.thread_name+"= "+str(getSeqNum(incoming_packet)) 
            debug+=" IS NOT CORRUPT= " + str(notCorrupt(incoming_packet))
            
            if( notCorrupt(incoming_packet) ): #not corrupt
                
                recieved_data=getData(incoming_packet)
                recieved_ack=getSeqNum(incoming_packet)
                
                if(recieved_ack==expected_seq_num): #in-order packet
                    debug+= " IN ORDER PACKET"
                    
                    i=isContigious(out_of_order_array,expected_seq_num)
                    
                    debug+= " out of order array= "
                    debug+= str( out_of_order_array)
                    debug+=" i= "+str(i)
                    
                    out_of_order_array=out_of_order_array[i:]
                    last_send_ack=recieved_ack+i
                    debug+= "IN THE SENDER " + " SENDING= "+makePacket(ip,dest_ip,last_send_ack,"ACK")+ " TO  "+str(dest_ip)+" "+str(dest_port)
                    
                    threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start() #send ack
                    expected_seq_num+=1+i

                    self.output_que.put(recieved_data)
                    while(i>0):
                        self.output_que.put(buffer_que.get()[1])
                        i-=1
                    
                    if(recieved_data=="break"):
                        ending_seq_num = recieved_ack

                    debug+= " EXP SEQ NUM= "+str(expected_seq_num)+" LAST SEND ACK= "+str(last_send_ack)
                
                elif(recieved_ack>expected_seq_num): #out of order packet
                    debug+= " OUT OF ORDER, "
                    if(recieved_ack in out_of_order_array):
                        debug += "CONTINUEING "
                        print debug
                        continue
                    out_of_order_array = ekle(out_of_order_array, recieved_ack)
                    debug+= "out_array= "+str(out_of_order_array)+", "
                    buffer_que.put((recieved_ack, recieved_data))
                    debug+= "IN THE SENDER " + " SENDING= "+makePacket(ip,dest_ip,last_send_ack,"ACK")+ " TO  "+str(dest_ip)+" "+str(dest_port)
                    threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start() #send duplicate ack



                    if(recieved_data=="break"):
                        ending_seq_num = recieved_ack

                    
            else: #corrupt packet, send duplicate ack
                debug+= "IN THE SENDER " + " SENDING= "+makePacket(ip,dest_ip,last_send_ack,"ACK")+ " TO  "+str(dest_ip)+" "+str(dest_port)
                threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start()
            
            print ""
            print debug
            print ""
        print "FROM "+thread_name+" SENDING BREAK"
        sending_packet = makePacket(ip,dest_ip,last_send_ack,"break")
        self.sock.sendto(sending_packet,(dest_ip,dest_port))

