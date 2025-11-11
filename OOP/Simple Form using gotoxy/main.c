#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}


struct Employee {
    int id;
    char name[50];
    int salary;
    int bonus;
    int deduct;
};

static int emp_counter = 0;    
static int emp_limit = 0;      
struct Employee* e = NULL;     

void displayNew()
{
    system("cls");
    int width = getConsoleWidth() / 6;
    int height = getConsoleHeight() / 6;


    if (emp_counter >= emp_limit)
    {
        gotoxy(width * 2, height * 3);
        setColor(12);
        printf("You reached the maximum number of employees (%d)!", emp_limit);
        setColor(7);
        _getch();
        return;
    }

    char ch;

    gotoxy(width * 2, height * 1);
    setColor(31);
    printf(" ===> Id: ");
    setColor(7);
    scanf_s("%d", &e[emp_counter].id);

    gotoxy(width * 2, height * 2);
    setColor(31);
    printf(" ===> Name: ");
    setColor(7);
    getchar();
    gets_s(e[emp_counter].name, 50);

    gotoxy(width * 2, height * 3);
    setColor(31);
    printf(" ===> Salary: ");
    setColor(7);
    scanf_s("%d", &e[emp_counter].salary);

    gotoxy(width * 2, height * 4);
    setColor(31);
    printf(" ===> Bonus: ");
    setColor(7);
    scanf_s("%d", &e[emp_counter].bonus);

    gotoxy(width * 2, height * 5);
    setColor(31);
    printf(" ===> Deduct: ");
    setColor(7);
    scanf_s("%d", &e[emp_counter].deduct);

    gotoxy(width * 2, height * 6);
    printf("Are you sure you want to save? (S/N): ");
    ch = _getch();

    if (ch == 's' || ch == 'S')
    {
        emp_counter++;
        printf("\nEmployee added successfully!");
    }
    else
    {
        printf("\nCanceled. Press any key to return...");
    }

    _getch();
}


void displayEmployees()
{
    system("cls");
    int width = getConsoleWidth() / 6;
    int height = getConsoleHeight() / 6;

    if (emp_counter == 0)
    {
        gotoxy(width * 2, height * 2);
        printf("No employees to display.");
        _getch();
        return;
    }

    int i = 0;
    while (1)
    {
        system("cls");
        gotoxy(width, height * 2);
        printf("Employee %d of %d\n", i + 1, emp_counter);
        gotoxy(width, height * 3);
        printf("\nId: %d", e[i].id);
        gotoxy(width, height * 4);
        printf("\nName: %s", e[i].name);
        gotoxy(width, height * 5);
        printf("\nSalary: %d", e[i].salary);
        gotoxy(width, height * 6);
        printf("\nBonus: %d", e[i].bonus);
        gotoxy(width, height * 7);
        printf("\nDeduct: %d", e[i].deduct);
        gotoxy(width, height * 8);
        printf("\nNet Salary: %d\n", e[i].salary + e[i].bonus - e[i].deduct);

        gotoxy(width, height * 10);
        printf("Use ? ? to navigate, ESC to return");

        int x = _getch();
        if (x == 224) // arrow keys
        {
            x = _getch();
            switch (x)
            {
            case 75: // Left arrow
                if (i > 0)
                    i--;
                break;
            case 77: // Right arrow
                if (i < emp_counter - 1)
                    i++;
                break;
            }
        }
        else if (x == 27) // ESC
        {
            break;
        }
    }
}

// Main menu
void mainMenu()
{
    int width = getConsoleWidth() / 4;
    int height = getConsoleHeight() / 4;

    char menu[3][10] = { "New", "Display", "Exit" };
    int turn = 1;

    while (1)
    {
        system("cls");
        for (int i = 0; i < 3; i++)
        {
            gotoxy(width * 2, height * (i + 1));
            if ((i + 1) == turn)
            {
                setColor(31);
                printf(" ===>  %s  ", menu[i]);
                setColor(7);
            }
            else
            {
                printf("     %s   ", menu[i]);
            }
        }

        int x = _getch();
        if (x == 224)
        {
            x = _getch();
            switch (x)
            {
            case 72:
                turn = (turn == 1) ? 3 : turn - 1;
                break;
            case 80:
                turn = (turn == 3) ? 1 : turn + 1;
                break;
            case 71:
                turn = 1;
                break;
            case 79:
                turn = 3;
                break;
            }
        }
        else if (x == 13)
        {
            if (turn == 1)
                displayNew();
            else if (turn == 2)
                displayEmployees();
            else if (turn == 3)
            {
                free(e);
                exit(0);
            }
        }
        else if (x == 27)
        {
            free(e);
            exit(0);
        }
    }
}


void setupEmployees()
{
    system("cls");
    int width = getConsoleWidth() / 4;
    int height = getConsoleHeight() / 4;

    gotoxy(width, height);
    //setColor(31);
    printf("Enter the number of employees you want to save: ");
    setColor(7);
    scanf_s("%d", &emp_limit);

    e = (struct Employee*)malloc(emp_limit * sizeof(struct Employee));

    if (e == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    gotoxy(width, height + 2);
    printf("Successfully allocated space for %d employees.", emp_limit);
    _getch();
}

int main()
{
    setupEmployees();
    mainMenu();
    return 0;
}
