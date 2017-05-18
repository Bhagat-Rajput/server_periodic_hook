/*!header files */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include"single_node_header.h"

node_t *head; /*! head node */

/**
 * @brief
 * get_node() - create a new node and filled the node
 * @param[in] attr_data - char pointer array holding information to be inserted
 * @return struct node* - structure that contains file attributes
 */
node_t * 
get_node(char *attr_data[3]) 
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));/*!allocating memory to node*/
	if(new_node == NULL){
		printf("Couldn't allocate memory\n");
		return NULL;
	}
	strncpy(new_node->node_attr_name, attr_data[0], sizeof(new_node->node_attr_name)); /*!copying attribute name */
	strncpy(new_node->node_attr_value, attr_data[1], sizeof(new_node->node_attr_value)); /*copying attribute value */
	strncpy(new_node->node_resc_name, attr_data[2], sizeof(new_node->node_resc_name)); /* copying resource name */
	new_node->node_prev = NULL;
	new_node->node_next = NULL;
	return new_node;
}

/**
 * @brief
 * insert() - inserts file records in data list
 * @param[in]  attr_data - char pointer array holding information to be inserted
 * @return 0 - success
 * @return 1 - failure
 */
int 
insert(char *attr_data[3]) 
{
	node_t *temp = head;
	node_t *new_node = get_node(attr_data);
	if(new_node == NULL){
		return 1;
	}
	if(head == NULL){  /*for first node only */
		head = new_node;
		return;
	}
	while(temp->node_next != NULL) temp = temp->node_next;
	temp->node_next = new_node;
	new_node->node_prev = temp;
	return 0;
}

/**
 * @brief
 * get_head() - return pointer to head node
 * @param[in]   void - No argument
 * @return struct node* - head node
 */
node_t *
get_head(void) 
{
	return head;
}

/**
 * @brief
 * file_read() - reading file data
 * @param[in]   void - No argument
 * @return 1 - if file is empty or not found
 */
int
file_read(void)
{
	FILE *fp;
	static char data [50]; /*!store char from file */
	char ch;/*!read char from file */
	char *token;/*store the token pointer  */
	char *attr_data[2]; /*!char pointer array to store attribute name and their values */
        const char *attr_names[7]; /*!const char pointer array to store the types of attribute in file */
	attr_names[0] = "Mom";
	attr_names[1] = "ntype";
	attr_names[2] = "state";
	attr_names[3] = "pcpus";
	attr_names[4] = "resources_available.arch";
	attr_names[5] = "resources_available.mem";
	attr_names[6] = "resources_available.ncpus";
	int char_pos = 0, perms = 0; /**/
	bool flag = true; /*flag is a bool variable which will be used to end the loop */
	fp = fopen("pbsnodes.txt", "r"); /*!opening file in read mode. */
	if(fp == NULL){
		printf("Could not open file or File is missing\n");
		return 1;
	}
	fseek(fp ,0 ,SEEK_END);/*!sets the file pointer position to the given offset */
	if(ftell(fp) == 0){
		printf("File is Empty\n");
		return 1;
	}
	rewind(fp); /*!sets the file pointer position to the beginning of the file */
        memset(&data[0], 0, sizeof(data)); /*!fill data array with 0*/
        while ((ch = getc(fp)) != EOF){
                if(ch == ' '){
                        continue;
		}
		else if(ch != '\n'){
                        data[char_pos] = ch;
                        char_pos++;
                }
		else{
			token = strtok(data,"="); /*!name and value tokenization */
			while(token != NULL ){	
				if(flag){
					attr_data[0] = "Mom_Name";
					attr_data[1] = token; 
					attr_data[2] = "NULL";
					if((insert(attr_data)) == 1){
						return 1;
					}
					flag = false;
				}
				/*!if attribute name is Mom*/
				else if(strncmp(data,attr_names[0],3) == 0){
					if(perms == 0){
						attr_data[0] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}
				/*!if attribute name is ntype */
				else if(strncmp(data,attr_names[1],5) == 0){
					if(perms == 0){
						attr_data[0] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}
				/*!if attribute name is state*/
				else if(strncmp(data,attr_names[2],5) == 0){
					if(perms == 0){
						attr_data[0] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}
				/*!if attribute name is pcpus*/
				else if(strncmp(data,attr_names[3],5) == 0){
					if(perms == 0){
						attr_data[0] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}
				/*!if attribute name is resources_available.arch*/
				else if(strncmp(data,attr_names[4],24) == 0){
					if(perms == 0){
						attr_data[2] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[0] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}
				/*!if attribute name is resources_available.mem*/
				else if(strncmp(data,attr_names[5],23) == 0){
					if(perms == 0){
						attr_data[2] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[0] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}
				/*!if attribute name is resources_available.ncpus*/
				else if(strncmp(data,attr_names[6],24) == 0){
					if(perms == 0){
						attr_data[2] = token;		
						perms++;
					}
					else{
						attr_data[1] = token;
						attr_data[0] = "NULL";
						if((insert(attr_data)) == 1){
							return 1;
						}
					}
				}	
	 			token = strtok(NULL,"=");	
			}
                      	char_pos = 0;
			perms = 0;
                        memset(&data[0], 0, sizeof(data)); /*!fill data array with 0 */
                }
        }
        fclose(fp);/*!file pointer closed */
return 0;
}

/**
 * @brief
 * free_memory() - freeing the memory
 * @param[in]   void - No argument
 * @return void
 * */
void
free_memory(void)
{
	node_t *temp, *curr;
        curr = get_head();
        while(curr != NULL){
        	temp = curr;
                curr = curr->node_next;
                free(temp);
                temp = NULL;
        }
}

/**
 * @brief
 * main() - main function
 * @param[in]   void - No argument
 * @return 0 - for success
 * @return 1 - for failure
 */
int 
main(void)
{
	int tmp_x;
	pid_t pid = fork();/*!fork() is used to create a new process */
        if(pid == 0){
		/*!child process */
                tmp_x = execl("./python_file.py", "python_file.py", NULL);/*!execl()- initiates a new program in the same environment*/
                if(tmp_x == -1){
                        perror("./python_file.py");
			return 1;
                }
        }
	else if (pid < 0){ /*!failed to fork */
        	printf("Failed to fork\n");
        	return 1;
        }
        else{
		/*!parent process */
                wait();
        }
	return 0;
}
