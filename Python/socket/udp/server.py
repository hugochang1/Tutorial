import socket

addr=("127.0.0.1", 10000)
s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(addr)
while 1:
	data,addr=s.recvfrom(2048)
	data = data.decode()
	print(data)
	if data == "exit":
		print("shutdown server")
		break
	# TODO your handling command
	

s.close()
