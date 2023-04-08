#include <iostream>

using namespace std;


// map[r][c] : 미세먼지 양
// 1. 미세먼지 네방향 확산 :  A[r][c]/5
// A[r][c] = A[r][c] - (A[r][c]/5) * 확산된 방향
// 미세먼지 확산은 새로운 맵A'에 해야함
// 2. 공기 청정기 작동
// T초가 지난 후 남은 미세먼지 양
int R, C, T;

//int A[50][50];
int A[2][50][50] = { 0, };
int cur = 0; // 현재 map index

int air_r1, air_c1;	// 공기청정 위
int air_r2, air_c2; // 공기청정 아래

// 방향정보
// 0 : 상하좌우
// 1 : 위쪽 시계(거꾸로)
// 2 : 아래쪽 반시계(거꾸로)

int D[3][4][2] = {
	{{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}},

	{{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}},

	{{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}}
};

void init_map(int map_index)
{

	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			A[map_index][r][c] = 0;
		}
	}

	A[map_index][air_r1][air_c1] = -1;
	A[map_index][air_r2][air_c2] = -1;
}

void print_map()
{
	cout << endl;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			cout << A[cur][r][c];
		}
		cout << endl;
	}
	cout << endl;
}


int check() {
	int ret = 0;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			if( A[cur][r][c] > 0 )
				ret += A[cur][r][c];
		}
	}
	return ret;
}

void dirty_on()
{
	int next = (cur + 1) % 2;
	init_map(next);

	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			if ( A[cur][r][c] > 0 ) {
				// 미세먼지 있으면
				int sum = 0;
				for (int d = 0; d < 4; d++) {
					int nr = r + D[0][d][0];
					int nc = c + D[0][d][1];

					// 청정기 있는 곳이나 범위밖은 못감
					if (nr < 0 || nr >= R || nc < 0 || nc >= C || A[cur][nr][nc] == -1)
						continue;

					// 이미 날아온 미세먼지 있을수도있으니, 누적
					A[next][nr][nc] += A[cur][r][c] / 5;	// 날아간 양
					sum += A[cur][r][c]/5;	// 날아간 양 총합
				}
				// 이미 날아온 미세먼지 있을수도있으니, 누적
				A[next][r][c] += A[cur][r][c] - sum;
			}
		}
	}

	cur = next;
}

void air_on()
{
	/////////////// up
	// 윗공간, 왼쪽변
	for (int r = air_r1 - 1; r > 0; r--) {
		A[cur][r][0] = A[cur][r-1][0];
	}
	// 윗공간, 윗변
	for (int c = 0; c < C-1; c++) {
		A[cur][0][c] = A[cur][0][c+1];
	}
	// 윗공간, 오른쪽변
	for (int r = 0; r < air_r1; r++) {
		A[cur][r][C-1] = A[cur][r+1][C-1];
	}
	// 윗공간, 아랫변
	for (int c = C- 1; c > 1; c--) {
		A[cur][air_r1][c] = A[cur][air_r1][c-1];
	}
	A[cur][air_r1][1] = 0;	// ** 당겨지면서 값이 지워지는데, 마지막칸은 안지워짐

	//////////////////// bottom
	// 아래공간, 왼쪽변
	for (int r = air_r2 + 1; r < R-1; r++) {	
		A[cur][r][0] = A[cur][r + 1][0];
	}
	// 아래공간, 아랫변
	for (int c = 0; c < C - 1; c++) {
		A[cur][R-1][c] = A[cur][R-1][c + 1];
	}
	// 아래공간, 오른쪽변
	for (int r = R-1; r > air_r2; r--) {
		A[cur][r][C - 1] = A[cur][r-1][C - 1];
	}
	// 아래 공간, 윗변
	for (int c = C - 1; c > 1; c--) {
		A[cur][air_r2][c] = A[cur][air_r2][c - 1];
	}
	A[cur][air_r2][1] = 0;
}

void air_on2()
{
	// up
	int r = air_r1;
	int c = air_c1;
	int d = 0;

	while (1) {
		int nr = r + D[1][d][0];
		int nc = c + D[1][d][1];

		// 유효한 방향아니면 방향만 바꾸기
		if ((nr < 0 || nr >= R || nc < 0 || nc >= C) || nr > air_r1 ) {
			d = (d + 1) % 4;
			continue;
		}

		if (nr == air_r1 && nc == air_c1 )
			break;

		// 다음칸에 미세먼지 있으면 당기고, 제거
		if (A[cur][nr][nc] > 0 ) {
				
			// 현재 공기청정기 있는 칸이면 값 당기면 안됨
			if( A[cur][r][c] != -1 )
				A[cur][r][c] = A[cur][nr][nc];
			A[cur][nr][nc] = 0;
		}

		// 한칸 이동
		r = nr;
		c = nc;
	}

	// bottom
	r = air_r2;
	c = air_c2;
	d = 0;

	while (1) {
		int nr = r + D[2][d][0];
		int nc = c + D[2][d][1];

		// 유효한 방향아니면 방향만 바꾸기
		if ((nr < 0 || nr >= R || nc < 0 || nc >= C) || nr < air_r2) {
			d = (d + 1) % 4;
			continue;
		}

		// 다음칸이 공기청저기 있으면 끝난것
		if (nr == air_r2 && nc == air_c2)
			break;

		// 다음칸에 미세먼지 있으면 당기고, 제거
		if (A[cur][nr][nc] > 0) {

			// 현재 공기청정기 있는 칸이면 값 당기면 안됨
			if (A[cur][r][c] != -1)
				A[cur][r][c] = A[cur][nr][nc];
			A[cur][nr][nc] = 0;
		}

		// 한칸 이동
		r = nr;
		c = nc;

	}
	
}

int main()
{
	//freopen("input.txt", "r", stdin);

	cin >> R >> C >> T;

	cur = 0;
	bool flag = true;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			cin >> A[cur][r][c];

			if ( A[cur][r][c] == -1 && flag ) {
				air_r1 = r;
				air_c1 = c;
				flag = false;
			}
			else if(A[cur][r][c] == -1 && !flag ) {
				air_r2 = r;
				air_c2 = c;
			}
		}
	}

	int time = 0;
	while (time < T) {

		dirty_on();
		air_on();

		time++;
	}

	cout << check();

	return 0;
}