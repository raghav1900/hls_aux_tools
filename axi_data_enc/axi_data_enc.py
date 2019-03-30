# A python script that serialises a bunch of variables in a csv file
# into AXI messages and vice-versa.
# Author: Raghav Subbaraman
# Date: 29 March 2019
# License: MIT
# Changelog: 
#	29 March 2019: File created
#
#
#

from optparse import OptionParser
import time
from sys import stderr, exit
import csv
import pandas as pd

def get_options():
	usage="%prog: [options] <input_csv>"
	parser = OptionParser( usage=usage)
	parser.add_option("-N", "--axiw", type="int", dest="axi_w",
		default=64,
		help="Width of the AXI bus")
	parser.add_option("-m", "--mode", type="int", dest="mode",
		default=0,
		help="Mode of variable conversion (0 - For var -> AXI | 1 - for AXI -> var)")
	(options, filename) = parser.parse_args()
	return (options, filename)

def main():
	(options,filename) = get_options()
	print(options)

if __name__== "__main__":
	main()
