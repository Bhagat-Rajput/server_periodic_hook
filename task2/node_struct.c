#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct node{
	char *node_name;
	struct attr *attr_list;
};

struct attr{
	char attr_name[15];
	char attr_value[15];
	char resc_name[40];
	struct attr *link_prev;
	struct attr *link_next;
};
int main(){
	FILE *fp;
	char data [50];
	struct node *nod;
	struct attr *atr;
	char ch,*token;
	const char *attr_names[3];
	attr_names[0]= "Mom";
	attr_names[1]= "ntype";
	attr_names[2]= "state";
	int i=0,per=0;
	
	bool flag = true;
	fp = fopen("pbsnodes.txt","r");
	if(fp == NULL)
	{
		printf("Could not open file");
		return 1;
	}
        memset(&data[0], 0, sizeof(data));
	nod = (struct node *)malloc(sizeof(struct node));
	//atr = (struct attr *)malloc(sizeof(struct attr));
	//nod->attr_list=atr;
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
                        	if(flag){
					nod->node_name=data;
					printf("Node_name=%s",nod->node_name);
					flag = false;
				}
				else if(strncmp(data,attr_names[0],3)== 0){
					atr = (struct attr *)malloc(sizeof(struct attr));
					nod->attr_list=atr;
					if(per == 0){
						strcpy(nod->attr_list->attr_name,token);
						printf("Attr_name = %s",nod->attr_list->attr_name);
						per++;
					}
					else{
						strcpy(nod->attr_list->attr_value,token);
						printf(" Value = %s",nod->attr_list->attr_value);
						strcpy(nod->attr_list->resc_name,"NULL");
						printf(" Resc_name = %s",nod->attr_list->resc_name);
					}
				}
				else if(strncmp(data,attr_names[1],4)== 0){
					//printf("dfdsggbdf");
					atr = (struct attr *)malloc(sizeof(struct attr));
					nod->attr_list->link_next = atr;
					if(per == 0){
						//printf("ntype");
						strcpy(nod->attr_list->link_next->attr_name,token);
						printf("Attr_name = %s",nod->attr_list->link_next->attr_name);
						per++;
					}
					else{
						strcpy(nod->attr_list->link_next->attr_value,token);
						printf(" value = %s",nod->attr_list->link_next->attr_value);
						strcpy(nod->attr_list->link_next->resc_name,"NULL");
						printf(" Resc_name = %s",nod->attr_list->link_next->resc_name);
					}					
				}
	 			token = strtok(NULL,"=");	
			}
                      	i = 0;
			per = 0;
                        memset(&data[0], 0, sizeof(data));
			printf("\n");
                }
        }
        fclose(fp);
	printf("\nFile Closed\n");
return 0;
}
