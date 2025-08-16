#include "myhead.h"
#include "admin.h"
#include "user.h"
#include "flight.h"

void my_init()
{
    FlightNode *flight_head = create_flight_list();
    UserNode *user_head = create_user_list(flight_head);
    AdminNode *admin_head = create_admin_list(flight_head, user_head);

    AdminNode *superadmin = create_admin_node("admin", "123456");
    insert_tail_admin(admin_head, superadmin);

    Flight flight1 = {
        .basic_flight.flight_no = "AB666",
        .basic_flight.company = "六六航空",
        .basic_flight.take_off_time = "2025/6/1 6:00",
        .basic_flight.arrival_time = "2025/6/1 8:00",
        .seat_status = {{0}}
    };
    FlightNode *flight_node1 = create_flight_node(flight1);
    insert_tail_flight(flight_head, flight_node1);

    Flight flight2 = {
        .basic_flight.flight_no = "LN665",
        .basic_flight.company = "牛牛航空",
        .basic_flight.take_off_time = "2025/6/1 9:00",
        .basic_flight.arrival_time = "2025/6/1 11:00",
        .seat_status = {{0}}
    };
    FlightNode *flight_node2 = create_flight_node(flight2);
    insert_tail_flight(flight_head, flight_node2);
    
    Flight flight3 = {
        .basic_flight.flight_no = "MI680",
        .basic_flight.company = "米莱航空",
        .basic_flight.take_off_time = "2025/6/1 13:00",
        .basic_flight.arrival_time = "2025/6/1 15:00",
        .seat_status = {{0}}
    };
    FlightNode *flight_node3 = create_flight_node(flight3);
    insert_tail_flight(flight_head, flight_node3);

    Flight flight4 = {
        .basic_flight.flight_no = "AX192",
        .basic_flight.company = "阿莱航空",
        .basic_flight.take_off_time = "2025/6/9 9:00",
        .basic_flight.arrival_time = "2025/6/9 10:00",
        .seat_status = {{0}}
    };
    FlightNode *flight_node4 = create_flight_node(flight4);
    insert_tail_flight(flight_head, flight_node4);

    Flight flight5 = {
        .basic_flight.flight_no = "VP696",
        .basic_flight.company = "心悦航空",
        .basic_flight.take_off_time = "2025/6/5 6:00",
        .basic_flight.arrival_time = "2025/6/5 8:00",
        .seat_status = {{0}}
    };
    FlightNode *flight_node5 = create_flight_node(flight5);
    insert_tail_flight(flight_head, flight_node5);

    int choice;
    bool quit = false;
    while(!quit)
    {
        while(1)
        {
            printf("欢迎使用航班管理系统！\n");
            printf("======选择登录身份======\n");
            printf("1、普通用户\n");
            printf("2、管理员\n");
            printf("3、退出\n");
            printf("请输入数字选择：");

            if(scanf("%d", &choice) != 1)
            {
                printf("无效输入，请重新输入！\n");
                while(getchar() != '\n');
            }
            else if(choice >= 1 && choice <= 3)
            {
                printf("\n");
                break;
            }
            else
            {
                printf("输入无效，请重新输入！\n");
                while(getchar() != '\n');
            }
            printf("\n");
        }

        switch(choice)
        {
            case Identity_User:
                user_login_choice(user_head);
                break;
            case Identity_Admin:
                admin_login_choice(admin_head);
                break;
            case Identity_Quit:
                quit = true;
                break;
        }
    }

    free_admin_list(admin_head);
    free_user_list(user_head);
    free_flight_list(flight_head);
}

void print_flight_list(FlightNode *flight_head)
{
    FlightNode *p = flight_head;
    while(p->next != NULL)
    {
        p = p->next;
        printf("航班号：%s\n", p->flight.basic_flight.flight_no);
        printf("航空公司：%s\n", p->flight.basic_flight.company);
        printf("起飞时间：%s\n", p->flight.basic_flight.take_off_time);
        printf("到达时间：%s\n", p->flight.basic_flight.arrival_time);
        printf("\n");
    }
}

void check_all_flight(FlightNode *flight_head)
{
    print_flight_list(flight_head);
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}

void check_one_flight(FlightNode *flight_head)
{
    char flight_no[50];

    printf("请输入要查询的航班的航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');
    printf("\n");

    FlightNode *p = find_node_flightno(flight_head, flight_no);
    if(p == NULL)
    {
        printf("没有该航班\n\n");
        return;
    }

    printf("该航班的信息为：\n");
    printf("航班号：%s\n", p->flight.basic_flight.flight_no);
    printf("航空公司：%s\n", p->flight.basic_flight.company);
    printf("起飞时间：%s\n", p->flight.basic_flight.take_off_time);
    printf("到达时间：%s\n", p->flight.basic_flight.arrival_time);
    printf("\n");

    printf("请按回车键继续\n");
    while(getchar() != '\n'); 
}