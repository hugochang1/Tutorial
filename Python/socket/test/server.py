import socket

def recv_handler(data):
	if data[0] == "1":
		if len(data) != 1:
			print("[Server] ERR: case 0 fail")
			return False
		else:
			print("[Server] PASS: case 1")
	if data[0] == "2":
		if len(data) != 2:
			print("[Server] ERR: case 1 fail 1")
			return False
		elif data[1] != "2":
			print("[Server] ERR: case 1 fail 2")
			return False
		else:
			print("[Server] PASS: case 2")
	return True

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
				client.close()
				break;
			print("[Server] recv data=%s" % data)
			recv_handler(data.decode())
			client.sendall("1".encode())
	except Exception as err:
		print("[Server] exception: " + str(err))
		client.close()
