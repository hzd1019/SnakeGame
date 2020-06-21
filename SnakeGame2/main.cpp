#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

bool game_over;
const int GAME_SIZE_HORIZONTAL = 33;
const int GAME_SIZE_VERTICAL = 16;
int snake_x;
int snake_y;
int tails_x[100];
int tails_y[100];
int n_tails;
int fruit_x;
int fruit_y;

int SCORE;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;



void SetUp() {
game_over = false;
dir = STOP;

snake_x = GAME_SIZE_HORIZONTAL/2;
snake_y = GAME_SIZE_VERTICAL/2;

fruit_x = rand() % (GAME_SIZE_HORIZONTAL-2)+1;
fruit_y = rand() % (GAME_SIZE_VERTICAL-2)+1;

SCORE = 0;
n_tails = 1;



}

void Draw() {

    system("cls");

    for(int i = 0; i < GAME_SIZE_HORIZONTAL ; i++) {
        cout << "#";
    }
    cout << endl;
for(int j = 0; j < GAME_SIZE_VERTICAL; j++) {

    for(int i = 0; i < GAME_SIZE_HORIZONTAL ; i++) {
        if(i == 0 || i == GAME_SIZE_HORIZONTAL -1) {
            cout <<  "#";
        }

        else if(i == snake_x && j == snake_y) {
            cout << "O";
        }



        else if(i == fruit_x && j == fruit_y) {
            cout << "@";
        }

        else {
                bool print = false;

                for(int k = 0; k < n_tails; k++) {


                    if(tails_x[k] == i && tails_y[k] == j) {
                        cout << "o";
                        print = true;
                    }
                }

              if(!print) {
                cout << " ";

                   }

        }


    }

    cout << endl;

}

for(int i = 0; i < GAME_SIZE_HORIZONTAL; i++) {
        cout << "#";
    }

cout << endl << endl << "SCORE: " << SCORE << endl;


}


void Logic() {

    int prevX = tails_x[0];
    int prevY = tails_y[0];
    int prev2X, prev2Y;
    tails_x[0] = snake_x;
    tails_y[0] = snake_y;

    for(int i = 1; i < n_tails; i++) {
        prev2X = tails_x[i];
        prev2Y = tails_y[i];
        tails_x[i] = prevX;
        tails_y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir) {
     case LEFT:
     snake_x--;
     break;
     case RIGHT:
      snake_x++;
      break;
     case UP:
        snake_y--;
        break;
     case DOWN:
        snake_y++;
        break;
     default:
        break;
    }



  if(snake_x >= GAME_SIZE_HORIZONTAL-1) {
    snake_x = 1;
  }

  else if(snake_x <= 0) {
    snake_x = GAME_SIZE_HORIZONTAL-1;
  }

  else if(snake_y >= GAME_SIZE_VERTICAL) {
    snake_y = 0;
  }

  else if(snake_y < 0) {
    snake_y = GAME_SIZE_VERTICAL - 1;
  }


  for(int i = 1; i < 100; i++) {
    if(tails_x[i] == snake_x && tails_y[i] == snake_y) {
            Draw();
        game_over = true;
    }
  }

  if(snake_x == fruit_x && snake_y == fruit_y) {
    SCORE++;

    fruit_x = rand() % (GAME_SIZE_HORIZONTAL-2)+1;
    fruit_y = rand() % (GAME_SIZE_VERTICAL-2)+1;
     n_tails++;
  }


}

void Input() {

if(_kbhit()) {
    switch(_getch()) {

    case 'a':
     dir = LEFT;
     break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    case 'v':
      game_over = true;
        break;

    }
}

}




int main()
{
    bool play = true;

    while(play) {
    srand(time(0));
   SetUp();

  while(!game_over) {
    Draw();
    Input();
    Logic();
    Sleep(10);

  }

  cout << "Do you want to play again?" << endl;
  char y_n;
  cin >> y_n;
  if(y_n != 'y') {
    play  = false;
  }

  else {
    n_tails = 1;
  }

}
    return 0;
}
