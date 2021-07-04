import socket

bind_ip = "0.0.0.0"
bind_port = 9999
RECV_DATA_SIZE = 1024 * 16

def recv_handler(data):
	if data[0] == "1":
		if len(data) != 1:
			print("[Server] ERR: case 1 fail")
			return False
		print("[Server] PASS: case 1")
		return True
	if data[0] == "2":
		if len(data) != 2:
			print("[Server] ERR: case 2 fail 1")
			return False
		if data[1] != "2":
			print("[Server] ERR: case 2 fail 2")
			return False
		print("[Server] PASS: case 2")
		return True
	if data[0] == "3":
		for i in range(1000):
			if data[i+1] != "a":
				print("[Server] ERR: case 3 fail 1")
				return False
			if data[1001] != "!":
				print("[Server] ERR: case 3 fail 2")
				return False
		return True
	if data[0] == "4":
		for i in range(2000):
			if data[i+1] != "a":
				print("[Server] ERR: case 4 fail 1")
				return False
			if data[2001] != "!":
				print("[Server] ERR: case 4 fail 2")
				return False
		return True
	if data[0] == "5":
		for i in range(16000):
			if data[i+1] != "a":
				print("[Server] ERR: case 5 fail 1")
				return False
			if data[16001] != "!":
				print("[Server] ERR: case 5 fail 2")
				return False
		return True
	print("[Server] ERR: unknown command")
	return False

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
			if recv_handler(data.decode()) == True:
				client.sendall("0".encode()) # pass
			else:
				client.sendall("1".encode()) # fail
	except Exception as err:
		print("[Server] exception: " + str(err))
		client.close()
