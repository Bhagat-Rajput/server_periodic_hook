#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char *node_name;
	struct attr *attr_list ;
};

struct attr{
	char attr_name[15];
	int attr_value;
	char resc_name[10];
	int resc_value;
	struct node *link_prev;
	struct node *link_next;
};
int main(){
	FILE *fp;
	char data [100];
	struct node *n;
	struct attr *a;
	char c;
	int i = 0;
	fp = fopen("pbsnodes.txt","r");
	if(fp == NULL)
	{
		printf("Could not open file");
		return 1;
	}
	
       while ((c = getc(fp)) != EOF){
                if(c == ' ')
                        continue;
                else if(c != '\n'){
                        data[i]=c;
                        //printf("hello\n");
                        //printf("%c",c);
                        i++;
                }

                else{
                        //printf("%s\n",data);
                        char *token=strtok(data,"=");
                        //printf("Inside token block \n");
                        while(token != NULL){
                                printf("%s--(%d)\n",token,strlen(token));
                                token = strtok(NULL,"=");
                        }
                        i=0;
                        memset(&data[0], 0, sizeof(data));
                }
        }
        fclose(fp);
	printf("\nFile Closed");

return 0;
}
