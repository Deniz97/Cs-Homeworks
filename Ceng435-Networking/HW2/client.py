from netprotocol import *
from client_thread import *
import socket
import os
import threading
import Queue
import time

time_stamp = time.time()

if not os.path.isfile("./input.txt"):
	print "Could not locate the file, exiting."
	exit()
try :
	input_file = open("input.txt","r")
except Exception:
	print "Could not open file input.txt"

def compDestIp(ip,numberOfInterfaces):
	retval=ip
	retval=ip[:6]+str(int(ip[6])+numberOfInterfaces) +ip[7:]
	return retval

# Create new threads
interface_ip_array = findInterfaces()
interface_ip_array.sort()
numberOfInterfaces = len(interface_ip_array)
print interface_ip_array
thread_array = []
que_array = []
i=0
while i<numberOfInterfaces :
	que_array.append( Queue.Queue(6000/numberOfInterfaces)  )
	my_thread = MainSender("Threadd-"+str(i),interface_ip_array[i] , compDestIp(interface_ip_array[i],numberOfInterfaces),3000+i,que_array[i]  )
	my_thread.start()
	thread_array.append(my_thread)
	i=i+1
j=0

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
	

for t in thread_array:
	t.join()
	print t.thread_name+" JOINED"
input_file.close()

print time_stamp
