import threading
import time
import chardet
import subprocess
import os

# ------------- os.system() -------------
# this is blocking API
# the result will show to console directly
# the return value indicate the result of exection of the program
ret = os.system("cls")
print(ret)  # 0

os.system("dir")

# ------------- os.popen() -------------
# this is blocking API
# the result will NOT show to console
# the return value are the console message
ret = os.popen("ping 127.0.0.1 -n 1")
print(ret.read().strip())
"""
Ping 127.0.0.1 (使用 32 位元組的資料):
回覆自 127.0.0.1: 位元組=32 時間<1ms TTL=128

127.0.0.1 的 Ping 統計資料:
    封包: 已傳送 = 1，已收到 = 1, 已遺失 = 0 (0% 遺失)，  
大約的來回時間 (毫秒):
    最小值 = 0ms，最大值 = 0ms，平均 = 0ms
"""

ret = os.popen("gggg")
print(ret.read().strip())
# 'gggg' 不是內部或外部命令、可執行的程式或批次檔。

# ------------- subprocess -------------
cmd = "ping 127.0.0.1 -n 2"
sp = subprocess.Popen(
    cmd.split(" "), stdout=subprocess.PIPE, stdin=subprocess.PIPE)

while True:
    line = sp.stdout.readline()
    if len(line) == 0:
        break
    encoding = chardet.detect(line)['encoding']
    line = line.decode(encoding)
    line = line.strip()
    print(line)

sp.terminate()
"""
Ping 127.0.0.1 (使用 32 位元組的資料):
回覆自 127.0.0.1: 位元組=32 時間<1ms TTL=128
回覆自 127.0.0.1: 位元組=32 時間<1ms TTL=128

127.0.0.1 的 Ping 統計資料:
封包: 已傳送 = 2，已收到 = 2, 已遺失 = 0 (0% 遺失)，      
大約的來回時間 (毫秒):
最小值 = 0ms，最大值 = 0ms，平均 = 0ms
"""

# ------------- subprocess with thread -------------


def sp_routine(sp):
    while True:
        line = sp.stdout.readline()
        if len(line) == 0:
            break
        encoding = chardet.detect(line)['encoding']
        line = line.decode(encoding)
        line = line.strip()
        print(line)


cmd = "ping 127.0.0.1 -n 2"
sp = subprocess.Popen(
    cmd.split(" "), stdout=subprocess.PIPE, stdin=subprocess.PIPE)

t1 = threading.Thread(target=sp_routine, args=[sp])
t1.start()
time.sleep(1)
sp.terminate()
t1.join()
"""
Ping 127.0.0.1 (使用 32 位元組的資料):
回覆自 127.0.0.1: 位元組=32 時間<1ms TTL=128
"""
