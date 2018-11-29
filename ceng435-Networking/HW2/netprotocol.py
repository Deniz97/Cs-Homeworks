import socket
import fcntl
import struct
import array
import hashlib

#returns the available interface ip address in an array
def findInterfaces():
    def formatIp(addr):
        return str(ord(addr[0])) + '.' + \
               str(ord(addr[1])) + '.' + \
               str(ord(addr[2])) + '.' + \
               str(ord(addr[3]))

    max_possible = 1280  # arbitrary. raise if needed.
    bytes = max_possible * 32
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    names = array.array('B', '\0' * bytes)
    outbytes = struct.unpack('iL', fcntl.ioctl(
        s.fileno(),
        0x8912,  # SIOCGIFCONF
        struct.pack('iL', bytes, names.buffer_info()[0])
    ))[0]
    namestr = names.tostring()
    lst = []
    for i in range(0, outbytes, 40):
        name = namestr[i:i+16].split('\0', 1)[0]
        ip   = namestr[i+20:i+24]

        if(formatIp(ip)[:2]=="10"):
            lst.append( formatIp(ip) )
    return lst


def makePacket(seq_num,data): 
    packet = str(seq_num) + "/" + str(data)
    checksum = makeChecksum(packet)
    return checksum+"/"+ str(seq_num) + "/" + str(data)


def getSeqNum(packet):
    return int(packet.split("/")[1])

def getData(packet):
    delim_array = [pos for pos, char in enumerate(packet) if char == "/"]
    return packet[delim_array[1]+1:]


def makeChecksum(packet):
    return hashlib.md5(packet).hexdigest()


def notCorrupt(packet):

    index = packet.find("/")
    notcorrupt = makeChecksum( packet[index+1:]    ) == packet[:index] 

    return notcorrupt