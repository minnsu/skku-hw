import socket
import sys

def udp_client(server_ip):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto('Hello i am client'.encode('utf-8'), (server_ip, 12345))
    data, addr = s.recvfrom(1024)
    print("The message from server:", data.decode('utf-8'))
    s.close()

udp_client(sys.argv[1])
