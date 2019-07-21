#!/usr/bin/env python3
# -*- coding: utf-8 -*-
##################################################
# 
# Title: axi_data_enc
# Created: Friday, 29 March 2019
# Author: Raghav Subbaraman
# Organisation: IIT Madras
# A python script that serialises a bunch of variables in a csv file
# into AXI messages and vice-versa. It can also define structures or 
# assign values to structure elements.
# Changelog: 
#	29 March 2019: File created
#	17 July 2019: Some major changes
##################################################

from optparse import OptionParser
import sys
import time
from sys import stderr, exit
import csv
import pandas as pd
import pdb

def encode_axi(options,df_in):
	
	size_vec = df_in['Size'].tolist();
	df_in['start_addr'] = df_in['Size'].cumsum()
	start_ind_vec = df_in['start_addr'].tolist()
	start_ind_vec.insert(0,0)
	options.prev_index = 0;
	options.offset = 0;
	cur_mesg = 1
	options.cur_mesg = cur_mesg - 1;
	total_offset =0 ;

	# Names
	var_name_vec = df_in['Parameter'].tolist()
	desc_vec = df_in['Description'].tolist()
	val_vec = df_in['valid'].tolist()
	ip_var_vec = df_in['struct_name']
	op_var_vec = df_in['op_var_name']

	print('//#BEGIN#')

	index = 0;
	while index < len(start_ind_vec):


		if(size_vec[index] + start_ind_vec[index] + total_offset > options.axi_w):
		
			options.offset =  options.offset + (options.axi_w - start_ind_vec[index] - total_offset);
			cur_mesg = cur_mesg + 1;
			options.cur_mesg = cur_mesg - 1;

			total_offset = options.offset - options.cur_mesg*options.axi_w;

			print('//#END#')
			print()
			print('//#BEGIN#')
		else:
			description = str(desc_vec[index])
			print("// "+description.strip())
			
			if(options.mode==0):
				if(val_vec[index]==1):
					print(op_var_vec[index]+'.range('+str(int(start_ind_vec[index+1]-1 + total_offset))+','+str(int(start_ind_vec[index]+ total_offset))+')'+' = '+ip_var_vec[index]+'.'+var_name_vec[index]+';')
				else:
					print(op_var_vec[index]+'.range('+str(int(start_ind_vec[index+1]-1 + total_offset))+','+str(int(start_ind_vec[index]+ total_offset))+')'+' = 0;')
			elif(options.mode==1):
				if(val_vec[index]==1):
					print(ip_var_vec[index]+'.'+var_name_vec[index]+' = '+op_var_vec[index]+'.range('+str(int(start_ind_vec[index+1]-1+ total_offset))+','+str(int(start_ind_vec[index]+ total_offset))+')'+';')
				else:
					print('//'+str(ip_var_vec[index])+'.'+str(var_name_vec[index])+' = '+op_var_vec[index]+'.range('+str(int(start_ind_vec[index+1]-1+ total_offset))+','+str(int(start_ind_vec[index]+ total_offset))+')'+';')
			elif(options.mode==2):
				if(val_vec[index]==1):
					print(ip_var_vec[index]+'.'+var_name_vec[index]+' = '+op_var_vec[index]+';')
				else:
					print('//'+ip_var_vec[index]+'.'+var_name_vec[index]+' = '+op_var_vec[index]+';')

			if(start_ind_vec[index+1] + total_offset == 64):
				cur_mesg = cur_mesg + 1;
				options.cur_mesg = cur_mesg - 1;
				total_offset = total_offset - options.axi_w;
				print('//#END#')
				print()
				print('//#BEGIN#')

			index = index +1;


def struct_encode(options,df_in):
	# Function that creates structures from excel sheets
	struct_name_vec = df_in['struct_name'].tolist()
	parameter_vec = df_in['Parameter'].tolist()
	size_vec = df_in['Size'].tolist()
	desc_vec = df_in['Description'].tolist();

	cur_struct = '';
	idx = 0;

	for parameter in parameter_vec:
		if((not isinstance(parameter, str)) or str(size_vec[idx])=='0'):
			idx = idx + 1;
			continue;

		if(cur_struct != struct_name_vec[idx]):
			print('}'+str(cur_struct)+';');
			print();
			cur_struct = struct_name_vec[idx];
			print('typedef struct '+str(cur_struct)+'{');

		if(size_vec[idx].isdigit()):
			type_str = 'ap_uint<'+str(size_vec[idx])+'>';
		else:
			type_str = str(size_vec[idx]);

		print('/*\n'+str(desc_vec[idx])+'\n*/');
		print('    '+type_str+' '+str(parameter)+';');

		idx = idx + 1;

	print('}'+str(cur_struct)+';');
	cur_struct = struct_name_vec[idx-1];

	return 0;

def get_options():
	usage="%prog: [options] <input_csv>"
	parser = OptionParser( usage=usage)
	parser.add_option("-N", "--axiw", type="int", dest="axi_w",
		default=64,
		help="Width of the AXI bus")
	parser.add_option("-m", "--mode", type="int", dest="mode",
		default=0,
		help='Mode of variable conversion \n 0 - For var -> AXI \n 1 - for AXI -> var \n 2 - Struct Assignment \n 3 - Struct Definition')
	(options, filename) = parser.parse_args()
	return (options, filename)

def main():
	(options,filename) = get_options()
	options.filename = filename;
	df_in = pd.read_csv(options.filename[0])
	df_out = pd.DataFrame()

	if(options.mode == 3):
		struct_encode(options,df_in);
	else:
		encode_axi(options,df_in)

	print('/*')
	print(options)
	print('*/')

if __name__== "__main__":
	main()
