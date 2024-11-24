import socket
import sys
import time

delay = 0.001
def tcp_client(s_ip, s_port):
    Soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    Soc.connect((s_ip, s_port))

    while True:
        Soc.send(bytes(4096))

        receive = Soc.recv(4096)
        time.sleep(delay)
    
    Soc.send('close'.encode())
    Soc.close()

port = 12345
tcp_client(sys.argv[1], port)