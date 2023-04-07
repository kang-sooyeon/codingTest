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

// �ʿ� ���ǥ��
// ��� index : 1~
// ��ĭ : 0

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

		// 2. �������� ��� ���(��� �����)
		for( int r = 0; r < R; r++ ) {
			// ��ĭ�� �ƴϸ� ��� ���, ��� ����
			if (map[r][fisher_c] != 0) {
				int shark_index = map[r][fisher_c];
				score += sharks[shark_index].size;
				sharks[shark_index].gotten = true;
				map[r][fisher_c] = 0;
				break;
			}
		}
		// 3. ��� �̵�
		// ****��� �̵���Ű�� ��ġ���� Ȯ���ؾ���(**���� ��� ����)
		for (int m = 1; m <= M; m++) {

			if (sharks[m].gotten)
				continue;

			int r = sharks[m].r;
			int c = sharks[m].c;
			int dir = sharks[m].dir;
			int fast = sharks[m].fast;

			if (dir == 1) {
				// y ����
				r = ((R - 1) * 2 - r);	// y �����ϱ� ������, �����ϴ� index ����(index ��ȯ)
				r = r + fast;	// �̵����� ���ϰ�
				r = r % ((R - 1) * 2); // ��ⷯ�ϸ� index ����.
				dir = 2;	// ����
				
				if (r >= R - 1) {
					// ������ index �����̸�, ���� �ٲٰ�, index ��ȯ
					r = ((R - 1) * 2 - r);
					dir = 1;
				}
			} else if (dir == 2) {
				// y ����
				r = r + fast;	// �̵����� ���ϰ�
				r = r % ((R - 1) * 2); // ��ⷯ�ϸ� index ����.
				dir = 2;	// ����
				if (r >= R - 1) {
					// ������ index �����̸�, ���� �ٲٰ�, index ��ȯ
					r = ((R - 1) * 2 - r);
					dir = 1;
				}

			} else if (dir == 3) {
				// x ����
				c = c + fast;	// �̵����� ���ϰ�
				c = c % ((C - 1) * 2); // ��ⷯ�ϸ� index ����.
				dir = 3;	// ����
				if (c >= C - 1) {
					// ������ index �����̸�, ���� �ٲٰ�, index ��ȯ
					c = ((C - 1) * 2 - c);
					dir = 4;
				}
			} else if (dir == 4) {
				// x ����
				c = ((C - 1) * 2) - c;
				c = c + fast;	// �̵����� ���ϰ�
				c = c % ((C - 1) * 2); // ��ⷯ�ϸ� index ����.
				dir = 3;	// ����
				if (c >= C - 1) {
					// ������ index �����̸�, ���� �ٲٰ�, index ��ȯ
					c = ((C - 1) * 2 - c);
					dir = 4;
				}
			}

			sharks[m].r = r;
			sharks[m].c = c;
			sharks[m].dir = dir;
		}

		// 4. ������ ǥ�� �� ��ġ�� ��� ó��(***���� ��� ����)
		int next_map[100][100] = { 0, };
		for (int m = 1; m <= M; m++) {

			if (sharks[m].gotten)
				continue;

			int r = sharks[m].r;
			int c = sharks[m].c;

			if (next_map[r][c] == 0) {
				// ��� ����
				next_map[r][c] = m;
			} else {
				// �̹� ��� ����
				int shark_index = next_map[r][c];
				if (sharks[shark_index].size < sharks[m].size) {
					// ���� �� �� ũ�� 
					next_map[r][c] = m;
					sharks[shark_index].gotten = true;
				}
				else {
					// ������ �� �� ũ��
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