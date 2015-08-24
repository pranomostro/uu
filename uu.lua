#!/usr/bin/env lua

local c=io.read()
local tab={}

while c ~= nil do
	if tab[c]==nil then
		print(c)
		tab[c]=1
	end
	c=io.read()
end
