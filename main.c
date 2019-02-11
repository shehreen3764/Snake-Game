#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <conio.h>

#include <ctype.h>
#include <string.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length, bend_no, len, life;
char key, key1;

typedef struct
{
    int x, y, direction;
} Coordinate;
Coordinate head, bend[550], body[550], food;

void instruction()
{
    printf("\t\t\t\t WELCOME TO THE SLITHER SNAKE GAME\n\n\n");
    printf("Game Instructions:\n\n");
    printf("1.Use arrow keys to move the snake.\n");
    printf("2.You'll be provided with foods in random coordinates which you have to eat.\n");
    printf("3.Every time you eat a food, your score will increase by 1 and so will the length of the snake.\n");
    printf("4.You'll be provided with 3 lives at the beginning and you lose a life if you hit the snake's body or the wall.\n");
    printf("5.You can pause the game by pressing any key.\n");
    printf("\n\nPress any key to start playing or Esc to quit...\n");

    if(getch()==27)
        exit(1);
}

void level_menu()
{
    printf("Level:\n\n");
    printf("1. Beginner\n");
    printf("2. Expert");
    printf("\n\nPress 1 or 2 to select difficulty\n");
}

void food_fn()
{
    if(head.x==food.x && head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%60;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;

        if((food.x>=36&&food.x<=45&&food.y==14)||(food.x>=25&&food.x<=43&&food.y==29))
        {
            Sleep(30);
            food.x=rand()%60;
            if(food.x<=10)
                food.x+=11;
            food.y=rand()%30;
            if(food.y<=10)
                food.y+=11;
        }
    }
    else if(food.x==0)//create food for 1st time
    {
        food.x=rand()%60;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;

        if((food.x>=36&&food.x<=45&&food.y==14)||(food.x>=25&&food.x<=43&&food.y==29))
        {
            Sleep(35);
            food.x=rand()%60;
            if(food.x<=10)
                food.x+=11;
            food.y=rand()%30;
            if(food.y<=10)
                food.y+=11;
        }

    }

}

void gotoxy(int x, int y)
{
    HANDLE a;//HANDLE==pointer to a structure with no certain data type
    COORD b;//COORD==basic coordinate system where y=vertical axis, x=horizontal axis
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);//for cursor pos in console
    SetConsoleCursorPosition(a,b);
}

void obstacle()
{
    int row, col;
    gotoxy(36,14);
    for(row=1; row<=9; row++)
        printf("%c", 178);
    gotoxy(25, 29);
    for(row=1; row<=18; row++)
        printf("%c", 178);
}

void border()
{
    int i;
    gotoxy(food.x, food.y); //displays food
    printf("@");
    for(i=10; i<61; i++) //horizontal border
    {
        gotoxy(i,10);
        printf("_");
        gotoxy(i,30);
        printf("_");
    }
    for(i=11; i<31; i++)//vertical border
    {
        gotoxy(10,i);
        printf("|");
        gotoxy(60,i);
        printf("|");
    }
}

void loading()
{
    int row;
    gotoxy(36,14);
    printf("Loading...");
    gotoxy(32,15);
    for(row=1; row<=16; row++)
    {
        Sleep(200);
        printf("%c", 177);
    }
}

void move()
{
    int i;
    do
    {
        food_fn();
        fflush(stdout);
        len=0;
        for(i=0; i<30; i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
                break;
        }
        Sleep(40);

        Score();

        system("cls");
        border();

        if(key1=='2')
            obstacle();

        if(head.direction==RIGHT)
            right();
        else if(head.direction==LEFT)
            left();
        else if (head.direction==UP)
            up();
        else
            down();

        gameover();
    }
    while(!kbhit());


    if(getch()==27)
    {
        system("cls");
        exit(1);
    }

    key=getch();
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;

        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;

        move();
    }

    else if(key==27)
    {
        system("cls");
        exit(1);
    }

    else
    {
        printf("\a");
        move();
    }
}

void down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        gotoxy(head.x, head.y-i);
        {
            if(len==0)
                printf("X");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }

    BEND();
    if(!kbhit())
        head.y++;
}

void up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        gotoxy(head.x, head.y+i);
        {
            if(len==0)
                printf("X");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }

    BEND();
    if(!kbhit())
        head.y--;
}

void right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        gotoxy(body[len].x,body[len].y);
        {
            if(len==0)
                printf("X");
            else
                printf("*");
        }

        len++;
    }

    BEND();
    if(!kbhit())
        head.x++;
}

