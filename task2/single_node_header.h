/**
 * @file    single_node_header.h
 *
 * @brief
 * Single node interface. (Functions declarations and structures)
 *
 * This header file contains functions to access the single node structure 
 */
#ifndef _SINGLE_NODE_HEADER_H_
#define _SINGLE_NODE_HEADER_H_
struct node{
        char node_attr_name[30];
        char node_attr_value[20];
        char node_resc_name[40];
        struct node *node_next;
        struct node *node_prev;
};
typedef struct node node_t;
node_t *get_head();
node_t *get_node(char *attr_data[3]);
extern int get_attr_list();
extern int insert (char *attr_data[3]);
extern int file_read();
extern void free_memory();
#endif /* _SINGLE_NODE_HEADER_H_ */
