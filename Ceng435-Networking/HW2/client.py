
from netprotocol import *
from client_thread import *
import socket
import os
import threading
import Queue
import time

def client(given_ips=[]):
        time_stamp = time.time()
        #open the files
        if not os.path.isfile("./input.txt"):
                print "Could not locate the file, exiting."
                exit()
        try :
                input_file = open("input.txt","r")
        except Exception:
                print "Could not open file input.txt"
        #compute the default dest_ip for a given ip
        def compDestIp(ip,numberOfInterfaces):
                retval=ip
                retval=ip[:6]+str(int(ip[6])+numberOfInterfaces) +".2"
                return retval

        #set the ip and dest_ip arrays, uses compDestIp for default if no target ip specified
        interface_ip_array = findInterfaces()
        interface_ip_array.sort()
        numberOfInterfaces = len(interface_ip_array)
        
        dest_ip_array = []
        if(len(given_ips)==0):
                for ip in interface_ip_array:
                        dest_ip_array.append( compDestIp(ip,numberOfInterfaces) )
        elif(len(given_ips)==numberOfInterfaces):
                dest_ip_array=given_ips[:]
        else:
                raise "Bad ip arguments"



        #Create the threads and their ques
        thread_array = []
        que_array = []
        i=0
        while i<numberOfInterfaces :
                que_array.append( Queue.Queue(6000/numberOfInterfaces)  )
                my_thread = MainSender("Threadd-"+str(i),interface_ip_array[i] ,    dest_ip_array[i]  ,3000+i,que_array[i]  )
                my_thread.start()
                thread_array.append(my_thread)
                i=i+1
        j=0

        #Read from file and write to ques in loop
        to_push=input_file.read(900)
        while  to_push!="" and j<i:
                que_array[j].put(to_push)
                j=(j+1)%i
                to_push=input_file.read(900)
                if( len(to_push)==0  ):
                        j=0
                        while(j<i):
                                que_array[j].put("break")
                                j+=1
                        break

        #terminate
        for t in thread_array:
                t.join()
        input_file.close()

        print time_stamp


