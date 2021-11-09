import socket
import time

def udp_send(str_data, addr):
	s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.sendto(str_data.encode(), addr)
	s.close()


addr=("127.0.0.1", 10000)
for i in range(1, 21):
	print("i=", i)
	udp_send("hello" + str(i), addr)

udp_send("exit", addr)
