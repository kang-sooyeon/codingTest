#include <iostream>
#include <queue>

using namespace std;

// 사과 위치 : 1
// 뱀 위치 : -1
// 빈칸 0
// ***시작위치 (1,1), 사과위치도 이 기준으로 주어짐

struct CMD {
	int time;
	char dir;
};

struct Snake{
	int y;
	int x;
};

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

int time_ = 0;
int N, K, L;
int map[101][101] = { 0, };
char cmd[10101];
Snake snake[10101];
int head_y, head_x, dir;
int tail_index = 0;


int main() {

	//freopen("input.txt", "r", stdin);

	cin >> N >> K;

	int y, x;
	for (int k = 0; k < K; k++) {
		cin >> y >> x;
		map[y][x] = 1;
	}

	cin >> L;
	int t;
	for (int l = 0; l < L; l++) {
		cin >> t;
		cin >> cmd[t];
	}

	// 뱀머리 방향 설정
	head_y = 1;
	head_x = 1;
	dir = 0;

	// 위치 기록
	snake[time_].y = head_y; snake[time_].x = head_x;
	tail_index = 0;  // head index는 time하고 같으므로 생략
	// 맵표시
	map[head_y][head_x] = -1;


	while (1) {

		time_++;

		// 머리 이동
		head_y += dy[dir];
		head_x += dx[dir];

		if (head_x < 1 || head_x > N || head_y < 1 || head_y > N)	//*** 기준(1,1)~(N, N)까지 유효범위
			break;

		// 머리가 자기 몸이랑 부딪힘
		if (map[head_y][head_x] == -1)
			break;

		// 사과 있다면, 사과 먹고 꼬리 그대로
		// 사과 없다면, 꼬리 제거
		if (map[head_y][head_x] == 0) {
			map[snake[tail_index].y][snake[tail_index].x] = 0;
			tail_index++;
		}
		// 머리 맵에 표시
		map[head_y][head_x] = -1;
		// 좌표 기록
		snake[time_].y = head_y;
		snake[time_].x = head_x;


		// *** x초 끝난뒤에 명령어 적용
		if (cmd[time_] == 'L') {
			dir = (dir + 3) % 4;
		}
		if (cmd[time_] == 'D') {
			dir = (dir + 1) % 4;
		}
	}

	cout << time_;

	return 0;
}