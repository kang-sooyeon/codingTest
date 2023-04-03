#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

struct Pos {
    int y;
    int x;
};

struct Status {
    int candy;
    Pos p;
};

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0 , 0 };


int bfs(vector<string> maps, Pos sp, Pos dp) {

    bool visited[100][100];
    int candy = 0;
    int N = maps.size();
    int M = maps[0].length();
    cout << "N : " << N << endl;
    cout << "M : " << M << endl;

    //memset(visited, 100*100, false);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = false;
        }
    }



    queue<Status> q;
    q.push({ 0, sp });
    visited[sp.y][sp.x] = true;


    while (!q.empty()) {

        Status s = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = s.p.x + dx[dir];
            int ny = s.p.y + dy[dir];
            int nc = s.candy;

            //cout << "ny, nx : " << ny << ", " << nx << endl;


            // out bound
            if (nx < 0 || nx >= M || ny < 0 || ny >= N) {
                continue;
            }

            //cout << "maps[ny][nx] : " << maps[ny][nx]  << endl;
            //cout << "visited[ny][nx] : " << visited[ny][nx]  << endl;

            if (visited[ny][nx] == false && maps[ny][nx] != 'X') {
                //cout << "nc, ny, nx : " << nc+1 << ", " << ny << ", " << nx << endl;
                q.push({ nc + 1, {ny, nx} });
                visited[ny][nx] = true;
            }

            if (dp.y == ny && dp.x == nx)
                return nc + 1;
        }
    }

    return -1;
}

int solution(vector<string> maps) {
    int answer = 0;

    int sx, sy, ly, lx, ey, ex;
    for (int i = 0; i < maps.size(); i++) {
        for (int j = 0; j < maps[i].length(); j++) {
            if (maps[i][j] == 'S') {
                sy = i;
                sx = j;
            }
            else if (maps[i][j] == 'L') {
                ly = i;
                lx = j;
            }
            else if (maps[i][j] == 'E') {
                ey = i;
                ex = j;
            }
        }
    }

    //cout << "sy, sx : " << sy << ", " << sx << endl;
    //cout << "ly, lx : " << ly << ", " << lx << endl;

    int l_candy = bfs(maps, { sy, sx }, { ly, lx });
    if (l_candy == -1)
        return -1;
    cout << "l_candy : " << l_candy << endl;
    int e_candy = bfs(maps, { ly, lx }, { ey, ex });
    if (e_candy == -1)
        return -1;
    cout << "e_candy : " << e_candy << endl;

    answer = l_candy + e_candy;
    return answer;
}