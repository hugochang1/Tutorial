# ----------------- Concept -----------------
def a():
    """this is a() function"""
    print("hello")

a()  # hello

print(a.__doc__)  # this is a() function
print(a())
"""
hello
None
"""

def a(a,b):
    return a+b
b = a(1,2)
print(b)  # 3
print(a(1, b=2))   # 3
print(a(a=1, b=2)) # 3
print(a(b=1, a=2)) # 3

# ----------------- return multiple values -----------------
def f():
    return 1,2,"aa"
a = f()
print(a)  # (1, 2, 'aa')
a,b,c = f()
print(a,b,c)  # 1 2 aa

# ----------------- parameters -----------------
def f(a,b,c=0):
    print(a,b,c)    
f(1,2)   # 1 2 0
f(1,2,3) # 1 2 3

def f(a=0,b):
    pass
# SyntaxError: non-default argument follows default argument

def f(*a):
    print(a)        
f()      # ()
f(1)     # (1,)
f(1,2,3) # (1, 2, 3)


def f(a, *b):
    print(a, b)
f(1)  # 1 ()
f(1,2,3,)  # 1 (2, 3)

def f(**a):
    print(a)
f()  # {}
f(aaa=1, bbb=2, ccc="abc")  # {'aaa': 1, 'bbb': 2, 'ccc': 'abc'}

f(1="a")
# SyntaxError: keyword can't be an expression

f("a"=1)
# SyntaxError: keyword can't be an expression

# ----------------- global variable, local variable -----------------
def f():
    a = 2
    print(a)    
a = 1
f()
print(a)
"""
2
1
"""

def f():
    global a
    a = 2    
a = 1
f()
print(a)  # 2

# ----------------- lambda -----------------
a = lambda x: x*2
print(a(5))  # 10

#lambda on filter
a = [1,2,3,4,5,6]
a = list(filter(lambda x: x % 2 == 0, a))
print(a)  # [2, 4, 6]

#lambda on map
a = [1,2,3,4,5,6]
a = list(map(lambda x: x*2, a))
print(a)  # [2, 4, 6, 8, 10, 12]
