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

tabledump.dump(tabledump)
--[[
{
    ['a2'] = 2,
    ['s1'] = 'hello',
    ['dump'] = 'function: 0x1c309a0',
    ['a1'] = 1
}
--]]

----------------- use pcall() to check whether specific module exsits -----------------
function require_module_if_exists(module_name)
    if pcall(require, module_name) then
        return require(module_name)
    else
        return nil
    end
end

print(require_module_if_exists("io"))  -- table: 0x1242020
print(require_module_if_exists("io2"))  -- nil

----------------- other -----------------
