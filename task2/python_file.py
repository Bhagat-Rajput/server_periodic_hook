#!/bin/python
"""@package single_node_interface
"""
import single_node_interface

""" @brief
	file_read() - read file and populate attribute list 
"""
single_node_interface.get_attr_list()

""" @brief
	file_read() - read file and fill nodes 
""" 
single_node_interface.file_read()

""" @brief
	node()-	return the node sturcture 
"""
head = single_node_interface.node()

""" @brief
	get_head() - return the head node 
"""
head = single_node_interface.get_head()
while(head != None):
	if(head.node_resc_name == "NULL"):
		print"Attr_name = %s  Attr_value = %s" %(head.node_attr_name,head.node_attr_value)
		head = head.node_next
	else:
		attr_data = head.node_resc_name.split(".")
		print"Attr_name = %s  Attr_value = %s  Resc_name = %s" %(attr_data[0],head.node_attr_value,attr_data[1])
		head = head.node_next

""" @brief
	file_read() - free memory 
"""
single_node_interface.free_memory()
