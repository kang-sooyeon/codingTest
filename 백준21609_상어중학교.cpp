#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int board[20][20];

const int dy[] = { -1, 0, +1, 0 };
const int dx[] = { 0, -1, 0, +1 };
 
int calcPoint()
{
	int point = 0;
	vector<int> maxArea;	// 지워야하는 가장 큰 블록그룹의 좌표들
	int maxRainbow = 0;

	for (int color = 1; color <= M; color++) {
		bool visited[20][20] = { 0, };	
		// visted 원래는 1번 블록하고, 2번블록하고 겹칠일 없어서 밖에다 둬도 되는데
		// visted 무지개블록은 1번, 2번 모두 밟을수 있기 때문에 반드시 안에다 놔야함. 
		
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				
				if( !visited[y][x] && board[y][x] == color) {
					// 방문할 곳

					queue<int> q;
					vector<int> vec;
					int rainbow = 0;

					q.push(y * 100 + x);
					vec.push_back(y * 100 + x); // 기준블록(가장 위 왼쪽에 있는 숫자블록
					visited[y][x] = true;

					while (!q.empty()) {
						int cy = q.front() / 100;
						int cx = q.front() % 100;
						q.pop();

						for (int d = 0; d < 4; d++) {
							int ny = cy + dy[d];
							int nx = cx + dx[d];
							if (ny < 0 || ny >= N || nx < 0 || nx >= N)
								continue;

							if (!visited[ny][nx] && (board[ny][nx] == color || board[ny][nx] == 0)) {
								q.push(ny * 100 + nx);
								vec.push_back(ny * 100 + nx);
								visited[ny][nx] = true;
								if (board[ny][nx] == 0) {
									++rainbow;
								}
							}
						}
					}

					if (maxArea.size() < vec.size() || (maxArea.size() == vec.size() && maxRainbow < rainbow) 
						|| (maxArea.size() == vec.size() && maxRainbow == rainbow && maxArea[0] < vec[0] )) {
						maxArea = vec;
						maxRainbow = rainbow;
					}

				}
			}
		}
	}

	if (maxArea.size() >= 2) {
		point = maxArea.size() * maxArea.size();
		for (int i = 0; i < maxArea.size(); ++i) {
			int y = maxArea[i] / 100;
			int x = maxArea[i] % 100;
			board[y][x] = -2;
		}
	}

	return point;
}

void down()
{
	for (int x = 0; x < N; ++x) {
		int blank = 0;
		for (int y = N - 1; y >= 0; --y) {
			if (board[y][x] == -2) {
				++blank;
			}
			else if (board[y][x] == -1) {
				blank = 0;
			}
			else {
				if (blank != 0) {
					// blank만큼 옮기면됨
					// 단 blank가 0인 경우, 자기자리에 그대로 옮겨지고 자리 지워버리므로 조심!
					board[y + blank][x] = board[y][x];
					board[y][x] = -2;	// 블록 지우기
				}
			}
		}
	}

}

void rotate()
{
	int back[20][20];
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			back[N - 1 - x][y] = board[y][x];
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			board[y][x] = back[y][x];
		}
	}
}

int solve()
{
	int point = 0;
	int curPoint = 0;
	do {
		curPoint = calcPoint();
		point += curPoint;
		down();
		rotate();
		down();
	} while (curPoint != 0);

	return point;
}
int main()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}

	int ret = solve();
	cout << ret;

	return 0;
}