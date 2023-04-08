#include <iostream>

using namespace std;


// map[r][c] : �̼����� ��
// 1. �̼����� �׹��� Ȯ�� :  A[r][c]/5
// A[r][c] = A[r][c] - (A[r][c]/5) * Ȯ��� ����
// �̼����� Ȯ���� ���ο� ��A'�� �ؾ���
// 2. ���� û���� �۵�
// T�ʰ� ���� �� ���� �̼����� ��
int R, C, T;

//int A[50][50];
int A[2][50][50] = { 0, };
int cur = 0; // ���� map index

int air_r1, air_c1;	// ����û�� ��
int air_r2, air_c2; // ����û�� �Ʒ�

// ��������
// 0 : �����¿�
// 1 : ���� �ð�(�Ųٷ�)
// 2 : �Ʒ��� �ݽð�(�Ųٷ�)

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
				// �̼����� ������
				int sum = 0;
				for (int d = 0; d < 4; d++) {
					int nr = r + D[0][d][0];
					int nc = c + D[0][d][1];

					// û���� �ִ� ���̳� �������� ����
					if (nr < 0 || nr >= R || nc < 0 || nc >= C || A[cur][nr][nc] == -1)
						continue;

					// �̹� ���ƿ� �̼����� ��������������, ����
					A[next][nr][nc] += A[cur][r][c] / 5;	// ���ư� ��
					sum += A[cur][r][c]/5;	// ���ư� �� ����
				}
				// �̹� ���ƿ� �̼����� ��������������, ����
				A[next][r][c] += A[cur][r][c] - sum;
			}
		}
	}

	cur = next;
}

void air_on()
{
	/////////////// up
	// ������, ���ʺ�
	for (int r = air_r1 - 1; r > 0; r--) {
		A[cur][r][0] = A[cur][r-1][0];
	}
	// ������, ����
	for (int c = 0; c < C-1; c++) {
		A[cur][0][c] = A[cur][0][c+1];
	}
	// ������, �����ʺ�
	for (int r = 0; r < air_r1; r++) {
		A[cur][r][C-1] = A[cur][r+1][C-1];
	}
	// ������, �Ʒ���
	for (int c = C- 1; c > 1; c--) {
		A[cur][air_r1][c] = A[cur][air_r1][c-1];
	}
	A[cur][air_r1][1] = 0;	// ** ������鼭 ���� �������µ�, ������ĭ�� ��������

	//////////////////// bottom
	// �Ʒ�����, ���ʺ�
	for (int r = air_r2 + 1; r < R-1; r++) {	
		A[cur][r][0] = A[cur][r + 1][0];
	}
	// �Ʒ�����, �Ʒ���
	for (int c = 0; c < C - 1; c++) {
		A[cur][R-1][c] = A[cur][R-1][c + 1];
	}
	// �Ʒ�����, �����ʺ�
	for (int r = R-1; r > air_r2; r--) {
		A[cur][r][C - 1] = A[cur][r-1][C - 1];
	}
	// �Ʒ� ����, ����
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

		// ��ȿ�� ����ƴϸ� ���⸸ �ٲٱ�
		if ((nr < 0 || nr >= R || nc < 0 || nc >= C) || nr > air_r1 ) {
			d = (d + 1) % 4;
			continue;
		}

		if (nr == air_r1 && nc == air_c1 )
			break;

		// ����ĭ�� �̼����� ������ ����, ����
		if (A[cur][nr][nc] > 0 ) {
				
			// ���� ����û���� �ִ� ĭ�̸� �� ���� �ȵ�
			if( A[cur][r][c] != -1 )
				A[cur][r][c] = A[cur][nr][nc];
			A[cur][nr][nc] = 0;
		}

		// ��ĭ �̵�
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

		// ��ȿ�� ����ƴϸ� ���⸸ �ٲٱ�
		if ((nr < 0 || nr >= R || nc < 0 || nc >= C) || nr < air_r2) {
			d = (d + 1) % 4;
			continue;
		}

		// ����ĭ�� ����û���� ������ ������
		if (nr == air_r2 && nc == air_c2)
			break;

		// ����ĭ�� �̼����� ������ ����, ����
		if (A[cur][nr][nc] > 0) {

			// ���� ����û���� �ִ� ĭ�̸� �� ���� �ȵ�
			if (A[cur][r][c] != -1)
				A[cur][r][c] = A[cur][nr][nc];
			A[cur][nr][nc] = 0;
		}

		// ��ĭ �̵�
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