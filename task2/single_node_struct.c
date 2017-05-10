#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
struct node{
	char attr_name[15];
	char attr_value[20];
	char resc_name[40];
	//int data;
	struct node *next;
	struct node *prev;
};

struct node* head;
struct node* get_node(char *attr_data[3]) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	strcpy(new_node->attr_name,attr_data[0]);
	strcpy(new_node->attr_value,attr_data[1]);
	strcpy(new_node->resc_name,attr_data[2]);
	//new_node->attr_name = attr_data[0];
	//new_node->attr_value = attr_data[1];
	//new_node->resc_name = attr_data[2]; 
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void insert(char *attr_data[3]) {
	struct node* temp = head;
//	printf("\nnode name= %s",attr_data[0]);
	struct node* new_node = get_node(attr_data);
	if(head == NULL) {
		head = new_node;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = new_node;
	new_node->prev = temp;
}

void print() {
	struct node* temp = head;
	while(temp != NULL) {
		printf("Attr_Name = %s  Attr_Value = %s   Resc_Name = %s\n",temp->attr_name,temp->attr_value,temp->resc_name);
		temp = temp->next;
	}
//	printf("\n");
}
int main(){
	FILE *fp;
	static char data [50];
	char ch,*token;
	char *attr_data[2];
        const char *attr_names[6];
	attr_names[0] = "Mom";
	attr_names[1] = "ntype";
	attr_names[2] = "state";
	attr_names[3] = "pcpus";
	attr_names[4] = "resources_available.arch";
	attr_names[5] = "resources_available.mem";
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
			//printf("DATA = %s",data);
			token = strtok(data,"=");
			while(token != NULL ){	
                        	//printf("\nToken = %s",token);
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
				else if(strncmp(data,attr_names[5],24)== 0){
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
		//	printf("\n");
                }
        }
        fclose(fp);
print();
printf("\nFile Closed\n");
return 0;
}
