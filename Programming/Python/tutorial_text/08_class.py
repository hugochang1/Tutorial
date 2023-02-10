# ----------------- Definition -----------------
class A:
    """the document of class A"""
    def __init__(self, a):
        """the document of A's constructor"""
        self.a = a
        self.b = 2
    
    def f1(self, x, y):
        """the document of f1()"""
        return x+y

print(A.__doc__)  # the document of class A
print(A.__init__.__doc__)  # the document of A's constructor
print(A.f1.__doc__)  # the document of f1()

a = A(1)
print(type(a))  # <class '__main__.A'>
print(a)  # <__main__.A object at 0x0000000004D7BF60>
print(a.f1(1,2))  # 3
print(a.a)  # 2
print(a.b)  # 1

# ----------------- private -----------------
class A:
    def __init__(self):
        self.__a = 1  #cannot be accessed from the outside
        self.__b = 2  #cannot be accessed from the outside
        
    def f1(self, x):
        return self.__f1(x)
        
    def __f1(self, x):
        """cannot be access by outside"""
        return x*2
    
a = A()
print(a.f1(5))  # 10

# ----------------- inheritance -----------------
class A:
    def __init__(self):
        print("A.__init__()")
        
    def f1(self):
        print("A.f1()")
        
class B(A):  # inheritance
    def __init__(self):
        print("B.__init__()")
        
    def f1(self):
        print("B.f1()")
        
a = A()  # A.__init__()
b = B()  # B.__init__()
a.f1()  # A.f1()
b.f1()  # B.f1()


class A():
    def __init__(self):
        print("A.__init__()")
        
    def f1(self):
        print("A.f1()")
        
class B(A):
    def __init__(self):
        super().__init__()  # call parent's constructor
        print("B.__init__()")
b = B()
b.f1()
"""
A.__init__()
B.__init__()
A.f1()
"""

# ----------------- polymorphism -----------------
class A():
    def f1(self):
        print("A.f1()")
        
class B(A):
    def f1(self):
        print("B.f1()")
        
class C(B):
    def f1(self):
        print("C.f1()")
        
a = A()
b = B()
c = C()

a.f1()  # A.f1()
b.f1()  # B.f1()
c.f1()  # C.f1()

# ----------------- type, instance -----------------
print(type(a))  # <class '__main__.A'>
print(type(b))  # <class '__main__.B'>
print(type(c))  # <class '__main__.C'>

print(isinstance(a, A))  # True
print(isinstance(a, B))  # False
print(isinstance(a, C))  # False

print(isinstance(b, A))  # True
print(isinstance(b, B))  # True
print(isinstance(b, C))  # False

print(isinstance(c, A))  # True
print(isinstance(c, B))  # True
print(isinstance(c, C))  # True

# ----------------- attribute -----------------
if __name__ == "__main__":
    print("yes")  # yes
    
#__str__, __repr__
class A():
    """the document of class A"""
    def __init__(self):
        self.a = 1
        self.b = 2
        
    def __str__(self):  # this is for print
        return "class.A a=%d b=%d" % (self.a, self.b)
    
    __repr__ = __str__  # this is console output
    
a = A()
a.a = 11
a.b = 22
print(a)  # class.A a=11 b=22



#__iter__, __next__
class A():
    def __init__(self):
        self.a = 0
        
    def __iter__(self):
        return self
    
    def __next__(self):
        self.a +=2
        if self.a > 10:
            raise StopIteration
        return self.a

for i in A():
    print(i)
"""
2
4
6
8
10
"""
