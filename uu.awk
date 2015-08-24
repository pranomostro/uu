#!/usr/bin/awk -f

{ 
	if(a[$0]==0)
		{ print($0); a[$0]=1; }
}
