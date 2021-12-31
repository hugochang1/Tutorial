# ------------- print -------------
print("%d" % 1)  # 1
print("%s" % "abc")  # abc
print("%d %s" % (1, "abc"))  # 1 abc

# ------------- type -------------
print(type(1))  # <class 'int'>
print(type(1.1))  # <class 'float'>
print(type("abc"))  # <class 'str'>
print(type(True))  # <class 'bool'>
print(type(None))  # <class 'NoneType'>

# ------------- number presentation -------------
print("%d" % 10)  # Decimal
print("%d" % 0b10)  # Binary
print("%d" % 0o10)  # Octal
print("%d" % 0x10)  # Hexadecimal

# ------------- casting -------------
print(bool(None))  # False
print(bool(0))  # False
print(bool(""))  # False
print(bool(1))  # True

print(int(False))  # 0
print(int(True))  # 1
print(int(11.9))  # 11
print(int("-10"))  # -10

print(float(1))  # 1.0
print(float("11.23"))  # 11.23

print(str(1))  # "1"
print(str(-1.23))  # "-1.23"

# ------------- str -------------
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
