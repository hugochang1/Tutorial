from . import my2

def f1():
    print("f1()")
	
def f2(a, b):
    return a + b

def f3():
    print("f3()")
    my2.f4()

class A():
    def __init__(self):
	    print("A.__init__()");
	
if __name__ == "__main__":
    print("my.py main is run")
	
print("you have included my.py")