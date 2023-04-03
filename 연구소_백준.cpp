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

			// 맵 백업
			backup[i][j] = map[i][j];

			// ** 해당 좌표에서부터 확산 == seed들 세팅
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

			// 유효좌표확인
			if (!is_valid(next.r, next.c)) continue;
			// 방문여부 확인
			if (visited[next.r][next.c] == 1) continue;

			// 빈 공간이여야 확산
			if (backup[next.r][next.c] == 0) {
				// 새 좌표 추가 및 방문 체크
				q.push(next);
				visited[next.r][next.c] = 1;

				//** 백업 맵에 바이러스 2 표시
				backup[next.r][next.c] = 2;
			}
		}
	}

	// ** 빈공간 셀때 backup맵에서 세야함.(map에서 세면 안됨!)
		// candi : 현재 안전 공간 개수
	int candi = count_safe(backup);
	// ret : 전체 안전 공간 개수
	if (ret < candi) ret = candi;
}

void pick_dfs(int count, int sr, int sc) {

	// 빈칸 세개 고름
	if (count == 3) {
		bfs();
		return;
	}

	for (int i = sr; i < N; i++) {
		for (int j = sc; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				pick_dfs(count + 1, i, j);
				// ** pick_dfs하고 나왔다는건 골랐던거 계산 끝난것, 다시 0으로 세팅
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