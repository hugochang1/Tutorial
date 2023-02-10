: How to disable the cached to ensure Lua related modifications can be applied without rebooting the device
adb shell uci set luci.ccache.enable=0
adb shell uci commit luci

: How to enable WebUI via USB
adb shell uci set network.lan.ifname="usb0"
adb shell uci commit network
adb shell reload_config

adb shell mkdir /usr/lib/lua/luci/controller/myapp/
adb shell mkdir /usr/lib/lua/luci/view/myapp/
adb shell mkdir /usr/lib/lua/luci/model/cbi/myapp/

: comment Lua module must push to /usr/lib/lua/
adb push root/usr/lib/lua/mydump.lua  /usr/lib/lua/

adb push luasrc/controller/myapp/my_controller.lua  /usr/lib/lua/luci/controller/myapp/

cd luasrc/view/myapp
adb push . /usr/lib/lua/luci/view/myapp/
cd ../../..

adb push luasrc/model/cbi/myapp/cbi_example.lua  /usr/lib/lua/luci/model/cbi/myapp/

adb push root/etc/config/cbi_file  /etc/config/

: comment LuaC must push to /usr/lib/lua/
adb push Y:\openwrt\build_dir\<tool_chain>\luci-app-myapp\ipkg-all\luci-app-myapp\usr\lib\lua\my_app.so /usr/lib/lua/

pause
