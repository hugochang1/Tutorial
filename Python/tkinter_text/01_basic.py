from tkinter import *
from tkinter.scrolledtext import ScrolledText

FONT_TITLE = ("", 24)
FONT_CTX = ("", 16)
tk = Tk()
# ---------------- events ---------------------


def keyEvent(event):
    if event.keysym == "Escape":
        tk.destroy()


def btnClick():
    print("buttonClick")


def periodEvt():
    print("periodEvt")
    text_1["state"] = "normal"
    text_1.insert(END, "Hello World\n")
    text_1["state"] = "disabled"
    tk.after(1000, periodEvt)


def evt1(*args):
    print("evt1", args)


def evt2(**args):
    print("evt2", args)


# -----------------layout --------------------
btn_1 = Button(tk, text="1 start", width=None, height=None,
               font=FONT_TITLE, command=btnClick)
btn_1.grid(row=0, column=0)

btn_2 = Button(tk, text="2 stop", width=None,
               height=None, font=FONT_TITLE, command=None)
btn_2.grid(row=0, column=1)

Label(tk, text="Label 1", width=None, font=FONT_TITLE).grid(row=1, column=0)

entry_1 = Entry(tk, font=FONT_TITLE)
entry_1.grid(row=1, column=1)
entry_1.focus_force()

text_1 = ScrolledText(tk, width=60, height=5,
                      font=FONT_CTX, wrap="none", undo=True)
text_1.insert(END, "Hello World\n")
text_1["state"] = "disabled"
text_1.grid(row=2, column=0, columnspan=2)


# ------------------ tk -------------------
tk.bind_all("<KeyPress>", keyEvent)
tk.lift()
tk.focus_force()
tk.after(1000, periodEvt)
tk.after(0, evt1)
tk.after(0, lambda: evt1())
tk.after(0, lambda: evt1(1))
tk.after(0, lambda: evt1(1, 2))
tk.after(0, evt2)
tk.after(0, lambda: evt2(a=1, b=2))
tk.mainloop()  # blocking here until tk.destroy()
