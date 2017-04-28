#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
struct node{
	char *name;
	int age;
};

int main(){
	int pid,x;
	char arg_buff[30];
	struct node *new_node;
	new_node = (struct node *)malloc(sizeof(struct node));
	printf("Enter Your Name:");
	scanf("%s",&new_node->name);
	printf("Enter your Age:");
	scanf("%d",&new_node->age);
	pid = fork();
	if(pid==0){
		printf("Child process called\n");
		snprintf(arg_buff, sizeof(arg_buff), "%s:%d", &new_node->name, new_node->age);
		x = execl("./python_file.py", "python_file.py", arg_buff, (char*)NULL);
		if(x==-1){
			perror("./test.py");
		}
	}
	else{
		wait();
		printf("Parent Process called\n");
        }

	//printf("Name = %s",&new_node->name);
	//printf("\nAge = %d\n",new_node->age);
return 0;
}



