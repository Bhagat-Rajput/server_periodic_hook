#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include"single_node_header.h"

struct node* get_node(char *attr_data[3]) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	strcpy(new_node->attr_name,attr_data[0]);
	strcpy(new_node->attr_value,attr_data[1]);
	strcpy(new_node->resc_name,attr_data[2]);
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void insert(char *attr_data[3]) {
	struct node* temp = head;
	struct node* new_node = get_node(attr_data);
	if(head == NULL) {
		head = new_node;
		return;
	}
	while(temp->next != NULL) temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void print_result() {
	struct node* temp = head;
	while(temp != NULL) {
		printf("Attr_Name = %s  Attr_Value = %s   Resc_Name = %s\n",temp->attr_name,temp->attr_value,temp->resc_name);
		temp = temp->next;
	}
}

int file_read(){
	FILE *fp;
	static char data [50];
	char ch,*token;
	char *attr_data[2];
        const char *attr_names[7];
	attr_names[0] = "Mom";
	attr_names[1] = "ntype";
	attr_names[2] = "state";
	attr_names[3] = "pcpus";
	attr_names[4] = "resources_available.arch";
	attr_names[5] = "resources_available.mem";
	attr_names[6] = "resources_available.ncpus";
	int i=0,per=0;
	bool flag = true;
	fp = fopen("pbsnodes.txt","r");
	if(fp == NULL)
	{
		printf("Could not open file");
		return 1;
	        	
	}
        memset(&data[0], 0, sizeof(data));
        while ((ch = getc(fp)) != EOF){
                if(ch == ' ')
                        continue;
                else if(ch != '\n'){
                        data[i]=ch;
                        i++;
                }
                else{
			token = strtok(data,"=");
			while(token != NULL ){	
				if(flag){
					attr_data[0] = "Mom_Name";
					attr_data[1] = token; 
					attr_data[2] = "NULL";
					insert(attr_data);
					flag = false;
				}
				else if(strncmp(data,attr_names[0],3)== 0){
					if(per == 0){
						attr_data[0] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						insert(attr_data);
					}
				}
				else if(strncmp(data,attr_names[1],5)== 0){
					if(per == 0){
						attr_data[0] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						insert(attr_data);
					}
				}
				else if(strncmp(data,attr_names[2],5)== 0){
					if(per == 0){
						attr_data[0] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						insert(attr_data);
					}
				}
				else if(strncmp(data,attr_names[3],5)== 0){
					if(per == 0){
						attr_data[0] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[2] = "NULL";
						insert(attr_data);
					}
				}
				else if(strncmp(data,attr_names[4],24)== 0){
					if(per == 0){
						attr_data[2] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[0] = "NULL";
						insert(attr_data);
					}
				}
				else if(strncmp(data,attr_names[5],23)== 0){
					if(per == 0){
						attr_data[2] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[0] = "NULL";
						insert(attr_data);
					}
				}
				else if(strncmp(data,attr_names[6],24)== 0){
					if(per == 0){
						attr_data[2] = token;		
						per++;
					}
					else{
						attr_data[1] = token;
						attr_data[0] = "NULL";
						insert(attr_data);
					}
				}	
	 			token = strtok(NULL,"=");	
			}
                      	i = 0;
			per = 0;
                        memset(&data[0], 0, sizeof(data));
                }
        }
        fclose(fp);
return 0;
}

int main(){
file_read();
int x;
pid_t pid = fork();
        if(pid==0){
                printf("Child process called\n");
                x = execl("./python_file.py", "python_file.py", NULL);
                if(x==-1){
                        perror("./python_file.py");
                }
        }
        else{
                wait();
                printf("Parent Process called\n");
        }
}
