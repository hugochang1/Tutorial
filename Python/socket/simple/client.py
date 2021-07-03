import socket
import time

HOST = '127.0.0.1'
PORT = 9999
RECV_DATA_SIZE = 1024 * 16

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

cmd = "client hello"
s.send(cmd.encode())
data = s.recv(RECV_DATA_SIZE)
print("[Client] recv=%s" % data)

s.close()
