import socket
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
cmd = "3" + "a" * 1000 + "!"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

# ------------ test 4 ------------
cmd = "4" + "a" * 2000 + "!"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

# ------------ test 5 ------------
cmd = "5" + "a" * 16000 + "!"
s.sendall(cmd.encode())
read_and_expect_value(s, "0")

# ------------ test 6 ------------
cmd = "6"
s.sendall(cmd.encode())
ret = s.recv(RECV_DATA_SIZE).decode()
if ret != "6" + "b"*100 + "!":
	print("[Client] case 6 fail, data=", ret)

# ------------ test 7 ------------
cmd = "7"
s.sendall(cmd.encode())
ret = s.recv(RECV_DATA_SIZE).decode()
if ret != "7" + "b"*1000 + "!":
	print("[Client] case 7 fail, data=", ret)

# ------------ test 8 ------------
cmd = "8"
s.sendall(cmd.encode())
ret = s.recv(RECV_DATA_SIZE).decode()
if ret != "8" + "b"*2000 + "!":
	print("[Client] case 8 fail, data=", ret)
	
# ------------ test 9 ------------
cmd = "9"
s.sendall(cmd.encode())
ret = s.recv(RECV_DATA_SIZE).decode()
if ret != "9" + "b"*16000 + "!":
	print("[Client] case 9 fail, data=", ret)

s.close()
