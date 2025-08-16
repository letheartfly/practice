#include "myhead.h"
#include "user.h"

UFlightNode *create_uflight_list()
{
    UFlightNode *uflight_head = calloc(1, sizeof(UFlightNode));
    if(!uflight_head)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    uflight_head->next = NULL;
    return uflight_head;
}

UFlightNode *create_uflight_node(const BasicFlight basic_flight, const char *seat_no)
{
    UFlightNode *new_node = calloc(1, sizeof(UFlightNode));
    if(!new_node)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    new_node->basic_flight = basic_flight;
    strcpy(new_node->seat_no, seat_no);
    return new_node;
}

void insert_tail_uflight(UFlightNode *uflight_head, UFlightNode *new_node)
{
    UFlightNode *p = uflight_head;
    while(p->next != NULL)
    {
        p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
}

UFlightNode *find_node_uflightno(UFlightNode *uflight_head, const char *flight_no)
{
    UFlightNode *p = uflight_head->next;
    while(p != NULL && strcmp(p->basic_flight.flight_no, flight_no) != 0)
    {
        p = p->next;
    }
    return p;
}

void remove_node_uflightno(UFlightNode *uflight_head, const char *flight_no)
{
    UFlightNode *pre = uflight_head;
    UFlightNode *p = pre->next;
    while(p != NULL && strcmp(p->basic_flight.flight_no, flight_no) != 0)
    {
        pre = p;
        p = p->next;
    }
    pre->next = p->next;
    p->next = NULL;
    free(p);
}

void free_uflight_list(UFlightNode *uflight_head)
{
    UFlightNode *temp = uflight_head->next;
    while(temp != NULL)
    {
        uflight_head->next = temp->next;
        temp->next = NULL;
        free(temp);
        temp = uflight_head->next;
    }
    free(uflight_head);
}