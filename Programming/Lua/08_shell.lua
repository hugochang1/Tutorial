----------------- send command only -----------------
os.execute("mkdir myfolder")

----------------- send command and get result -----------------
function shell_command(command)
	local retry_count = 10
	local fp, txt, err
	repeat
		fp = io.popen(command)
		txt, err = fp:read("*a")
		fp:close()
		retry_count = retry_count - 1
	until err == nil or retry_count == 0
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
