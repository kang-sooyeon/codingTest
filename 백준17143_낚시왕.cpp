#include <iostream>

using namespace std;

struct SHARK {
	int r;
	int c;
	int size;
	int fast;
	int dir;
	bool gotten;
};

int dr[] = {-1,0, 1, 0};
int dc[] = {0, 1, 0, -1};

int R, C, M;
int map[100][100] = { 0,};
int fisher_c, score;
SHARK sharks[10001];

// 맵에 상어표시
// 상어 index : 1~
// 빈칸 : 0

void copy_map(int dst[][100], int src[][100])
{
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			dst[r][c] = src[r][c];
		}
	}
}

void print_map()
{
	cout << "----------map-------" << endl;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (map[r][c] == 0 ){
				cout << map[r][c];
			}
			else {
				char char_index = map[r][c] - 1 + 'A';
				cout << char_index;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	cin >> R >> C >> M;

	int r, c, dir, size, fast;
	for (int m = 1; m <= M; m++) {
		cin >> r;
		--r;
		cin >> c;
		--c;
		cin >> fast;
		cin >> dir;
		cin >> size;

		sharks[m].r = r;
		sharks[m].c = c;
		sharks[m].fast = fast;
		sharks[m].dir = dir;
		sharks[m].size = size;
		sharks[m].gotten = false;
		map[r][c] = m;
	}

	score = 0;
	for( int fisher_c = 0; fisher_c < C; fisher_c++ ) {

		// 2. 지도에서 상어 잡기(상어 사라짐)
		for( int r = 0; r < R; r++ ) {
			// 빈칸이 아니면 상어 잡기, 상어 제거
			if (map[r][fisher_c] != 0) {
				int shark_index = map[r][fisher_c];
				score += sharks[shark_index].size;
				sharks[shark_index].gotten = true;
				map[r][fisher_c] = 0;
				break;
			}
		}
		// 3. 상어 이동
		// ****모두 이동시키고 겹치는지 확인해야함(**잡힌 상어 무시)
		for (int m = 1; m <= M; m++) {

			if (sharks[m].gotten)
				continue;

			int r = sharks[m].r;
			int c = sharks[m].c;
			int dir = sharks[m].dir;
			int fast = sharks[m].fast;

			if (dir == 1) {
				// y 감소
				r = ((R - 1) * 2 - r);	// y 감소하기 때문에, 역행하는 index 구간(index 변환)
				r = r + fast;	// 이동방향 더하고
				r = r % ((R - 1) * 2); // 모듈러하면 index 나옴.
				dir = 2;	// 증가
				
				if (r >= R - 1) {
					// 역행하 index 구간이면, 방향 바꾸고, index 변환
					r = ((R - 1) * 2 - r);
					dir = 1;
				}
			} else if (dir == 2) {
				// y 증가
				r = r + fast;	// 이동방향 더하고
				r = r % ((R - 1) * 2); // 모듈러하면 index 나옴.
				dir = 2;	// 증가
				if (r >= R - 1) {
					// 역행하 index 구간이면, 방향 바꾸고, index 변환
					r = ((R - 1) * 2 - r);
					dir = 1;
				}

			} else if (dir == 3) {
				// x 증가
				c = c + fast;	// 이동방향 더하고
				c = c % ((C - 1) * 2); // 모듈러하면 index 나옴.
				dir = 3;	// 증가
				if (c >= C - 1) {
					// 역행하 index 구간이면, 방향 바꾸고, index 변환
					c = ((C - 1) * 2 - c);
					dir = 4;
				}
			} else if (dir == 4) {
				// x 감소
				c = ((C - 1) * 2) - c;
				c = c + fast;	// 이동방향 더하고
				c = c % ((C - 1) * 2); // 모듈러하면 index 나옴.
				dir = 3;	// 증가
				if (c >= C - 1) {
					// 역행하 index 구간이면, 방향 바꾸고, index 변환
					c = ((C - 1) * 2 - c);
					dir = 4;
				}
			}

			sharks[m].r = r;
			sharks[m].c = c;
			sharks[m].dir = dir;
		}

		// 4. 지도에 표시 및 겹치는 상어 처리(***잡힌 상어 무시)
		int next_map[100][100] = { 0, };
		for (int m = 1; m <= M; m++) {

			if (sharks[m].gotten)
				continue;

			int r = sharks[m].r;
			int c = sharks[m].c;

			if (next_map[r][c] == 0) {
				// 상어 없음
				next_map[r][c] = m;
			} else {
				// 이미 상어 있음
				int shark_index = next_map[r][c];
				if (sharks[shark_index].size < sharks[m].size) {
					// 새로 온 상어가 크면 
					next_map[r][c] = m;
					sharks[shark_index].gotten = true;
				}
				else {
					// 이전에 온 상어가 크면
					sharks[m].gotten = true;
				}
			}
		}

		copy_map(map, next_map);
		//print_map();
	}

	cout << score;
	return 0;
}