from netprotocol import *
from netp_thread import *
import socket
import os
import threading
import Queue

def computeDestIp(ip):
	"""TODO: WRITE THIS"""

if not os.path.isfile("./input.txt"):
	print "Could not locate the file, exiting."
	exit()
try :
	input_file = open("input.txt","r")
except Exception:
	print "Could not open file input.txt"



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
	
j=0
while(j<i):
	thread_array[j].join()
	j=j+1