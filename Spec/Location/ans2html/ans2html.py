import os
import sys
import time

def ExtractDefinition(line):
    return line.split('::=')[0].split(' ')[0]

def ParseASN(asn):
    items = []
    for line in open(asn):
        line = line.strip()
        if '::=' in line:
            items.append(ExtractDefinition(line))
    return items

def IsValidChar(chr):
    if chr.isalnum(): return True
    if chr == '-': return True
    return False

def HasItem(line, item):
    begin = 0
    while True:
        begin = line.find(item, begin)
        if begin == -1: return -1
        if begin > 1 and IsValidChar(line[begin-1]):
            # not this one.
            begin += len(item)
            continue
        else:
            # found the item.
            break
    end = begin + len(item)
    if end < len(line) and IsValidChar(line[end]): return -1
    return begin

def ModifyHtml(html, items):
    f = open(html + '.link.html', 'w')
    f.write("<!doctype html>\n<html>\n  <head>\n    <title></title>\n    <style type=\"text/css\">\n      pre{\n        background-color:white;\n        font-family:Consolas\n      }\n    </style>\n  </head>\n<body><pre>\n");
    for line in open(html):
        #line = line.strip()
        if '::=' in line:
            line = InsertAnchor(line, items)
        else:
            line = InsertLink(line, items)
        if '--' in line:
            line = InsertComment(line)
        f.write('%s' % line)
    f.write("</pre></body>\n</html>");

def InsertAnchor(line, items):
    for item in items:
        ret = HasItem(line, item)
        if ret >= 0:
            line = line[:ret] + '<a name="%s"><font color="DarkViolet"><b>%s</b></font></a>' % (item, item) + line[ret+len(item):]
            #line = line.replace(item, '<a name="%s">%s</a>' % (item, item))
            break
    return line

def InsertLink(line, items):
    for item in items:
        ret = HasItem(line, item)
        if ret >= 0:
            #print line
            #print ret
            line = line[:ret] + '<a href="#%s">%s</a>' % (item, item) + line[ret+len(item):]
            #line = line.replace(item, '<a href="#%s">%s</a>' % (item, item))
    return line

def InsertComment(line):
    pos = line.find("--")
    if pos >=0:
        line = line[:pos] + '<font color="green"><i>' + line[pos:] + '</i></font>'
    return line

if __name__ == '__main__':
    items = ParseASN(sys.argv[1])
    ModifyHtml(sys.argv[1], items)

    #test = r'&nbsp;&nbsp;&nbsp;&nbsp;message&nbsp;&nbsp;[<font color="#ffa0a0">3</font>] <font color="#40ffff">EXPLICIT</font>&nbsp;UlpMessage<br>'
    #print HasItem(test, 'UlpMessage')
