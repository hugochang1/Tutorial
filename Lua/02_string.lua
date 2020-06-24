tabledump = require("tabledump")
--------------------------  --------------------------

-------------------------- APIs --------------------------
a = "aBc"
print(string.upper(a))  -- ABC
print(string.lower(a))  -- abc


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
tabledump.dump(a)
--[[
{
    [1] = 'aaa',
    [2] = '1',
    [3] = '23a'
}
--]]
-------------------------- others --------------------------

