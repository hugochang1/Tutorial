import socket
import traceback

bind_ip = "0.0.0.0"
bind_port = 9999
RECV_DATA_SIZE = 1024 * 16

def show_traceback():
    for line in traceback.format_stack():
        print(line.strip())

def recv_handler(data, client):
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
		if data != "3" + "a"*1000 + "!":
				print("[Server] ERR: case 3, data=", data)
		return True
	if data[0] == "4":
		if data != "4" + "a"*2000 + "!":
				print("[Server] ERR: case 4, data=", data)
		return True
	if data[0] == "5":
		if data != "5" + "a"*16000 + "!":
				print("[Server] ERR: case 5, data=", data)
		return True
	if data[0] == "6":
		send_data = "6" + "b" * 100 + "!"
		client.sendall(send_data.encode())
		return None
	if data[0] == "7":
		send_data = "7" + "b" * 1000 + "!"
		client.sendall(send_data.encode())
		return None
	if data[0] == "8":
		send_data = "8" + "b" * 2000 + "!"
		client.sendall(send_data.encode())
		return None
	if data[0] == "9":
		send_data = "9" + "b" * 16000 + "!"
		client.sendall(send_data.encode())
		return None
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
			ret = recv_handler(data.decode(), client)
			if ret == True:
				client.sendall("0".encode()) # pass
			elif ret == False:
				client.sendall("1".encode()) # fail
			else:
				pass
	except Exception as err:
		print("[Server] exception: " + str(err))
		print(traceback.format_exc())
		client.close()
