# ----------------- log for threads -----------------
from threading import Lock
_log_lock = Lock()
def log(*a, **b):
    with _log_lock:
        print(*a, **b)

log("123")
# 123

import threading, time, sys
# ----------------- thread -----------------

def f1():
    print("f1 start")
    time.sleep(0.5)
    print("f1 end")
    
print("main start")
t = threading.Thread(target=f1)
t.start()
time.sleep(1)
print("main end")
"""
main start
f1 start
<after 0.5 s>
f1 end
<after 0.5 s>
main end
"""

# ----------------- send parameters -----------------
def f1(a, b):
    print("f1 start ", a, b)
    time.sleep(0.5)
    print("f1 end")

print("main start")
t = threading.Thread(target=f1, args=[123, "hello"]) # send parameters
t.start()
time.sleep(1)
print("main end")

# ----------------- thread name -----------------
def f1():
    log(threading.currentThread().getName(), "start") # thread name
    # Thread-20 start
    # Thread-21 start
    # Hugo start
    time.sleep(1)
    log(threading.currentThread().getName(), "end") # thread name
    # Thread-20 end
    # Thread-21 end
    # Hugo end

print(threading.currentThread().getName())
# MainThread
threading.Thread(target=f1).start()
threading.Thread(target=f1).start()
threading.Thread(target=f1, name="Hugo").start() # thread name

# ----------------- join -----------------
def f1():
    time.sleep(1)
    
a = threading.Thread(target=f1)
a.start()
log("join before")
a.join() # join()
log("join after")

# ----------------- join with a timeout -----------------
def f1():
    time.sleep(1)
    
a = threading.Thread(target=f1)
a.start()
log("join before")
a.join(0.5) # join() with a timeout
log("join after")

# ----------------- active_count & threading.enumerate -----------------
def f1():
    time.sleep(1)

threading.Thread(name="A", target=f1).start()
threading.Thread(name="B", target=f1).start()
threading.Thread(name="C", target=f1).start()

log("count=", threading.active_count())
# count= 8

for t in threading.enumerate():
    log(t.name)
"""
MainThread
Thread-4
Thread-5
IPythonHistorySavingThread
Thread-3
A
B
C
"""

# ----------------- thread class -----------------
class MyThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
    def run(self):
        log("stat")
        time.sleep(1)
        log("end")

a = MyThread()
a.start()
b = MyThread()
b.start()

a.join()
b.join()

# ----------------- lock -----------------
lock = threading.Lock()
lock.acquire()
lock.acquire(timeout=0.5)
lock.release()

with lock:
    pass

# recursive lock
lock = threading.RLock()
lock.acquire()
lock.acquire()
lock.release()
lock.release()

# ----------------- queue -----------------

# queue is a thread safe
import queue

q = queue.Queue(3) # queue size is 5
print(q.qsize())
# 0
print(q.full())
# False
print(q.empty())
# True

q.put(1)
q.put(2)
q.put(3)
# if queue is full, calling put() will be blocking
# q.put(4) 
print(q.qsize())
# 3
print(q.full())
# True
print(q.empty())
# False

print(q.get())
# 1
print(q.get())
# 2
print(q.get())
# 3
# if queue is empty, calling get() will be blocking
#print(q.get())
print(q.qsize())
# 0

# ----------------- Barrier -----------------
# if barrier reaches the count, then wait() will be returned
b = threading.Barrier(3)

def f1():
    log("start")
    b.wait()
    log("end")

for i in range(1, 4):
    threading.Thread(target=f1).start()
    time.sleep(0.5)

"""
start
<after 0.5 s>
start
<after 0.5 s>
start
end
end
end
"""

# ----------------- Event -----------------
event = threading.Event()

# if event is not set, wait() will be blocking
# event.wait()

print(event.is_set())
# False
event.set()
print(event.is_set())
# True
event.wait()
event.clear()
print(event.is_set())
# False

# ----------------- subprocess -----------------
import subprocess

# launch calcuator
a = subprocess.Popen("calc")

# launch notepad
b = subprocess.Popen("notepad")

# launch wordpad
c = subprocess.Popen("write")

# launch painter
d = subprocess.Popen("mspaint")
e = subprocess.Popen(["mspaint", "pictures\\i1.png"])

time.sleep(3)

a.terminate()
b.terminate()
c.terminate()
d.terminate()
e.terminate()

# ----------------- run -----------------
# the caller will be blocking until the program exits
a = subprocess.run("calc")