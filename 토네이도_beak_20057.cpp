#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N;

int sand[499][499] = {
    0,
};

bool visited[499][499];

int weights[4][5][5] = {
    // 0 왼, 1 아래, 2 오른, 3 위
    {
        //왼
        {0, 0, 2, 0, 0},
        {0, 10, 7, 1, 0},
        {5, -1, -2, -3, 0}, // -1 a, -2 y, -3 x
        {0, 10, 7, 1, 0},
        {0, 0, 2, 0, 0},
    },
    {
        //아래
        {0, 0, 0, 0, 0},
        {0, 1, -3, 1, 0},
        {2, 7, -2, 7, 2}, // -1 a, -2 y, -3 x
        {0, 10, -1, 10, 0},
        {0, 0, 5, 0, 0},
    },
    {
        //오른
        {0, 0, 2, 0, 0},
        {0, 1, 7, 10, 0},
        {0, -3, -2, -1, 5}, // -1 a, -2 y, -3 x
        {0, 1, 7, 10, 0},
        {0, 0, 2, 0, 0},
    },
    {
        //위
        {0, 0, 5, 0, 0},
        {0, 10, -1, 10, 0},
        {2, 7, -2, 7, 2}, // -1 a, -2 y, -3 x
        {0, 1, -3, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

template <typename T>
void print_array(T array[499][499], int R, int C)
{
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cout << array[r][c] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}


int d; // 0 : left, 1 : down, 2 : right, 3 : up

class Pos {

public:
    int r;
    int c;

public:

    Pos()
    {
        r = 0;
        c = 0;
    }

    Pos(int _r, int _c)
    {
        r = _r;
        c = _c;
    }

    void print()
    {
        cout << "r , c : " << r << ", " << c << endl;
    }
};

bool is_valid_pos(Pos p)
{
    if (p.c >= 0 && p.c < N && p.r >= 0 && p.r < N)
        return true;
    else
        return false;
}

Pos next_position(Pos start_pos, int dir)
{
    Pos next_pos;
    next_pos = start_pos;

    switch (dir) // left
    {
    case 0:
        next_pos.c = start_pos.c - 1;
        break;
    case 1:
        next_pos.r = start_pos.r + 1;
        break;
    case 2:
        next_pos.c = start_pos.c + 1;
        break;
    case 3:
        next_pos.r = start_pos.r - 1;
        break;
    }

    return next_pos;

}

void update_direction(int& cur_dir, Pos& cur_pos)
{
    int next_dir = cur_dir;
    next_dir++;
    next_dir = next_dir % 4;

    // 다음 예상 좌표 위치
    Pos next_pos = next_position(cur_pos, next_dir);
    if (visited[next_pos.r][next_pos.c] == true) // 이미 방문 좌표
    {

        // 방향 그대로, 예상 좌표 다시 받기
        next_pos = next_position(cur_pos, cur_dir);

    }
    else {// 처음 방문
        // 방향 업데이트
        cur_dir = next_dir;
    }
    // 좌표 업데이트
    cur_pos = next_pos;
    visited[cur_pos.r][cur_pos.c] = true;
}

int sand_amount_out = 0;


void tornado(Pos y, int dir)
{
    int sand_amount = 0;
    int sand_amount_y = sand[y.r][y.c];
    int sand_amount_total = 0;

    // y자리 모래 날아감
    sand[y.r][y.c] = 0;
    Pos pos_a;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            int r_ = y.r + r - 2;
            int c_ = y.c + c - 2;

            if (weights[dir][r][c] > 0)
            {

                    sand_amount = (int)(sand_amount_y * (weights[dir][r][c] / 100.f));
                    sand_amount_total += sand_amount;

                    if (is_valid_pos(Pos(r_, c_)))
                    {
                        sand[r_][c_] += sand_amount;
                    }
                    else {
                        sand_amount_out += sand_amount;
                    }

            }
            else if (weights[dir][r][c] == -1) // a자리
            {
                pos_a.r = r_;
                pos_a.c = c_;
            }

        }
    }

    if (is_valid_pos(pos_a))
    {
        sand[pos_a.r][pos_a.c] += sand_amount_y - sand_amount_total;
    }
    else {
        sand_amount_out += sand_amount_y - sand_amount_total;
    }
}

int main()
{
    memset(sand, 0, 499 * 499);
    memset(visited, 0, 499 * 499);

    cin >> N;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cin >> sand[r][c];
        }
    }

    // 현재 좌표, 시작 좌표
    int cur_dir = 3;
    Pos cur_pos(N / 2, N / 2);
    visited[cur_pos.r][cur_pos.c] = true;
    Pos next_pos;

    while (1) {
        update_direction(cur_dir, cur_pos);
        tornado(cur_pos, cur_dir);

        // 종료
        if (cur_pos.r == 0 && cur_pos.c == 0)
            break;

        //cout << "sand" << endl;
        //print_array(sand, N, N);
        //cout << "visited" << endl;
        //print_array(visited, N, N);
    }

    cout << sand_amount_out << endl;
}