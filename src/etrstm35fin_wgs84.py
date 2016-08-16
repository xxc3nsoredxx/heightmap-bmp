#!/usr/bin/python

from coordinates import ETRSTM35FINxy_to_WGS84lalo
from sys import argv

if (len(argv) < 3):
	print ('Too few arguments')
	print ('Enter coordinates as <N> <E>')
	print ('For example, coordinates N12345 E67890 would be entered as 12345 67890')
	exit (-1)

dict_in = {
	'N': float (argv[1]),
	'E': float (argv[2])
}

dict_out = ETRSTM35FINxy_to_WGS84lalo (dict_in)

print ('Lat:', dict_out['La'])
print ('Lon:', dict_out['Lo'])
