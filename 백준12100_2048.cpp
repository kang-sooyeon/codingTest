#include <iostream>
#include <queue>

using namespace std;

int N;
int ret = 0;

// ���� ȸ�� �޼���
// ���� �ø��� �޼���
// ���忡�� �ִ밪 ã�� �޼���

struct Board {

	// board1 = board2 �ص� copy������ �����..
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
					// target�ϰ� y ���� ��, �ι�° �������� ��� 
					// �� ����
					temp[target][x] += map[y][x];	// �ι�° ������
					flag = 0;
				} else {
					// target�ϰ� y �ٸ� ��, ó�� �������� ���
					// target index �ø���
					// �� ����
					target++;
					temp[target][x] += map[y][x];
					flag = 1;	// ù��° ������
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
		// �ð�������� ȸ��
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