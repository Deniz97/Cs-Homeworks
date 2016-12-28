import socket
import os
from netprotocol import *
import threading

class MainSender(threading.Thread):
    def __init__(self, thread_name,ip,port, queue):
        self.thread_name = thread_name
        self.port = port
        self.ip = ip
        self.input_que=queue
        #self.DEST_IP= ""  #not needed, just send back to recieved addr
        self.DEST_PORT = port
        self.sock = socket.socket(socket.AF_INET, # Internet
                                            socket.SOCK_DGRAM) # UDP
                                            sock.bind((self.ip,self.port))
        threading.Thread.__init__(self)
        self.timer_function = threading.Timer(1,timeout,args= [self.sock] )

    def run(self):
