#include <iostream>
using namespace std;

#define MAX 4
#define UP 1
#define DOWN 2
#define FRONT 3
#define BACK 4
#define LEFT 5
#define RIGHT 6
char cube[7][MAX][MAX];

void left_rotate(char str) {
    char temp[7][MAX][MAX] = {0, };
    if(str == '-') {
        for(int i = 1; i <= 3; i++) temp[BACK][i][1] = cube[UP][i][1];
        for(int i = 1; i <= 3; i++) temp[UP][i][1] = cube[FRONT][i][1];
        for(int i = 1; i <= 3; i++) temp[FRONT][i][1] = cube[DOWN][i][1];
        for(int i = 1; i <= 3; i++) temp[DOWN][i][1] = cube[BACK][i][1];

        for(int i = 1; i <= 3; i++) temp[LEFT][1][4 - i] = cube[LEFT][i][1];
        for(int i = 1; i <= 3; i++) temp[LEFT][i][1] = cube[LEFT][3][i];
        for(int i = 1; i <= 3; i++) temp[LEFT][3][4 - i] = cube[LEFT][i][3];
        for(int i = 1; i <= 3; i++) temp[LEFT][i][3] = cube[LEFT][1][i];

        for(int i = 1; i <= 3; i++) cube[LEFT][1][i] = temp[LEFT][1][i];
        for(int i = 1; i <= 3; i++) cube[LEFT][i][3] = temp[LEFT][i][3];
        for(int i = 1; i <= 3; i++) cube[LEFT][3][i] = temp[LEFT][3][i];
        for(int i = 1; i <= 3; i++) cube[LEFT][i][1] = temp[LEFT][i][1];
    }
    else if(str == '+') {
        for(int i = 1; i <= 3; i++) temp[FRONT][i][1] = cube[UP][i][1];
        for(int i = 1; i <= 3; i++) temp[DOWN][i][1] = cube[FRONT][i][1];
        for(int i = 1; i <= 3; i++) temp[BACK][i][1] = cube[DOWN][i][1];
        for(int i = 1; i <= 3; i++) temp[UP][i][1] = cube[BACK][i][1];

        for(int i = 1; i <= 3; i++) temp[LEFT][3][i] = cube[LEFT][i][1];
        for(int i = 1; i <= 3; i++) temp[LEFT][4 - i][3] = cube[LEFT][3][i];
        for(int i = 1; i <= 3; i++) temp[LEFT][1][i] = cube[LEFT][i][3];
        for(int i = 1; i <= 3; i++) temp[LEFT][4 - i][1] = cube[LEFT][1][i];

        for(int i = 1; i <= 3; i++) cube[LEFT][1][i] = temp[LEFT][1][i];
        for(int i = 1; i <= 3; i++) cube[LEFT][i][3] = temp[LEFT][i][3];
        for(int i = 1; i <= 3; i++) cube[LEFT][3][i] = temp[LEFT][3][i];
        for(int i = 1; i <= 3; i++) cube[LEFT][i][1] = temp[LEFT][i][1];
    }
    for (int i = 1; i <= 3; i++) cube[UP][i][1] = temp[UP][i][1];
    for (int i = 1; i <= 3; i++) cube[BACK][i][1] = temp[BACK][i][1];
    for (int i = 1; i <= 3; i++) cube[DOWN][i][1] = temp[DOWN][i][1];
    for (int i = 1; i <= 3; i++) cube[FRONT][i][1] = temp[FRONT][i][1];
}

