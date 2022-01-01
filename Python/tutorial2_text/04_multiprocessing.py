import time
import os
import multiprocessing

# multiprocessing.Process just likes fork in C, different process communication must through IPC instead variable
a = 0
print("enter the program!!!")


def my_process():
    print("my_process pid=", os.getpid())
    global a
    a = 1  # it will not impact to main thread


if __name__ == "__main__":
    print("main pid=", os.getpid())
    print("before a=", a)  # 0
    p = multiprocessing.Process(target=my_process)
    p.start()
    time.sleep(1)
    p.terminate()
    print("after a=", a)  # 0
