print("----------------- type -----------------")
print(type(1))                  # <class 'int'>
print(type(1.1))                # <class 'float'>
print(type("hello"))            # <class 'str'>
print(type(None))               # <class 'NoneType'>
print(type(False))              # <class 'bool'>
print(type(enumerate("aa")))    # <class 'enumerate'>
print(type(range(0)))           # <class 'range'>

print("----------------- print -----------------")
print("%d" % 1)  # 1
print("%s" % "abc")  # abc
print("%d %s" % (1, "abc"))  # 1 abc

print("%d %f %s" % (1, 1.1, "hello"))
# 1 1.100000 hello

print("|%6d|" % (1))
print("|%-6d|" % (1))
print("|%+6d|" % (1))
# |     1|
# |1     |
# |    +1|

print("|%6s|" % ("a"))
print("|%-6s|" % ("a"))
print("|%+6s|" % ("a"))
# |     a|
# |a     |
# |     a|

# ----------------- format -----------------
print("{} {} {}".format("a", "b", "c"))
print("{2} {1} {0}".format("a", "b", "c"))
# a b c
# c b a

print("----------------- 二進位, 八進位, 十六進位 -----------------")
a = 0b1101
print(a)            # 13
print(bin(a))       # 0b1101
print(type(bin(a)))  # <class 'str'>

a = 0o57
print(a)            # 47
print(oct(a))       # 0o57
print(type(oct(a)))  # <class 'str'>

a = 0x1B
print(a)            # 27
print(hex(a))       # 0x1b
print(type(hex(a)))  # <class 'str'>

print("----------------- operator -----------------")
print(2 + 1)        # 3
print(2 - 1)        # 1
print(2 * 2)        # 4
print(9 / 2)        # 4.5
print(9 // 2)       # 4
print(9 % 2)        # 1
print(2 ** 3)       # 8

print("----------------- abs, pow -----------------")
a = -10
print(abs(a))       # 10
print(pow(2, 3))    # 8

print("----------------- string -----------------")
a = "aa"
b = "bb"
print(a+b)     # aabb
print(a*2)     # aaaa

a = """multiple
line"""

# 防止escape character
a = r"asdfasdf\n"
print(a)       # asdfasdf\n

print(chr(97))         # a
print(type(chr(97)))   # <class'str'>

print(ord("a"))        # 97
print(type(ord("A")))  # <class 'int'>

print("----------------- casting -----------------")
print(bool(None))  # False
print(bool(0))     # False
print(bool(""))    # False
print(bool(1))     # True

print(int(False))  # 0
print(int(True))   # 1
print(int(11.9))   # 11
print(int("-10"))  # -10

print(float(1))    # 1.0
print(float("11.23"))  # 11.23

print(str(1))      # "1"
print(str(-1.23))  # "-1.23"

print("----------------- str -----------------")
s = "hello world, this is hugo, here we are"

print(s.split())
# ['hello', 'world,', 'this', 'is', 'hugo,', 'here', 'we', 'are']

print(s.split(","))
# ['hello world', ' this is hugo', ' here we are']

s = ["gg", "kk", "mm"]
print(",".join(s))  # gg,kk,mm

s = "hello world, this is hugo, here we are"
print(len(s))  # 38
print(s.startswith("hell"))  # True
print(s.endswith("are"))  # True
print(s.find("world"))  # 6
print(s.rfind("we"))  # 32
print(s.count("we"))  # 1
print(s.isalnum())  # False
print(s.isalpha())  # False

print(s.capitalize())  # Hello world, this is hugo, here we are
print(s.title())  # Hello World, This Is Hugo, Here We Are
print(s.upper())  # HELLO WORLD, THIS IS HUGO, HERE WE ARE
print(s.lower())  # hello world, this is hugo, here we are
print(s.swapcase())  # HELLO WORLD, THIS IS HUGO, HERE WE ARE

print(s.replace("hugo", "GGGG"))  # hello world, this is GGGG, here we are

print("----------------- dir -----------------")
print(dir())      # ['__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', 'a', 'b', 's']
print(dir(list))  # ['__add__', '__class__', '__class_getitem__', '__contains__', '__delattr__', '__delitem__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__gt__', '__hash__', '__iadd__', '__imul__', '__init__', '__init_subclass__', '__iter__', '__le__', '__len__', '__lt__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__reversed__', '__rmul__', '__setattr__', '__setitem__', '__sizeof__', '__str__', '__subclasshook__', 'append', 'clear', 'copy', 'count', 'extend', 'index', 'insert', 'pop', 'remove', 'reverse', 'sort']

print("----------------- input -----------------")
a = input("enter sth:")
print(a)               # print your input
