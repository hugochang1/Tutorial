# ----------------- compile -----------------
import re

msg = """aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""

rule = re.compile(r"\d\d\d\d-\d\d\d-\d\d\d")
ret = rule.search(msg)
print(ret)
# <_sre.SRE_Match object; span=(19, 31), match='0912-345-678'>

print(ret.group())
# 0912-345-678

msg = "hello world"
ret = rule.search(msg)
print(ret)
# None

# ----------------- findall -----------------
msg = """aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""

rule = re.compile(r"\d\d\d\d-\d\d\d-\d\d\d")
ret = rule.findall(msg)
print(ret)
# ['0912-345-678', '1234-456-789', '0987-654-321']


rule = re.compile(r"\d{4}-\d{3}-\d{3}")
ret = rule.findall(msg)
print(ret)
# ['0912-345-678', '1234-456-789', '0987-654-321']

# ----------------- re.search -----------------

msg =  """aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""

ret = re.search(r"\d{4}-\d{3}-\d{3}", msg)
print(ret)
# <_sre.SRE_Match object; span=(19, 31), match='0912-345-678'>
print(ret.group())
# 0912-345-678
print(ret.groups())
# ()
print(ret.start())
# 19
print(ret.end())
# 31
print(ret.span())
# (19, 31)

# ----------------- re.findall -----------------
msg =  """aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""

ret = re.findall(r"\d{4}-\d{3}-\d{3}", msg)
print(ret)
# ['0912-345-678', '1234-456-789', '0987-654-321']

# ----------------- re.finditer -----------------
msg =  """aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""

ret = re.finditer(r"\d{4}-\d{3}-\d{3}", msg)
print(ret)
# <callable_iterator object at 0x000000000A464630>
for a in ret:
    print(a)
"""
<_sre.SRE_Match object; span=(19, 31), match='0912-345-678'>
<_sre.SRE_Match object; span=(46, 58), match='1234-456-789'>
<_sre.SRE_Match object; span=(67, 79), match='0987-654-321'>
"""

# ----------------- re.match -----------------
msg =  """0912-345-678 aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""

ret = re.match(r"\d{4}-\d{3}-\d{3}", msg)
print(ret)
# <_sre.SRE_Match object; span=(0, 12), match='0912-345-678'>
print(ret.group())
# 0912-345-678
print(ret.start())
# 0
print(ret.end())
# 12
print(ret.span())
# (0, 12)

msg =  """aaaabbbb000111234, 0912-345-678, 1234-456-44, 1234-456-789
    aaaa0987-654-321,,,,,,,"""
ret = re.match(r"\d{4}-\d{3}-\d{3}", msg)
print(ret)
# None

# ----------------- group -----------------
# r"\d\d-\d\d\d\d"
# r"\d{2}-\d{4}"
# r"(\d{2})-(\d{4})" -> group

msg = "asdfasdfasdf 02-1234 basdfa"
num = re.search(r"(\d{2})-(\d{4})", msg)
print(num)
# <_sre.SRE_Match object; span=(13, 20), match='02-1234'>
print(num.group())
# 02-1234
print(num.group(0))
# 02-1234
print(num.group(1))
# 02
print(num.group(2))
# 1234
print(num.groups())
# ('02', '1234')

msg = "asdfasdfasdf 02-1234 basdfa"
num = re.findall(r"(\d{2})-(\d{4})", msg)
print(num)
# [('02', '1234')]

# ----------------- or -----------------
msg = "aaa bbb ccc ddd bbb aaa"
ret = re.findall("aaa|bbb", msg)
print(ret)
# ['aaa', 'bbb', 'bbb', 'aaa']

msg = "aaabbb aaaccc aaaddd aaaeee aaaccc bbbccc"
ret = re.findall("aaa(bbb|ccc|eee)", msg)
print(ret)
# ['bbb', 'ccc', 'eee', 'ccc']

msg = "aaabbb aaaccc aaaddd aaaeee aaaccc"
ret = re.search("aaa(bbb|ccc|eee)", msg)
print(ret)
# <_sre.SRE_Match object; span=(0, 6), match='aaabbb'>
print(ret.group())
# aaabbb
print(ret.group())
# aaabbb
print(ret.group(1))
# bbb

# ----------------- zero or once -----------------
msg = "aaa abc aebc"
ret = re.search("a((e)?bc)", msg)
print(ret.group())
# abc
print(ret.group(1))
# bc

msg = "aaa aebc"
ret = re.search("a((e)?bc)", msg)
print(ret.group())
# aebc
print(ret.group(1))
# ebc

# ----------------- more than zero times -----------------
msg = "aaa abc"
ret = re.search("a((e)*bc)", msg)
print(ret.group())
# abc
print(ret.group(1))
# bc

msg = "aaa aeeeeeeeeebc"
ret = re.search("a((e)*bc)", msg)
print(ret.group())
# aeeeeeeeeebc
print(ret.group(1))
# eeeeeeeeebc

# ----------------- more than one time -----------------
msg = "aaa abc"
ret = re.search("a((e)+bc)", msg)
print(ret)
# None

msg = "aaa aebc"
ret = re.search("a((e)+bc)", msg)
print(ret.group())
# aebc
print(ret.group(1))
# ebc

# ----------------- case-insensitive -----------------
msg = "aAa bBb CCC def"
ret = re.findall("aaa|bbb|ccc", msg, re.I)
print(ret)
# ['aAa', 'bBb', 'CCC']

ret = re.findall("aaa|bbb|ccc", msg)
print(ret)
# []

