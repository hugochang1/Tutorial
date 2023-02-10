# ----------------- create the test folder -----------------
import os

try:
    os.mkdir("test")
except Exception as err:
    pass

import csv
# ----------------- delimiter="," -----------------
with open("test/c1.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["lastname", "firstname"])
    writer.writerow(["hugo","chang"])
    writer.writerow(["bean","chan"])
    writer.writerow(["gg","yyy"])
"""
lastname,firstname
hugo,chang
bean,chan
gg,yyy
"""

with open("test/c1.csv", "r") as f:
    reader = csv.reader(f)
    for row in reader:
        print(row)
"""
['lastname', 'firstname']
['hugo', 'chang']
['bean', 'chan']
['gg', 'yyy']
"""

#list
with open("test/c1.csv", "r") as f:
    reader = csv.reader(f)
    data = list(reader)
print(data)
"""
[['lastname', 'firstname'], ['hugo', 'chang'], ['bean', 'chan'], ['gg', 'yyy']]
"""
# ----------------- delimiter="\t" -----------------
with open("test/c2.csv", "w", newline="") as f:
    writer = csv.writer(f, delimiter="\t")
    writer.writerow(["lastname", "firstname"])
    writer.writerow(["hugo","chang"])
    writer.writerow(["bean","chan"])
    writer.writerow(["gg","yyy"])
"""
lastname	firstname
hugo	chang
bean	chan
gg	yyy
"""

with open("test/c2.csv", "r") as f:
    reader = csv.reader(f, delimiter="\t")
    for row in reader:
        print(row)
"""
['lastname', 'firstname']
['hugo', 'chang']
['bean', 'chan']
['gg', 'yyy']
"""

# ----------------- Chinese -----------------
with open("test/c_utf8.csv", "w", newline="", encoding="utf8") as f:
    writer = csv.writer(f)
    writer.writerow(["lastname", "firstname"])
    writer.writerow(["hugo","chang"])
    writer.writerow(["bean","chan"])
    writer.writerow(["中文","測試"])
"""
lastname,firstname
hugo,chang
bean,chan
中文,測試
"""

with open("test/c_utf8.csv", "r", encoding="utf8") as f:
    reader = csv.reader(f)
    for row in reader:
        print(row)
"""
['lastname', 'firstname']
['hugo', 'chang']
['bean', 'chan']
['中文', '測試']
"""
# ----------------- DictWirter() -----------------
with open("test/c3.csv", "w", newline="") as f:
    fields = ["name", "age", "city"]
    writer = csv.DictWriter(f, fieldnames=fields)
    writer.writeheader()
    writer.writerow({"name":"hugo", "age":"33", "city":"taipei"})
    writer.writerow({"name":"bean", "age":"34", "city":"home"})    
"""
name,age,city
hugo,33,taipei
bean,34,home
"""

with open("test/c3.csv", "r") as f:
    reader = csv.DictReader(f)
    for row in reader:
        print(row)
"""
OrderedDict([('name', 'hugo'), ('age', '33'), ('city', 'taipei')])
OrderedDict([('name', 'bean'), ('age', '34'), ('city', 'home')])
"""
