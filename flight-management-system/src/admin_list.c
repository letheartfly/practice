#include "myhead.h"
#include "admin.h"

AdminNode *create_admin_list(FlightNode *flight_head, UserNode *user_head)
{
    AdminNode *admin_head = calloc(1, sizeof(AdminNode));
    if(!admin_head)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    admin_head->flight_head = flight_head;
    admin_head->user_head = user_head;
    admin_head->next = NULL;
    return admin_head;
}

AdminNode *create_admin_node(const char *adminname, const char *password)
{
    AdminNode *new_node = calloc(1, sizeof(AdminNode));
    if(!new_node)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->admin.adminname, adminname);
    strcpy(new_node->admin.password, password);
    new_node->flight_head = NULL;
    new_node->user_head = NULL;
    new_node->next = NULL;
    return new_node;
}

void insert_tail_admin(AdminNode *admin_head, AdminNode *new_node)
{
    AdminNode *p = admin_head;
    while(p->next != NULL)
    {
        p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
}

AdminNode *find_node_adminname(AdminNode *admin_head, const char *adminname)
{
    AdminNode *p = admin_head->next;
    while(p != NULL && strcmp(p->admin.adminname, adminname) != 0)
    {
        p = p->next;
    }
    return p;
}

void free_admin_list(AdminNode *admin_head)
{
    AdminNode *temp = admin_head->next;
    while(temp != NULL)
    {
        admin_head->next = temp->next;
        temp->next = NULL;
        temp->flight_head = NULL;
        temp->user_head = NULL;
        free(temp);
        temp = admin_head->next;
    }
    free(admin_head);
}