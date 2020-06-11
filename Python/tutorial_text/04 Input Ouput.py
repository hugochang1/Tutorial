# ----------------- help -----------------
help(print)
"""
Help on built-in function print in module builtins:

print(...)
    print(value, ..., sep=' ', end='\n', file=sys.stdout, flush=False)
    
    Prints the values to a stream, or to sys.stdout by default.
    Optional keyword arguments:
    file:  a file-like object (stream); defaults to the current sys.stdout.
    sep:   string inserted between values, default a space.
    end:   string appended after the last value, default a newline.
    flush: whether to forcibly flush the stream.
"""

# ----------------- print -----------------
import sys
print("a", "b", sep="!", end="\n\n", file=sys.stdout, flush=True)
# a!b

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

# ----------------- open -----------------
"""
r: read
w: write, if file exists, overwrite it
a: write, if file exists, write data will be appended in the last
x: write, if file exsits, exception happen
b: write with binary format
t: text mode
+: open file for update
"""
with open("test.txt", "w") as f:
    f.write("abc")
    
with open("test.txt", "r") as f:
    s = f.read()
    print(s) # "abc"

try:
    with open("test.txt", "x") as f:
        pass
except Exception as err:
    print(err)  # [Errno 17] File exists: 'test.txt'
    
# ----------------- input -----------------
a = input("please enter someting: ")
print(a)

# please enter someting: 123
# 123

# ----------------- dir -----------------
# return its attributes
dir()
"""
['In',
 'Out',
 '_',
 '__',
 '___',
 ...
 'quit',
 's',
 'sys']
"""

dir(list)
"""
['__add__',
 '__class__',
 '__contains__',
 '__delattr__',
 '__delitem__',
 '__dir__',
 '__doc__',
 '__eq__',
 '__format__',
 '__ge__',
 '__getattribute__',
 '__getitem__',
 '__gt__',
 '__hash__',
 '__iadd__',
 '__imul__',
 '__init__',
 '__init_subclass__',
 '__iter__',
 '__le__',
 '__len__',
 '__lt__',
 '__mul__',
 '__ne__',
 '__new__',
 '__reduce__',
 '__reduce_ex__',
 '__repr__',
 '__reversed__',
 '__rmul__',
 '__setattr__',
 '__setitem__',
 '__sizeof__',
 '__str__',
 '__subclasshook__',
 'append',
 'clear',
 'copy',
 'count',
 'extend',
 'index',
 'insert',
 'pop',
 'remove',
 'reverse',
 'sort']
"""
