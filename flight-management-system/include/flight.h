#ifndef FLIGHT_H
#define FLIGHT_H

typedef enum SeatStatus
{
    SeatStatus_Available = 0,
    SeatStatus_Occupied = 1
}SeatStatus;

typedef struct BasicFlight
{
    char flight_no[50];
    char company[50];
    char take_off_time[50];
    char arrival_time[50];
}BasicFlight;

typedef struct Flight
{
    BasicFlight basic_flight;
    SeatStatus seat_status[100][10];
}Flight;

typedef struct FlightNode
{
    Flight flight;
    struct FlightNode *next;
}FlightNode;

FlightNode *create_flight_list();
FlightNode *create_flight_node(const Flight flight);
void insert_tail_flight(FlightNode *flight_head, FlightNode *new_node);
FlightNode *find_node_flightno(FlightNode *flight_head, const char *flight_no);
void free_flight_list(FlightNode *flight_head);

void print_flight_list(FlightNode *flight_head);

#endif