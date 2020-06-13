# ----------------- for -----------------
a = [1,2,3]
for b in a:
    print(b)  # 1 2 3
    
for b in a: print(b)  # 1 2 3

# ----------------- range -----------------
# end
for b in range(3):
    print(b)  # 0 1 2

# start end
for b in range(1,3):
    print(b) # 1 2
    
#start, end, step
for b in range(1, 10, 2):
    print(b, end=" ") # 1 3 5 7 9

a = list(range(3))
print(a) # [0, 1, 2]

b = [a for a in range(5)]
print(b) # [0, 1, 2, 3, 4]

b = [a*a for a in range(5)]
print(b) # [0, 1, 4, 9, 16]

# ----------------- for else -----------------
for a in range(3):
    print(a)
else:
    print("else")
# 0 1 2 else

# ----------------- break -----------------
for a in range(5):
    if a == 3:
        break
    print(a)
# 0 1 2

for a in range(5):
    if a == 3:
        break
    print(a)
else:
    print("no else")
# 0 1 2

# ----------------- continue -----------------
for a in range(5):
    if a < 2:
        continue
    print(a)
# 2 3 4

for a in range(5):
    if a < 2:
        continue
    print(a)
else:
    print("else")
# 2 3 4 else

# ----------------- while -----------------
a = 0
while a < 5:
    print(a)
    a+=1
# 0 1 2 3 4

a = 0
while a < 5:
    print(a)
    a+=1
else:
    print("else")
# 0 1 2 3 4 else

# ----------------- emunerate in for loop -----------------
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
