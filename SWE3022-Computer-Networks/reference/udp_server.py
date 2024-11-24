import socket

def udp_server():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(('10.0.0.2', 12345))
    data, addr = s.recvfrom(1024)
    s.sendto("Hi I'm server!".encode('utf-8'), addr)
    s.close()


udp_server()
