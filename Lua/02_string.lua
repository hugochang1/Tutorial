-- http://lua-users.org/wiki/StringLibraryTutorial

------- string.len(s), s:len() -------
print(string.len("abc")) -- 3
print(string.len("")) -- 0

------- string.rep(s, n), s:rep(n) -------
print(string.rep("Lua", 3))  -- LuaLuaLua

------- string.reverse(s), s:reverse() -------
print(string.reverse("lua")) -- aul

------- sstring.sub(s, i [, j]), s:sub(i [,j]) -------
print(string.sub("Hello Lua user", 7))      -- from character 7 including 7 until the end)
-- Lua user
print(string.sub("Hello Lua user", 7, 9))   -- from character 7 until and including 9)
-- Lua
print(string.sub("Hello Lua user", -4))     -- 4 from the end until the end
-- user
print(string.sub("Hello Lua user", -4, -2)) -- 4 from the end until 1 from the end
-- use

------- string.upper(s), s:upper() -------
print(string.upper("AbcD")) -- ABCD

------- string.lower(s), s:lower() -------
print(string.lower("AbcD")) -- abcd

------- string.byte(s [, i [, j]]), s:byte([i [, j]]) -------
print(string.byte("ABCDE"))      -- no index, so the First character 65
print(string.byte("ABCDE",1))    -- indexes start at 1, 65
print(string.byte("ABCDE",100))  -- index out of range, no value returned
print(string.byte("ABCDE",3,4))  -- 67  68

------- string.char(i1, i2, ...) -------
print(string.char(65,66,67))  -- ABC
print(string.char())  -- empty string

------- string.find(s, pattern [, index [, plain]]), s:find(pattern [, index [, plain]]) -------
-- finds the first occurrence of a pattern in a string
-- returns start and end indices of the first and last characters that matched the text
print(string.find("banana", "an"))  -- 2  3
print(string.find("banana", "lua")) -- nil

------- string.match (s, pattern [, index]), s:match(pattern [, index]) -------
-- It returns the matched text, or nil if the pattern is not found
print(string.match("abcdefg", 'b..')) -- bcd
print(string.match("abcdefg", '123')) -- nil

------- string.format(s, e1, e2, ...), s:format(e1, e2, ...) -------
print(string.format("%s %q", "Hello", "Lua user!"))   -- Hello "Lua user!"
print(string.format("%c%c%c", 76, 117, 97))           -- Lua
print(string.format("%e, %E", math.pi, math.pi))      -- 3.141593e+000, 3.141593E+000
print(string.format("%f", math.pi))                   -- 3.141593
print(string.format("%g, %g", math.pi, 10^9))         -- 3.14159, 1e+09
print(string.format("%d, %i, %u", -100, -100, -100))  -- -100, -100, 4294967196
print(string.format("%o, %x, %X", -100, -100, -100))  -- 37777777634, ffffff9c, FFFFFF9C

------- string.gmatch(s, pattern), s:gmatch(pattern) -------
-- This returns a pattern finding iterator. The iterator will search through the string passed looking for instances of the pattern you passed.
for word in string.gmatch("hello world in Lua", "%a+") do
    print(word)
end
--[[
hello
world
in
Lua
--]]

------- string.gsub(s, pattern, replace [, n]), s:gsub(pattern, replace [,n]) -------
--replace all instances of the pattern provided with the replacement
--A pair of values is returned, the modified string and the number of substitutions made
--The optional fourth argument n can be used to limit the number of substitutions made
print(string.gsub("Hello banana", "banana", "Lua user"))  -- Hello Lua user	1
print(string.gsub("banana", "a", "A", 2))  -- bAnAna  2

print(string.gsub("banana", "(an)", "%1-"))    -- capture any occurences of "an" and replace)
-- ban-an-a	2

print(string.gsub("banana", "a(n)", "a(%1)"))  -- brackets around n's which follow a's
-- ba(n)a(n)a      2

print(string.gsub("banana", "(a)(n)", "%2%1"))  -- reverse any "an"s
-- bnanaa  2

--If the replacement is a function, not a string, the arguments passed to 
--the function are any captures that are made. If the function returns a string,
--the value returned is substituted back into the string.

print(string.gsub("Hello Lua user", "(%w+)", print)) -- print any words found
--[[
Hello
Lua
user
Hello Lua user	3
--]]

print(string.gsub("Hello Lua user", "(%w+)", function(w) return string.len(w) end))  -- replace with lengths
-- 5 3 4	3

print(string.gsub("banana", "(a)", string.upper))  -- make all "a"s found uppercase
-- bAnAnA	3

print(string.gsub("banana", "(a)(n)", function(a,b) return b..a end))  -- reverse any "an"s
-- bnanaa  2


-------------------------- split --------------------------
function mysplit(inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local t={}
    for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
        table.insert(t, str)
    end
    return t
end

a = mysplit("aaa.1.23a", ".")
print(a) -- table: 0x1137f30
tabledump = require("tabledump")
tabledump.dump(a)
--[[
{
    [1] = 'aaa',
    [2] = '1',
    [3] = '23a'
}
--]]

-------------------------- trim --------------------------
function mytrim(s)
    if s then return (s:gsub("^%s*(.-)%s*$", "%1")) end
end

s = "  abc  "
print(s)  --   abc  
print(mytrim("  abc  "))  -- abc

-------------------------- str2table --------------------------
function str2table(str)
    local t = {}
    for line in str:gmatch("(.-)\r?\n") do
        table.insert(t, line)
    end
    return t
end

s = "aaa\nbbb\r\nddd\n"
a = str2table(s)
tabledump = require("tabledump")
tabledump.dump(a)
--[[
{
    [1] = 'aaa',
    [2] = 'bbb',
    [3] = 'ddd'
}
--]]
-------------------------- others --------------------------

