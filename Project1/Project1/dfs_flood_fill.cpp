#include <iostream>
#include <stack>

using namespace std;


#define MAX_N 10

struct Point {
	int r;
	int c;
};

int D[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

int N, Board[MAX_N][MAX_N];

void print_board()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << Board[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

bool is_valid(Point p)
{
	if (p.r >= 0 && p.r < N && p.c >= 0 && p.c < N)
		return true;
	return false;
}

void dfs(int sr, int sc, int color)
{
	stack<Point> mystack;
	bool visited[MAX_N][MAX_N] = {false};

	mystack.push({ sr, sc });

	while ( !mystack.empty()) {

		Point cur = mystack.top();
		mystack.pop();

		// �̹� �湮�� ��ǥ�� pass, stack�� ���� ��ǥ�� �ߺ����� ��������
		if (visited[cur.r][cur.c]) continue;
		
		visited[cur.r][cur.c] = true;
		Board[cur.r][cur.c] = color;

		// �� Ž�� ��ǥ �ֱ�
		Point next;
		for (int i = 0; i < 4; i++) {
			next.r = cur.r + D[i][0];
			next.c = cur.c + D[i][1];
			
			// pass�� ��ǥ case
			//if ( Board[next.r][next.c] == 1 || Board[next.r][next.c] == color) continue; --> 3�� �湮�� ���
			if (Board[next.r][next.c] == 1 ) continue;

			if (visited[next.r][next.c]) continue;
			if (!is_valid(next)) continue;
			
			// ��ȿ�� ��ǥ�� push
			mystack.push(next);
		}
		
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> Board[i][j];

	int sr, sc, color;
	cin >> sr >> sc >> color;

	print_board();

	dfs(sr, sc, color);

	print_board();

	return 0;
}