import time, os, subprocess, threading
import signal
import chardet # pip install chardet

def popen_read_thread(p):
	while True:
		line = p.stdout.readline()
		if len(line) == 0:
			break
		encoding_type = chardet.detect(line)['encoding']
		line = line.strip()
		print(line.decode(encoding_type))

##### demo how to start a ping
p = subprocess.Popen(["ping", "8.8.8.8", "-n", "2"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, stdin=subprocess.PIPE)
t = threading.Thread(target=popen_read_thread, args=[p])
t.start()
# wait until ping finishes
t.join()
p.terminate()
""" output result:
Ping 8.8.8.8 (使用 32 位元組的資料):
回覆自 8.8.8.8: 位元組=32 時間=4ms TTL=116
回覆自 8.8.8.8: 位元組=32 時間=5ms TTL=116

8.8.8.8 的 Ping 統計資料:
封包: 已傳送 = 2，已收到 = 2, 已遺失 = 0 (0% 遺失)，
大約的來回時間 (毫秒):
最小值 = 4ms，最大值 = 5ms，平均 = 4ms
"""

##### demo how to start a ping and finish it with ctrl+c to all this process
p = subprocess.Popen(["ping", "8.8.8.8", "-n", "5"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, stdin=subprocess.PIPE, shell=True)
t = threading.Thread(target=popen_read_thread, args=[p])
t.start()

time.sleep(1.5)
#you can use either os.kill() or p.send_signal() to send ctrl+c, both will got the same results
os.kill(signal.CTRL_C_EVENT, 0)
#p.send_signal(signal.CTRL_C_EVENT)
time.sleep(1) # this is need to print the rest of ping messages
# the rest of part will not be executed
print("no execution here")
""" output result:
Ping 8.8.8.8 (使用 32 位元組的資料):
回覆自 8.8.8.8: 位元組=32 時間=5ms TTL=116
回覆自 8.8.8.8: 位元組=32 時間=6ms TTL=116
Traceback (most recent call last):
  File "Python\subprocess\test.py", line 39, in <module>
8.8.8.8 的 Ping 統計資料:
    time.sleep(1) # this is need to print the rest of messages
封包: 已傳送 = 2，已收到 = 2, 已遺失 = 0 (0% 遺失)，
KeyboardInterrupt
大約的來回時間 (毫秒):
最小值 = 5ms，最大值 = 6ms，平均 = 5ms
Control-C
^C
^C
"""
