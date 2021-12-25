import select
import socket
import threading
import traceback

# ------------------ util functions -------------------


def socket_server_create(host, port):
    server = socket.socket()
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.setblocking(0)
    server.listen(5)
    return server


def socket_client_connect(host, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))
    return client


# ------------------ parameters -------------------
HOST = '0.0.0.0'
PORT = 1234

# ------------------ server -------------------
server = socket_server_create("0.0.0.0", PORT)
inputs = [server]

# ------------------ client -------------------


def client_thread():
    client = socket_client_connect("127.0.0.1", PORT)
    client.send(b"client data")
    data = client.recv(1024)
    print("client recv", data)
    client.close()


threading.Thread(target=client_thread).start()
# ------------------ select -------------------

while True:
    readable, _, _ = select.select(inputs, [], [], 10)
    for sck in readable:
        if sck is server:
            try:
                client, addr = sck.accept()
                print("server, new client connected", addr)
                client.setblocking(0)
                inputs.append(client)
            except Exception as err:
                print(traceback.format_exc())
        else:
            try:
                data = sck.recv(1024)
                print("server recv", data)
                sck.send(b"server ack")
                sck.close()
            except Exception as err:
                print(traceback.format_exc())
            finally:
                inputs.remove(sck)


server.close()
