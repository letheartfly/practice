#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "flight.h"

typedef struct Admin
{
    char adminname[50];
    char password[50];
}Admin;

typedef struct AdminNode
{
    Admin admin;
    FlightNode *flight_head;
    UserNode *user_head;
    struct AdminNode *next;
}AdminNode;

typedef enum AdminChoice
{
    AdminChoice_CheckAllFlight = 1,
    AdminChoice_CheckOneFlight,
    AdminChoice_ChangeFlight,
    AdminChoice_AddFlight,
    AdminChoice_SetBlack,
    AdminChoice_Quit
}AdminChoice;

typedef enum ChangeChoice
{
    ChangeChoice_FlightNo = 1,
    ChangeChoice_Company,
    ChangeChoice_TakeOffTime,
    ChangeChoice_ArrivalTime
}ChangeChoice;

typedef enum BlacklistChoice
{
    BlacklistChoice_Ban = 1,
    BlacklistChoice_Unban
}BlacklistChoice;

AdminNode *create_admin_list(FlightNode *flight_head, UserNode *user_head);
AdminNode *create_admin_node(const char *adminname, const char *password);
void insert_tail_admin(AdminNode *admin_head, AdminNode *new_node);
AdminNode *find_node_adminname(AdminNode *admin_head, const char *adminname);
void free_admin_list(AdminNode *admin_head);

void admin_login_choice(AdminNode *admin_head);
bool admin_login(AdminNode *admin_head);
bool check_admin_login(AdminNode *admin_head, const char *adminname, const char *password);
void admin_register(AdminNode *admin_head);
void admin_interface(AdminNode *admin_head);
void check_all_flight(FlightNode *flight_head);
void check_one_flight(FlightNode *flight_head);
void change_flight(FlightNode *flight_head);
void change_flightno(FlightNode *p);
void change_company(FlightNode *p);
void change_take_off_time(FlightNode *p);
void change_arrival_time(FlightNode *p);
void add_flight(FlightNode *flight_head);
void set_blacklist(UserNode *user_head);

#endif