# ----------------- get current working directory -----------------
import os

print(os.getcwd())
# C:\Users\Hugo\workspace

# ----------------- get absolute path -----------------
print(os.path.abspath(""))
# C:\Users\Hugo\workspace

print(os.path.abspath("."))
# C:\Users\Hugo\workspace

print(os.path.abspath(".."))
# C:\Users\Hugo

print(os.path.abspath("123"))
# C:\Users\Hugo\workspace\123

# ----------------- get relative path -----------------
print(os.path.relpath("C:\\"))
# ..\..\..

print(os.path.relpath("C:\\Porgram Files"))
# ..\..\..\Porgram Files

# ----------------- is directory -----------------
print(os.path.isdir("123"))
# False

print(os.path.isdir("C"))
# False

print(os.path.isdir("C:"))
# True

print(os.path.isdir("C:/Program Files"))
# True

print(os.path.isdir("C:/Program Files/GG"))
# False

# ----------------- is file -----------------
print(os.path.isfile("C"))
# False

print(os.path.isfile("C:/"))
# False

print(os.path.isfile("C:/Install.log"))
# True

print(os.path.isfile("./14 File Read Write.py"))
# True

# ----------------- mkdir -----------------
folder = "test1"
if not os.path.exists(folder):
    os.mkdir(folder)

# ----------------- makedirs -----------------
folder = "test1/test2/test3"

if not os.path.exists(folder):
    os.makedirs(folder)
    
# ----------------- rmdir -----------------
os.rmdir("test1/test2/test3")
os.rmdir("test1/test2")
os.rmdir("test1")

# ----------------- remove -----------------
file = "aaaaaaa"
with open(file, "w") as f:
    pass

os.remove(file)

print(os.path.exists(file))
# False

# ----------------- chdir -----------------
print(os.getcwd())
# C:\Users\Hugo\workspace

os.chdir("src")
print(os.getcwd())
# C:\Users\Hugo\workspace\src

os.chdir("..")
print(os.getcwd())
# C:\Users\Hugo\workspace

# ----------------- join -----------------
print(os.path.join("aaa","bbb","ccc"))
# aaa\bbb\ccc

print(os.path.join("aaa/ccc","bbb"))
# aaa/ccc\bbb

# ----------------- getsize -----------------
print(os.path.getsize("src"))
# 0

print(os.path.getsize("src/my.py"))
# 299

try:
    print(os.path.getsize("zzzzzz"))
except Exception as err:
    print(err)
# [WinError 2] 系統找不到指定的檔案。: 'zzzzzz'

# ----------------- listdir -----------------
for a in os.listdir("."):
    print(a, os.path.getsize(a))

"""
history.py 8284
history_internal.py 68
kernel.log 5712961
...
"""

# ----------------- glob - list all -----------------
import glob

for s in glob.glob("*"):
    print(s)
"""
history.py
history_internal.py
kernel.log
...
"""

for s in glob.glob("*.py"):
    print(s)
"""
history.py
history_internal.py
...
"""

# ----------------- walk -----------------
for dirName, subDirNames, fileNames in os.walk("."):
    print("dirName=", dirName)
    print("subDirNames=", subDirNames)
    print("fileNames=", fileNames)
    print("")
"""

dirName= .
subDirNames= ['.ropeproject', 'certs', 'config', 'db', 'defaults', 'pictures', 'plugins', 'spyder.lock', 'src']
fileNames= ['asyncore_tester.py', 'history.py', 'history_internal.py', 'kernel.log', 'kernel.log_1.6G', 'kernel.log_1G', 'kernel.log_2G', 'langconfig', 'log.txt', 'movies.xml', 'onlinehelp', 'spyder.ini', 'spyder.ini.bak', 'temp.py', 'template.py', 'test.py', 'workingdir']

dirName= .\.ropeproject
subDirNames= []
fileNames= ['config.py']

dirName= .\certs
subDirNames= []
fileNames= ['UbuntuOne-Go_Daddy_CA.pem']

dirName= .\db
subDirNames= []
fileNames= ['submodules']

dirName= .\defaults
subDirNames= []
fileNames= ['defaults-43.0.0.ini']

dirName= .\pictures
subDirNames= []
fileNames= ['i1.png']

dirName= .\plugins
subDirNames= []
fileNames= []

dirName= .\spyder.lock
subDirNames= []
fileNames= ['symlink']

dirName= .\src
subDirNames= ['__pycache__']
fileNames= ['my.py', 'my2.py']

dirName= .\src\__pycache__
subDirNames= []
fileNames= ['my.cpython-36.pyc', 'my2.cpython-36.pyc']
"""

