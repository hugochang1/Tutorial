----------------- io.open -----------------
local fd = io.open("/etc/config", "r")
if not fd then
    print("io.open() failed")
else
    print("io.open() success")
    fd:close()
end
