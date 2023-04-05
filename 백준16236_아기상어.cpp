#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
// �ڱ⺸�� �۰ų� ���� ����� ������������(ū�� no)
// �ڱ⺸�� ���� ����⸸ ���� �� ����

// ������ ������ ���� ���� ���� ��û
// ���� ����� �����, ���� ��, ���� ����.

// �ڽ��� ũ��� ���� ����� ������ ũ�� 1 ����
// ó�� ũ�� 1

//0: �� ĭ
//1, 2, 3, 4, 5, 6 : ĭ�� �ִ� ������� ũ��
//9 : �Ʊ� ����� ��ġ


struct Shark {
	int y;
	int x;
	int time;
};

int N;
int map[20][20];
Shark shark, next_shark; // �켱���� ���� ���� shark
int shark_size; // �ѹ� bfs Ž�� �ϴµ��� ������ ����
int shark_eat;

int dy[] = { -1, 0, 0, 1 };
int dx[] = { 0, -1, 1, 0 };

bool is_update = false;

void bfs() {

	is_update = false;
	next_shark = { 20, 20, -1 };	// ���� �����ǥ

	int visited[20][20] = { 0, };
	queue<Shark> q;

	q.push(shark);
	visited[shark.y][shark.x] = 1;

	while (!q.empty()) {

		Shark cur = q.front(); q.pop();

		// *** ���� ����� ����� ã���� Ž�� ����. ��ü �� Ž���� �ȵ�.
		if (next_shark.time != -1 && next_shark.time < cur.time)
			break;

		// ���� ũ�⺸�� ���� ����� ã��(��, ��ĭ�� �ƴϿ�����)
		if (shark_size > map[cur.y][cur.x] && map[cur.y][cur.x] != 0) {
			is_update = true;
			// �켱���� ��ǥ ����
			if (next_shark.y > cur.y || (next_shark.y == cur.y && next_shark.x > cur.x)) {
				next_shark = cur;
				//printf("next shark.y : %d, next_shark.x : %d, next_shark.time: %d\n", next_shark.y, next_shark.x, next_shark.time);
			}
		}

		// ������ ������ǥ�� ť�� �ֱ�
		Shark next;
		for (int dir = 0; dir < 4; dir++) {
			next.y = cur.y + dy[dir];
			next.x = cur.x + dx[dir];
			next.time = cur.time + 1;

			// ��ȿ���� ���� ��ǥ
			if (next.y < 0 || next.y >= N || next.x < 0 || next.x >= N)
				continue;

			// �������� ����� ũ�Ⱑ ���ũ�⺸�� ŭ
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
		bfs();	// �� ��ü �� ��ġ �غ���, ����� ����� ���� �� �ִ��� �ľ� ����

		if (is_update == false)
			break;

		shark = next_shark; // ���� ����� �� ��ġ���� ��� �ٽ� bfs ����
		map[shark.y][shark.x] = 0; // ���� ���� ��ġ 0���� �����ؾ���

		// ��� ũ�� ����
		shark_eat++;
		if (shark_eat == shark_size) {
			shark_eat = 0;
			shark_size++;
		}
	}

	cout << shark.time;
	return 0;
}