print("----------------- comparison operators -----------------")
print(1 == 1)     # True
print(1 != 2)     # True
print(2 > 1)      # True
print(1 < 2)      # True
print(1 >= 1)     # True
print(1 <= 1)     # True

print("----------------- boolean comparison -----------------")
print(True and True)   # True
print(True or False)   # True
print(not True)        # False

print("----------------- if, elif, else -----------------")
if True:
    print("here")     # here

if False:
    print("not here")
else:
    print("here")     # here

if False:
    print("not here")
elif True:
    print("here")     # here

if False:
    print("not here")
elif False:
    print("not here")
else:
    print("here")     # here

if True:
    if True:
        print("here")     # here

print("----------------- while, break -----------------")
a = 0
while True:
    a += 1
    print(a)
    if a >= 3:
        break
"""
1
2
3
"""

print("----------------- for -----------------")
for i in range(3):
    print(i)
"""
0
1
2
"""
for i in range(1, 4):
    print(i)
"""
1
2
3
"""
for i in range(1, 6, 2):
    print(i)
"""
1
3
5
"""

a = ["a","b","c"]
for b in enumerate(a):
    print(b)
"""
(0, 'a')
(1, 'b')
(2, 'c')
"""

for b, c in enumerate(a):
    print(b, c)
"""
0 a
1 b
2 c
"""

print("----------------- sys.exit() -----------------")
import sys
sys.exit(0)
