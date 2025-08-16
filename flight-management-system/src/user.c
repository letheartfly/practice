#include "myhead.h"
#include "user.h"

void user_login_choice(UserNode *user_head)
{
    int choice;
    bool quit = false;
    while(!quit)
    {
        while(1)
        {
            printf("======普通用户登录======\n");
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
                user_login(user_head);
                break;
            case LoginChoice_Register:
                user_register(user_head);
                break;
            case LoginChoice_Quit:
                quit = true;
                break;
        }
    }
}

void user_login(UserNode *user_head)
{
    char username[50];
    char password[50];
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));

    printf("======登录======\n");

    printf("请输入用户名：");
    scanf("%s", username);
    while(getchar() != '\n');

    printf("请输入密码：");
    scanf("%s", password);
    while(getchar() != '\n');

    UserNode *user_node = find_node_username(user_head, username);
    if(user_node == NULL)
    {
        printf("用户名不存在\n\n");
        return;
    }

    if(!check_user_login(user_node, password))
    {
        return;
    }

    printf("登录成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');

    user_interface(user_head, user_node);
}

bool check_user_login(UserNode *user_node, const char *password)
{
    if(strcmp(user_node->user.password, password) != 0)
    {
        printf("密码错误\n\n");
        return false;
    }
    if(user_node->user.in_blacklist)
    {
        printf("账号处于被封禁状态！请联系管理员\n\n");
        return false;
    }
    return true;
}

