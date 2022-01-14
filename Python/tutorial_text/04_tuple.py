# ----------------- definition -----------------
a = (1,)
print(type(a))  # <class 'tuple'>

a = (1,2,3)
print(type(a))  # <class 'tuple'>

# ----------------- access -----------------
a = ("a","b","c")
print(a[1])  # b

a = (1,2,3)
for b in a:
    print(b)  # 1 2 3

# ----------------- tuple cannot be modified -----------------
a = (1,2,3)
try:
    a[0] = 1
except Exception as err:
    print(err) # 'tuple' object does not support item assignment
    
try:
    a.pop()
except Exception as err:
    print(err)  # 'tuple' object has no attribute 'pop'

try:
    a.append("a")
except Exception as err:
    print(err)  # 'tuple' object has no attribute 'append'

# ----------------- slices -----------------
a = (1,2,3,4,5)
print(a[:3])  # (1, 2, 3)

# ----------------- len -----------------
a = (1,2,3)
print(len(a))  # 3

# ----------------- change to list -----------------
a = (1,2,3)
b = list(a)
print(b)  # [1, 2, 3]

# ----------------- change to tuple -----------------
a = [1,2,3]
b = tuple(a)
print(b)  # (1, 2, 3)

# ----------------- zip -----------------
a = [1,2,3]
b = ["a","b","c"]
z = zip(a,b)
print(type(z))  # <class 'zip'>

c = list(z)
print(c)  # [(1, 'a'), (2, 'b'), (3, 'c')]

d, e = zip(*c)  # unzip
print(d)        # (1, 2, 3)
print(e)        # ('a', 'b', 'c')
print(type(e))  # <class 'tuple'>