void right_rotate(char str) {
    char temp[7][MAX][MAX] = {0, };
    if(str == '-') {
        for(int i = 1; i <= 3; i++) temp[FRONT][i][3] = cube[UP][i][3];
        for(int i = 1; i <= 3; i++) temp[DOWN][i][3] = cube[FRONT][i][3];
        for(int i = 1; i <= 3; i++) temp[BACK][i][3] = cube[DOWN][i][3];
        for(int i = 1; i <= 3; i++) temp[UP][i][3] = cube[BACK][i][3];

        for(int i = 1; i <= 3; i++) temp[RIGHT][1][4 - i] = cube[RIGHT][i][1];
        for(int i = 1; i <= 3; i++) temp[RIGHT][i][1] = cube[RIGHT][3][i];
        for(int i = 1; i <= 3; i++) temp[RIGHT][3][4 - i] = cube[RIGHT][i][3];
        for(int i = 1; i <= 3; i++) temp[RIGHT][i][3] = cube[RIGHT][1][i];

        for(int i = 1; i <= 3; i++) cube[RIGHT][1][i] = temp[RIGHT][1][i];
        for(int i = 1; i <= 3; i++) cube[RIGHT][i][3] = temp[RIGHT][i][3];
        for(int i = 1; i <= 3; i++) cube[RIGHT][3][i] = temp[RIGHT][3][i];
        for(int i = 1; i <= 3; i++) cube[RIGHT][i][1] = temp[RIGHT][i][1];
    }
    else if(str == '+') {
        for(int i = 1; i <= 3; i++) temp[BACK][i][3] = cube[UP][i][3];
        for(int i = 1; i <= 3; i++) temp[UP][i][3] = cube[FRONT][i][3];
        for(int i = 1; i <= 3; i++) temp[FRONT][i][3] = cube[DOWN][i][3];
        for(int i = 1; i <= 3; i++) temp[DOWN][i][3] = cube[BACK][i][3];

        for(int i = 1; i <= 3; i++) temp[RIGHT][3][i] = cube[RIGHT][i][1];
        for(int i = 1; i <= 3; i++) temp[RIGHT][4 - i][3] = cube[RIGHT][3][i];
        for(int i = 1; i <= 3; i++) temp[RIGHT][1][i] = cube[RIGHT][i][3];
        for(int i = 1; i <= 3; i++) temp[RIGHT][4 - i][1] = cube[RIGHT][1][i];

        for(int i = 1; i <= 3; i++) cube[RIGHT][1][i] = temp[RIGHT][1][i];
        for(int i = 1; i <= 3; i++) cube[RIGHT][i][3] = temp[RIGHT][i][3];
        for(int i = 1; i <= 3; i++) cube[RIGHT][3][i] = temp[RIGHT][3][i];
        for(int i = 1; i <= 3; i++) cube[RIGHT][i][1] = temp[RIGHT][i][1];
    }
    for (int i = 1; i <= 3; i++) cube[UP][i][3] = temp[UP][i][3];
    for (int i = 1; i <= 3; i++) cube[BACK][i][3] = temp[BACK][i][3];
    for (int i = 1; i <= 3; i++) cube[DOWN][i][3] = temp[DOWN][i][3];
    for (int i = 1; i <= 3; i++) cube[FRONT][i][3] = temp[FRONT][i][3];
}

