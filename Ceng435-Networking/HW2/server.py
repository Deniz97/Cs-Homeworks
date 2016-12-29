import socket
import os
from netprotocol import *
import threading
import Queue
from server_thread import *


def compDestIp(ip):
	retval=ip
	retval[7] =  str(int(ip[7])-3)  
	return retval

#Open a file to write delay values in to
if not os.path.isfile("./output.txt"):
    os.system("touch output.txt")
try :
    output_file = open("output.txt","r")
except Exception:
    print "Could not open file output.txt"



# Create new threads
interface_ip_array = findInterfaces()
thread_array = []
que_array = []
i=0
while i<len(interface_ip_array) :
	que_array.append( Queue.Queue(2000)  )
	thread_array.append( MainReciever("Thread-"+"i",interface_ip_array[i],compDestIp(interface_ip_array[i])3000+i,que_array[i]  )
	thread_array[i].start()
	i=i+1

j=0
control=0
while(control<i) :
	to_write=que_array[j].get()
	j=(j+1)%i
	if(to_write=="break"):
		que_array[j].put("break")
		control+=1
		continue
	output_file.write(to_write)
	

j=0
while(j<i):
	thread_array[j].join()
	j=j+1
   	
