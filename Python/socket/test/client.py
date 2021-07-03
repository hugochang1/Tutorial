import socket
import time

HOST = '127.0.0.1'
PORT = 9999
RECV_DATA_SIZE = 1024 * 16

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

cmd = "1"
s.sendall(cmd.encode())
s.recv(RECV_DATA_SIZE)

cmd = "1"
s.sendall(cmd.encode())
s.recv(RECV_DATA_SIZE)

cmd = "2"
s.sendall(cmd.encode())
s.recv(RECV_DATA_SIZE)

cmd = "22"
s.sendall(cmd.encode())
s.recv(RECV_DATA_SIZE)

cmd = "20"
s.sendall(cmd.encode())
s.recv(RECV_DATA_SIZE)

cmd = "222"
s.sendall(cmd.encode())
s.recv(RECV_DATA_SIZE)

s.close()
