#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, M;
struct Robot {
	int y;
	int x;
	int dir;
};

Robot robot;

int map[50][50];

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };



int main() {
	cin >> N >> M;

	cin >> robot.y >> robot.x >> robot.dir;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	queue<Robot> q;
	q.push(robot);

	int ret = 0;
	while (!q.empty()) {
		Robot cur = q.front(); q.pop();

		if (map[cur.y][cur.x] == 0) {
			map[cur.y][cur.x] = 2;
			++ret;
		}

		for (int dir = 0; dir < 4; ++dir) {
			Robot next;
			next.dir = (cur.dir + 3 + dir * 3) % 4;
			next.y = cur.y + dy[next.dir];
			next.x = cur.x + dx[next.dir];

			if (map[next.y][next.x] == 0) {
				q.push(next);
				break;
			}
		}

		if (q.empty()) {
			Robot next;
			next.dir = cur.dir;
			next.y = cur.y + dy[(next.dir + 2) % 4];
			next.x = cur.x + dx[(next.dir + 2) % 4];

			if (map[next.y][next.x] == 1)
				break;

			q.push(next);
		}
	}

	cout << ret;

	return 0;
}