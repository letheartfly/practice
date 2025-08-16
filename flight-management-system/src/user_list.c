#include "myhead.h"
#include "user.h"

UserNode *create_user_list(FlightNode *flight_head)
{
    UserNode *user_head = calloc(1, sizeof(UserNode));
    if(!user_head)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    user_head->flight_head = flight_head;
    user_head->user.uflight_head = NULL;
    user_head->next = NULL;
    return user_head;
}

UserNode *create_user_node(const char *username, const char *password, const char *phone)
{
    UserNode *new_node = calloc(1, sizeof(UserNode));
    if(!new_node)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    strcpy(new_node->user.username, username);
    strcpy(new_node->user.password, password);
    strcpy(new_node->user.phone, phone);
    new_node->user.in_blacklist = false;
    new_node->flight_head = NULL;
    new_node->user.uflight_head = create_uflight_list();
    return new_node;
}

void insert_tail_user(UserNode *user_head, UserNode *new_node)
{
    UserNode *p = user_head;
    while(p->next != NULL)
    {
        p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
}

UserNode *find_node_username(UserNode *user_head, const char *username)
{
    UserNode *p = user_head->next;
    while(p != NULL && strcmp(p->user.username, username) != 0)
    {
        p = p->next;
    }
    return p;
}

void free_user_list(UserNode *user_head)
{
    UserNode *temp = user_head->next;
    while(temp != NULL)
    {
        user_head->next = temp->next;
        temp->next = NULL;
        temp->flight_head = NULL;
        free(temp->user.uflight_head);
        free(temp);
        temp = user_head->next;
    }
    free(user_head);
}