void front_rotate(char str) {
    char temp[7][MAX][MAX] = {0, };
    if(str == '-') {
        for(int i = 1; i <= 3; i++) temp[LEFT][3][4 - i] = cube[UP][3][i];
        for(int i = 1; i <= 3; i++) temp[UP][3][i] = cube[RIGHT][1][i];
        for(int i = 1; i <= 3; i++) temp[RIGHT][1][4 - i] = cube[DOWN][1][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][1][i] = cube[LEFT][3][i];

        for(int i = 1; i <= 3; i++) temp[FRONT][4 - i][1] = cube[FRONT][1][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][1][i] = cube[FRONT][i][3];
        for(int i = 1; i <= 3; i++) temp[FRONT][4 - i][3] = cube[FRONT][3][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][3][i] = cube[FRONT][i][1];

        for(int i = 1; i <= 3; i++) cube[FRONT][1][i] = temp[FRONT][1][i];
        for(int i = 1; i <= 3; i++) cube[FRONT][i][3] = temp[FRONT][i][3];
        for(int i = 1; i <= 3; i++) cube[FRONT][i][1] = temp[FRONT][i][1];
        for(int i = 1; i <= 3; i++) cube[FRONT][3][i] = temp[FRONT][3][i];
    }
    else if(str == '+') {
        for(int i = 1; i <= 3; i++) temp[RIGHT][1][i] = cube[UP][3][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][1][4 - i] = cube[RIGHT][1][i];
        for(int i = 1; i <= 3; i++) temp[LEFT][3][i] = cube[DOWN][1][i];
        for(int i = 1; i <= 3; i++) temp[UP][3][4 - i] = cube[LEFT][3][i];

        for(int i = 1; i <= 3; i++) temp[FRONT][i][3] = cube[FRONT][1][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][3][4 - i] = cube[FRONT][i][3];
        for(int i = 1; i <= 3; i++) temp[FRONT][i][1] = cube[FRONT][3][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][1][4 - i] = cube[FRONT][i][1];

        for(int i = 1; i <= 3; i++) cube[FRONT][1][i] = temp[FRONT][1][i];
        for(int i = 1; i <= 3; i++) cube[FRONT][i][3] = temp[FRONT][i][3];
        for(int i = 1; i <= 3; i++) cube[FRONT][i][1] = temp[FRONT][i][1];
        for(int i = 1; i <= 3; i++) cube[FRONT][3][i] = temp[FRONT][3][i];
    }
    for (int i = 1; i <= 3; i++) cube[UP][3][i] = temp[UP][3][i];
    for (int i = 1; i <= 3; i++) cube[LEFT][3][i] = temp[LEFT][3][i];
    for (int i = 1; i <= 3; i++) cube[DOWN][1][i] = temp[DOWN][1][i];
    for (int i = 1; i <= 3; i++) cube[RIGHT][1][i] = temp[RIGHT][1][i];
}

void back_rotate(char str) {
    char temp[7][MAX][MAX] = {0, };
    if(str == '-') {
        for(int i = 1; i <= 3; i++) temp[RIGHT][3][i] = cube[UP][1][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][3][4 - i] = cube[RIGHT][3][i];
        for(int i = 1; i <= 3; i++) temp[LEFT][1][i] = cube[DOWN][3][i];
        for(int i = 1; i <= 3; i++) temp[UP][1][4 - i] = cube[LEFT][1][i];

        for(int i = 1; i <= 3; i++) temp[BACK][4 - i][3] = cube[BACK][3][i];
        for(int i = 1; i <= 3; i++) temp[BACK][1][i] = cube[BACK][i][3];
        for(int i = 1; i <= 3; i++) temp[BACK][4 - i][1] = cube[BACK][1][i];
        for(int i = 1; i <= 3; i++) temp[BACK][3][i] = cube[BACK][i][1];

        for(int i = 1; i <= 3; i++) cube[BACK][3][i] = temp[BACK][3][i];
        for(int i = 1; i <= 3; i++) cube[BACK][i][3] = temp[BACK][i][3];
        for(int i = 1; i <= 3; i++) cube[BACK][1][i] = temp[BACK][1][i];
        for(int i = 1; i <= 3; i++) cube[BACK][i][1] = temp[BACK][i][1];
    }
    else if(str == '+') {
        for(int i = 1; i <= 3; i++) temp[LEFT][1][4 - i] = cube[UP][1][i];
        for(int i = 1; i <= 3; i++) temp[UP][1][i] = cube[RIGHT][3][i];
        for(int i = 1; i <= 3; i++) temp[RIGHT][3][4 - i] = cube[DOWN][3][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][3][i] = cube[LEFT][1][i];

        for(int i = 1; i <= 3; i++) temp[BACK][i][1] = cube[BACK][3][i];
        for(int i = 1; i <= 3; i++) temp[BACK][3][4 - i] = cube[BACK][i][3];
        for(int i = 1; i <= 3; i++) temp[BACK][i][3] = cube[BACK][1][i];
        for(int i = 1; i <= 3; i++) temp[BACK][1][4 - i] = cube[BACK][i][1];
        
        for(int i = 1; i <= 3; i++) cube[BACK][3][i] = temp[BACK][3][i];
        for(int i = 1; i <= 3; i++) cube[BACK][i][3] = temp[BACK][i][3];
        for(int i = 1; i <= 3; i++) cube[BACK][1][i] = temp[BACK][1][i];
        for(int i = 1; i <= 3; i++) cube[BACK][i][1] = temp[BACK][i][1];
    }
    for (int i = 1; i <= 3; i++) cube[UP][1][i] = temp[UP][1][i];
    for (int i = 1; i <= 3; i++) cube[LEFT][1][i] = temp[LEFT][1][i];
    for (int i = 1; i <= 3; i++) cube[DOWN][3][i] = temp[DOWN][3][i];
    for (int i = 1; i <= 3; i++) cube[RIGHT][3][i] = temp[RIGHT][3][i];
}

