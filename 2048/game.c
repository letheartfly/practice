#include "game.h"

void init_game(GameState *game_state)
{
    // 初始化随机数种子
    srand(time(NULL));  

    // 选择两个随机位置，各放一个2
    int pos1_x, pos1_y, pos2_x, pos2_y;
    do
    {
        pos1_x = rand() % 4;
        pos1_y = rand() % 4;

        pos2_x = rand() % 4;
        pos2_y = rand() % 4;
    } while (pos1_x == pos2_x && pos1_y == pos2_y);

    game_state->map[pos1_x][pos1_y] = gener_num();
    game_state->map[pos2_x][pos2_y] = gener_num();
}    

void print_state(GameState *game_state)
{
    printf("\033[H\033[J");  // 清屏
    printf("当前分数：%lld\n", game_state->score);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%-6d", game_state->map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool get_operator(char *input, char *operator, int size)
{
    int i = 0;
    while(i < size && input[i] == ' ')
    {
        i++;
    }
    if(i >= size)  return false;
    if(input[i] == 'w' || input[i] == 'a' || input[i] == 's' || input[i] == 'd' || input[i] == 'q')
    {
        input[i] = input[i] - 'a' + 'A';
    }
    if(input[i] == 'W' || input[i] == 'A' || input[i] == 'S' || input[i] == 'D' || input[i] == 'Q')
    {
        if(input[i + 1] == '\n')
        {
            *operator = input[i];
            return true;
        }
    }
    while(i < size && input[i] != '\n')
    {
        i++;
    }
    if(i >= size)
    {
        while(getchar() != '\n');
    }
    return false;
}

void playing(GameState *game_state)
{
    char input[10], operator = '\0';
    while(1)
    {
        print_state(game_state);

        printf("请输入移动方向（W/A/S/D），输入Q结束游戏：\n");
        int size = sizeof(input);
        fgets(input, size, stdin);

        if(!get_operator(input, &operator, size))
        {
            printf("输入有误，请重新输入！\n");
            printf("请按回车键继续\n");
            while(getchar() != '\n');
            continue;
        }

        bool move = false, win = false;
        switch(operator)
        {
            case 'W':
                move = move_up(game_state);
                break;
            case 'A':
                move = move_left(game_state);
                break;
            case 'S':
                move = move_down(game_state);
                break;
            case 'D':
                move = move_right(game_state);
                break;
            default:
                printf("游戏结束，得分：%lld\n", game_state->score);
                printf("请按回车键退出游戏\n");
                while(getchar() != '\n');
                return;
        }

        if(!win && check_win(game_state))
        {
            win = true;
            printf("成功合成2048！\n");
            printf("请按回车键继续游戏\n");
            while(getchar() != '\n');
        }

        if(move)
        {
            spawn_tile(game_state);
        }

        if(game_over(game_state))
        {
            print_state(game_state);
            printf("游戏结束，得分：%lld\n", game_state->score);
            break;
        }
    }
}

bool check_win(GameState *game_state)
{
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            if(game_state->map[x][y] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool check_blank(GameState *game_state)
{
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            if(!game_state->map[x][y])
            {
                return true;
            }
        }
    }
    return false;
}

void spawn_tile(GameState *game_state)
{
    if(!check_blank(game_state))  return;

    int new_x, new_y;

    do
    {
        new_x = rand() % 4;
        new_y = rand() % 4;
    } while (game_state->map[new_x][new_y]);
    
    game_state->map[new_x][new_y] = gener_num();
}

bool game_over(GameState *game_state)
{
    if(check_blank(game_state))  return false;
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            if((x - 1 >= 0 && game_state->map[x - 1][y] == game_state->map[x][y])
              || (y - 1 >= 0 && game_state->map[x][y - 1] == game_state->map[x][y])
              || (x + 1 < 4 && game_state->map[x + 1][y] == game_state->map[x][y])
              || (y + 1 < 4 && game_state->map[x][y + 1] == game_state->map[x][y]))
            {
                return false;
            }
        }
    }
    return true;
}

