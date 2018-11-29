
def makePacket(source_ip,dest_ip,data,time_stamp=0):
    return source_ip + "/" + dest_ip + "/" + str(time_stamp) + "/" + str(data)

def getSourceIp(packet):
    return packet.split("/")[0]

def getDestinationIp(packet):
    return packet.split("/")[1]

def getTimeStamp(packet):
    return float(packet.split("/")[2])

def getData(packet):
    return packet.split("/")[3]

def getTable(source_ip):
    if(source_ip=="10.10.1.1" or source_ip=="10.10.2.2"):
        return {"10.10.1.1":"10.10.1.1","10.10.2.1":"","10.10.2.2":"10.10.2.2","10.10.3.2":"10.10.2.2","10.10.4.2":"10.10.2.2"}
    elif(source_ip=="10.10.2.1" or source_ip=="10.10.3.2"):
        return {"10.10.1.1":"10.10.2.1","10.10.2.1":"10.10.2.1","10.10.3.1":"","10.10.3.2":"10.10.3.2","10.10.4.2":"10.10.3.2"}
    elif(source_ip=="10.10.3.1" or source_ip=="10.10.4.2"):
        return {"10.10.1.1":"10.10.3.1","10.10.2.1":"10.10.3.1","10.10.3.1":"10.10.3.1","10.10.4.1":"","10.10.4.2":"10.10.4.2"}


def getTargetIp(packet,address):
    table = getTable(address[0])
    return table[getDestinationIp(packet)]

