#ifndef MYHEAD_H
#define MYHEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>

#include "flight.h"

typedef enum Identity
{ 
    Identity_User = 1,
    Identity_Admin,
    Identity_Quit
}Identity;

typedef enum LoginChoice
{ 
    LoginChoice_Login = 1,
    LoginChoice_Register,
    LoginChoice_Quit
}LoginChoice;

void my_init();
void print_flight_list(FlightNode *flight_head);
void check_all_flight(FlightNode *flight_head);
void check_one_flight(FlightNode *flight_head);

#endif