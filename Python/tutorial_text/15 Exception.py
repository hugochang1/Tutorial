# ----------------- try except -----------------
try:
    1+1
except:
    print("not come here")

try:
    1/0
except:
    print("except")
    
try:
    1/0
except ZeroDivisionError:
    print("ZeroDivisionError")
    
try:
    1/0
except Exception:
    print("Exception")

try:
    1/0
except Exception as err:
    print(err)
    # division by zero

try:
    1/0
except (ZeroDivisionError, Exception) as err:
    print(err)
    # division by zero

try:
    1/0
except ZeroDivisionError as err:
    print(1, err)
    # 1 division by zero
except TypeError as err:
    print(2, err)

# ----------------- try except else -----------------
try:
    pass
except Exception:
    print("Exception")
else:
    print("no exception will come here")
    # no exception will come here

# ----------------- try except else finally -----------------
try:
    pass
except Exception as err:
    print(err)
else:
    print("no exception will come here")
    # no exception will come here
finally:
    print("always doing no matter exception happens")
    # always doing no matter exception happens or not

# ----------------- traceback -----------------
import traceback

try:
    1/0
except Exception as err:
    tb = traceback.format_exc()
    print(tb)
"""
Traceback (most recent call last):
  File "C:/Users/Hugo/.spyder-py3/test2.py", line 67, in <module>
    1/0
ZeroDivisionError: division by zero
"""

# ----------------- assert -----------------
# assert is just for debugging purpose, do not use it for official SW release

assert True, "if False, it will raise the AssertionError"

try:
    assert False, "failed"
except Exception as err:
    print(err)
    # failed
