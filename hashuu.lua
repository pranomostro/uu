#!/usr/bin/env lua

--probably use a better hashing algorithm
--or at least do some research

function hash(str)
	local h, i
	h=128
	for i=1, #str do
		h=h*string.byte(str, i)+i
	end
	return h/string.byte(str, math.ceil(#str/2))
end

local c=io.read()
local tab={}

while c ~= nil do
	if tab[hash(c)]==nil then
		print(c)
		tab[hash(c)]=1
	end
	c=io.read()
end
