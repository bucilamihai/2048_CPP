#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<winuser.h>
using namespace std;

char board[17][33];
int brd[4][4];
bool gameOver;

void Setup()
{
    int i,j;
    for(i=0;i<17;i++)
        for(j=0;j<33;j++)
            board[i][j]=' ';
    for(i=0;i<17;i++)
        for(j=0;j<33;j+=8)
            board[i][j]='|';
    for(i=0;i<17;i+=4)
        for(j=0;j<33;j++)
            board[i][j]='-';
    /*
    [2][4]   [2][12] [2][20] [2][28]
    [6][4]   [6][12] [6][20] [6][28]
    [10][4] [10][12] [10][20] [10][28]
    [14][4] [14][12] [14][20] [14][28]
    */
}

void Display()
{
    int i,j;
    for(i=0;i<17;i++,cout<<"\n")
        for(j=0;j<33;j++)
            cout<<board[i][j];
    /*
    for(i=0;i<4;i++,cout<<"\n")
        for(j=0;j<4;j++,cout<<" ")
            cout<<brd[i][j];
            */
}

void Up()
{
    int i,j,k;
    for(j=0;j<4;j++)
        for(k=1;k<=3;k++)
            for(i=3;i>=0;i--)
                if(!brd[i][j] && brd[i+1][j])
                    brd[i][j]=brd[i+1][j],brd[i+1][j]=0;
    for(j=0;j<4;j++)
        for(i=0;i<3;i++)
            if(brd[i][j]==brd[i+1][j] && brd[i][j])
                brd[i][j]=brd[i][j]*2,brd[i+1][j]=0;
    for(j=0;j<4;j++)
        for(k=1;k<=3;k++)
            for(i=3;i>=0;i--)
                if(!brd[i][j] && brd[i+1][j])
                    brd[i][j]=brd[i+1][j],brd[i+1][j]=0;
}

void Down()
{
    int i,j,k;
    for(j=0;j<4;j++)
        for(k=1;k<=3;k++)
            for(i=0;i<3;i++)
                if(brd[i][j] && !brd[i+1][j])
                    brd[i+1][j]=brd[i][j],brd[i][j]=0;
    for(j=0;j<4;j++)
        for(i=3;i>=0;i--)
            if(brd[i][j]==brd[i+1][j] && brd[i][j])
                brd[i][j]=brd[i][j]*2,brd[i+1][j]=0;
    for(j=0;j<4;j++)
        for(k=1;k<=3;k++)
            for(i=0;i<3;i++)
                if(brd[i][j] && !brd[i+1][j])
                    brd[i+1][j]=brd[i][j],brd[i][j]=0;
}

void Left()
{
    int i,j,k;
    for(i=0;i<4;i++)
        for(k=1;k<=3;k++)
            for(j=3;j>=0;j--)
                if(!brd[i][j] && brd[i][j+1])
                    brd[i][j]=brd[i][j+1],brd[i][j+1]=0;
    for(i=0;i<4;i++)
        for(j=0;j<3;j++)
            if(brd[i][j]==brd[i][j+1] && brd[i][j])
                brd[i][j]=brd[i][j]*2,brd[i][j+1]=0;
    for(i=0;i<4;i++)
        for(k=1;k<=3;k++)
            for(j=3;j>=0;j--)
                if(!brd[i][j] && brd[i][j+1])
                    brd[i][j]=brd[i][j+1],brd[i][j+1]=0;
}

void Right()
{
    int i,j,k;
    for(i=0;i<4;i++)
        for(k=1;k<=3;k++)
            for(j=0;j<3;j++)
                if(brd[i][j] && !brd[i][j+1])
                    brd[i][j+1]=brd[i][j],brd[i][j]=0;
    for(i=0;i<4;i++)
        for(j=3;j>=0;j--)
            if(brd[i][j]==brd[i][j+1] && brd[i][j])
                brd[i][j]=brd[i][j]*2,brd[i][j+1]=0;
    for(i=0;i<4;i++)
        for(k=1;k<=3;k++)
            for(j=0;j<3;j++)
                if(brd[i][j] && !brd[i][j+1])
                    brd[i][j+1]=brd[i][j],brd[i][j]=0;
}

void Add()
{
    Setup();
    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(!brd[i][j])
                board[i*4+2][j*8+4]=' ';
            else
            {
                int x=brd[i][j];
                int y=j*8+4;
                while(x)
                {
                    board[i*4+2][y]='0'+x%10;
                    x=x/10;
                    y--;
                }
            }
    int x,posX,posY;
    x=2;
    do
    {
        posX=rand()%4;
        posY=rand()%4;
    }
    while(brd[posX][posY]);
    brd[posX][posY]=x;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(!brd[i][j])
                board[i*4+2][j*8+4]=' ';
            else
            {
                int x=brd[i][j];
                int y=j*8+4;
                while(x)
                {
                    board[i*4+2][y]='0'+x%10;
                    x=x/10;
                    y--;
                }
            }
    system("cls");
    Display();
}

void CheckGameOver()
{
    int i,j;
    bool ok=false,brdFull=true;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(!brd[i][j])
                brdFull=false;
    /// row check
    for(i=0;j<4;i++)
        for(j=0;j<3;j++)
            if(brd[i][j] && brd[i][j]==brd[i][j+1])
                ok=true;
    /// column check
    for(j=0;j<4;j++)
        for(i=0;i<3;i++)
            if(brd[i][j] && brd[i][j]==brd[i+1][j])
                ok=true;
    if(!ok && brdFull)
        gameOver=true;
}

int main()
{
    srand(time(0));
    Setup();
    Add();
    Add();
    gameOver=false;
    while(!gameOver)
    {
        /// this move the numbers up, down, left or right
        if(GetAsyncKeyState(VK_UP))
        {
            Up();
            Add();
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            Down();
            Add();
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            Left();
            Add();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            Right();
            Add();
        }
        CheckGameOver();
    }
    return 0;
}

/*
To do:

some kind of score / highscore
debugging
*/
