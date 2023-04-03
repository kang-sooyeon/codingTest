#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

// 상하좌우 복제
// 연구소 바이러스 M개 활성 상태로 pick
// 0 빈칸, 1 벽, 2 바이러스

// 바이러스 위치 저장
// 바이러스 고르기

struct Pos {
	int y;
	int x;
};

int N, M;
int map[50][50];
Pos virus[10];
vector<Pos> pick;
int virus_size=0;
int empty_count = 0;

struct State {
	int y;
	int x;
	int time;
};

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
int ret = 0x7fffffff;

int bfs() {
	
	int _empty_count = empty_count; // * empty_count 매번 새로 세팅해줘야함
	// 칸 확장할 때마다, emtpy_count 제거해가고, 전부 제거되면 return cur.time
	int visited[50][50]{ 0, };
	queue<State> q;

	// 폭탄 seed들 한꺼번에 큐에 push
	for (int i = 0; i < pick.size(); i++) {
		q.push({pick[i].y, pick[i].x, 0});
		visited[pick[i].y][pick[i].x] = 1;
	}

	while (!q.empty()) {
		State cur = q.front(); q.pop();	

		// 바이러스일때는 empty_count--하면 안됨..
		if( map[cur.y][cur.x] == 0 )
			_empty_count--;

		if (_empty_count == 0)
			return cur.time;

		for (int d = 0; d < 4; d++) {
			State next;
			next.y = cur.y + dy[d];
			next.x = cur.x + dx[d];
			next.time = cur.time + 1;

			if (next.y < 0 || next.y >= N || next.x < 0 || next.x >= N )
				continue;

			// 벽만 아니면 확장가능(2인 바이러스여도 확장 가능)
			if ( !visited[next.y][next.x] && map[next.y][next.x] != 1) {
				q.push(next);
				visited[next.y][next.x] = 1;
			}
		}
	}
	return 0x7fffffff;
}

void dfs(int index) 
{
	
	if (pick.size() == M) {
		int time = bfs();
		if (ret > time) ret = time;
		return;
	}

	for (int i = index; i < virus_size; i++) {
		pick.push_back(virus[i]);
		dfs(i+1);
		pick.pop_back();
	}
}

int main() 
{

	//freopen("input.txt", "r", stdin);

	cin >> N >> M;

	virus_size = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			cin >> map[i][j];

			if (map[i][j] == 2) {
				virus[virus_size++] = { i, j };
			}

			if (map[i][j] == 0)
				empty_count++;
		}
	}

	dfs(0);

	if (ret == 0x7fffffff)
		cout << "-1";
	else 
		cout << ret;

	return 0;
}