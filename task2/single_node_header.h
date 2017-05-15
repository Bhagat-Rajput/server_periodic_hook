struct node{
        char attr_name[15];
        char attr_value[20];
        char resc_name[40];
        struct node *next;
        struct node *prev;
};
struct node* head,temp;
struct node* get_node(char *attr_data[3]);
void insert(char *attr_data[3]);
struct node *print_result();
int file_read();
