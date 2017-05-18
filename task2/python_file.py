#!/bin/python
"""@package single_node_interface
"""
import single_node_interface

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
	print"Attr_name = %s  Attr_value = %s  Resc_name = %s" %(head.node_attr_name,head.node_attr_value,head.node_resc_name)
	head = head.node_next

""" @brief
	file_read() - free memory 
"""
single_node_interface.free_memory()
