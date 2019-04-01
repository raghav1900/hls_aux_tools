#!/usr/bin/env python3
# -*- coding: utf-8 -*-
##################################################
# 
# Title: axi_data_enc
# Created: Friday, 29 March 2019
# Author: Raghav Subbaraman
# Organisation: IIT Madras
# A python script that serialises a bunch of variables in a csv file
# into AXI messages and vice-versa.
# Changelog: 
#	29 March 2019: File created
##################################################

from optparse import OptionParser
import sys
import time
from sys import stderr, exit
import csv
import pandas as pd
import pdb

def encode_axi_sub(options,df_in):
	start_ind_vec = df_in['start_addr'].tolist()
	var_name_vec = df_in['var_name'].tolist()
	val_range_vec = df_in['val_range'].tolist()
	desc_vec = df_in['desc'].tolist()
	ip_var_name = df_in['ip_var_name'][0]
	op_var_name = df_in['op_var_name'][0]
	for i in range(options.prev_index,options.index):
		description = str(desc_vec[i])
		value_range = str(val_range_vec[i])
		print("// "+description.strip()+', '+value_range.strip())
		print(op_var_name+'.range('+str(start_ind_vec[i+1]-1-options.cur_mesg*options.axi_w)+','+str(start_ind_vec[i]-options.cur_mesg*options.axi_w)+')'+' = '+ip_var_name+'.'+var_name_vec[i])

	return 0

def encode_axi(options,df_in):
	cur_mesg = 1
	start_ind_vec = df_in['start_addr'].tolist()
	options.prev_index = 0;
	for i in start_ind_vec:
		if(i > cur_mesg*options.axi_w-1):
			options.cur_mesg = cur_mesg - 1
			options.index = start_ind_vec.index(i);
			encode_axi_sub(options,df_in)
			options.prev_index = options.index;
			cur_mesg = cur_mesg+1
			print
	print("Total Number of AXI Messages = "+str(cur_mesg))
	return 0;

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
	options.filename = filename;
	df_in = pd.read_csv(options.filename[0])
	df_out = pd.DataFrame()
	# pdb.set_trace()
	encode_axi(options,df_in)
	# pdb.set_trace()
	print(options)

if __name__== "__main__":
	main()
