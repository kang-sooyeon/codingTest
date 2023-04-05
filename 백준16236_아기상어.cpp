#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
// 자기보다 작거나 같은 물고기 지나갈수있음(큰거 no)
// 자기보다 작은 물고기만 먹을 수 있음

// 먹을게 없으면 엄마 상어에게 도움 요청
// 가장 가까운 물고기, 가장 위, 가장 왼쪽.

// 자신의 크기와 같은 물고기 먹을때 크기 1 증가
// 처음 크기 1

//0: 빈 칸
//1, 2, 3, 4, 5, 6 : 칸에 있는 물고기의 크기
//9 : 아기 상어의 위치


struct Shark {
	int y;
	int x;
	int time;
};

int N;
int map[20][20];
Shark shark, next_shark; // 우선순위 높은 다음 shark
int shark_size; // 한번 bfs 탐색 하는동안 변하지 않음
int shark_eat;

int dy[] = { -1, 0, 0, 1 };
int dx[] = { 0, -1, 1, 0 };

bool is_update = false;

void bfs() {

	is_update = false;
	next_shark = { 20, 20, -1 };	// 다음 상어좌표

	int visited[20][20] = { 0, };
	queue<Shark> q;

	q.push(shark);
	visited[shark.y][shark.x] = 1;

	while (!q.empty()) {

		Shark cur = q.front(); q.pop();

		// *** 가장 가까운 물고기 찾으면 탐색 종료. 전체 맵 탐색면 안됨.
		if (next_shark.time != -1 && next_shark.time < cur.time)
			break;

		// 현재 크기보다 작은 물고기 찾음(단, 빈칸은 아니여야함)
		if (shark_size > map[cur.y][cur.x] && map[cur.y][cur.x] != 0) {
			is_update = true;
			// 우선순위 좌표 갱신
			if (next_shark.y > cur.y || (next_shark.y == cur.y && next_shark.x > cur.x)) {
				next_shark = cur;
				//printf("next shark.y : %d, next_shark.x : %d, next_shark.time: %d\n", next_shark.y, next_shark.x, next_shark.time);
			}
		}

		// 가능한 다음좌표들 큐에 넣기
		Shark next;
		for (int dir = 0; dir < 4; dir++) {
			next.y = cur.y + dy[dir];
			next.x = cur.x + dx[dir];
			next.time = cur.time + 1;

			// 유효하지 않은 좌표
			if (next.y < 0 || next.y >= N || next.x < 0 || next.x >= N)
				continue;

			// 먹으려는 물고기 크기가 상어크기보다 큼
			if (map[next.y][next.x] > shark_size)
				continue;

			if (!visited[next.y][next.x]) {

				q.push(next);
				visited[next.y][next.x] = 1;
			}
		}
	}
}

int main() {

	//freopen("input.txt", "r", stdin);

	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];

			if (map[y][x] == 9) {
				shark.y = y;
				shark.x = x;
				shark.time = 0;
				shark_size = 2;
				shark_eat = 0;

				map[y][x] = 0;
			}
		}
	}


	while (1) {
		bfs();	// 맵 전체 다 서치 해봐야, 어디어디 물고기 먹을 수 있는지 파악 가능

		if (is_update == false)
			break;

		shark = next_shark; // 최종 골라진 그 위치에서 상어 다시 bfs 시작
		map[shark.y][shark.x] = 0; // 최종 먹은 위치 0으로 세팅해야함

		// 상어 크기 조정
		shark_eat++;
		if (shark_eat == shark_size) {
			shark_eat = 0;
			shark_size++;
		}
	}

	cout << shark.time;
	return 0;
}