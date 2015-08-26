#!/usr/bin/env lua

function hash(str)
	local h, i
	h=128
	for i=1, #str do
		h=h*string.byte(str, i)+i
	end
	return bit32.bxor(h, string.byte(str, math.ceil(#str/2)))
end

local c=io.read()

while c ~= nil do
	print(hash(c), c)
	c=io.read()
end
