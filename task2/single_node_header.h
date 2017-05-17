#ifndef _SINGLE_NODE_HEADER_H_
#define _SINGLE_NODE_HEADER_H_
struct node{
        char attr_name[15];
        char attr_value[20];
        char resc_name[40];
        struct node *next;
        struct node *prev;
};
struct node *get_node(char *attr_data[3]);
struct node *get_head();
extern int insert (char *attr_data[3]);
extern int file_read();
extern void free_memory();
#endif
