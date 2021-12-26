from tkinter import *
from tkinter.scrolledtext import ScrolledText
from socket_part import *
import select
import threading
import traceback

PORT = 12345
FONT_TITLE = ("", 24)
FONT_CTX = ("", 12)
tk = Tk()

# ---------------- variables ---------------------
server = None
client = None
inputs = []  # for select
ui_exit = False


# ---------------- UI utils (can be called from outside of UI) ---------------------


def addMsg2ServerText(str):
    tk.after(0, lambda: evtAddMsg2ServerText(str))


def addMsg2ClientText(str):
    tk.after(0, lambda: evtAddMsg2ClientText(str))


# ---------------- UI events (in TK thread) ---------------------


def keyEvent(event):
    if event.keysym == "Escape":
        tk.destroy()
        global ui_exit
        ui_exit = True


def evtAddMsg2ServerText(str):
    text_server["state"] = "normal"
    text_server.insert(END, str + "\n")
    text_server["state"] = "disabled"
    text_server.yview_moveto(1)


def evtAddMsg2ClientText(str):
    text_client["state"] = "normal"
    text_client.insert(END, str + "\n")
    text_client["state"] = "disabled"
    text_client.yview_moveto(1)


def btnClientConnectClick():
    threading.Thread(target=client_connect_thread).start()


def btnClientDisconnectClick():
    threading.Thread(target=client_disconnect_thread).start()


def btnClientSendClick():
    threading.Thread(target=client_send_thread).start()

# ----------------- socket thread --------------------


def client_connect_thread():
    global client
    addMsg2ClientText("connecting...")
    try:
        client = socket_client_connect("127.0.0.1", PORT)
        addMsg2ClientText("connected")
    except Exception as err:
        addMsg2ClientText("connection failure due to " + str(err))


def client_disconnect_thread():
    global client
    try:
        client.close()
        addMsg2ClientText("disconnected")
    except Exception as err:
        addMsg2ClientText("disconnected failed, " + str(err))


def client_send_thread():
    global client
    try:
        client.send(entryClient.get().encode())
        data = client.recv(1024)
        addMsg2ClientText("recv, " + str(data))
    except Exception as err:
        addMsg2ClientText("send failed, " + str(err))


def socket_thread():
    while True:
        readable, _, _ = select.select(inputs, [], [], 1)
        if ui_exit:
            break
        for sck in readable:
            if sck is server:
                try:
                    client, addr = sck.accept()
                    addMsg2ServerText("new client connected, " + str(addr))
                    client.setblocking(0)
                    inputs.append(client)
                except Exception as err:
                    addMsg2ServerText(
                        "new client connection failure, " + str(err))
                    print(traceback.format_exc())
            else:
                try:
                    data = sck.recv(1024)
                    if len(data) == 0:
                        addMsg2ServerText("client disconnected")
                        inputs.remove(sck)
                        sck.close()
                    else:
                        addMsg2ServerText("recv " + str(data))
                        sck.send(entryServer.get().encode())
                except Exception as err:
                    addMsg2ServerText(
                        "client disconnected abnormally, " + str(err))
                    print(traceback.format_exc())
                    inputs.remove(sck)
                    sck.close()
    print("exit socket_thread()")
    server.close()


if __name__ == '__main__':
    # ----------------- UI layout --------------------
    btnClientConnectClick = Button(tk, text="client connect", width=None, height=None,
                                   font=FONT_TITLE, command=btnClientConnectClick)
    btnClientConnectClick.grid(row=0, column=0)

    btnClientDisconnectClick = Button(tk, text="client disconnect", width=None,
                                      height=None, font=FONT_TITLE, command=btnClientDisconnectClick)
    btnClientDisconnectClick.grid(row=0, column=1)

    btnClientSendClick = Button(tk, text="client send", width=None, height=None,
                                font=FONT_TITLE, command=btnClientSendClick)
    btnClientSendClick.grid(row=0, column=2)

    Label(tk, text="Client Send Data", width=None,
          font=FONT_TITLE).grid(row=1, column=0)

    entryClient = Entry(tk, font=FONT_TITLE)
    entryClient.grid(row=1, column=1)
    entryClient.focus_force()
    entryClient.insert(0, "client DATA")

    Label(tk, text="Server ACK Data", width=None,
          font=FONT_TITLE).grid(row=2, column=0)

    entryServer = Entry(tk, font=FONT_TITLE)
    entryServer.grid(row=2, column=1)
    entryServer.focus_force()
    entryServer.insert(0, "server ACK")

    text_server = ScrolledText(tk, width=60, height=30,
                               font=FONT_CTX, wrap="none", undo=True)
    text_server.insert(END, "Server Info\n")
    text_server["state"] = "disabled"
    text_server.grid(row=10, column=0, columnspan=2)

    text_client = ScrolledText(tk, width=60, height=30,
                               font=FONT_CTX, wrap="none", undo=True)
    text_client.insert(END, "Client Info\n")
    text_client["state"] = "disabled"
    text_client.grid(row=10, column=2, columnspan=2)

    # ------------------ UI  tk -------------------
    tk.bind_all("<KeyPress>", keyEvent)
    tk.lift()
    tk.focus_force()

    # ----------------- create socket thread --------------------
    server = socket_server_create("0.0.0.0", PORT)
    inputs.append(server)
    threading.Thread(target=socket_thread).start()

    tk.mainloop()  # blocking here until tk.destroy()
