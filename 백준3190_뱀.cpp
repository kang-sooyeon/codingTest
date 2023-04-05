#include <iostream>
#include <queue>

using namespace std;

// ��� ��ġ : 1
// �� ��ġ : -1
// ��ĭ 0
// ***������ġ (1,1), �����ġ�� �� �������� �־���

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

	// ��Ӹ� ���� ����
	head_y = 1;
	head_x = 1;
	dir = 0;

	// ��ġ ���
	snake[time_].y = head_y; snake[time_].x = head_x;
	tail_index = 0;  // head index�� time�ϰ� �����Ƿ� ����
	// ��ǥ��
	map[head_y][head_x] = -1;


	while (1) {

		time_++;

		// �Ӹ� �̵�
		head_y += dy[dir];
		head_x += dx[dir];

		if (head_x < 1 || head_x > N || head_y < 1 || head_y > N)	//*** ����(1,1)~(N, N)���� ��ȿ����
			break;

		// �Ӹ��� �ڱ� ���̶� �ε���
		if (map[head_y][head_x] == -1)
			break;

		// ��� �ִٸ�, ��� �԰� ���� �״��
		// ��� ���ٸ�, ���� ����
		if (map[head_y][head_x] == 0) {
			map[snake[tail_index].y][snake[tail_index].x] = 0;
			tail_index++;
		}
		// �Ӹ� �ʿ� ǥ��
		map[head_y][head_x] = -1;
		// ��ǥ ���
		snake[time_].y = head_y;
		snake[time_].x = head_x;


		// *** x�� �����ڿ� ��ɾ� ����
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