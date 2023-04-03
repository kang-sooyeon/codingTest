#include <iostream>
#include <queue>

using namespace std;

#define MAX_N 10

int N, Board[MAX_N][MAX_N];

int D[4][2] = {
	{-1, 0 }, // 상
	{1, 0 }, // 하
	{0, -1 }, // 좌
	{0, 1 }  // 우
};

struct Point {
	int row, col, dist;
};



int bfs(int srcRow, int srcCol, int dstRow, int dstCol)
{
	bool visited[MAX_N][MAX_N] = { false };
	queue<Point> myqueue;

	visited[srcRow][srcCol] = true;
	myqueue.push({ srcRow, srcCol, 0});

	while (!myqueue.empty())
	{
		Point cur = myqueue.front();
		myqueue.pop();

		// 목표 좌표에 도달 return!
		if (cur.row == dstRow && cur.col == dstCol)
			return cur.dist;

		for (int i = 0; i < 4; i++)
		{
			// 새로운 탐색 좌표
			int nr = cur.row + D[i][0];
			int nc = cur.col + D[i][1];

			// 바운더리 넘으면 pass
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			// 벽이면 pass
			if (Board[nr][nc] == 1) continue;
			// 방문했으면 pass
			if (visited[nr][nc]) continue;

			visited[nr][nc] = true;
			myqueue.push({ nr, nc, cur.dist + 1 });
		}
	}

	// 경로 찾기 불가
	return -1;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Board[i][j];
		}
	}

	int srcRow, srcCol, dstRow, dstCol;
	cin >> srcRow >> srcCol >> dstRow >> dstCol;

	cout << bfs(srcRow, srcCol, dstRow, dstCol);

	return 0;
}