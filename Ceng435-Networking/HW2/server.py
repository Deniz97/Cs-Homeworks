from netprotocol import *
import socket
import os

#Required variables
UDP_IP="10.10.4.1"
UDP_PORT = 5005

#Open a file to write delay values in to
if not os.path.isfile("./output.txt"):
    os.system("touch output.txt")
try :
    output_file = open("output.txt","r")
except Exception:
    print "Could not open file output.txt"

   while True:
   	
