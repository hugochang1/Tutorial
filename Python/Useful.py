# --------------- log ---------------

import datetime
from threading import Lock

module_version = "[1.00]"
log_file_path = "./log.txt"
_log_lock = Lock()

def LOGD(*args, **args2):
    with _log_lock:
        prefix = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S.%f') + " " + module_version + '[D]'
        print(prefix, *args, **args2)
        with open(log_file_path, "a") as f:
            print(prefix, *args, **args2, file=f)

def LOGW(*args, **args2):
    with _log_lock:
        prefix = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S.%f') + " " + module_version + '[W]'
        print(prefix, *args, **args2)
        with open(log_file_path, "a") as f:
            print(prefix, *args, **args2, file=f)

def LOGE(*args, **args2):
    with _log_lock:
        prefix = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S.%f') + " " + module_version + '[E]'
        print(prefix, *args, **args2)
        with open(log_file_path, "a") as f:
            print(prefix, *args, **args2, file=f)
        
LOGD("LOGD") # 2020/05/17 09:01:47.947437 [1.00][D] LOGD
LOGW("LOGW") # 2020/05/17 09:01:47.949437 [1.00][W] LOGW
LOGE("LOGE") # 2020/05/17 09:01:47.950437 [1.00][E] LOGE

# --------------- config file ---------------
import json

config_file_path = "config_file.txt"

try:
	with open(config_file_path, "r") as f:
		config = json.load(f)
		LOGD(config)
		LOGD(config['key1'])
		LOGD(config['key2'])
		LOGD(config['key3'])
		LOGD(config['key4'])
except Exception as err:
	LOGE(err)

# --------------- sleep ---------------
import time

LOGD("sleep before")
time.sleep(0.3)
LOGD("sleep after")

# --------------- random ---------------
import random

for i in range(10):
	LOGD(random.randint(0, 3)); # 0~3


# --------------- traceback ---------------
import traceback
try:
	assert False, "my error message!!!"
except Exception as err:
	LOGD(err) # my error message!!!
	LOGD(traceback.format_exc())
"""
raceback (most recent call last):
  File "<ipython-input-24-a705662e5f11>", line 3, in <module>
    assert False, "my error message!!!"
AssertionError: my error message!!!
"""

# --------------- assertEqual ---------------
def assertEqual(a, b):
	if a != b:
		assert False, "a=[%s] is not equals to b=[%s]" % (a, b)

try:
	assertEqual(1, 2)
except Exception as err:
	LOGD(err) # a=[1] is not equals to b=[2]

