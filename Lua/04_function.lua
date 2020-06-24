------------------ parameters ------------------
function f1(a1, a2, a3)
    print(a1, a2, a3)
end

f1()           -- nil, nil, nil
f1(1)          -- 1, nil, nil
f1(1, 2)       -- 1, 2, nil
f1(1, 2, 3)    -- 1, 2, 3
f1(1, 2, 3, 4) -- 1, 2, 3

------------------ return ------------------
function f1()
end
a = f1()
print(type(a)) -- nil
print(a)       -- nil

function f1()
    return 1
end
f1()
a = f1()
print(a)    -- 1
a, b = f1()
print(a, b)  -- 1  nil

function f1()
    return 1, 2, "abc"
end
a = f1()
print(a)    -- 1
a, b = f1()
print(a, b)  -- 1  2
a, b, c = f1()
print(a, b, c)  -- 1  2  abc
a, b, c, d = f1()
print(a, b, c, d)  -- 1  2  abc  nil

------------------ arbitrary argument ------------------
function f3(...)
    for i, e in ipairs{...} do
        print(e)
    end
end

f3(1, 2, "gg")


------------------ use table as argument ------------------
function f4(a)
    print(a.a1, a.a2) -- data1 data2
end

f4{a1="data1", a2="data2"}
