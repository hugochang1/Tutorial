import datetime


def __log(tag, *args):
    prefix = datetime.datetime.now().strftime("%Y%m%d_%H%M%S.%f") + \
        " [1.00]" + tag
    print(prefix, *args)
    try:
        with open("log.txt", "a") as f:
            print(prefix, *args, file=f)
    except Exception as err:
        pass


def LOGD(*args):
    __log("[D]", *args)


def LOGW(*args):
    __log("[W]", *args)


def LOGE(*args):
    __log("[E]", *args)


LOGD("LOGD")  # 20211231_222344.503551 [1.00][D] LOGD
LOGW("LOGW")  # 20211231_222344.505592 [1.00][W] LOGW
LOGE("LOGE")  # 20211231_222344.507825 [1.00][E] LOGE
