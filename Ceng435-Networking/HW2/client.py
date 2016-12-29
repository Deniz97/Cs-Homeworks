from netprotocol import *
from netp_thread import *
import socket
import os
import threading
import Queue

if not os.path.isfile("./input.txt"):
	print "Could not locate the file, exiting."
	exit()
try :
	input_file = open("input.txt","r")
except Exception:
	print "Could not open file input.txt"

def computeDestIp(ip):
	retval=ip
	retval[7]=str(int(ip[7])+3) 
	return retval


# Create new threads
interface_ip_array = findInterfaces()
thread_array = []
que_array = []
i=0
while i<len(interface_ip_array) :
	que_array.append( Queue.Queue(2000)  )
	DEST_IP = computeDestIp(interface_ip_array[i])
	thread_array.append( MainSender("Thread-"+"i",interface_ip_array[i] , DEST_IP,3000+i,que_array[i]  )
	thread_array[i].start()
	i=i+1
j=0
to_push=input_file.read(900)
while  to_push!="":
	que_array[j].put(to_push)
	j=(j+1)%i
	to_push=input_file.read(900)
	if(to_push==""):
		j=0
		while(j<i):
			que_array[j].put("break")
		break
	
j=0
while(j<i):
	thread_array[j].join()
	j=j+1