void up_rotate(char str) {
    char temp[7][MAX][MAX] = {0, };
    if(str == '-') {
        for(int i = 1; i <= 3; i++) temp[RIGHT][i][1] = cube[FRONT][1][i];
        for(int i = 1; i <= 3; i++) temp[BACK][3][4 - i] = cube[RIGHT][i][1];
        for(int i = 1; i <= 3; i++) temp[LEFT][4 - i][1] = cube[BACK][3][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][1][i] = cube[LEFT][i][1];

        for(int i = 1; i <= 3; i++) temp[UP][4 - i][1] = cube[UP][1][i];
        for(int i = 1; i <= 3; i++) temp[UP][1][i] = cube[UP][i][3];
        for(int i = 1; i <= 3; i++) temp[UP][4 - i][3] = cube[UP][3][i];
        for(int i = 1; i <= 3; i++) temp[UP][3][i] = cube[UP][i][1];

        for(int i = 1; i <= 3; i++) cube[UP][1][i] = temp[UP][1][i];
        for(int i = 1; i <= 3; i++) cube[UP][i][3] = temp[UP][i][3];
        for(int i = 1; i <= 3; i++) cube[UP][i][1] = temp[UP][i][1];
        for(int i = 1; i <= 3; i++) cube[UP][3][i] = temp[UP][3][i];
    }
    else if(str == '+') {
        for(int i = 1; i <= 3; i++) temp[LEFT][i][1] = cube[FRONT][1][i];
        for(int i = 1; i <= 3; i++) temp[BACK][3][4 - i] = cube[LEFT][i][1];
        for(int i = 1; i <= 3; i++) temp[RIGHT][4 - i][1] = cube[BACK][3][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][1][i] = cube[RIGHT][i][1];

        for(int i = 1; i <= 3; i++) temp[UP][i][3] = cube[UP][1][i];
        for(int i = 1; i <= 3; i++) temp[UP][3][4 - i] = cube[UP][i][3];
        for(int i = 1; i <= 3; i++) temp[UP][i][1] = cube[UP][3][i];
        for(int i = 1; i <= 3; i++) temp[UP][1][4 - i] = cube[UP][i][1];

        for(int i = 1; i <= 3; i++) cube[UP][1][i] = temp[UP][1][i];
        for(int i = 1; i <= 3; i++) cube[UP][i][3] = temp[UP][i][3];
        for(int i = 1; i <= 3; i++) cube[UP][i][1] = temp[UP][i][1];
        for(int i = 1; i <= 3; i++) cube[UP][3][i] = temp[UP][3][i];
    }
    for (int i = 1; i <= 3; i++) cube[FRONT][1][i] = temp[FRONT][1][i];
    for (int i = 1; i <= 3; i++) cube[LEFT][i][1] = temp[LEFT][i][1];
    for (int i = 1; i <= 3; i++) cube[BACK][3][i] = temp[BACK][3][i];
    for (int i = 1; i <= 3; i++) cube[RIGHT][i][1] = temp[RIGHT][i][1];
}

