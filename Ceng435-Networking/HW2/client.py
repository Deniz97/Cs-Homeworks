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

def compDestIp(ip):
	retval=ip
	retval=ip[:6]+str(int(ip[6])+3) +ip[7:]
	return retval

# Create new threads
interface_ip_array = findInterfaces()
print interface_ip_array
thread_array = []
que_array = []
i=0
while i<len(interface_ip_array) :
	que_array.append( Queue.Queue(6000/len(interface_ip_array))  )
	my_thread = MainSender("Threadd-"+str(i),interface_ip_array[i] , compDestIp(interface_ip_array[i]),3000+i,que_array[i]  )
	my_thread.start()
	thread_array.append(my_thread)
	i=i+1
j=0
print "ABOUT TO READ THE FILE"
to_push=input_file.read(900)
while  to_push!="" and j<i:
	que_array[j].put(to_push)
	j=(j+1)%i
	to_push=input_file.read(900)
	if( len(to_push)==0  ):
		j=0
		while(j<i):
			que_array[j].put("break")
		break
	

for t in thread_array:
	t.join()