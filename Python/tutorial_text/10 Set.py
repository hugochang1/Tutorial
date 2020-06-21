# ----------------- Create a Set -----------------
# this is dict
a = {}
print(type(a))  # <class 'dict'>

# below is set
a = set()
print(type(a))  # <class 'set'>

a = {1}
print(type(a))  # <class 'set'>

a = {1,2,3}
print(type(a))  # <class 'set'>

#duplicated elements will be removed
a = {1,1,2,2}
print(a)  # {1, 2}

a = {1,(1,2)}
print(a)  # {(1, 2), 1}

try:
    a = {1, [1,2]}
except Exception as err:
    print(err)  # unhashable type: 'list'
    
a = set("aabbccdef")
print(a)  # {'c', 'f', 'd', 'a', 'e', 'b'}

a = set([1,2,3])
print(a)  # {1, 2, 3}

#set -> list
a = list(set([1,2,3]))
print(a)        # [1, 2, 3]
print(type(a))  # <class 'list'>

#list -> set
a = set(list([1,2,3]))
print(a)        # {1, 2, 3}
print(type(a))  # <class 'set'>

# ----------------- Operation -----------------
#intersection
a = {1,2,3}
b = {3,4,5}

print(a & b)  # {3}
print(b & a)  # {3}
print(a.intersection(b))  # {3}
print(b.intersection(a))  # {3}

a = {1,2}
b = {3,4}
print(a & b)  # set()

#union
print(a | b)  # {1, 2, 3, 4, 5}
print(b | a)  # {1, 2, 3, 4, 5}
print(a.union(b))  # {1, 2, 3, 4, 5}
print(b.union(a))  # {1, 2, 3, 4, 5}

#difference
print(a - b)  # {1, 2}
print(b - a)  # {4, 5}
print(a.difference(b))  # {1, 2}
print(b.difference(a))  # {4, 5}

#symmetric difference
print(a ^ b)  # {1, 2, 4, 5}
print(b ^ a)  # {1, 2, 4, 5}
print(a.symmetric_difference(b))  # {1, 2, 4, 5}
print(b.symmetric_difference(a))  # {1, 2, 4, 5}

#equal, not equal
print(a == b)  # False
print(a != b)  # True

#in, not in
print(1 in a)  # True
print(1 not in a)  # False

# ----------------- Methods -----------------
#add
a = {1,2,3}
a.add(4)
print(a)  # {1, 2, 3, 4}

a.add(3)
print(a)  # {1, 2, 3, 4}

#copy
a = {1,2,3}
b = a.copy()
print(id(a))  # 80487368
print(id(b))  # 80489608
print(a)  # {1, 2, 3}
print(b)  # {1, 2, 3}

#remove
a = {1,2,3}
a.remove(1)
print(a)  # {2, 3}

try:
    a.remove(4)
except Exception as err:
    print("KeyError", err)  # KeyError 4

#discard
#same as remove but will not throw exception if item not exist
a = {1,2,3}
a.discard(1)
print(a)  # {2, 3}

a.discard(4)
print(a)  # {2, 3}

#pop
#drop a element by random
a = {1,2,3}
print(a.pop())  # 1
print(a)  # {2, 3}

#clear
a = {1,2,3}
a.clear()
print(a) # set()

#isdisjoint
a = {1,2}
b = {3,4}
print(a.isdisjoint(b))  # True

b = {2,3}
print(a.isdisjoint(b))  # False

#issubset
a = {1,2}
b = {1,2,3}
print(a.issubset(b))  # True

b = {2,3}
print(a.issubset(b))  # False

#issuperset
a = {1,2,3}
b = {1,2}
print(a.issuperset(b))  # True

b = {1,2,3,4}
print(a.issuperset(b))  # False

#intersection_update
#will update the caller
a = {1,2,3}
b = {3,4,5}
a.intersection_update(b)
print(a)  # {3}

#update
#will update the caller
a = {1,2,3}
b = {3,4,5}
a.update(b)
print(a)  # {1, 2, 3, 4, 5}

#difference_update
#will update the caller
a = {1,2,3}
b = {3,4,5}
a.difference_update(b)
print(a)  # {1, 2}

#symmetric_difference_update
#will update the caller
a = {1,2,3}
b = {3,4,5}
a.symmetric_difference_update(b)
print(a)  # {1, 2, 4, 5}

# ----------------- Functions -----------------
#max, min, sum
a = {1,2,3}
print(max(a))  # 3
print(min(a))  # 1
print(sum(a))  # 6

a = {"a","b","c"}
print(max(a))  # c
print(min(a))  # a

#len
a = {1,2,3}
print(len(a))  # 3

#sorted
#will change to list type
a = {1,2,3}
print(sorted(a))  # [1, 2, 3]

#enumerate
a = {"a","b","c"}
for b, c in enumerate(a):
    print(b, c)
"""
0 c
1 b
2 a
"""

for b, c in enumerate(a, 10):
    print(b, c)
"""
10 c
11 b
12 a
"""

# ----------------- frozenset -----------------
#forzenset cannot use add(), remove()
#but it can use intersection(), union(), difference(), ...
a = frozenset([1,2,3])
b = frozenset([3,4,5])

print(a)  # frozenset({1, 2, 3})
print(b)  # frozenset({3, 4, 5})

print(a | b)  # frozenset({1, 2, 3, 4, 5})
print(a & b)  # frozenset({3})

try:
    a.add(3)
except Exception as err:
    print(err)  # 'frozenset' object has no attribute 'add'
