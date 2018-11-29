import sys
import client
import time

args = sys.argv
args=args[1:]

#first argument is run count
counter=1
if(len(args)>0):
	if(len(args[0])<8 ):
		counter = int(args[0])
		args=args[1:]

#the rests are dest_ip array.
given_ips=[]
if(len(args)>0):
	given_ips=args[:]

while(counter>0):
	try:
		client.client(given_ips)
	except Exception as e:
		print str(e)
		
	if(counter!=1):
		time.sleep(1)
	counter -= 1