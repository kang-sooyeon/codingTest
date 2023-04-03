#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct CCTV {
	int y;
	int x;
	int type;
};

int N, M;
int map[8][8];
CCTV cctv[8];
int cctv_size = 0;

int ret;
int rot_size[] = {4, 2, 4, 4, 1};
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };

void map_copy(int dst[8][8], int src[8][8])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

void update(int dir, CCTV cctv)
{
	dir = dir % 4;
	int y = cctv.y;
	int x = cctv.x;
	while (1) {
		y += dy[dir];
		x += dx[dir];

		if (y < 0 || y >= N || x < 0 || x >= M)
			break;

		if (map[y][x] == 6)
			break;

		map[y][x] = -1;
	}
}


void dfs(int cctv_index) 
{
	if (cctv_index == cctv_size) {

		// 빈공간 세기
		int zero_count = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 0)
					zero_count++;
			}
		}

		if (ret > zero_count) 
			ret = zero_count;

		return;
	}
	
	int backup[8][8];	//**전역변수말고 지역변수로 해야 백트래킹 가능

	//  방향 돌려가면서 맵 업데이트
	int cctv_type = cctv[cctv_index].type;
	//int cctv_type = map[cctv[cctv_index].y][cctv[cctv_index].x] - 1;	 // *** 이때 타입 맵에서 얻으면, 다른 cctv에 의해서 값이 변경됐을수있음. 위처럼 초기에 받아서 저장해야함.
	for (int dir = 0; dir < rot_size[cctv_type]; dir++) {
		// map backup
		map_copy(backup, map);

		// map update
		if (cctv_type == 0) {
			update(dir, cctv[cctv_index]);
		}
		if (cctv_type == 1) {
			update(dir, cctv[cctv_index]);
			update(dir + 2, cctv[cctv_index]);
		}
		if (cctv_type == 2) {
			update(dir, cctv[cctv_index]);
			update(dir+1, cctv[cctv_index]);
		}
		if (cctv_type == 3) {
			update(dir, cctv[cctv_index]);
			update(dir + 1, cctv[cctv_index]);
			update(dir + 2, cctv[cctv_index]);
		}
		if (cctv_type == 4) {
			update(dir, cctv[cctv_index]);
			update(dir + 1, cctv[cctv_index]);
			update(dir + 2, cctv[cctv_index]);
			update(dir + 3, cctv[cctv_index]);
		}
		
		// 다음 cctv
		dfs(cctv_index + 1);

		// map recover
		map_copy(map, backup);
	}

}

//0:빈칸, 6:벽, 1~5:cctv
int main() {

	//freopen("input.txt", "r", stdin);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			cin >> map[i][j];

			if (map[i][j] >= 1 && map[i][j] <= 5) {
				cctv[cctv_size].y = i;
				cctv[cctv_size].x = j;
				cctv[cctv_size].type = map[i][j] - 1;	//** 미리 type 세팅
				cctv_size++;
			}
		}
	}

	ret = 100;
	dfs(0);
	cout << ret;

	return 0;
}


