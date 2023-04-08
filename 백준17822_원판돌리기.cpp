#include <iostream>
#include <queue>

using namespace std;

// ������ i == ���� i 
// ���Ǿ� ����(1~M)



// xi : ȸ����ų ���� ��ȣ(xi�� ���)
// ki : k ĭ
// d : ����, 0: �ð�, 1: �ݽð�

// ������ T�� ȸ����Ų �� ���ǿ� ���� ���� ��

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
		// �ݽð� �����̸� ����ĭ �ݴ��
		k = -k;
	}

	for (int j = 0; j < M; j++) {
		int next = (j + k + M) % M;	// index ������ ��� ����ؼ� +M�ϰ� %M
		temp[next] = map[pick][j];	// �� �̵�
	}
	for (int j = 0; j < M; j++) {
		map[pick][j] = temp[j];
	}
}

void update()
{
	// *** ����°� ���� ǥ���ϰ� �Ѳ����� ��������. �ȱ׷� ���� �����Ѱ� ��ã��.
	bool erase_map[50][50] = { 0, };
	bool is_erase = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			for (int d = 0; d < 4; d++) {
				int ny = i + dy[d];
				int nx = j + dx[d];
				nx = (nx + M) % M;	// ������ ��� ����ؼ� +M�ϰ� %M

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
		// ����� ���� ��쿡�� ���ǿ� ���� ���� ����� ���ϰ�
		// ��պ��� ū ������ 1�� ����, ���� ������ 1�� ���Ѵ�
		float avg = get_average();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {

				if (map[i][j] != DEL) {	///** ���� �ִ� ������ �����ؾ���
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

		// ��ȣ�� x�� ����� ������ ���鼭 d�������� kĭ ȸ��
		for (int pick = x; pick <= N; pick += x) {
			rotate(pick-1, d, k);	//*** ���� id 0���ͷ� ��ȯ
		}

		// ���ǿ� ���� ���� ������, �����ϸ鼭 ���� ���� ���� ��� ã�� ����
		// �����Ѱ� ������ ��ձ��ؼ� ���� ����
		update();
	}

	cout << get_sum();

	return 0;
}