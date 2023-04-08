#include <iostream>
#include <queue>

using namespace std;

// 반지름 i == 원판 i 
// 원판안 숫자(1~M)



// xi : 회전시킬 원판 번호(xi의 배수)
// ki : k 칸
// d : 방향, 0: 시계, 1: 반시계

// 원판을 T번 회전시킨 후 원판에 적힌 수의 합

const int DEL = -1;

int dy[] = {0, 0, 1, -1};
int dx[] = {1, -1, 0, 0};

int N, M, T;
int map[50][50];

int get_sum()
{
	int sum=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != DEL ) {
				sum += map[i][j];
			}
		}
	}
	return sum;
}

float get_average() {
	float sum = 0;
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != DEL) {
				sum += map[i][j];
				count++;
			}
		}
	}
	return sum/count;
}

void rotate(int pick, int d, int k)
{
	int temp[50] = { 0, };
	if (d == 1) {
		// 반시계 방향이면 증가칸 반대로
		k = -k;
	}

	for (int j = 0; j < M; j++) {
		int next = (j + k + M) % M;	// index 음수인 경우 대비해서 +M하고 %M
		temp[next] = map[pick][j];	// 수 이동
	}
	for (int j = 0; j < M; j++) {
		map[pick][j] = temp[j];
	}
}

void update()
{
	// *** 지우는거 따로 표시하고 한꺼번에 지워야함. 안그럼 연속 인접한것 못찾음.
	bool erase_map[50][50] = { 0, };
	bool is_erase = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			for (int d = 0; d < 4; d++) {
				int ny = i + dy[d];
				int nx = j + dx[d];
				nx = (nx + M) % M;	// 음수인 경우 대비해서 +M하고 %M

				if (ny < 0 || ny >= N)
					continue;

				if (map[i][j] <= 0)
					continue;

				if (map[i][j] == map[ny][nx] ) {
					is_erase = true;
					erase_map[i][j] = true;
				}
			}
		}
	}

	if (is_erase) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (erase_map[i][j])
					map[i][j] = DEL;
			}
		}
	} else {
		// 지울게 없는 경우에는 원판에 적힌 수의 평균을 구하고
		// 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다
		float avg = get_average();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {

				if (map[i][j] != DEL) {	///** 점수 있는 곳에만 적용해야함
					if (avg > map[i][j]) {
						map[i][j]++;
					}
					else if (avg < map[i][j]) {
						map[i][j]--;
					}
				}
			}
		}
	}
}

int main()
{
	cin >> N >> M >> T;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	
	int x, d, k;
	for (int t = 0; t < T; t++) {
		cin >> x >> d >> k;

		// 번호가 x의 배수인 원판을 돌면서 d방향으로 k칸 회전
		for (int pick = x; pick <= N; pick += x) {
			rotate(pick-1, d, k);	//*** 원판 id 0부터로 변환
		}

		// 원판에 수가 남아 있으면, 인접하면서 수가 같은 것을 모두 찾아 제거
		// 인접한것 없으면 평균구해서 점수 수정
		update();
	}

	cout << get_sum();

	return 0;
}