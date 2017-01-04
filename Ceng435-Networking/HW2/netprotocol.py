import socket
import fcntl
import struct
import array

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


def makePacket(source_ip,dest_ip,seq_num,data): #ASISTANA SOURCE AND DEST IP GEREKLI MI DIYE SOR
    packet = source_ip+ "/" + dest_ip + "/" + str(seq_num) + "/" + str(data)
    
    #packet str(len(str(seq_num))) +str(seq_num)+ str(len(str(data))) + str(data)

    checksum = makeChecksum(packet)
    return str(checksum)+"/"+source_ip + "/" + dest_ip + "/" + str(seq_num) + "/" + str(data)
    #return str(len(str(checksum))) + str(checksum) + packet

def getSourceIp(packet):
    return packet.split("/")[1]

def getDestinationIp(packet):
    return packet.split("/")[2]

def getSeqNum(packet):
    return int(packet.split("/")[3])

def getData(packet):
    delim_array = [pos for pos, char in enumerate(packet) if char == "/"]
    return packet[delim_array[3]+1:]

def makeChecksum(packet):
    return reduce(lambda x,y:x+y, map(ord, packet)) % 256


def notCorrupt(packet):
    try:
        index = packet.find("/")
        notcorrupt = makeChecksum( packet[index+1:]    ) ^ int(packet[:index]) == 0
    except Exception:
        return false
    return notcorrupt




"""
ifs = all_interfaces()
for i in ifs:
    print "%12s bom   %s" % (i[0], format_ip(i[1]))
"""

"""
import socket
import fcntl
import struct
import array

def all_interfaces():
    max_possible = 128  # arbitrary. raise if needed.
    bytes = max_possible * 32
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    names = array.array('B', '\0' * bytes)
    outbytes = struct.unpack('iL', fcntl.ioctl(
        s.fileno(),
        0x8912,  # SIOCGIFCONF
        struct.pack('iL', bytes, names.buffer_info()[0])
    ))[0]
    namestr = names.tostring()
    return [namestr[i:i+32].split('\0', 1)[0] for i in range(0, outbytes, 32)]
    """
