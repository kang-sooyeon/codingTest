#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, M, H;
int map[31][11] = { 0, };
int total_count = 0;
bool is_success = false;
int ret;

struct Pos {
	int y;
	int x;
};

bool check()
{
	is_success = true;

	for (int i = 1; i <= N; i++) {

		int cur_i = i;
		for (int j = 1; j <= H; j++) {
			if (map[j][cur_i] == 1)
				cur_i++;
			else if (map[j][cur_i - 1] == 1)
				cur_i--;
		}
		if (i != cur_i ) return is_success = false;
	}

	return is_success;
}

void dfs(int count, int sy, int sx) {

	// dfs 탐색을 멈추는 조건들
	if (count >= ret) return;	// 1) ******* 예를들어, ret가 1로 갱신된 경우에 그 이상 count는 해볼 필요가 없음.
	
	// 2) 성공하면 ret 갱신하고 끝냄
	if (check()) {
		ret = (ret < count)? ret : count;
		return;
	}

	if (count == 3) return; // 3) count가 3인경우, 더이상 안 넣어도됨.(빼도 통과하긴 하는데 시간더걸림)

	for (int i = sy; i <= H; i++) {
		for (int j = sx; j < N; j++) {

			// 가로선 놓을 수 있으면 설치
			if (map[i][j] == 0 && map[i][j - 1] != 1 && map[i][j + 1] != 1 ) {
				map[i][j] = 1;
				dfs(count + 1, i, j);
				map[i][j] = 0;
			}
		}
		sx = 1;
	}
}

int main() {

	//freopen("input.txt", "r", stdin);

	cin >> N >> M >> H;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;

		map[a][b] = 1;
	}

	// ret는 현재 최소 횟수 저장할 변수
	ret = 4;
	// 맵의 빈공간에 가로선 설치(최대 3개)해서 맵 업데이트
	dfs(0, 1, 1);

	if (ret == 4) ret = -1;
	cout << ret << endl;
	
	return 0;
}

