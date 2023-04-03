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

	// dfs Ž���� ���ߴ� ���ǵ�
	if (count >= ret) return;	// 1) ******* �������, ret�� 1�� ���ŵ� ��쿡 �� �̻� count�� �غ� �ʿ䰡 ����.
	
	// 2) �����ϸ� ret �����ϰ� ����
	if (check()) {
		ret = (ret < count)? ret : count;
		return;
	}

	if (count == 3) return; // 3) count�� 3�ΰ��, ���̻� �� �־��.(���� ����ϱ� �ϴµ� �ð����ɸ�)

	for (int i = sy; i <= H; i++) {
		for (int j = sx; j < N; j++) {

			// ���μ� ���� �� ������ ��ġ
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

	// ret�� ���� �ּ� Ƚ�� ������ ����
	ret = 4;
	// ���� ������� ���μ� ��ġ(�ִ� 3��)�ؼ� �� ������Ʈ
	dfs(0, 1, 1);

	if (ret == 4) ret = -1;
	cout << ret << endl;
	
	return 0;
}

