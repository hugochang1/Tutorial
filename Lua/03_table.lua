----------- array -----------
local arr = {1, 2, 3}
print(arr) -- 0x112e040
print(type(arr)) -- table
print(arr[0], arr[1], arr[2]) -- nil	1	2
print(#arr) -- the length of arr, 3

-- traversal
for i, e in ipairs(arr) do
    print(e)
end

for i = 1, #arr do
    print(arr[i])
end

-- insert
table.insert(arr, "f")
assert(arr[4] == "f")

arr[#arr+1] = "g"
assert(arr[5] == "g")

-- remove
local data = table.remove(arr) -- remove the last one
print(data) -- "g"

local data = table.remove(arr, 1) -- remove the first one
print(data) -- 1

for i = 1, #arr do
    print(arr[i])  -- 2, 3, f
end

-- dump
tabledump = require("tabledump")
tabledump.dump(arr)
--[[
{
    [1] = 2,
    [2] = 3,
    [3] = 'f'
}
--]]

----------- key/value -----------
local dict = {one=1, two=2, three=3}

-- add
dict["four"] = "gg"

assert(dict["one"] == 1)
assert(dict["four"] == "gg")
assert(dict["five"] == nil)

-- traversal
for k, v in pairs(dict) do
    print(k, v)
end

-- remove
dict["three"] = nil

-- dump
tabledump = require("tabledump")
tabledump.dump(dict)
--[[
{
    ['four'] = 'gg',
    ['one'] = 1,
    ['two'] = 2
}
--]]
