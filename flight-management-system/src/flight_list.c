#include "myhead.h"
#include "flight.h"

FlightNode *create_flight_list()
{
    FlightNode *flight_head = calloc(1, sizeof(FlightNode));
    if(!flight_head)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    flight_head->next = NULL;
    return flight_head;
}

FlightNode *create_flight_node(const Flight flight)
{
    FlightNode *new_node = calloc(1, sizeof(FlightNode));
    if(!new_node)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    new_node->flight = flight;
    return new_node;
}

void insert_tail_flight(FlightNode *flight_head, FlightNode *new_node)
{
    FlightNode *p = flight_head;
    while(p->next != NULL)
    {
        p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
}

FlightNode *find_node_flightno(FlightNode *flight_head, const char *flight_no)
{
    FlightNode *p = flight_head->next;
    while(p != NULL && strcmp(p->flight.basic_flight.flight_no, flight_no) != 0)
    {
        p = p->next;
    }
    return p;
}

void free_flight_list(FlightNode *flight_head)
{
    FlightNode *temp = flight_head->next;
    while(temp != NULL)
    {
        flight_head->next = temp->next;
        temp->next = NULL;
        free(temp);
        temp = flight_head->next;
    }
    free(flight_head);
}