void left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {

        gotoxy(head.x+i,head.y);
        {
            if(len==0)
                printf("X");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }

    BEND();
    if(!kbhit())
        head.x--;
}

void BEND()
{
    int i, j, difference;
    for(i=bend_no; i>=0 && len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            difference=bend[i].y-bend[i-1].y;
            if(difference<0)
            {
                for(j=1; j<=(-difference); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    gotoxy(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            }

            else if(difference>0)
            {
                for(j=1; j<=difference; j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    gotoxy(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            }
        }

        else if(bend[i].y==bend[i-1].y)
        {
            difference=bend[i].x-bend[i-1].x;
            if(difference<0)
            {
                for(j=1; j<=(-difference) && len<length; j++)
                {
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    gotoxy(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            }

            else if(difference>0)
            {
                for(j=1; j<=difference && len<length; j++)
                {
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    gotoxy(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            }
        }
    }
}

int score_only()
{
    int score=Score();
    system("cls");
    return score;
}

void gameover()
{
    int i, flag=0, k;

    //touch itself
    for(i=4; i<length; i++)
    {
        if(body[0].x==body[i].x && body[0].y==body[i].y)
            flag=1;
        if(i==length||flag==1)
            break;
    }

    //touch border
    if(head.x<=10||head.x>=60||head.y<=10||head.y>=30||flag==1)
    {
        life--;
        if(life>0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            move();
        }
        else
        {
            system("cls");
            printf("\n\n\t\tGAME OVER\n\t\tSCORE: %d\n\n\tPress any key to quit the game.\n", k=score_only());
            record();
            exit(1);
        }
    }

    //touch obstacle
    if(key1=='2')
    {
        if(((head.x>=36&&head.x<=45)&&head.y==14)||((head.x<=25&&head.x>=43)&&head.y==29)||flag==1)
        {
            life--;
            if(life>0)
            {
                head.x=25;
                head.y=20;
                bend_no=0;
                head.direction=RIGHT;
                move();
            }
            else
            {
                system("cls");
                printf("\n\n\t\tGAME OVER\n\t\tSCORE: %d\n\n\tPress any key to quit the game.\n", k=score_only());
                record();
                exit(1);
            }
        }
    }
}

struct highscore
{
    char name[50];
    int score;
};
typedef struct highscore Hscore;

void record()
{
    FILE *fp;
    Hscore arr[100];
    char c[50];
    int i=0, j, k, q, number, n;
    fp=fopen("abcd.txt", "a");

    fflush(stdin);
    getch();
    system("cls");
    printf("Enter your name: ");
    gets(c);

    fputs(c, fp);
    fputc('\n', fp);
    number=score_only();
    fwrite(&number, sizeof(number), 1, fp);
    fclose(fp);

    fp=fopen("abcd.txt", "r");
    while(fgets(c, 50, fp)!=NULL)
    {
        strcpy(arr[i].name,c);
        fread(&n, sizeof(n), 1, fp);
        arr[i].score=n;
        i++;
    }

    Hscore temp;
    for(k=0; k<(i-1); k++)
    {
        for(q=(k+1); q<i; q++)
        {
            if(arr[k].score<arr[q].score)
            {
                temp=arr[k];
                arr[k]=arr[q];
                arr[q]=temp;
            }
        }
    }

    system("cls");
    printf("Do you wanna see past record? (Y/y)/(N/n)\n\n");
    char ch=getch();
    if(ch=='Y'||ch=='y')
    {
        system("cls");
        printf("\tThese are the top 10 highscores\n\n");
        for(k=0; k<10; k++)
        {
            printf("\n\t\t%s", arr[k].name);
            printf("\t\t  %d\n", arr[k].score);
            for(int l=0; l<50; l++)
                printf("_");
            printf("\n");
        }
    }
    else
        exit(1);

    fclose(fp);
}

int Score()
{
    int score;
    gotoxy(20,8);
    score=length-5;
    printf("SCORE: %d", score);
    gotoxy(50,8);
    printf("LIFE: %d", life);
    return score;
}

int main()
{
    instruction();
    system("cls");
    level_menu();
    key1=getch();
    system("cls");
    loading();

    length=5;
    head.x=25;
    head.y=20;
    head.direction=RIGHT;

    if(key1=='1')
    {
        food_fn();
        life=3;
        bend[0]=head;
        move();
    }

    else if(key1=='2')
    {
        food_fn();
        life=3;
        bend[0]=head;
        move();
    }

    return 0;
}
