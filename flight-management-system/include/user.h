#ifndef USER_H
#define USER_H

#include "flight.h"

typedef struct UFlightNode
{
    BasicFlight basic_flight;
    char seat_no[10];
    struct UFlightNode *next;
}UFlightNode;

typedef struct User
{
    char username[50];
    char password[50];
    char phone[15];
    bool in_blacklist;
    UFlightNode *uflight_head;
}User;

typedef struct UserNode
{
    User user;
    FlightNode *flight_head;
    struct UserNode *next;
}UserNode;

typedef enum UserChoice
{
    UserChoice_CheckAllFlight = 1,
    UserChoice_CheckOneFlight,
    UserChoice_BuyTicket,
    UserChoice_Refund,
    UserChoice_Rebook,
    UserChoice_Quit
}UserChoice;

UserNode *create_user_list(FlightNode *flight_head);
UserNode *create_user_node(const char *username, const char *password, const char *phone);
void insert_tail_user(UserNode *user_head, UserNode *new_node);
UserNode *find_node_username(UserNode *user_head, const char *username);
void free_user_list(UserNode *user_head);

UFlightNode *create_uflight_list();
UFlightNode *create_uflight_node(const BasicFlight basic_flight, const char *seat_no);
void insert_tail_uflight(UFlightNode *uflight_head, UFlightNode *new_node);
UFlightNode *find_node_uflightno(UFlightNode *uflight_head, const char *flight_no);
void remove_node_uflightno(UFlightNode *uflight_head, const char *flight_no);
void free_uflight_list(UFlightNode *uflight_head);

void user_login_choice(UserNode *user_head);
void user_login(UserNode *user_head);
bool check_user_login(UserNode *user_head, const char *password);
void user_register(UserNode *user_head);
void user_interface(UserNode *user_head, UserNode *user_node);
bool check_number(char *seat_no, int num_len);
bool check_seat_no(char *seat_no);
void buy_ticket(UserNode *user_head, UserNode *user_node);
void refund(UserNode *user_head, UserNode *user_node);
void rebook(UserNode *user_head, UserNode *user_node);

#endif