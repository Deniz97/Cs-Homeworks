import socket
import os
from netprotocol import *
import threading
import Queue
from server_thread import *
import time

def server(given_ips=[]):
    def compDestIp(ip,numberOfInterfaces):
        retval=ip
        retval=ip[:6]+str(int(ip[6])-numberOfInterfaces) +".1"
        return retval

    #Open a file to write delay values in to
    if not os.path.isfile("./output.txt"):
        os.system("touch output.txt")
    try :
        output_file = open("output.txt","w")
    except Exception:
        print "Could not open file output.txt"



    # Create new threads
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


    thread_array = []
    que_array = []
    i=0
    while i<numberOfInterfaces :
        que_array.append( Queue.Queue(6000/numberOfInterfaces)  )
            
        my_thread=MainReciever("Threadd-"+str(i),interface_ip_array[i], dest_ip_array[i] ,3000+i,que_array[i] )
        my_thread.start()
        thread_array.append(my_thread)
        i=i+1

    j=0
    control=0
    while(control< (2**i)-1 ) :
        to_write=que_array[j].get()

        if(to_write=="break"):
            que_array[j].put("break")
            control= control | (1<<j)
            j=(j+1)%i
            continue

        j=(j+1)%i
        output_file.write( to_write )


    for t in thread_array:
        t.join()

    output_file.close()

    print time.time()