void down_rotate(char str) {
    char temp[7][MAX][MAX] = {0, };
    if(str == '-') {
        for(int i = 1; i <= 3; i++) temp[LEFT][i][3] = cube[FRONT][3][i];
        for(int i = 1; i <= 3; i++) temp[BACK][1][4 - i] = cube[LEFT][i][3];
        for(int i = 1; i <= 3; i++) temp[RIGHT][4 - i][3] = cube[BACK][1][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][3][i] = cube[RIGHT][i][3];

        for(int i = 1; i <= 3; i++) temp[DOWN][4 - i][1] = cube[DOWN][1][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][1][i] = cube[DOWN][i][3];
        for(int i = 1; i <= 3; i++) temp[DOWN][4 - i][3] = cube[DOWN][3][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][3][i] = cube[DOWN][i][1];

        for(int i = 1; i <= 3; i++) cube[DOWN][1][i] = temp[DOWN][1][i];
        for(int i = 1; i <= 3; i++) cube[DOWN][i][3] = temp[DOWN][i][3];
        for(int i = 1; i <= 3; i++) cube[DOWN][i][1] = temp[DOWN][i][1];
        for(int i = 1; i <= 3; i++) cube[DOWN][3][i] = temp[DOWN][3][i];
    }
    else if(str == '+') {
        for(int i = 1; i <= 3; i++) temp[RIGHT][i][3] = cube[FRONT][3][i];
        for(int i = 1; i <= 3; i++) temp[BACK][1][4 - i] = cube[RIGHT][i][3];
        for(int i = 1; i <= 3; i++) temp[LEFT][4 - i][3] = cube[BACK][1][i];
        for(int i = 1; i <= 3; i++) temp[FRONT][3][i] = cube[LEFT][i][3];

        for(int i = 1; i <= 3; i++) temp[DOWN][i][3] = cube[DOWN][1][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][3][4 - i] = cube[DOWN][i][3];
        for(int i = 1; i <= 3; i++) temp[DOWN][i][1] = cube[DOWN][3][i];
        for(int i = 1; i <= 3; i++) temp[DOWN][1][4 - i] = cube[DOWN][i][1];

        for(int i = 1; i <= 3; i++) cube[DOWN][1][i] = temp[DOWN][1][i];
        for(int i = 1; i <= 3; i++) cube[DOWN][i][3] = temp[DOWN][i][3];
        for(int i = 1; i <= 3; i++) cube[DOWN][i][1] = temp[DOWN][i][1];
        for(int i = 1; i <= 3; i++) cube[DOWN][3][i] = temp[DOWN][3][i];
    }
    for (int i = 1; i <= 3; i++) cube[FRONT][3][i] = temp[FRONT][3][i];
    for (int i = 1; i <= 3; i++) cube[LEFT][i][3] = temp[LEFT][i][3];
    for (int i = 1; i <= 3; i++) cube[BACK][1][i] = temp[BACK][1][i];
    for (int i = 1; i <= 3; i++) cube[RIGHT][i][3] = temp[RIGHT][i][3];
}

void cube_init(void) {
    // 1(U), 2(D), 3(F), 4(B), 5(L), 6(R)
    for(int k = 1; k <= 6; k++){
        for(int i = 1; i <= 3; i++){
            for(int j = 1; j <= 3; j++){
                if(k == UP) cube[k][i][j] = 'w';
                else if(k == DOWN) cube[k][i][j] = 'y';
                else if(k == FRONT) cube[k][i][j] = 'r';
                else if(k == BACK) cube[k][i][j] = 'o';
                else if(k == LEFT) cube[k][i][j] = 'g';
                else if(k == RIGHT) cube[k][i][j] = 'b';
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int C; cin >> C;
        cube_init();
        for(int j = 0; j < C; j++) {
            char str[3]; cin >> str;
            if(str[0] == 'L') left_rotate(str[1]);
            if(str[0] == 'R') right_rotate(str[1]);
            if(str[0] == 'U') up_rotate(str[1]);
            if(str[0] == 'D') down_rotate(str[1]);
            if(str[0] == 'F') front_rotate(str[1]);
            if(str[0] == 'B') back_rotate(str[1]);
        }
        for (int h = 1; h <= 3; h++){
            for (int w = 1; w <= 3; w++){
                cout << cube[UP][h][w];
            }
            cout << '\n';
        }
    }
    return 0;
}