bool move_up(GameState *game_state)
{
    bool move = false;
    for(int y = 0; y < 4; y++)
    {
        int i = 0;

        // 找到从上往下第一个0
        while(i < 4 && game_state->map[i][y] != 0)
        {
            i++;
        }

        // i == 3：只有这一列最后一个是0；i == 4：这一列全部都是非0数

        if(i < 3)
        {
            // 将非0数全部向上移
            // 此时的game_state->map[i][y]是0
            int j = i + 1;
            while(j < 4)
            {
                if(game_state->map[j][y])
                {
                    move = true;
                    game_state->map[i][y] = game_state->map[j][y];
                    game_state->map[j][y] = 0;
                    i++;
                    while(i < 4 && game_state->map[i][y] != 0)
                    {
                        i++;
                    }
                    if(i >= 4)  break;
                }
                j++;
            }
        }

        // 合并
        if(game_state->map[0][y] && game_state->map[1][y] && game_state->map[0][y] == game_state->map[1][y])
        {
            move = true;
            game_state->map[0][y] *= 2;
            game_state->score += game_state->map[0][y];
            if(game_state->map[2][y] && game_state->map[3][y] && game_state->map[2][y] == game_state->map[3][y])
            {
                game_state->map[1][y] = game_state->map[2][y] * 2;
                game_state->score += game_state->map[1][y];
                game_state->map[2][y] = game_state->map[3][y] = 0;
            }
            else
            {
                for(int x = 1; x < 3; x++)
                {
                    game_state->map[x][y] = game_state->map[x + 1][y];
                }
                game_state->map[3][y] = 0;
            }
        }
        else if(game_state->map[1][y] && game_state->map[2][y] && game_state->map[1][y] == game_state->map[2][y])
        {
            move = true;
            game_state->map[1][y] *= 2;
            game_state->score += game_state->map[1][y];
            game_state->map[2][y] = game_state->map[3][y];
            game_state->map[3][y] = 0;
        }
        else if(game_state->map[2][y] && game_state->map[3][y] && game_state->map[2][y] == game_state->map[3][y])
        {
            move = true;
            game_state->map[2][y] *= 2;
            game_state->score += game_state->map[2][y];
            game_state->map[3][y] = 0;
        }
    }
    return move;
}

bool move_left(GameState *game_state)
{
    bool move = false;
    for(int x = 0; x < 4; x++)
    {
        int i = 0;

        // 找到从左往右第一个0的y下标
        while(i < 4 && game_state->map[x][i] != 0)
        {
            i++;
        }

        // i == 3：只有这一行最后一个是0；i == 4：这一行全部都是非0数

        if(i < 3)
        {
            // 将非0数全部向左移
            // 此时的game_state->map[x][i]是0
            int j = i + 1;
            while(j < 4)
            {
                if(game_state->map[x][j])
                {
                    move = true;
                    game_state->map[x][i] = game_state->map[x][j];
                    game_state->map[x][j] = 0;
                    i++;
                    while(i < 4 && game_state->map[x][i] != 0)
                    {
                        i++;
                    }
                    if(i >= 4)  break;
                }
                j++;
            }
        }

        // 合并
        if(game_state->map[x][0] && game_state->map[x][1] && game_state->map[x][0] == game_state->map[x][1])
        {
            move = true;
            game_state->map[x][0] *= 2;
            game_state->score += game_state->map[x][0];
            if(game_state->map[x][2] && game_state->map[x][3] && game_state->map[x][2] == game_state->map[x][3])
            {
                game_state->map[x][1] = game_state->map[x][2] * 2;
                game_state->score += game_state->map[x][1];
                game_state->map[x][2] = game_state->map[x][3] = 0;
            }
            else
            {
                for(int y = 1; y < 3; y++)
                {
                    game_state->map[x][y] = game_state->map[x][y + 1];
                }
                game_state->map[x][3] = 0;
            }
        }
        else if(game_state->map[x][1] && game_state->map[x][2] && game_state->map[x][1] == game_state->map[x][2])
        {
            move = true;
            game_state->map[x][1] *= 2;
            game_state->score += game_state->map[x][1];
            game_state->map[x][2] = game_state->map[x][3];
            game_state->map[x][3] = 0;
        }
        else if(game_state->map[x][2] && game_state->map[x][3] && game_state->map[x][2] == game_state->map[x][3])
        {
            move = true;
            game_state->map[x][2] *= 2;
            game_state->score += game_state->map[x][2];
            game_state->map[x][3] = 0;
        }
    }
    return move;
}

