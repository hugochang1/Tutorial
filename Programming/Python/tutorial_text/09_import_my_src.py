# ----------------- import -----------------
import  src.my

src.my.A()
src.my.f1()
print(src.my.f2(1,2))
src.my.f3()

"""
you have included my2.py
you have included my.py
A.__init__()
f1()
3
f3()
f4()
"""

# ----------------- import as -----------------
import src.my as my

my.A()
my.f1()
my.f2(2,3)

"""
you have included my.py
A.__init__()
f1()
"""
