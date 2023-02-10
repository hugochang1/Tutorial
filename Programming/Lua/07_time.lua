----------- sleep -----------
function sleep_busy(n)
    local t = os.clock() + n
    repeat until os.clock() > t
end

function sleep_linux(n)
    os.execute("sleep "..n)
end

print("start", os.clock())  -- start	0.0
sleep_busy(1.5)
print("end1", os.clock())  -- end1	1.51
sleep_linux(1.5)
print("end2", os.clock())  -- end2	3.02

----------- other -----------
