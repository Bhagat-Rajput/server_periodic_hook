#!/bin/python
import single_node_interface
single_node_interface.file_read()
head = single_node_interface.node()
head = single_node_interface.get_head()
while(head != None):
	print"Attr_name = %s  Attr_value = %s  Resc_name = %s" %(head.attr_name,head.attr_value,head.resc_name)
	head = head.next
single_node_interface.free_memory()
