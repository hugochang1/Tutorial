import socket
import time
import traceback

HOST = '127.0.0.1'
PORT = 9999
RECV_DATA_SIZE = 1024 * 16

def show_traceback():
    for line in traceback.format_stack():
        print(line.strip())

def read_and_expect_value(s, expect_value):
	data = s.recv(RECV_DATA_SIZE).decode()
	if len(data) == 0:
		print("[Client] ERR: server close the connection")
		exit(1)
	if data[0] != expect_value:
		print("[Client] ERR: test failed")
		show_traceback()
		exit(1)


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

# ------------ test 1 ------------
cmd = "1"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

cmd = "11"
s.sendall(cmd.encode())
read_and_expect_value(s, "1")

# ------------ test 2 ------------
cmd = "22"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

cmd = "2"
s.sendall(cmd.encode())
read_and_expect_value(s, "1")

cmd = "20"
s.sendall(cmd.encode())
read_and_expect_value(s, "1")

cmd = "222"
s.sendall(cmd.encode())
read_and_expect_value(s, "1")

# ------------ test 3 ------------
cmd = "3"
for i in range(1000):
	cmd += "a"
cmd += "!"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

# ------------ test 4 ------------
cmd = "4"
for i in range(2000):
	cmd += "a"
cmd += "!"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

# ------------ test 5 ------------
cmd = "5"
for i in range(16000):
	cmd += "a"
cmd += "!"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

s.close()
