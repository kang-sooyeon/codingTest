#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, M;
int y, x, d;
int map[50][50];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};


int main() {

	// 0 : û�ҵ��� ���� ��ĭ
	// 1 : ��
	// 2 : û�ҵ� ĭ
	
	//freopen("input.txt", "r", stdin);

	cin >> N >> M;

	cin >> y >> x >> d;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	int ret = 0;
	bool is_none;

	while (1) {

		if (map[y][x] == 0) {
			map[y][x] = 2;
			ret++;
		}

		is_none = false;
		for (int di = 0; di < 4; di++) {
			int _y = y + dy[di];
			int _x = x + dx[di];

			// û�ҵ��� ���� ��ĭ ����
			if (map[_y][_x] == 0) {
				d = (d + 3)%4;
				int _y = y + dy[d];
				int _x = x + dx[d];

				if ( map[_y][_x] == 0) {
					y = _y;
					x = _x;
				}
				is_none = true;
				break;
			}
		}

		// û�ҵ��� ���� ��ĭ ����
		if ( !is_none ) {
			//�����Ҽ������� ����
			int _d = (d+2)%4;
			int _y = y + dy[_d];
			int _x = x + dx[_d];
			
			if ( map[_y][_x] == 1 )
				break;
			
			y = _y;
			x = _x;
		}
	}

	cout << ret;

	return 0;
}