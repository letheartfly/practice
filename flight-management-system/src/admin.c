#include "myhead.h"
#include "admin.h"

void admin_login_choice(AdminNode *admin_head)
{
    int choice;
    bool quit = false;
    while(!quit)
    {
        while(1)
        {
            printf("======管理员登录======\n");
            printf("1、登录\n");
            printf("2、注册\n");
            printf("3、退出\n");
            printf("请输入数字选择下一步：");

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
            case LoginChoice_Login:
                if(admin_login(admin_head))
                {
                    admin_interface(admin_head);
                }
                break;
            case LoginChoice_Register:
                admin_register(admin_head);
                break;
            case LoginChoice_Quit:
                quit = true;
                break;
        }
        printf("\n");
    }
}

bool admin_login(AdminNode *admin_head)
{
    char adminname[50];
    char password[50];
    memset(adminname, 0, sizeof(adminname));
    memset(password, 0, sizeof(password));

    printf("======登录======\n");

    printf("请输入管理员用户名：");
    scanf("%s", adminname);
    while(getchar() != '\n');

    printf("请输入密码：");
    scanf("%s", password);
    while(getchar() != '\n');

    if(!check_admin_login(admin_head, adminname, password))
    {
        printf("用户名或密码错误\n\n");
        return false;
    }

    printf("登录成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');

    return true;
}

bool check_admin_login(AdminNode *admin_head, const char *adminname, const char *password)
{
    AdminNode *p = find_node_adminname(admin_head, adminname);
    if(p == NULL)
    {
        return false;
    }
    if(strcmp(p->admin.password, password) != 0)
    {
        return false;
    }
    return true;
}

void admin_register(AdminNode *admin_head)
{
    printf("请登录已有管理员账户以获得注册管理员权限！\n");
    if(!admin_login(admin_head))
    {
        return;
    }

    char adminname[50];
    char password[50];
    memset(adminname, 0, sizeof(adminname));
    memset(password, 0, sizeof(password));

    printf("======注册======\n");

    printf("请输入管理员用户名：");
    scanf("%s", adminname);
    while(getchar() != '\n');

    while(find_node_adminname(admin_head, adminname) != NULL)
    {
        printf("该管理员用户名已存在，请重新输入新的管理员用户名：\n");
        memset(adminname, 0, sizeof(adminname));
        scanf("%s", adminname);
        while(getchar() != '\n');
    }

    printf("请输入密码：");
    scanf("%s", password);
    while(getchar() != '\n');
    
    AdminNode *new_node = create_admin_node(adminname, password);
    insert_tail_admin(admin_head, new_node);
    
    printf("注册成功\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}

void admin_interface(AdminNode *admin_head)
{
    int choice;
    bool quit = false;
    while(!quit)
    {
        while(1)
        {
            printf("======管理员界面======\n");
            printf("1、查看所有航班信息\n");
            printf("2、查询指定航班信息\n");
            printf("3、修改航班信息\n");
            printf("4、添加新的航班信息\n");
            printf("5、设置黑名单\n");
            printf("6、退出\n");
            printf("请输入数字选择下一步：");

            if(scanf("%d", &choice) != 1)
            {
                printf("无效输入，请重新输入！\n");
                while(getchar() != '\n');
            }
            else if(choice >= 1 && choice <= 6)
            {
                while(getchar() != '\n');
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
            case AdminChoice_CheckAllFlight:
                check_all_flight(admin_head->flight_head);
                break;
            case AdminChoice_CheckOneFlight:
                check_one_flight(admin_head->flight_head);
                break;
            case AdminChoice_ChangeFlight:
                change_flight(admin_head->flight_head);
                break;
            case AdminChoice_AddFlight:
                add_flight(admin_head->flight_head);
                break;
            case AdminChoice_SetBlack:
                set_blacklist(admin_head->user_head);
                break;
            case AdminChoice_Quit:
                quit = true;
                break;
        }
        printf("\n");
    }
}

void change_flight(FlightNode *flight_head)
{
    char flight_no[50];

    printf("请输入要修改的航班的航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');
    printf("\n");

    FlightNode *p = find_node_flightno(flight_head, flight_no);
    if(p == NULL)
    {
        printf("没有该航班\n\n");
        return;
    }

    printf("该航班当前的信息为：\n");
    printf("航班号：%s\n", p->flight.basic_flight.flight_no);
    printf("航空公司：%s\n", p->flight.basic_flight.company);
    printf("起飞时间：%s\n", p->flight.basic_flight.take_off_time);
    printf("到达时间：%s\n", p->flight.basic_flight.arrival_time);
    printf("\n");

    int choice;
    while(1)
    {
        printf("请选择要修改的信息：\n");
        printf("1、航班号\n");
        printf("2、航空公司名字\n");
        printf("3、起飞时间\n");
        printf("4、到达时间\n");
        printf("请输入数字选择下一步：");

        if(scanf("%d", &choice) != 1)
        {
            printf("无效输入，请重新输入！\n");
            while(getchar() != '\n');
        }
        else if(choice >= 1 && choice <= 4)
        {
            while(getchar() != '\n');
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
        case ChangeChoice_FlightNo:
            change_flightno(p);
            break;
        case ChangeChoice_Company:
            change_company(p);
            break;
        case ChangeChoice_TakeOffTime:
            change_take_off_time(p);
            break;
        case ChangeChoice_ArrivalTime:
            change_arrival_time(p);
            break;
    }
    printf("修改成功!\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');     
}

void change_flightno(FlightNode *p)
{
    char flight_no[50];
    printf("请输入航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');
    strcpy(p->flight.basic_flight.flight_no, flight_no);
}

void change_company(FlightNode *p)
{
    char company[50];
    printf("请输入航空公司名字：\n");
    scanf("%s", company);
    while(getchar() != '\n');
    strcpy(p->flight.basic_flight.company, company);
}

void change_take_off_time(FlightNode *p)
{
    char take_off_time[50];
    printf("请输入起飞时间：\n");
    fgets(take_off_time, sizeof(take_off_time), stdin);
    take_off_time[strcspn(take_off_time, "\n")] = '\0';
    strcpy(p->flight.basic_flight.take_off_time, take_off_time);
}

void change_arrival_time(FlightNode *p)
{
    char arrival_time[50];
    printf("请输入到达时间：\n");
    fgets(arrival_time, sizeof(arrival_time), stdin);
    arrival_time[strcspn(arrival_time, "\n")] = '\0';
    strcpy(p->flight.basic_flight.arrival_time, arrival_time);
}

void add_flight(FlightNode *flight_head)
{
    printf("======添加新的航班信息======\n");
    char flight_no[50];
    printf("请输入航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');

    while(find_node_flightno(flight_head, flight_no) != NULL)
    {
        printf("该航班号已存在，请重新输入\n");
        scanf("%s", flight_no);
        while(getchar() != '\n');
    }

    char company[50];
    printf("请输入航空公司名字：\n");
    scanf("%s", company);
    while(getchar() != '\n');

    char take_off_time[50];
    printf("请输入起飞时间：\n");
    fgets(take_off_time, sizeof(take_off_time), stdin);
    take_off_time[strcspn(take_off_time, "\n")] = '\0';

    char arrival_time[50];
    printf("请输入到达时间：\n");
    fgets(arrival_time, sizeof(arrival_time), stdin);
    arrival_time[strcspn(arrival_time, "\n")] = '\0';
    
    Flight flight = {0};
    strcpy(flight.basic_flight.flight_no, flight_no);
    strcpy(flight.basic_flight.company, company);
    strcpy(flight.basic_flight.take_off_time, take_off_time);
    strcpy(flight.basic_flight.arrival_time, arrival_time);

    FlightNode *new_node = create_flight_node(flight);
    insert_tail_flight(flight_head, new_node);

    printf("添加成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n'); 
}

void set_blacklist(UserNode *user_head)
{
    printf("======设置黑名单======\n");
    printf("请输入要设置的账号的用户名：\n");
    char username[50];
    scanf("%s", username);
    while(getchar() != '\n');

    UserNode *p = find_node_username(user_head, username);

    int choice;
    while(1)
    {
        printf("请选择要设置的选项：\n");
        printf("1、封禁该账号\n");
        printf("2、解封该账号\n");
        printf("请输入数字选择：");

        if(scanf("%d", &choice) != 1)
        {
            printf("无效输入，请重新输入！\n");
            while(getchar() != '\n');
        }
        else if(choice >= 1 && choice <= 2)
        {
            while(getchar() != '\n');
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
        case BlacklistChoice_Ban:
            p->user.in_blacklist = true;
            break;
        case BlacklistChoice_Unban:
            p->user.in_blacklist = false;
            break;
    }
    printf("设置成功\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}