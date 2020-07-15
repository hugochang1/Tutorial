mydump = require("mydump")


function f1()
    print("f1")
end

arr = {
    true,
    false,
    1,
    2,
    nil,
    "aaa",
    f1,
    {
        1,
        2,
        true,
        false,
        "bbb",
        f1,
    },
    "bbb",
    {},
    {
        false,
        f1,
        nil,
        "ccc",
    },
}

d = {
    ["a1"]=true,
    ["a2"]=false,
    ["a3"]=1,
    ["a4"]=2,
    ["a5"]=nil,
    ["a6"]="ddd",
    ["a7"]=f1,
    ["a8"]={
    },
    ["a9"]={
        1
    },
    ["a10"]={
        1,
        nil,
        2,
        true,
        false,
        "aaa",
        f1,
    },
    ["a11"]={
        ["b1"]=1,
        ["b2"]=2,
        ["b3"]=true,
        ["b4"]=false,
        ["b5"]=f1,
        ["b6"]="eee",
        ["b7"]=nil,
        ["b8"]={
            {
                1,2,3,{
                    ["c1"]=1,
                    ["c2"]=2,
                    ["c3"]=true,
                    ["c4"]=false,
                    ["c5"]=f1,
                    ["c6"]="ffff",
                }
            }
        },
    }
}

mydump.print(nil)
mydump.print(1.111)
mydump.print("abc")
mydump.print(f1)
mydump.print({})
mydump.print(arr)
mydump.print(d)
