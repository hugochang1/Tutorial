# --------------- log ---------------
import datetime

module_version = "[1.00]"
log_file_path = "./log.txt"

def LOGD(*args):
	prefix = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S.%f') + " " + module_version + '[D]'
	print(prefix, *args)
	with open(log_file_path, "a") as f:
		print(prefix, *args, file=f)

def LOGW(*args):
	prefix = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S.%f') + " " + module_version + '[W]'
	print(prefix, *args)
	with open(log_file_path, "a") as f:
		print(prefix, *args, file=f)

def LOGE(*args):
	prefix = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S.%f') + " " + module_version + '[E]'
	print(prefix, *args)
	with open(log_file_path, "a") as f:
		print(prefix, *args, file=f)

LOGD("aaa", 123, 11.22, "hello world")
LOGW("aaa", 123, 11.22, "hello world")
LOGE("aaa", 123, 11.22, "hello world")

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
	LOGD(err)
	LOGD(traceback.format_exc())

# --------------- assertEqual ---------------
def assertEqual(a, b):
	if a != b:
		assert False, "a=[%s] is not equals to b=[%s]" % (a, b)

try:
	assertEqual(1, 2)
except Exception as err:
	LOGD(err)

