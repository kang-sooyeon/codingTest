#include <iostream>
#include <queue>

#define MAX 8

using namespace std;

int map[MAX][MAX];

int N, M;
int ret;

int count_safe(int array[MAX][MAX]) {
	int count=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (array[i][j] == 0)
				count++;
		}
	}
	return count;
}

struct Point {
	int r;
	int c;
};

int D[4][2] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

bool is_valid(int r, int c) {
	if (r >= 0 && r < N && c >= 0 && c < M)
		return true;
	return false;
}

void bfs()
{
	queue<Point> q;
	int backup[MAX][MAX];
	int visited[MAX][MAX] = { 0 };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			// �� ���
			backup[i][j] = map[i][j];

			// ** �ش� ��ǥ�������� Ȯ�� == seed�� ����
			if (backup[i][j] == 2) {
				q.push({ i, j });
				visited[i][j] = 1;	
			}
		}
	}

	while (!q.empty()) {
		Point cur = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			Point next;
			next.r = cur.r + D[d][0];
			next.c = cur.c + D[d][1];

			// ��ȿ��ǥȮ��
			if (!is_valid(next.r, next.c)) continue;
			// �湮���� Ȯ��
			if (visited[next.r][next.c] == 1) continue;

			// �� �����̿��� Ȯ��
			if (backup[next.r][next.c] == 0) {
				// �� ��ǥ �߰� �� �湮 üũ
				q.push(next);
				visited[next.r][next.c] = 1;

				//** ��� �ʿ� ���̷��� 2 ǥ��
				backup[next.r][next.c] = 2;
			}
		}
	}

	// ** ����� ���� backup�ʿ��� ������.(map���� ���� �ȵ�!)
		// candi : ���� ���� ���� ����
	int candi = count_safe(backup);
	// ret : ��ü ���� ���� ����
	if (ret < candi) ret = candi;
}

void pick_dfs(int count, int sr, int sc) {

	// ��ĭ ���� ��
	if (count == 3) {
		bfs();
		return;
	}

	for (int i = sr; i < N; i++) {
		for (int j = sc; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				pick_dfs(count + 1, i, j);
				// ** pick_dfs�ϰ� ���Դٴ°� ������� ��� ������, �ٽ� 0���� ����
				map[i][j] = 0;
			}
		}
		sc = 0;
	}
	
}

int main()
{
	cin >> N >> M;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	ret = 0;
	pick_dfs(0, 0, 0);

	cout << ret << endl;
}