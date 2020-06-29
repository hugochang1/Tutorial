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

----------------- shell command line by using io.popen -----------------
local dir = io.popen("ls /") -- user data
for line in dir:lines() do
  print(line)
end

--[[
bin
dev
etc
...
--]]

----------------- other -----------------
