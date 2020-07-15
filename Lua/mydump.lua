local mydump = {}

function mydump.__table_get_dump_string(data, space, newline, indent)
    local output = ""
    
    for k,v in pairs(data) do
        output = output..string.rep(space, indent)
        
        -- dump key
        if(type(k) == "number" or type(k) == "boolean") then
            output = output.."["..tostring(k).."]="
        else
            output = output.."['"..tostring(k).."']="
        end
        
        -- dump value
        if(type(v) ~= "table") then
            if(type(v) == "string") then
                output = output.."'"..v.."'"..","..newline
            else
                output = output..tostring(v)..","..newline
            end
        else
            output = output.."{"..newline
            output = output..mydump.__table_get_dump_string(v, space, newline, indent+2)
            output = output..string.rep(space, indent).."},"..newline
        end
    end
    
    return output
end

function mydump.get_dump_string(data, space, newline)
    if(space == nil) then
        space = " "
    end
    if(newline == nil) then
        newline = "\n"
    end
    
    local output = ""
    
    if(type(data) ~= "table") then
        output = tostring(data)
    else
        output = output.."{"..newline
        output = output..mydump.__table_get_dump_string(data, space, newline, 2)
        output = output.."}"
    end
    return output
end

function mydump.print(data, space, newline)
    print(mydump.get_dump_string(data, space, newline))
end

return mydump
