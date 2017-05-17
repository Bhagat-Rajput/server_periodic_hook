INCLUDE = -I /usr/include/python2.7/
SHARED = -fPIC
CC = gcc
SWIG = swig
SWIGFLAG = -python
OBJ1 = single_node_interface
OBJ2 = single_node_struct

executable: shared
	$(CC) $(OBJ2).c -o exec_single_node

shared: single_node_struct
	$(CC) -shared $(OBJ2).o $(OBJ1)_wrap.o -o _$(OBJ1).so

single_node_struct: single_node_interface
	$(CC) -c $(OBJ2).c $(OBJ1)_wrap.c $(SHARED) $(INCLUDE)

single_node_interface:
	 $(SWIG) $(SWIGFLAG) $(OBJ1).i	

clean:
	rm -f *.o _*.* $(OBJ1)_wrap.*
	rm -f $(OBJ1).py $(OBJ1).pyc
	rm -f exec_single_node
