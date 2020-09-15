#include <syslog.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int c_input_test1(lua_State* L) {
	syslog(0, "myapp c_input_test1");
	return 0;
}

static int c_input_test2(lua_State* L) {
	int int1 = luaL_checknumber(L, 1);
	const char *str1 = luaL_checkstring(L, 2);
	const char *str2 = luaL_checkstring(L, 3);
	syslog(0, "myapp c_input_test2 int1=[%d] str1=[%s] str2=[%s]", int1, str1, str2);
	return 0;
}

static int c_output_test1(lua_State* L) {
	lua_pushnil(L);
	lua_pushnumber(L, 1234567890);
	lua_pushstring(L, "hello");
	//c_output_test1() ret=	nil	ret2=	1234567890	ret3=	hello
	return 3;
}

static int c_output_test2(lua_State* L) {
	lua_newtable(L);
	
	lua_pushstring(L, "key1");
	lua_pushstring(L, "value1"); 
	lua_settable(L, -3);
	//c_output_test2() ret=	{ ['key1']='value1', }
	return 1;
}

static int c_output_test3(lua_State* L) {
	lua_newtable(L);
	
	lua_pushstring(L, "key1");
	lua_pushstring(L, "value1"); 
	lua_settable(L, -3);
	lua_pushstring(L, "key2");
	lua_pushstring(L, "value2"); 
	lua_settable(L, -3);
	lua_pushstring(L, "key3");
	lua_pushstring(L, "value3"); 
	lua_settable(L, -3);
	//c_output_test3() ret=	{ ['key1']='value1', ['key3']='value3', ['key2']='value2', }
	return 1;
}

static int c_output_test4(lua_State* L) {
	lua_createtable(L, 0, 3);
	
	lua_pushstring(L, "value1");
	lua_setfield(L, -2, "key1");
	lua_pushstring(L, "value2");
	lua_setfield(L, -2, "key2");
	lua_pushstring(L, "value3");
	lua_setfield(L, -2, "key3");
	//c_output_test4() ret=	{ ['key1']='value1', ['key3']='value3', ['key2']='value2', }
	return 1;
}

static int c_output_test5(lua_State* L) {
	lua_createtable(L, 3, 0);
	
	lua_pushnumber(L, 1);
	lua_pushstring(L, "value1");
	lua_settable(L, -3);
	lua_pushnumber(L, 2);
	lua_pushstring(L, "value2");
	lua_settable(L, -3);
	lua_pushnumber(L, 3);
	lua_pushstring(L, "value3");
	lua_settable(L, -3);
	//c_output_test5() ret=	{ [1]='value1', [2]='value2', [3]='value3', }
	return 1;
}

static int c_output_test6(lua_State* L) {
	lua_createtable(L, 3, 0);
	
	lua_pushnumber(L, 1);
	lua_createtable(L, 0, 2);
	lua_settable(L, -3);
	
	lua_pushnumber(L, 2);
	lua_createtable(L, 0, 2);
	lua_pushstring(L, "vv2");
	lua_setfield(L, -2, "kk1");
	lua_pushstring(L, "vv2");
	lua_setfield(L, -2, "kk2");
	lua_settable(L, -3);
	
	lua_pushnumber(L, 3);
	lua_pushstring(L, "value3");
	lua_settable(L, -3);
	//c_output_test6() ret=	{ [1]={ }, [2]={ ['kk2']='vv2', ['kk1']='vv1', }, [3]='value3', }
	return 1;
}

// luaopen_<shared_library_name>()
int luaopen_my_app(lua_State *L) {
	lua_register(L, "c_input_test1", c_input_test1);
	lua_register(L, "c_input_test2", c_input_test2);
	lua_register(L, "c_output_test1", c_output_test1);
	lua_register(L, "c_output_test2", c_output_test2);
	lua_register(L, "c_output_test3", c_output_test3);
	lua_register(L, "c_output_test4", c_output_test4);
	lua_register(L, "c_output_test5", c_output_test5);
	lua_register(L, "c_output_test6", c_output_test6);
	return 0;
}
