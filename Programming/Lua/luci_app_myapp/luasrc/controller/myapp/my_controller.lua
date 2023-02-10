function log(msg, ...)
    if pcall(require, "nixio") then
        local nixio = require("nixio")
        nixio.syslog("debug", string.format(msg, ...))
    else
        print(os.date("%x %X").." "..string.format(msg, ...))
    end
end

module("luci.controller.myapp.my_controller", package.seeall)
function index()
	--- view mapping
	entry({"admin", "my_app"}, firstchild(), "my tab", 60).dependent=false
	entry({"admin", "my_app", "cbi_example"}, cbi("myapp/cbi_example"), "CBI example", 1).leaf = true --- need to set leaf as true for passing additional info in http address
	entry({"admin", "my_app", "htm_example"}, template("myapp/htm_example"), "HTML example", 2).leaf = true
	entry({"admin", "my_app", "htm_example2"}, template("myapp/htm_example2"), "HTML example 2", 3).leaf = true

	--- function mapping (log)
	entry({"admin", "my_app", "lua_http_log_demo"}, call("lua_http_log_demo")).leaf = true
	entry({"admin", "my_app", "lua_http_echo"}, call("lua_http_echo")).leaf = true
	
	--- function mapping (input parameters)
	entry({"admin", "my_app", "lua_http_input_array"}, call("lua_http_input_array")).leaf = true
	entry({"admin", "my_app", "lua_http_input_dictionary"}, call("lua_http_input_dictionary")).leaf = true
	entry({"admin", "my_app", "lua_http_input_array_dictionary"}, call("lua_http_input_array_dictionary")).leaf = true
	
	--- function mapping (output parameters)
	entry({"admin", "my_app", "lua_http_return_nil"}, call("lua_http_return_nil")).leaf = true
	entry({"admin", "my_app", "lua_http_return_int"}, call("lua_http_return_int")).leaf = true
	entry({"admin", "my_app", "lua_http_return_string"}, call("lua_http_return_string")).leaf = true
	entry({"admin", "my_app", "lua_http_return_array"}, call("lua_http_return_array")).leaf = true
	entry({"admin", "my_app", "lua_http_return_dictionary"}, call("lua_http_return_dictionary")).leaf = true
end

function lua_http_log_demo()
	log("myapp lua_http_log_demo()")
	log("myapp log demo 1 %d %f %s", 123, 456.789, "hello")
	log("myapp log demo 2 %s %d %f",
		tostring(nil), tonumber("987"), tonumber("111.222"))
end

function lua_http_echo(data)
	log("myapp lua_http_echo() data=%s", tostring(data))
	luci.http.write_json(data)
end

function lua_http_input_array(data1, data2, data3)
	--- input parameters could be nil or string
	log("myapp lua_http_input_array() data1=%s data2=%s data3=%s", tostring(data1), tostring(data2), tostring(data3))
end

function lua_http_input_dictionary()
	---luci.http.formvalue() could be nil or string type
	local d1 = luci.http.formvalue("k1")
	local d2 = luci.http.formvalue("k2")
	log("myapp lua_http_input_dictionary() d1=%s type=%s", tostring(d1), type(d1))
	log("myapp lua_http_input_dictionary() d2=%s type=%s", tostring(d2), type(d2))
end

function lua_http_input_array_dictionary(data1, data2, data3)
	local d1 = luci.http.formvalue("k1")
	local d2 = luci.http.formvalue("k2")
	log("myapp lua_http_input_array_dictionary() data1=%s data2=%s data3=%s d1=%s d2=%s",
		tostring(data1), tostring(data2), tostring(data3), tostring(d1), tostring(d2))
end

function lua_http_return_nil()
	log("myapp lua_http_return_nil()")
	luci.http.write_json()
	--- same as luci.http.write_json(nil)
end

function lua_http_return_int()
	log("myapp lua_http_return_int()")
	luci.http.write_json(123)
end

function lua_http_return_string()
	log("myapp lua_http_return_string()")
	luci.http.write_json("123")
end

function lua_http_return_array()
	log("myapp lua_http_return_array()")
	local ret = {1, 2, 3, "hello", 45.67, {11, 22}, nil, "world"}
	luci.http.write_json(ret)
end

function lua_http_return_dictionary(data)
	log("myapp lua_http_return_dictionary()")
	local ret = {}
	ret["a1"] = 1
	ret["a2"] = "hello"
	ret["a3"] = 123.456
	ret["a4"] = nil
	ret["a5"] = {}
	ret["a6"] = {}
	ret["a6"]["b1"] = 2
	ret["a6"]["b2"] = "world"
	luci.http.write_json(ret)
end
