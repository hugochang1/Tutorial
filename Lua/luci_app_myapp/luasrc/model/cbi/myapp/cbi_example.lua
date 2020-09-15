m = Map("cbi_file", translate("First Tab Form"), translate("Please fill out the form below"))
d = m:section(TypedSection, "info", "Part A of the form")
a = d:option(Value, "name", "Name"); a.optional=false; a.rmempty = false;
return m
