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
            while(i<len(array)):
                if(array[i]>item):
                    retval.append(item)
                retval.append(array[i] )
                i+=1
            return retval

        def Sender(sock, seq_num,ip,dest_ip,dest_port):
            sending_packet = makePacket(ip,dest_ip,seq_num,"ACK")
            self.sock.sendto(sending_packet,(dest_ip,dest_port))

        print "LISTENING"
        ip=self.ip
        dest_ip=self.dest_ip
        port=self.port
        dest_port=self.dest_port
        thread_name=self.thread_name

        expected_seq_num=0
        buffer_que=Queue.PriorityQueue(3000)
        out_of_order_array=[]
        last_send_ack=0
        break_flag= False
        while(1):
            debug=""
            if(last_send_ack==expected_seq_num-1 and break_flag):
                break
            
            incoming_packet, addr = self.sock.recvfrom(1024)
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
                    
                    self.output_que.put(recieved_data)
                    while(i>0):
                        self.output_que.put(buffer_que.get())
                    
                    if(recieved_data=="break"):
                        break
                    expected_seq_num+=1
                    debug+= " EXP SEQ NUM= "+str(expected_seq_num)+" LAST SEND ACK= "+str(last_send_ack)
                elif(recieved_ack>expected_seq_num): #out of order packet
                    debug+= " OUT OF ORDER, "
                    recieved_data=getData(incoming_packet)
                    recieved_seq_num=getSeqNum(incoming_packet)

                    out_of_order_array = ekle(out_of_order_array, recieved_seq_num)
                    debug+= "out_array= "+str(out_of_order_array)+", "
                    buffer_que.put((recieved_seq_num, recieved_data))
                    debug+= "IN THE SENDER " + " SENDING= "+makePacket(ip,dest_ip,last_send_ack,"ACK")+ " TO  "+str(dest_ip)+" "+str(dest_port)
                    threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start() #send duplicate ack



                    if(recieved_data=="break"):
                        break_flag=true

                    
            else: #corrupt packet, send duplicate ack
                debug+= "IN THE SENDER " + " SENDING= "+makePacket(ip,dest_ip,last_send_ack,"ACK")+ " TO  "+str(dest_ip)+" "+str(dest_port)
                threading.Thread(target=Sender, args = (self.sock,last_send_ack,ip,dest_ip,dest_port )).start()
            print ""
            print debug
            print ""
