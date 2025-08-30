from tkinter import *

# who_play means 1 = player1, 2 = player2
who_play = 1
game_over = False
matrix = [
    [0, 0, 0],
    [0, 0, 0],
    [0, 0, 0]
]
oids = []

def keyEvent(event):
    if event.keysym == "Escape":
        tk.destroy()

def mouse_motion(event):
    #canvas.itemconfig(text_id_1, text="x=" + str(event.x) + " y=" + str(event.y))
    pass

def check_win():
    global game_over
    for p in range(1,3):
        for i in range(3):
            if matrix[i][0] == p and matrix[i][1] == p and matrix[i][2] == p:
                game_over = True
                oid = canvas.create_text(300, 300, text="player " + str(p) + " win!!!", fill="red",
                                font=("Arial", 20), tags="toast")
                oids.append(oid)
                break
            
            if matrix[0][i] == p and matrix[1][i] == p and matrix[2][i] == p:
                game_over = True
                oid = canvas.create_text(300, 300, text="player " + str(p) + " win!!!", fill="red",
                                font=("Arial", 20), tags="toast")
                oids.append(oid)
                break
            
            if matrix[0][0] == p and matrix[1][1] == p and matrix[2][2] == p:
                game_over = True
                oid = canvas.create_text(300, 300, text="player " + str(p) + " win!!!", fill="red",
                                font=("Arial", 20), tags="toast")
                oids.append(oid)
                break

            if matrix[2][0] == p and matrix[1][1] == p and matrix[0][2] == p:
                game_over = True
                oid = canvas.create_text(300, 300, text="player " + str(p) + " win!!!", fill="red",
                                font=("Arial", 20), tags="toast")
                oids.append(oid)
                break
        if game_over:
            break


def mouse_button(event):
    global who_play
    print("mouse_button x=" + str(event.x) + " y=" + str(event.y))
    if game_over:
        return
    selected_x = int(event.x / 200)
    selected_y = int(event.y / 200)
    circle_x = selected_x * 200 + 100
    circle_y = selected_y * 200 + 100
    canvas.itemconfig(text_id_2, text="x=" + str(selected_x) + " y=" + str(selected_y))
    if matrix[selected_x][selected_y] == 0:
        matrix[selected_x][selected_y] = who_play
        oid = -1
        if who_play == 1:
            oid = canvas.create_oval(circle_x-30 , circle_y-30, circle_x+30, circle_y+30,
                          outline="blue", width=3, fill="lightblue")
            who_play = 2
        else:
            oid = canvas.create_oval(circle_x-30 , circle_y-30, circle_x+30, circle_y+30,
                          outline="red", width=3, fill="lightblue")
            who_play = 1
        oids.append(oid)
        check_win()
    else:
        text = canvas.create_text(300, 500, text="這格已經被使用, 請點選別格", fill="red",
                              font=("Arial", 20), tags="toast")
        # Remove after duration (ms)
        tk.after(1500, lambda: canvas.delete("toast"))

def click_reset_btn():
    print("click_reset_btn")
    global who_play, matrix, oids, game_over
    who_play = 1
    game_over = False
    matrix = [
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0]
    ]
    for oid in oids:
        canvas.delete(oid)
    oids = []

tk = Tk()
# -------------------------------------
canvas = Canvas(tk, width=600, height=600, bg="#00ff00")
canvas.pack()
button = Button(tk, text="reset", command=click_reset_btn)
button.pack(pady=0)

# x
canvas.create_line(0, 200, 600, 200, fill="blue", width=3)
canvas.create_line(0, 400, 600, 400, fill="blue", width=3)

# y
canvas.create_line(200, 0, 200, 600, fill="blue", width=3)
canvas.create_line(400, 0, 400, 600, fill="blue", width=3)

text_id_1 = canvas.create_text(300, 20, text="Mouse motion", fill="blue", font=("Arial", 20, "bold"))
text_id_2 = canvas.create_text(300, 40, text="Mouse click", fill="blue", font=("Arial", 20, "bold"))


#canvas.bind_all("<Motion>", mouse_motion)
#canvas.bind_all("<Button>", mouse_button)

# -------------------------------------
tk.bind_all("<KeyPress>", keyEvent)
tk.bind_all("<Motion>", mouse_motion)
tk.bind_all("<Button>", mouse_button)

tk.title("this is my game")
tk.lift()


tk.focus_force()
#tk.after(20000, tk.destroy)
tk.mainloop()
