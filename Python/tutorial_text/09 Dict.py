# ----------------- Definition -----------------
a = {}
print(type(a))  # <class 'dict'>

a = {"a":1, "b":2}
print(type(a))  # <class 'dict'>

# ----------------- access -----------------
a = {"a":1, "b":2}
print(a["a"])  # 1

a = {"a":1, "b":2}
try:
    print(a["z"])
except Exception as err:
    print("KeyError", err) # KeyError 'z'
    
# ----------------- add -----------------
a = {"a":1, "b":2}
a["c"]=3
print(a)  # {'a': 1, 'b': 2, 'c': 3}

# ----------------- modify -----------------
a = {"a":1, "b":2}
a["b"] = 100
print(a)  # {'a': 1, 'b': 100}

# ----------------- delete an element -----------------
a = {"a":1, "b":2}
del a["b"]
print(a)  # {'a': 1}

# ----------------- delete all element -----------------
a = {"a":1, "b":2}
a.clear()
print(a) # {}

# ----------------- delete dict -----------------
a = {}
del a

try:
    print(a)
except Exception as err:
    print(err)  # name 'a' is not defined
    
# ----------------- copy -----------------
a = {"a":1, "b":2, "c":3}
b = a.copy()

print(id(a))  # 82865680
print(id(b))  # 82751136

# ----------------- len -----------------
print(len(a))  # 3

# ----------------- exists -----------------
#key
a = {"a":1, "b":2, "c":3}

if "a" in a:
    print("y")

if "a" in a.keys():
    print("y")
    
if 2 in a.values():
    print("y")

# ----------------- traversal dict -----------------
a = {"a":1, "b":2, "c":3}

for b in a:
    print(b)  # a b c
    
for b in a.keys():
    print(b)  # a b c

for b in a.values():
    print(b) # 1 2 3
    
for b, c in a.items():
    print(b, c)
"""
a 1
b 2
c 3
"""
# ----------------- list or dict in dict -----------------
a = {"a":[1,2,3],
     "b":[4,5,6]}
print(a)  # {'a': [1, 2, 3], 'b': [4, 5, 6]}

a = {"a":{"aa":11,"bb":22}, "b":{"cc":33, "dd":44}}
print(a)             # {'a': {'aa': 11, 'bb': 22}, 'b': {'cc': 33, 'dd': 44}}
print(a["a"])        # {'aa': 11, 'bb': 22}
print(a["a"]["aa"])  # 11

# ----------------- fromkeys() -----------------
a = ["a","b"]
b = dict.fromkeys(a)
print(b)  # {'a': None, 'b': None}

b = dict.fromkeys(a, "defaultValue")
print(b)  # {'a': 'defaultValue', 'b': 'defaultValue'}

# ----------------- get() -----------------
a = {"a":1, "b":2, "c":3}

print(a.get("a"))                  # 1
print(a.get("z"))                  # None
print(a.get("z", "defaultValue"))  # defaultValue

# ----------------- setdefault() -----------------
# if key not exist, add new key with none
# if key exist, do nothing
a = {"a":1, "b":2, "c":3}

print(a.setdefault("a"))  # 1
print(a)                  # {'a': 1, 'b': 2, 'c': 3}

print(a.setdefault("d"))  # None
print(a)                  # {'a': 1, 'b': 2, 'c': 3, 'd': None}

# with default value
# if key not exist, add new key with default value
# if key exist, do nothing
print(a.setdefault("a", 11)) # 1
print(a)                     # {'a': 1, 'b': 2, 'c': 3, 'd': None}

print(a.setdefault("e", 22)) # 22
print(a)                     # {'a': 1, 'b': 2, 'c': 3, 'd': None, 'e': 22}

# ----------------- pop() -----------------
a = {"a":1, "b":2, "c":3}

print(a.pop("a"))  # 1
print(a)           # {'b': 2, 'c': 3}

print(a.pop("z", "defaultValue")) # defaultValue

try:
    a.pop("z")
except Exception as err:
    print("KeyError", err) # KeyError 'z'
