# ----------------- definition -----------------
a = []
a = [1,2,3]
a = ["aa", "bb"]
a = [1, "a"]
a = [[1, 2], 3]

# ----------------- access -----------------
a = ["a", "b", "c"]
print(a[0])  # a
print(a[-1]) # c (last one)

# ----------------- slice -----------------
a = ["a", "b", "c"]
print(a[:])   # ['a', 'b', 'c'] (all)
print(a[:1])  # ['a']
print(a[1:])  # ['b', 'c']
print(a[:-1]) # ['a', 'b']

# ----------------- max(), min(), sum(), len() -----------------
a = [0, 1, 2, 3, 4, 5]
print(max(a))  # 5
print(min(a))  # 0
print(sum(a))  # 15
print(len(a))  # 6

# ----------------- modify -----------------
a = [0, 1, 2]
a[0] = 10
print(a)  # [10, 1, 2]

# ----------------- add -----------------
a = [1, 2]
b = [3, 4]
print(a+b)  # [1, 2, 3, 4]

# ----------------- multiply -----------------
a = [1, 2]
print(a*3) # [1, 2, 1, 2, 1, 2]

# ----------------- delete -----------------
a = [1,2,3]
del a[1]
print(a)  # [1, 3]

a = [1,2,3]
del a[:2]
print(a)  # [3]

a = [1,2,3]
del a
try:
    a
except Exception as err:
    print(err)  # name 'a' is not defined

# ----------------- append -----------------
a = [1,2]
a.append(3)
print(a)  # [1, 2, 3]

a.append(["a", "b"])
print(a) # [1, 2, 3, ['a', 'b']]

# ----------------- extend -----------------
a = [1,2]
a.extend([3,4])
print(a) # [1, 2, 3, 4]

# ----------------- insert -----------------
a = [1,2,3]
a.insert(1, "a")
print(a)  # [1, 'a', 2, 3]
a.insert(-1, "b")
print(a)  # [1, 'a', 2, 'b', 3]

# ----------------- pop -----------------
a = [1,2,3]
print(a.pop())  # 3, get and remove last one
print(a.pop(1)) # 2
print(a)        # [1]
try:
    print(a.pop(10))
except Exception as err:
    print(err)  # pop index out of range
    
# ----------------- remove -----------------
# given a element to be removed
a = ["a", "b", "c"]
a.remove("a")
a.remove("c")
print(a)  # ['b']

try:
    a.remove("z")
except Exception as err:
    print(err) # list.remove(x): x not in list

# ----------------- reverse -----------------
a = [1,2,3]
a.reverse()
print(a)  # [3, 2, 1]

# ----------------- sort -----------------
a = [3,1,2]
a.sort()
print(a)  # [1, 2, 3]

a = ["b", "a", "c"]
a.sort()
print(a)  # ['a', 'b', 'c']

a.sort(reverse=True)
print(a)  # ['c', 'b', 'a']

a = ["b", "a", "c", 1]
try:
    a.sort()
except Exception as err:
    print(err)  # '<' not supported between instances of 'int' and 'str'

# ----------------- index -----------------
a = ["a", "b", "c"]
print(a.index("b"))  # 1

# ----------------- count -----------------
a = [1,2,1,3,1]
print(a.count(1)) # 3

# ----------------- join -----------------
c = "_"
a = ["a", "b", "c"]
print(c.join(a))  # a_b_c

# ----------------- copy -----------------
a = [1, 2]
b = a
print(id(a))  # 80502280
print(id(b))  # 80502280
print("-----------")
b = a.copy()
print(id(a))  # 80502280
print(id(b))  # 80527560
print("-----------")
b = a[:]  # same as copy()
print(id(a))  # 80502280
print(id(b))  # 79866760

# ----------------- string -----------------
a = " aaBB "
print(a.upper())  # AABB 
print(a.lower())  # aabb
print(a.title())  # Aabb
print("|", a.rstrip(), "|", sep="")  # | aaBB|
print("|", a.lstrip(), "|", sep="")  # |aaBB |
print("|", a.strip(), "|", sep="")   # |aaBB|

a = "aa"
print(a.islower())  # True
print(a.isupper())  # False
print(a.istitle())  # False

a = 5
print(a.bit_length())  # 3
a = 8
print(a.bit_length())  # 4

# ----------------- string access -----------------
a = "abc"
print(a[0])   # a

print(a[:2])  # ab

print(len(a)) # 3

a = list(a)
print(a)      # ['a', 'b', 'c']

a = "aaa bbb ccc"
print(a.split())  # ['aaa', 'bbb', 'ccc']

a = "1,2,3"
print(a.split(",")) # ['1', '2', '3']

# ----------------- in, not in -----------------
a = [1,2,3]

if 1 in a:
    print("y")
    
if 4 not in a:
    print("y")

# ----------------- is, is not -----------------
# check id whether they are identical
a = 1
b = a

if a is b:
    print("y")
    
if a is not 2:
    print("y")
    
# ----------------- enumerate -----------------
a = ["a","b","c"]
a = enumerate(a)  
print(type(a))  # <class 'enumerate'>
print(a)        # <enumerate object at 0x0000000004D017E0>
print(list(a))  # [(0, 'a'), (1, 'b'), (2, 'c')]
