#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos {
	int y;
	int x;
};

int N, M;
int map[8][8];
int cctv_size = 0;
Pos cctv[8];

int ret = 0x7fffffff;
int rot_size[] = {4, 2, 4, 4, 1};
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void map_copy(int dst[][8], int src[][8])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

void print_map()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void update(int d, Pos p)
{
	d = d % 4;
	
	if (d == 1) {
		for (int x = p.x + 1; x < M; ++x) {
			if (map[p.y][x] == 6) break;
			map[p.y][x] = -1;
		}
	}
	if (d == 3) {
		for (int y = p.y - 1; y >= 0; --y) {
			if (map[y][p.x] == 6) break;
			map[y][p.y] = -1;
		}
	}
	if (d == 2) {
		for (int x = p.x - 1; x >= 0; --x) {
			if (map[p.y][x] == 6) break;
			map[p.y][x] = -1;
		}
	}
	if (d == 2) {
		for (int y = p.y + 1; y < N; ++y) {
			if (map[y][p.x] == 6) break;
			map[y][p.x] = -1;
		}
	}
}

/*
void update(int d, Pos p)
{
	d = d % 4;
	int y = p.y;
	int x = p.x;
	while (1) {
		y += dy[d];
		x += dx[d];

		if (y < 0 || y >= N || x < 0 || x >= M)
			break;

		if (map[y][x] == 6)
			break;

		map[y][x] = 9;
	}
}
*/

void dfs(int index) 
{
	if (index == cctv_size) {
		
		//print_map();

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
	Pos cctv_pos = cctv[index];
	int cctv_type = map[cctv_pos.y][cctv_pos.x]-1;
	int rot_size_ = rot_size[cctv_type];

	//cout << "index : " << index << endl;
	//cout << "cctv_type : " << cctv_type << endl;
	//cout << "rot_size_ : " << rot_size_ << endl;

	for (int d = 0; d < rot_size_; d++) {
		// map update
		map_copy(backup, map);
		if (cctv_type == 0) {
			update(d+1, cctv[index]);
		}
		else if (cctv_type == 1) {
			update(d+1, cctv[index]);
			update(d+3, cctv[index]);
		}
		else if (cctv_type == 2) {
			update(d, cctv[index]);
			update(d+1, cctv[index]);
		}
		else if (cctv_type == 3) {
			update(d, cctv[index]);
			update(d + 1, cctv[index]);
			update(d + 3, cctv[index]);
		}
		else if (cctv_type == 4) {
			update(d, cctv[index]);
			update(d + 1, cctv[index]);
			update(d + 2, cctv[index]);
			update(d + 3, cctv[index]);
		}
		
		// 다음 cctv
		dfs(index + 1);

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
				cctv[cctv_size++] = { i, j };
			}
		}
	}

	dfs(0);

	cout << ret;
	return 0;
}


