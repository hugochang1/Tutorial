import socket

bind_ip = "0.0.0.0"
bind_port = 9999
RECV_DATA_SIZE = 1024 * 16

server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind((bind_ip,bind_port))
server.listen(5)

while True:
	client,addr = server.accept()
	print('[Server] Connected by ', addr)
	
	try:
		while True:
			data = client.recv(RECV_DATA_SIZE)
			if len(data) == 0:
				print("[Server] client is disconnected")
				break;
			print("[Server] recv data=%s" % data)
			client.send((data.decode() + " ACK!").encode())
	except Exception as err:
		print("[Server] client is disconnected abnormal: " + str(err))
