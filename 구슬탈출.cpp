#include <iostream>
#include <queue>

#define MAX_N 10

using namespace std;

char map[MAX_N][MAX_N];

struct Point {
	int r = 0;
	int c = 0;
};

struct INFO {
	Point red;
	Point blue;
	int cnt = 0;
};

int D[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
};

int R, C;
INFO start;

Point print_red;
Point print_blue;

void print_map()
{
	map[print_red.r][print_red.c] = 'R';
	map[print_blue.r][print_blue.c] = 'B';

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
			cout << map[r][c];
		cout << endl;
	}

	map[print_red.r][print_red.c] = '.';
	map[print_blue.r][print_blue.c] = '.';

	cout << endl;
}

int bfs()
{
	queue<INFO> myqueue;
	bool visited[MAX_N][MAX_N][MAX_N][MAX_N] = { false };

	visited[start.red.r][start.red.c][start.blue.r][start.blue.c] = true;
	myqueue.push(start);


	while (!myqueue.empty())
	{
		INFO cinfo = myqueue.front();
		myqueue.pop();

		Point cur_red = cinfo.red;
		Point cur_blue = cinfo.blue;

		// 홀에 빠졌으면 끝
		if (map[cur_red.r][cur_red.c] == 'O' )
			return cinfo.cnt;

		for (int i = 0; i < 4; i++)
		{

			// 한번 기울임
			Point next_red{cur_red.r, cur_red.c};
			Point next_blue{cur_blue.r, cur_blue.c };

			// 벽에 멈추거나 홀에 빠지기 전까지 계속 좌표 이동
			// 빨간공 움직이기
			while (1) {

				next_red.r += D[i][0];
				next_red.c += D[i][1];

				if (map[next_red.r][next_red.c] == '#') {
					//새로운 공 좌표
					//벽이라 다시 back
					next_red.r -= D[i][0];
					next_red.c -= D[i][1];
					break;
				}
				else if (map[next_red.r][next_red.c] == 'O') {
					break;
				}
			}

			// 파란공 움직이기
			while (1) {

				next_blue.r += D[i][0];
				next_blue.c += D[i][1];

				if (map[next_blue.r][next_blue.c] == '#') {
					//새로운 공 좌표
					//벽이라 다시 back
					next_blue.r -= D[i][0];
					next_blue.c -= D[i][1];
					break;
				}
				else if (map[next_blue.r][next_blue.c] == 'O') {
					break;
				}
			}

			// 파란공만 빠지거나, 빨간공 파랑공 둘다 홀이면 pass
			if (map[next_blue.r][next_blue.c] == 'O') continue;
 
			// 빨간공, 파란공 같은 위치에 겹치면 더 멀리서 온공 뒤로 back하기
			if (next_red.r == next_blue.r && next_red.c == next_blue.c )
			{
				int dist_red, dist_blue;

				dist_red = abs(cur_red.r - next_red.r) + abs(cur_red.c - next_red.c);
				dist_blue = abs(cur_blue.r - next_blue.r) + abs(cur_blue.c - next_blue.c);

				if (dist_red > dist_blue) {
					next_red.r -= D[i][0];
					next_red.c -= D[i][1];
				}
				else {
					next_blue.r -= D[i][0];
					next_blue.c -= D[i][1];
				}
			}

			// pass case
			// 횟수 초과면 pass
			if (cinfo.cnt + 1 > 10) continue;
			// 방문 노드면 pass
			if (visited[next_red.r][next_red.c][next_blue.r][next_blue.c]) continue;

			visited[next_red.r][next_red.c][next_blue.r][next_blue.c] = true;
			myqueue.push({ next_red, next_blue, cinfo.cnt + 1 });

			//print_red = next_red;
			//print_blue = next_blue;
			//print_map();
			//int a;
			//cin >> a;
		}
	}

	return -1;
}
	
int main()
{
	cin >> R >> C;

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			cin >> map[r][c];
			if (map[r][c] == 'R') {
				start.red.r = r;
				start.red.c = c;
				map[r][c] = '.';

				print_red.r = r;
				print_red.c = c;
			}
			else if (map[r][c] == 'B') {
				start.blue.r = r;
				start.blue.c = c;
				map[r][c] = '.';

				print_blue.r = r;
				print_blue.c = c;
			}
		}
	}
	start.cnt = 0;

	cout << bfs();

	return 0;
}