# ----------------- specific times match -----------------
#greedy search, will match as more as possible
pattern = "(ab){1,2}"
print(re.findall(pattern, "ab"))
# ['ab']
print(re.findall(pattern, "abab"))
# ['ab']
print(re.findall(pattern, "ababab"))
# ['ab', 'ab']
print(re.findall(pattern, "abababab"))
# ['ab', 'ab']
print(re.findall(pattern, "ababababab"))
# ['ab', 'ab', 'ab']
print(re.findall(pattern, "abababababab"))
# ['ab', 'ab', 'ab']

#non-greedy search, will match as less as possible
pattern = "(ab){1,2}?"
print(re.findall(pattern, "ab"))
# ['ab']
print(re.findall(pattern, "abab"))
# ['ab', 'ab']
print(re.findall(pattern, "ababab"))
# ['ab', 'ab', 'ab']
print(re.findall(pattern, "abababab"))
# ['ab', 'ab', 'ab', 'ab']
print(re.findall(pattern, "ababababab"))
# ['ab', 'ab', 'ab', 'ab', 'ab']
print(re.findall(pattern, "abababababab"))
# ['ab', 'ab', 'ab', 'ab', 'ab', 'ab']

# ----------------- special characters -----------------
# \\d [0-9] 
# \\D except [0-9] 
# \\s space, tab, new line, next page 
# \\S except \s 
# \\w [0-9A-Za-z] 
# \\W except [0-9A-Za-z] 
# \w+ 至少長度1由數字, 字母, 或底線的連續字串 
# \d+ 不限長度的數字

msg = "  abcd_efghABC mmdd __a_c__"
print(re.findall("\w+", msg))
# ['abcd_efghABC', 'mmdd', '__a_c__']

msg = " aabcd aadef, aaccc aa bb"
print(re.findall("aa\w*", msg))
# ['aabcd', 'aadef', 'aaccc', 'aa']

# ----------------- clarifiction -----------------
# [a-z]
# [A-Z]
# [0-9]

msg = "abcdefghijklmnopqrstuvwxyz"
print(re.findall("[c-i]", msg))
# ['c', 'd', 'e', 'f', 'g', 'h', 'i']

msg = "0123456789.!@#$%"
print(re.findall("[3-6]", msg))
# ['3', '4', '5', '6']

msg = "0123456789.!@#$%"
print(re.findall("[3-6.@]", msg))
# ['3', '4', '5', '6', '.', '@']

# ----------------- ^ in clarification -----------------
msg = "0123456789"
print(re.findall("[^3-6]", msg))
# ['0', '1', '2', '7', '8', '9']

# ----------------- begin with -----------------
msg = "abcdefg"
print(re.findall("^abc", msg))
# ['abc']

msg = "bcdefg"
print(re.findall("^abc", msg))
# []

# ----------------- end with -----------------
msg = "aaabbbcccxyz"
print(re.findall("xyz$", msg))
# ['xyz']

msg = "aaabbbcccxy"
print(re.findall("xyz$", msg))
# []

# ----------------- wildcard -----------------
msg = "cat hat sat at matter flat"
print(re.findall(".at", msg))
# ['cat', 'hat', 'sat', ' at', 'mat', 'lat']

msg = "name: hugo chang address: 4f, xihiz new taipei city"
print(re.search("name: (.*) address: (.*) ", msg).groups())
# ('hugo chang', '4f, xihiz new taipei')

# ----------------- .* with new line -----------------
msg = """abcdef
abcddd
abbbb
abcxyz"""
print(re.findall(".*", msg))
# ['abcdef', '', 'abcddd', '', 'abbbb', '', 'abcxyz', '']

print(re.findall(".*", msg, re.DOTALL))
# ['abcdef\nabcddd\nabbbb\nabcxyz', '']

# ----------------- substitute-----------------
msg = "aaa bbb ccc aaa ddd aaa"
pattern = r"aaa"
newstr = r"zzz"
print(re.sub(pattern, newstr, msg))
# zzz bbb ccc zzz ddd zzz

msg = "000 abc 111"
pattern = r"(a)(b)(c)"
newstr = r"\0zzz"
print(re.sub(pattern, newstr, msg))
# 000 zzz 111

newstr = r"\1zzz"
print(re.sub(pattern, newstr, msg))
# 000 azzz 111

newstr = r"\2zzz"
print(re.sub(pattern, newstr, msg))
# 000 bzzz 111

newstr = r"\3zzz"
print(re.sub(pattern, newstr, msg))
# 000 czzz 111

try:
    newstr = r"\4zzz"
    print(re.sub(pattern, newstr, msg))
except Exception as err:
    print(err)
    # invalid group reference 4 at position 1

# ----------------- re.VERBOSE -----------------
#if you want to use some comment on your regular expression, then you need to use re.VERBOSE
msg = "aa@gmail.com.tw bb@pmail.com"
pattern = r'''(
        [a-zA-Z0-9_.]+
        @
        [a-zA-Z0-9-.]+
        \.
        [a-zA-Z]{2,4}
        \.?
        ([a-zA-Z]{2,4})?
        )'''

print(re.findall(pattern, msg))
# []
print(re.findall(pattern, msg, re.VERBOSE))
# [('aa@gmail.com.tw', ''), ('bb@pmail.com', '')]

# ----------------- re.IGNORECASE re.DOTALL re.VERBOSE -----------------
msg = "aa@gmail.com.tw bb@pmail.com"
pattern = r'''(
        [a-zA-Z0-9_.]+
        @
        [a-zA-Z0-9-.]+
        \.
        [a-zA-Z]{2,4}
        \.?
        ([a-zA-Z]{2,4})?
        )'''

print(re.findall(pattern, msg, re.VERBOSE | re.IGNORECASE | re.DOTALL))
# [('aa@gmail.com.tw', ''), ('bb@pmail.com', '')]
