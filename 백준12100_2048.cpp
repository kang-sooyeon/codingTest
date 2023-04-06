#include <iostream>
#include <queue>

using namespace std;

int N;
int ret = 0;

// 보드 회전 메서드
// 보드 올리는 메서드
// 보드에서 최대값 찾는 메서드

struct Board {

	// board1 = board2 해도 copy본으로 복사됨..
	int map[20][20] = { 0, };

	int get_max()
	{
		int max = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (max < map[y][x])
					max = map[y][x];
			}
		}
		return max;
	}

	void up()
	{
		int temp[20][20] = { 0, };
		for (int x = 0; x < N; x++) {


			int target = -1;
			bool flag = 0;

			for (int y = 0; y < N; y++) {

				if (map[y][x] == 0)
					continue;
				
				if ( flag == 1 && temp[target][x] == map[y][x]) {
					// target하고 y 같을 때, 두번째 합쳐지는 경우 
					// 값 누적
					temp[target][x] += map[y][x];	// 두번째 합쳐짐
					flag = 0;
				} else {
					// target하고 y 다를 때, 처음 합쳐지는 경우
					// target index 올리기
					// 값 누적
					target++;
					temp[target][x] += map[y][x];
					flag = 1;	// 첫번째 합쳐짐
				}
				
			}
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				map[y][x] = temp[y][x];
			}
		}
	}

	void rotate()
	{
		int temp[20][20];
		// 시계방향으로 회전
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				temp[x][y] = map[N - 1 - y][x];
			}
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				map[y][x] = temp[y][x];
			}
		}
	}
};


void dfs(Board cur, int count)
{
	if (count == 5) {
		int max = cur.get_max();
		if( ret < max ) ret = max;
		return;
	}

	for( int dir = 0; dir < 4; dir++ ) {
		// board backup
		Board next = cur;
		// board update
		next.up();
		dfs(next, count + 1);
		// board recover and rotate
		cur.rotate();	
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);

	cin >> N;

	Board board;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board.map[y][x];
		}
	}

	dfs(board, 0);
	cout << ret;

	return 0;
}