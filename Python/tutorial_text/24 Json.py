# ----------------- create the test folder -----------------
import os

folder = "test"
if not os.path.exists(folder):
    os.mkdir(folder)

# ----------------- json -----------------
import json

a = [1,2,3,4,5]
b = json.dumps(a) # change to string
print(b)
# [1, 2, 3, 4, 5]
print(type(b))
# <class 'str'>

a = {"b":1, "a":2, "c":3}
b = json.dumps(a)
print(b)
# {"b": 1, "a": 2, "c": 3}
print(type(b))
# <class 'str'>

#sort_keys
a = {"b":1, "a":2, "c":3}
b = json.dumps(a, sort_keys=True)
print(b)
# {"a": 2, "b": 1, "c": 3}
print(type(b))
# <class 'str'>

#indent
a = {"b":1, "a":2, "c":3}
b = json.dumps(a, sort_keys=True, indent=4)
print(b)
"""
{
    "a": 2,
    "b": 1,
    "c": 3
}
"""

# ----------------- load json -----------------
a = '{"b":1, "a":2, "c":3}'
b = json.loads(a)
print(b)
# {'b': 1, 'a': 2, 'c': 3}
print(type(b))
# <class 'dict'>

# ----------------- dump json to the file -----------------
a = {"b":1, "a":2, "c":3}
with open("test/test.json", "w") as f:
    json.dump(a, f)

# ----------------- load json from the file -----------------
with open("test/test.json", "r") as f:
    data = json.load(f)
    print(data)
    # {'b': 1, 'a': 2, 'c': 3}
    print(type(data))
    # <class 'dict'>
    
