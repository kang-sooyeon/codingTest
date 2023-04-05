#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, L;
int map[200][100];



int main()
{

	freopen("input.txt", "r", stdin);

	cin >> N >> L;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			map[x+N][y] = map[y][x];
		}
	}

	//for (int y = 0; y < 2*N; y++) {
	//	for (int x = 0; x < N; x++) {
	//		cout << map[y][x];
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	int ladder[200][100] = {0,  };
	int ret = 0;
	bool is_success = true;
	int ladder_start, ladder_end;


	for (int y = 0; y < 2*N; y++) {
		is_success = true;
		for (int x = 0; x < N-1; x++) {

			// 높이 다름, 경사로 설치
			if (map[y][x] != map[y][x + 1]) {
				// 앞이 더 높음 (내리막)
				if (map[y][x] > map[y][x + 1]) {
					ladder_start = x + 1;
					ladder_end = x + L;

					if (ladder_end >= N) {
						is_success = false;
						break;
					}

					if (abs(map[y][x] - map[y][ladder_end]) > 1) {
						is_success = false;
						break;
					}
					int key = map[y][ladder_start];
					for (int k = ladder_start; k <= ladder_end; k++) {
						if (map[y][k] != key) {
							is_success = false;
							break;
						}
					}
					if (!is_success) break;

					// 사다리 설치
					for (int k = ladder_start; k <= ladder_end; k++) {
						if (ladder[y][k] == 1) {
							is_success = false;
							break;
						}
						ladder[y][k] = 1;
					}
					if (!is_success) break;

					x = ladder_end-1;
				}
				else {
					// 뒤가 더 높음
					ladder_end  = x;
					ladder_start = x - L;

					if (ladder_start < 0) {
						is_success = false;
						break;
					}

					if (abs(map[y][x+1] - map[y][ladder_end]) > 1) {
						is_success = false;
						break;
					}

					int key = map[y][ladder_start];
					for (int k = ladder_start; k <= ladder_end; k++) {
						if (map[y][k] != key) {
							is_success = false;
							break;
						}
					}
					if (!is_success) break;

					// 사다리 설치 가능 여부(겹치지 않는지)
					for (int k = ladder_start; k <= ladder_end; k++) {
						if (ladder[y][k] == 1) {
							is_success = false;
							break;
						}
						ladder[y][k] = 1;
					}
					if (!is_success) break;
				}
			}
		}	
		if (is_success) ret++;
	}

	cout << ret;

	return 0;
}