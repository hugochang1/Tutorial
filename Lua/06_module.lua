----------------- require module -----------------
tabledump = require("tabledump")
tabledump.dump({aaa="123", bbb="456", ccc="789"})

--[[
{
    ['aaa'] = '123',
    ['ccc'] = '789',
    ['bbb'] = '456'
}
--]]

----------------- other -----------------
