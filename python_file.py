#!/bin/python
import sys
print "Python File"
print sys.argv
info_list = sys.argv[1].split(":")
print "Name = ",info_list[0]
print "Age = ",info_list[1]
