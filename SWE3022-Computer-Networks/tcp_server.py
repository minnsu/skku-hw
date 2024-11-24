import socket
import sys

def tcp_server(ip, port):
    Soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    Soc.bind((ip, port))

    Soc.listen(1)
    conSoc, cli_addr = Soc.accept()

    while True:
        data = conSoc.recv(4096)
        conSoc.send(data.decode().encode())
        
        if data.decode() == 'close':
            conSoc.close()
            break

port = 12345
tcp_server(sys.argv[1], port)