import random
from tkinter import *
import time

WIDTH = 1200
HIGHT = 600

last_time = time.time()
fps_last_time = time.time()
frame_count = 0

press_space = False
action_state = 0 # 0 on ground, 1 up, 2 down

def keyPressEvent(event):
    global press_space
    if event.keysym == "Escape":
        tk.destroy() 
    if event.keysym == "space":
        press_space = True

def keyReleaseEvent(event):
    global press_space
    press_space = False

def mousePressEvent(event):
    global press_space
    press_space = True

def mouseReleaseEvent(event):
    global press_space
    press_space = False

obstacles = []
next_obs_time = 0

def game_loop():
    global last_time, press_space, frame_count, action_state, next_obs_time, obstacles

    frame_count += 1

    now = time.time()
    delta = now - last_time
    last_time = now

    # create a new obstacle if timeout
    next_obs_time -= delta
    if next_obs_time < 0:
        next_obs_time = random.uniform(2, 4)
        obs_w = random.randint(50, 150) # width 寬
        obs_h = random.randint(50, 250) # height 高
        r_id = canvas.create_rectangle(0, 0, 0, 0, fill="lightblue", outline="black", width=2)
        obstacles.append([r_id, WIDTH + 300, obs_w, obs_h])

    movement = delta * 500

    # update obstacles
    remove_num = 0
    for obs in obstacles:
        r_id = obs[0]
        x = obs[1]
        obs_w = obs[2]
        obs_h = obs[3]
        x -= movement / 2
        obs[1] = x # save back
        if (x + obs_w) < 0:
            remove_num += 1
        canvas.coords(r_id, x, HIGHT-50, x-obs_w, HIGHT-50-obs_h)

    obstacles = obstacles[1:] # remove obstacles

    #TODO 判斷 my 跟 obstacles 是否有碰撞

    if press_space:
        if action_state < 2:
            action_state = 1
            canvas.move(my, 0, -movement)
            my_coords = canvas.coords(my)
            if my_coords[1] < 50:
                action_state = 2
        else:
            my_coords = canvas.coords(my)
            if my_coords[3] < 550:
                canvas.move(my, 0, movement)
            else:
                action_state = 0
    else:
        if action_state == 1:
            action_state = 2
        my_coords = canvas.coords(my)
        if my_coords[3] < 550:
            canvas.move(my, 0, movement)
        else:
            action_state = 0

    # 60Hz
    tk.after(15, game_loop)

def update_fps():
    global frame_count, fps_last_time
    
    now = time.time()
    dt = now - fps_last_time

    fps_value = frame_count / dt
    canvas.itemconfig(fps_text, text=f"FPS: {fps_value:.1f}")
    
    # reset counter
    frame_count = 0
    fps_last_time = now
    
    # schedule next FPS update after 1 sec
    tk.after(1000, update_fps)

tk = Tk()
# -------------------------------------
canvas = Canvas(tk, width=WIDTH, height=HIGHT, bg="#00ff00")
canvas.pack()

my = canvas.create_oval(50, 500, 100, 550,
                outline="blue", width=3, fill="lightblue")

fps_text = canvas.create_text(10, 10, anchor="nw", text="FPS: 0", fill="black", font=("Arial", 12))
ground = canvas.create_line(0, HIGHT - 50, WIDTH, HIGHT - 50, fill="black", width=5)
ground = canvas.create_line(0, 50, WIDTH, 50, fill="black", width=5)

# -------------------------------------
tk.bind("<KeyPress>", keyPressEvent)
tk.bind("<KeyRelease>", keyReleaseEvent)
tk.bind_all("<Button>", mousePressEvent)
tk.bind_all("<ButtonRelease>", mouseReleaseEvent)

tk.title("this is my game")
tk.lift()
tk.geometry(str(WIDTH) + "x" + str(HIGHT) + "+0+0")
tk.focus_force()
#tk.after(20000, tk.destroy)
game_loop()
update_fps()

tk.mainloop()
