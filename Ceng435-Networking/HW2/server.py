import socket
import os
from netprotocol import *
import threading


		
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
	thread_array.append( MainSender("Thread-"+"i",interface_ip_array[i] ,3000+i,que_array[i]  )
	thread_array[i].start()
	i=i+1
"""
j=0
to_push=input_file.read(900)
while  to_push!="":
	que_array[j].put(to_push)
	j=(j+1)%i
	to_push=input_file.read(900)
"""

j=0
while :
	to_write=que_array[j].get()
	#if(to_write!="-1"):
	output_file.write(to_write)
	j=(j+1)%i

j=0
while(j<i):
	thread_array[j].join()
	j=j+1
   	
