#include <iostream>

using namespace std;

// �ֻ����� ������ ��, �̵��� ĭ�� ���� �ִ� ���� 0�̸�, 
// �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����
// 0�� �ƴ� ��쿡�� ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����Ǹ�, 
// ĭ�� ���� �ִ� ���� 0


// �̵��� ������ �ֻ����� �� �鿡 ���� �ִ� ���� ���

int N, M;
int map[20][20];
int cur_x, cur_y, K;
int cmd[1000];

void copy(int dst[], int src[])
{
	for (int i = 0; i < 6; i++) {
		dst[i] = src[i];
	}
}

struct DICE {

	int x, y;
	int val[6] = { 0, };

	void move_right() {
		y++;
		int temp[6];
		temp[0] = val[0];
		temp[1] = val[4];
		temp[2] = val[2];
		temp[3] = val[5];
		temp[4] = val[3];
		temp[5] = val[1];
		copy(val, temp);
	}

	void move_left() {
		y--;
		int temp[6];
		temp[0] = val[0];
		temp[1] = val[5];
		temp[2] = val[2];
		temp[3] = val[4];
		temp[4] = val[1];
		temp[5] = val[3];
		copy(val, temp);
	}
	void move_up() {
		x--;
		int temp[6];
		temp[0] = val[1];
		temp[1] = val[2];
		temp[2] = val[3];
		temp[3] = val[0];
		temp[4] = val[4];
		temp[5] = val[5];
		copy(val, temp);
	}

	void move_down() {
		x++;
		int temp[6];
		temp[0] = val[3];
		temp[1] = val[0];
		temp[2] = val[1];
		temp[3] = val[2];
		temp[4] = val[4];
		temp[5] = val[5];
		copy(val, temp);
	}
};

bool is_valid(int x, int y)
{
	if (x >= 0 && x < N && y >= 0 && y < M)
		return true;
	else
		return false;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	DICE dice;

	cin >> N >> M >> dice.x >> dice.y >> K;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			cin >> map[x][y];
		}
	}

	for (int k = 0; k < K; k++) {
		cin >> cmd[k];
	}


	for (int k = 0; k < K; k++) {

		// right
		if (cmd[k] == 1) {
			if (!is_valid(dice.x, dice.y + 1))
				continue;
			dice.move_right();
		}
		// left
		else if (cmd[k] == 2) {
			if (!is_valid(dice.x, dice.y - 1))
				continue;
			dice.move_left();
		}
		// up
		else if (cmd[k] == 3) {
			if (!is_valid(dice.x - 1, dice.y))
				continue;
			dice.move_up();
		}
		// down
		else if (cmd[k] == 4) {
			if (!is_valid(dice.x + 1, dice.y))
				continue;
			dice.move_down();
		}

		if (map[dice.x][dice.y] == 0) {
			map[dice.x][dice.y] = dice.val[3];
		}
		else {
			dice.val[3] = map[dice.x][dice.y];
			map[dice.x][dice.y] = 0;
		}
		cout << dice.val[1] << endl;
	}
	return 0;
}