void user_register(UserNode *user_head)
{
    char username[50];
    char password[50];
    char phone[15];
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    memset(phone, 0, sizeof(phone));

    printf("======注册======\n");

    printf("请输入用户名：");
    scanf("%s", username);
    while(getchar() != '\n');

    while(find_node_username(user_head, username) != NULL)
    {
        printf("该用户名已存在，请重新输入新的用户名：\n");
        memset(username, 0, sizeof(username));
        scanf("%s", username);
        while(getchar() != '\n');
    }

    printf("请输入密码：");
    scanf("%s", password);
    while(getchar() != '\n');

    printf("请输入电话号码：");
    scanf("%s", phone);
    while(getchar() != '\n');
    
    UserNode *new_node = create_user_node(username, password, phone);
    insert_tail_user(user_head, new_node);
    
    printf("注册成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}

void user_interface(UserNode *user_head, UserNode *user_node)
{
    int choice;
    bool quit = false;
    while(!quit)
    {
        while(1)
        {
            printf("======用户界面======\n");
            printf("1、查看所有航班信息\n");
            printf("2、查询指定航班信息\n");
            printf("3、买票\n");
            printf("4、退票\n");
            printf("5、改签\n");
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
            case UserChoice_CheckAllFlight:
                check_all_flight(user_head->flight_head);
                break;
            case UserChoice_CheckOneFlight:
                check_one_flight(user_head->flight_head);
                break;
            case UserChoice_BuyTicket:
                buy_ticket(user_head, user_node);
                break;
            case UserChoice_Refund:
                refund(user_head, user_node);
                break;
            case UserChoice_Rebook:
                rebook(user_head, user_node);
                break;
            case UserChoice_Quit:
                quit = true;
                break;
        }
        printf("\n");
    }
}

bool check_number(char *seat_no, int num_len)
{
    if(num_len < 1 || num_len > 2)
    {
        return false;
    }
    int num = atoi(seat_no);
    return num >= 1 && num <= 99;
}

bool check_seat_no(char *seat_no)
{
    int len = strlen(seat_no);
    if(len < 2 || len > 4)
    {
        printf("输入长度无效，请重新输入\n");
        if(seat_no[len - 1] != '\n')  // 最后一个字符不是\n，说明已经输入的字符串长度超出数组大小
        {
            while(getchar() != '\n');
        }
        return false;
    }

    int num_len = 0;
    while(num_len < len && seat_no[num_len] >= '0' && seat_no[num_len] <= '9')
    {
        num_len++;
    }
    if(!check_number(seat_no, num_len))
    {
        printf("输入数字无效，请重新输入座位号\n");
        return false;
    }

    if(num_len == len - 1)
    {
        printf("缺少字母，请重新输入座位号\n");
        return false;
    }

    seat_no[num_len] = toupper(seat_no[num_len]);
    if(seat_no[num_len] < 'A' || seat_no[num_len] > 'H')
    {
        printf("输入字母无效，请重新输入座位号\n");
        return false;
    }

    if(seat_no[num_len + 1] != '\n')
    {
        printf("有多余字符，格式为数字（1~99）+字母（A~H），请重新输入\n");
        return false;
    }
    
    return true;
}

void buy_ticket(UserNode *user_head, UserNode *user_node)
{
    char flight_no[50];
    char seat_no[10];
    int number;
    int letter;
    memset(flight_no, 0, sizeof(flight_no));
    memset(seat_no, 0, sizeof(seat_no));

    printf("请输入你要选择的航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');

    FlightNode *flight_node = find_node_flightno(user_head->flight_head, flight_no);
    if(flight_node == NULL)
    {
        printf("该航班号不存在\n");
        printf("请按回车键继续\n");
        while(getchar() != '\n');
        return;
    }

    printf("该航班的信息为：\n");
    printf("航班号：%s\n", flight_node->flight.basic_flight.flight_no);
    printf("航空公司：%s\n", flight_node->flight.basic_flight.company);
    printf("起飞时间：%s\n", flight_node->flight.basic_flight.take_off_time);
    printf("到达时间：%s\n", flight_node->flight.basic_flight.arrival_time);
    printf("\n");

    printf("请按回车键继续\n");
    while(getchar() != '\n');

    while(1)
    {
        printf("座位号为数字（1~99）+字母（A~H）\n");
        printf("请输入你要选择的座位号：");
        fgets(seat_no, sizeof(seat_no), stdin);

        if(check_seat_no(seat_no))
        {
            seat_no[strcspn(seat_no, "\n")] = '\0';
            number = atoi(seat_no);
            if(number < 10)
            {
                letter = seat_no[1] - 'A';
            }
            else
            {
                letter = seat_no[2] - 'A';
            }
            if(flight_node->flight.seat_status[number][letter] == SeatStatus_Available)
            {
                printf("您已选择座位号：%s\n", seat_no);
                break;
            }
            else
            {
                printf("该座位已被占用\n");
            }
        }
        printf("\n");
    }

    char choice;
    while(1)
    {
        printf("请问您是否要购买该趟航班的机票？是请输入Y，否请输入N\n");
        choice = toupper(choice);
        if(scanf("%c", &choice) != 1)
        {
            printf("无效输入，请重新输入！\n");
            while(getchar() != '\n');
        }
        else if(choice == 'Y' || choice == 'N')
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
    if(choice == 'N')
    {
        return;
    }

    printf("购买中......\n");
    
    flight_node->flight.seat_status[number][letter] = SeatStatus_Occupied;

    UFlightNode *uflight_node = create_uflight_node(flight_node->flight.basic_flight, seat_no);
    insert_tail_uflight(user_node->user.uflight_head, uflight_node);

    printf("购买成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}

void refund(UserNode *user_head, UserNode *user_node)
{
    char flight_no[50];
    memset(flight_no, 0, sizeof(flight_no));

    printf("请输入您要退票的航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');

    FlightNode *flight_node = find_node_flightno(user_head->flight_head, flight_no);
    if(flight_node == NULL)
    {
        printf("该航班号不存在\n");
        printf("请按回车键继续\n");
        while(getchar() != '\n');
        return;
    }

    UFlightNode *uflight_node = find_node_uflightno(user_node->user.uflight_head, flight_no);
    if(uflight_node == NULL)
    {
        printf("没有在您的已购票列表中找到该航班号\n");
        printf("请按回车键继续\n");
        while(getchar() != '\n');
        return;
    }

    printf("该航班的信息为：\n");
    printf("航班号：%s\n", flight_node->flight.basic_flight.flight_no);
    printf("航空公司：%s\n", flight_node->flight.basic_flight.company);
    printf("起飞时间：%s\n", flight_node->flight.basic_flight.take_off_time);
    printf("到达时间：%s\n", flight_node->flight.basic_flight.arrival_time);
    printf("\n");

    printf("请按回车键继续\n");
    while(getchar() != '\n');

    char choice;
    while(1)
    {
        printf("请问您是否要退掉该趟航班的机票？是请输入Y，否请输入N\n");
        choice = toupper(choice);
        if(scanf("%c", &choice) != 1)
        {
            printf("无效输入，请重新输入！\n");
            while(getchar() != '\n');
        }
        else if(choice == 'Y' || choice == 'N')
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
    if(choice == 'N')
    {
        return;
    }

    printf("退票中......\n");

    int number = atoi(uflight_node->seat_no);
    int letter;
    if(number < 10)
    {
        letter = uflight_node->seat_no[1] - 'A';
    }
    else
    {
        letter = uflight_node->seat_no[2] - 'A';
    }
    flight_node->flight.seat_status[number][letter] = SeatStatus_Available;
    remove_node_uflightno(user_node->user.uflight_head, flight_no);

    printf("退票成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}

void rebook(UserNode *user_head, UserNode *user_node)
{
    char flight_no[50];
    memset(flight_no, 0, sizeof(flight_no));

    printf("请输入您要改签的原航班号：\n");
    scanf("%s", flight_no);
    while(getchar() != '\n');

    UFlightNode *uflight_node = find_node_uflightno(user_node->user.uflight_head, flight_no);
    if(uflight_node == NULL)
    {
        printf("没有在您的已购票列表中找到该航班号\n");
        printf("请按回车键继续\n");
        while(getchar() != '\n');
        return;
    }

    printf("该航班的信息为：\n");
    printf("航班号：%s\n", uflight_node->basic_flight.flight_no);
    printf("航空公司：%s\n", uflight_node->basic_flight.company);
    printf("起飞时间：%s\n", uflight_node->basic_flight.take_off_time);
    printf("到达时间：%s\n", uflight_node->basic_flight.arrival_time);
    printf("\n");

    printf("请按回车键继续\n");
    while(getchar() != '\n');

    char new_flight_no[50];
    FlightNode *flight_node = NULL;

    while(1)
    {
        printf("请输入您改签的新航班号：\n");
        scanf("%s", new_flight_no);
        while(getchar() != '\n');

        if(strcmp(new_flight_no, flight_no) == 0)
        {
            printf("该航班号与原航班号一致，请重新输入\n");
            printf("请按回车键继续\n");
            while(getchar() != '\n');
        }
        else if((flight_node = find_node_flightno(user_head->flight_head, new_flight_no)) == NULL)
        {
            printf("该航班号不存在，请重新输入\n");
            printf("请按回车键继续\n");
            while(getchar() != '\n');
        }
        else
        {
            break;
        }
    }

    char choice;
    while(1)
    {
        printf("请问您是否要改签？是请输入Y，否请输入N\n");
        choice = toupper(choice);
        if(scanf("%c", &choice) != 1)
        {
            printf("无效输入，请重新输入！\n");
            while(getchar() != '\n');
        }
        else if(choice == 'Y' || choice == 'N')
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
    if(choice == 'N')
    {
        return;
    }

    int number = atoi(uflight_node->seat_no);
    int letter;
    if(number < 10)
    {
        letter = uflight_node->seat_no[1] - 'A';
    }
    else
    {
        letter = uflight_node->seat_no[2] - 'A';
    }
    flight_node->flight.seat_status[number][letter] = SeatStatus_Available;
    uflight_node->basic_flight = flight_node->flight.basic_flight;

    char seat_no[10];

    while(1)
    {
        printf("座位号为数字（1~99）+字母（A~H）\n");
        printf("请输入你要选择的座位号：");
        fgets(seat_no, sizeof(seat_no), stdin);

        if(check_seat_no(seat_no))
        {
            seat_no[strcspn(seat_no, "\n")] = '\0';
            number = atoi(seat_no);
            if(number < 10)
            {
                letter = seat_no[1] - 'A';
            }
            else
            {
                letter = seat_no[2] - 'A';
            }
            if(flight_node->flight.seat_status[number][letter] == SeatStatus_Available)
            {
                printf("您已选择座位号：%s\n", seat_no);
                break;
            }
            else
            {
                printf("该座位已被占用\n");
            }
        }
        printf("\n");
    }

    strcpy(uflight_node->seat_no, seat_no);
    flight_node->flight.seat_status[number][letter] = SeatStatus_Occupied;

    printf("改签成功！\n");
    printf("请按回车键继续\n");
    while(getchar() != '\n');
}