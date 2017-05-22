/*!header files */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include"single_node_header.h"

node_t *phead; /* Pointer to node */
static char *attr_names_g[20]; /* Store attribute names */

/**
 * @brief
 *      Create a new node and fills attribute data in node
 * @param[in] attr_data - holds attribute data to be inserted
 * @return struct node*
 * @retval - new node
 *
 */
node_t * 
get_node(char *attr_data[3]) 
{
	/* Allocating memory to node */
	node_t *new_node = (node_t *)malloc(sizeof(*new_node));
	/* Check whether memory is allocated or not? */
	if (new_node == NULL) {
		printf("Couldn't allocate memory\n");
		return NULL;
	}
	/* Copying attribute name */
	strncpy(new_node->node_attr_name, attr_data[0], sizeof(new_node->node_attr_name));
	/* Copying attribute value */
	strncpy(new_node->node_attr_value, attr_data[1], sizeof(new_node->node_attr_value));
	/* Copying resource name */
	strncpy(new_node->node_resc_name, attr_data[2], sizeof(new_node->node_resc_name)); 
	new_node->node_prev = NULL;
	new_node->node_next = NULL;
	return new_node;
}

/**
 * @brief
 *      Insert attribute data into node and attached node at the end of the list 
 * @param[in] attr_data - holds attribute data
 * @return	int
 * @retval	0 - on Success
 * @retval	1 - on Error
 *
 */
int
insert(char *attr_data[3]) 
{
	node_t *ptemp = phead;
	/* Creating a new node and filled attribute data */
	node_t *new_node = get_node(attr_data);
	/* Check whether new_node is created or not? */
	if (new_node == NULL) {
		/* Error occured */
		return 1;
	}
	/* Check list is empty or not */
	if (phead == NULL) {
		/* first node */
		phead = new_node;
		return;
	}
	while (ptemp->node_next != NULL) ptemp = ptemp->node_next;
	ptemp->node_next = new_node;
	new_node->node_prev = ptemp;
	return 0;
}

/**
 * @brief
 *      Return pointer to head node
 * @param[in] void - No argument
 * @return struct node* 
 * @retval - head node
 *
 */
node_t *
get_head(void) 
{
	return phead;
}

/**
 * @brief
 * 	Read resource and non-resource attributes from file
 * @param[in] void - No argument
 * @return - int  
 * @retval 0 - on Success
 * @retval 1 - on Failure
 *
 */
int
get_attr_list(void)
{
	int i;
	FILE *fp;
	char data [50]; /* Store char from file */
	char ch;/*! Read char from file */
	char *token;/* Store the token pointer  */
	int tmp_char_pos = 0, tmp_attr_pos = 0;
	bool flag = true; /* flag is a bool variable which will be used to end the loop */
	/* Opening file in read mode. */	
	fp = fopen("pbsnodes.txt", "r");
	/* Check whether file is present or not? */ 
	if (fp == NULL) {
		printf("Could not open attribute file or File is missing\n");
		/* Error occured */
		return 1;
	}
	/* Set the file pointer position to the given offset */
	fseek(fp, 0, SEEK_END);
	/* To check file is empty or not? */	
	if (ftell(fp) == 0) {
		printf("Attribute file is Empty\n");
		/* Error occured */
		return 1;
	}
	/* Set the file pointer position to the beginning of the file */
	rewind(fp);
	/* Fill data array with 0 */
	memset(&data[0], 0, sizeof(data));
	do {
		if (ch == ' ') {
			continue;
		} else if (ch != '\n') {
			data[tmp_char_pos] = ch;
			tmp_char_pos++;
		} else {
			if (strchr(data, '=') != NULL) {
				/* Attribute name and value tokenization */
				token = strtok(data, "="); 
				do {	
					if (flag) {
						/* Check attribute name is already present in attribute list or not? */
						for (i = 0; i < tmp_attr_pos; i++) { 
							if (strcmp(attr_names_g[i], token) == 0 ) {
								goto skip;
							}
						}
						/* Allocating memory to attribute names */
				 		attr_names_g[tmp_attr_pos]=(char *)malloc(25 * sizeof(attr_names_g[tmp_attr_pos]));
				 		/* Add name to the attribute list */
						strcpy(attr_names_g[tmp_attr_pos], token);
				 		tmp_attr_pos++;
				 		flag = false;
					}
					token = strtok(NULL, "=");	
				} while (token != NULL);
				flag = true;
			}
			skip:tmp_char_pos = 0;
			/* Fill data array with 0 */
			memset(&data[0], 0, sizeof(data));
		}
	} while ((ch = getc(fp)) != EOF);
	/*! File pointer closed */
	fclose(fp);
	return 0;
}