# ----------------- write a file -----------------
file = "aaaaaa"
with open(file, "w") as f:
    f.write("hello world\n")
    f.write("中文測試\n")

with open(file, "a") as f:
    f.write("add more msg ...\n")

# ----------------- read a file -----------------
with open(file, "r") as f:
    print(f.read())
"""
hello world
中文測試
add more msg ...
"""

with open(file, "r") as f:
    lines = f.readlines()
print(lines)
# ['hello world\n', '中文測試\n', 'add more msg ...\n']

os.remove(file)

# ----------------- shutil - copy file -----------------
import shutil

shutil.copy("src/my.py", "src/my.py2")
os.remove("src/my.py2")

try:
    shutil.copy("aaaaaaaaa", "bbbbbbbbbbb")
except Exception as err:
    print(err)
# [Errno 2] No such file or directory: 'aaaaaaaaa'

# ----------------- shutil - copy tree -----------------
shutil.copytree("src", "src2")

try:
    shutil.copytree("aaaaaaaaaaa", "bbbbbbbb")
except Exception as err:
    print(err)
# [WinError 3] 系統找不到指定的路徑。: 'aaaaaaaaaaa'

# ----------------- shutil - rename -----------------
shutil.move("src2", "src3")

try:
    shutil.move("aaaaaaaaaaa", "bbbbbbbb")
except Exception as err:
    print(err)
# [Errno 2] No such file or directory: 'aaaaaaaaaaa'

# ----------------- shutil - delete tree -----------------
shutil.rmtree("src3")

try:
    shutil.rmtree("aaaaaaaaaaa")
except Exception as err:
    print(err)
# [WinError 3] 系統找不到指定的路徑。: 'aaaaaaaaaaa'
    
# ----------------- zip file -----------------
import zipfile
import glob, os

z = zipfile.ZipFile("my.zip", "w")
for s in glob.glob("*.py"):
    z.write(s, os.path.basename(s), zipfile.ZIP_DEFLATED)
z.close()

z = zipfile.ZipFile("my.zip", "r")
for info in z.infolist():
    print(info.filename, "|", info.file_size, "|", info.compress_size)
z.close()
"""
asyncore_tester.py | 521 | 242
history.py | 8284 | 678
history_internal.py | 68 | 66
temp.py | 9777 | 1854
template.py | 81 | 72
test.py | 4612 | 959
test2.py | 6126 | 1586
tkinter_example.py | 9777 | 1854
tkinter_example2.py | 4612 | 959
tkinter_tcp_tester.py | 5207 | 1163
"""

z = zipfile.ZipFile("my.zip", "r")
z.extractall("./unzip")
z.close()

os.remove("my.zip")
shutil.rmtree("unzip")

# ----------------- encode -----------------
with open("encode_utf8.txt", "w", encoding="utf8") as f:
    f.write("hello world")
    f.write("中文測試")

with open("encode_950.txt", "w", encoding="950") as f:
    f.write("hello world")
    f.write("中文測試")

with open("encode_utf8.txt", "r", encoding="utf8") as f:
    print(f.read())
    # hello world中文測試

with open("encode_950.txt", "r", encoding="950") as f:
    print(f.read())
    # hello world中文測試

try:
    with open("encode_utf8.txt", "r") as f:
        print(f.read())
except Exception as err:
    print(err)
    # 'cp950' codec can't decode byte 0x96 in position 15: illegal multibyte sequence

try:
    with open("encode_950.txt", "r", encoding="utf8") as f:
        print(f.read())
except Exception as err:
    print(err)
    # 'utf-8' codec can't decode byte 0xa4 in position 11: invalid start byte

# ----------------- copy to clipboard -----------------
#pip install pyperclip
import pyperclip
pyperclip.copy("hello world")
s = pyperclip.paste()
print(s)
# hello world
