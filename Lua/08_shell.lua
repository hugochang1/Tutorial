----------------- send command only -----------------
os.execute("mkdir myfolder")

----------------- send command and get result -----------------
function shell_command(command)
    local fp = io.popen(command)
    local txt = fp:read("*a")
    fp:close()
    return txt
end

a = shell_command("ls /")
print(a)
--[[
bin
dev
etc
...
--]]

----------------- other -----------------