/**
 * @brief
 * 	Reading data from file
 * @param[in] void - No argument
 * @return - int
 * @retval 0 - on Success
 * @retval 1 - on Failure
 *
 */
int
file_read(void)
{
	FILE *fp;
	static char data [50]; /* Store char from file */
	char ch; /* Read char from file */
	char *token; /* Store the token pointer */
	char *attr_data[2]; /* Hold attribute name,resource name and their values */
	int tmp_char_pos = 0, tmp_perms = 0;
	char *attr_type = "resources";
	/* Opening file in read mode. */
	fp = fopen("pbsnodes.txt", "r");
	/* Check whether file is present or not? */
	if (fp == NULL) {
		printf("Could not open pbsnodes file or File is missing\n");
		return 1;
	}
	/* Set the file pointer position to the given offset */
	fseek(fp ,0 , SEEK_END);
	/* To check file is empty or not? */
	if (ftell(fp) == 0) {
		printf("pbsnodes file is Empty\n");
		/* Error occured */
		return 1;
	}
	/* Set the file pointer position to the beginning of the file */
	rewind(fp);
	/* Fill data array with 0 */
        memset(&data[0], 0, sizeof(data));
        do {
                if (ch == ' ') {
                        continue;
		} else if (ch != '\n') {
                        data[tmp_char_pos] = ch;
                        tmp_char_pos++;
                } else {
			/* Attribute name and value tokenization */
			token = strtok(data, "=");
			do {
				/* Resource attributes */
				if (strstr(data, attr_type)) {
					if (tmp_perms == 0) {
						attr_data[2] = token;		
						tmp_perms++;
					} else {
						attr_data[1] = token;
						attr_data[0] = "NULL";
						if ((insert(attr_data)) == 1) {
							/* Error occured */
							return 1;
						}
					}
				  /* Non-resource attributes */
				} else {					
					if (tmp_perms == 0) {
						attr_data[0] = token;		
						tmp_perms++;
					} else {
						attr_data[1] = token;
						attr_data[2] = "NULL";
						if ((insert(attr_data)) == 1) {
							/* Error occured */
							return 1;
						}
					}
				}	        	
	 			token = strtok(NULL, "=");	
			} while (token != NULL );
                      	tmp_char_pos = 0;
			tmp_perms = 0;
			/* Fill data array with 0 */
                        memset(&data[0], 0, sizeof(data)); 
                }
        } while ((ch = getc(fp)) != EOF);
	/* File pointer closed */
        fclose(fp);
	return 0;
}

/**
 * @brief
 * 	Freeing the allocated memory
 * @param[in] void - No argument
 * @return void
 *
 * */
void
free_memory(void)
{
	node_t *ptemp, *pcurr;
        pcurr = get_head();
        do {
        	ptemp = pcurr;
                pcurr = pcurr->node_next;
                free(ptemp);
                ptemp = NULL;
        } while (pcurr != NULL);
}

/**
 * @brief
 * main() - main function
 * @param[in] void - No argument
 * @retval int
 * @return 0 - on Success
 * @return 1 - on Failure
 *
 */
int 
main(void)
{
	int tmp_x;
	pid_t pid = fork(); /*!fork() is used to create a new process */
	if (pid == 0) {
		/*!child process */
		tmp_x = execl("./python_file.py", "python_file.py", NULL);/*!execl()- initiates a new program in the same environment*/
		if (tmp_x == -1) {
			perror("./python_file.py");
			/* Error occured */
			return 1;
		}
	  /*! if failed to fork */
	} else if (pid < 0) {
		printf("Failed to fork\n");
		/* Error occured */
		return 1;
	} else {
		/*!parent process */
		wait();
	}
	return 0;
}
