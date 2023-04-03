#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, L, R;
int map[50][50];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

struct Pos {
	int y;
	int x;
};

void create_union(int y, int x, int status[][50], int area_index, int &count, int &sum)
{
	int visited[50][50] = {0 };
	queue<Pos> q;

	q.push({ y, x });
	visited[y][x] = 1;
	
	while ( !q.empty() ) {

		Pos cur = q.front();
		q.pop();

		status[cur.y][cur.x] = area_index;
		sum += map[cur.y][cur.x];
		count++;

		for (int d = 0; d < 4; d++) {
			Pos next;
			next.y = cur.y + dy[d];
			next.x = cur.x + dx[d];

			if (next.y < 0 || next.y >= N || next.x < 0 || next.x >= N)
				continue;

			int diff = abs(map[cur.y][cur.x] - map[next.y][next.x]);
			if (!visited[next.y][next.x] && diff >= L && diff <= R) {
				q.push({ next.y, next.x });
				visited[next.y][next.x] = true;
			}
		}
	}
}

int main(void) 
{

	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	
	int answer = 0;

	bool is_update = true; // ��ȭ ����

	while ( is_update ) {

		is_update = false;

		/////////////// ��ü �α� �̵�
		int area_index = 0; // ���� �ε���
		int status[50][50] = {0, }; // ���� �ε��� ǥ���� ��
		int count[2501] = { 0, }; // ���� count ����ؼ� ����
		int sum[2501] = { 0, }; // ���� sum ����ؼ� ����

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// status[i][j],������ȣ seed �μ�..
				if (status[i][j] == 0) {
					area_index++;
					create_union(i, j, status, area_index, count[area_index], sum[area_index]);
				}
			}
		}
		////////////////

		// ������Ʈ ������ true
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				area_index = status[i][j];
				int avg = sum[area_index] / count[area_index];
				if (avg != map[i][j]) {
					map[i][j] = avg;
					is_update = true;
				}
			}
		}

		
		if ( is_update )
			answer++;
	}

	cout << answer << endl;
	
	return 0;
}