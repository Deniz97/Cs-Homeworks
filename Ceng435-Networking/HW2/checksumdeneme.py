def makeChecksum(packet):
    return reduce(lambda x,y:x+y, map(ord, packet)) % 256
def notCorrupt(packet):
    index = packet.find("/")
    return makeChecksum( packet[index+1:]    ) ^ int(packet[:index]) == 0
def makePacket(source_ip,dest_ip,seq_num,data,): #ASISTANA SOURCE AND DEST IP GEREKLI MI DIYE SOR
    packet = source_ip+ "/" + dest_ip + "/" + str(seq_num) + "/" + str(data)
    checksum = makeChecksum(packet)
    return str(checksum)+"/"+source_ip + "/" + dest_ip + "/" + str(seq_num) + "/" + str(data)

s=makePacket("10.01.1.1","10.10.4.1",1,"fasfarwqerwtqwrrwerqwerwqerqwetrewtqwerwqe")
print s
index = s.find("/")
print index
print s[index+1:]
print s[:index] 
print "******"
print str( makeChecksum( s[index+1:] )   )
print str(  int(s[:index])  )

print str(notCorrupt(s))
"""
s= "10.10.1.1/10.10.4.1/1/fsdafasdfgasfdgdsfgsa"
c = makeChecksum(s)
print s
print c
c=str(c)
c=int(c)
print c
print makeChecksum(s) ^ c == 0
s = "bla bla bla bla bom bom bla"
print makeChecksum(s)
print makeChecksum(s) ^ c == 0
print type(c) 
print type(s) 
"""