bool move_right(GameState *game_state)
{
    bool move = false;
    for(int x = 0; x < 4; x++)
    {
        int i = 3;

        // 找到从右往左第一个0的y下标
        while(i >= 0 && game_state->map[x][i] != 0)
        {
            i--;
        }

        // i == 0：只有这一行第一个是0；i < 0：这一行全部都是非0数

        if(i > 0)
        {
            // 将非0数全部向右移
            int j = i - 1;
            while(j >= 0)
            {
                if(game_state->map[x][j])
                {
                    move = true;
                    game_state->map[x][i] = game_state->map[x][j];
                    game_state->map[x][j] = 0;
                    i--;
                    while(i >= 0 && game_state->map[x][i] != 0)
                    {
                        i--;
                    }
                    if(i <= 0)  break;
                }
                j--;
            }
        }

        // 合并
        if(game_state->map[x][2] && game_state->map[x][3] && game_state->map[x][2] == game_state->map[x][3])
        {
            move = true;
            game_state->map[x][3] *= 2;
            game_state->score += game_state->map[x][3];
            if(game_state->map[x][0] && game_state->map[x][1] && game_state->map[x][0] == game_state->map[x][1])
            {
                game_state->map[x][2] = game_state->map[x][1] * 2;
                game_state->score += game_state->map[x][2];
                game_state->map[x][0] = game_state->map[x][1] = 0;
            }
            else
            {
                for(int y = 2; y > 0; y--)
                {
                    game_state->map[x][y] = game_state->map[x][y - 1];
                }
                game_state->map[x][0] = 0;
            }
        }
        else if(game_state->map[x][1] && game_state->map[x][2] && game_state->map[x][1] == game_state->map[x][2])
        {
            move = true;
            game_state->map[x][2] *= 2;
            game_state->score += game_state->map[x][2];
            game_state->map[x][1] = game_state->map[x][0];
            game_state->map[x][0] = 0;
        }
        else if(game_state->map[x][0] && game_state->map[x][1] && game_state->map[x][0] == game_state->map[x][1])
        {
            move = true;
            game_state->map[x][1] *= 2;
            game_state->score += game_state->map[x][1];
            game_state->map[x][0] = 0;
        }
    }
    return move;
}

bool move_down(GameState *game_state)
{
    bool move = false;
    for(int y = 0; y < 4; y++)
    {
        int i = 3;

        // 找到从下往上第一个0的x下标
        while(i >= 0 && game_state->map[i][y] != 0)
        {
            i--;
        }

        // i == 0：只有这一列第一个是0；i < 0：这一列全部都是非0数

        if(i > 0)
        {
            // 将非0数全部向下移
            int j = i - 1;
            while(j >= 0)
            {
                if(game_state->map[j][y])
                {
                    move = true;
                    game_state->map[i][y] = game_state->map[j][y];
                    game_state->map[j][y] = 0;
                    i--;
                    while(i >= 0 && game_state->map[i][y] != 0)
                    {
                        i--;
                    }
                    if(i <= 0)  break;
                }
                j--;
            }
        }

        // 合并
        if(game_state->map[2][y] && game_state->map[3][y] && game_state->map[2][y] == game_state->map[3][y])
        {
            move = true;
            game_state->map[3][y] *= 2;
            game_state->score += game_state->map[3][y];
            if(game_state->map[0][y] && game_state->map[1][y] && game_state->map[0][y] == game_state->map[1][y])
            {
                game_state->map[2][y] = game_state->map[1][y] * 2;
                game_state->score += game_state->map[2][y];
                game_state->map[0][y] = game_state->map[1][y] = 0;
            }
            else
            {
                for(int x = 2; x > 0; x--)
                {
                    game_state->map[x][y] = game_state->map[x - 1][y];
                }
                game_state->map[0][y] = 0;
            }
        }
        else if(game_state->map[1][y] && game_state->map[2][y] && game_state->map[1][y] == game_state->map[2][y])
        {
            move = true;
            game_state->map[2][y] *= 2;
            game_state->score += game_state->map[2][y];
            game_state->map[1][y] = game_state->map[0][y];
            game_state->map[0][y] = 0;
        }
        else if(game_state->map[0][y] && game_state->map[1][y] && game_state->map[0][y] == game_state->map[1][y])
        {
            move = true;
            game_state->map[1][y] *= 2;
            game_state->score += game_state->map[1][y];
            game_state->map[0][y] = 0;
        }
    }
    return move;
}