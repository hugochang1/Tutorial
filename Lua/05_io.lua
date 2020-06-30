----------------- io.open -----------------
local fd = io.open("/etc/config", "r")
if not fd then
    print("io.open() failed")
else
    print("io.open() success")
    fd:close()
end

----------------- is_file_or_folder_exists -----------------
function is_file_or_folder_exists(path)
    local fp = io.open(path, "r")
    if fp then fp:close() end
    return fp ~= nil
end

print(is_file_or_folder_exists("/usr")) -- true
print(is_file_or_folder_exists("/usr2")) -- false

----------------- read file -----------------
function file_read(path)
    local fd = io.open(path, "r")
    if not fd then return end
    local content = fd:read("*all")
    fd:close()
    return content
end

a = file_read("aaaaaaaaaaa")
print(a)  -- nil

a = file_read("/etc/BUILDTIME")
print(a)  -- 20151215_1554

----------------- other -----------------


