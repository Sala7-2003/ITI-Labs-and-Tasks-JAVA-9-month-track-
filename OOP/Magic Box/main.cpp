#include <stdio.h>
# include<Windows.h>
#include<conio.h>



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
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

int getConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}


int main()
{
      int g_size;
      printf( "Enter the grid size (it must be an odd value)\n");
      scanf_s("%d", &g_size);
      
      int width = getConsoleWidth();
      int height = getConsoleHeight();



      int x_ = 0, y_ = 0;
      int xStep = width / (g_size + 1);
      int yStep = height / (g_size + 1);


      int row = 0 ;              
      int col = 0;     

      for (int i = 1; i <= g_size * g_size; i++) {
          if (i == 1)
          {
              row = 1;
              col = (g_size + 1) / 2;
          }
          else if (((i-1)  % g_size) == 0) {
              row++;
              if (row > g_size)
                  row --;
          }
          else {
              row--; col--;
              if (row == 0)
                  row = g_size;
              if (col == 0)
                  col = g_size;
          }
          gotoxy(col * xStep, row * yStep);
          printf(" %d ", i);



          }
      }