#include <iostream>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N 1001
#define MAX_M 10000

int Graph[MAX_N][MAX_N];
int N, M, V;

void print_graph()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cout << Graph[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool Visited[MAX_N] = { false };

void dfs_recursive(int v)
{
	//if (Visited[v] == true) return; --> 해도 상관없지만 할 필요가 없음. 무조건 처음 들어오는 걸테니까..

	cout << v << ' ';
	Visited[v] = true;			// fibo처럼 값을 리턴할 필요가 없음. 출력만 하면됨

	// 다음 계산해야하는 함수(값) 부름.
	for (int next = 1; next <= N; next++ )
	{
		if (!Visited[next] && Graph[v][next] == 1) {
			dfs_recursive(next);
		}
	}
}

void dfs1(int v)
{
	stack<int> mystack;
	bool visited[MAX_N] = { false };

	mystack.push(v);

	while (!mystack.empty())
	{
		int cur = mystack.top();
		mystack.pop();

		if (visited[cur]) continue;

		visited[cur] = true;
		cout << cur << ' ';

		// 작은거 나중에 넣어서 작은것부터 나옹게...
		for (int next = N; next >= 1; next--)
		{
			if (!visited[next] && Graph[cur][next] == 1) {
				mystack.push(next);
			}
		}
	}
}

// dfs2 이렇게 하면 안됨.. 
// 너비우선 탐색으로 노드를 넣기 때문에(현재 노드와 연결된 노드들 모두 넣음)
// 스택으로 dfs를 구현할 때에는, 
// *** 1) 노드를 pop할 때 visited를 true해주어야함. 
// *** 2) 이렇게 되면 스택에 중복된 노드들이 들어가 있을 수 있기 때문에 pop하고 바로 출력하면 안됨 -->  출력하기 전에 visited가 true이면, 다음 pop을 해야함.
void dfs2(int v)
{
	stack<int> mystack;
	bool visited[MAX_N] = { false, };

	mystack.push(v);
	visited[v] = true;

	while (!mystack.empty())
	{
		int cur = mystack.top();
		mystack.pop();

	//	if (visited[cur]) continue;
	//	visited[cur] = true;
		cout << cur << ' ';

		// 작은거 나중에 넣어서 작은것부터 나옹게...
		for (int next = N; next >= 1; next--)
		{
			if (!visited[next] && Graph[cur][next] == 1) {
				mystack.push(next);
				visited[next] = true;
			}
		}
	}
}


// bfs는 너비우선 탐색이기 때문에, push할때 visited true해줌.
// pop하고 바로 출력

void bfs(int v)
{
	queue<int> myqueue;
	bool visited[MAX_N] = { false, };

	visited[v] = true;
	myqueue.push(v);

	while (!myqueue.empty()) {

		int cur = myqueue.front();
		myqueue.pop();

		cout << cur << ' ';

		for (int next = 1; next <= N; next++)
		{
			if (!visited[next] && Graph[cur][next] == 1) {
				visited[next] = true;
				myqueue.push(next);
			}
		}
	}
}

int main()
{
	memset(Graph, 0, sizeof(Graph));

	cin >> N >> M >> V;

	int u, v;
	for (int i = 1; i <= M; i++)
	{
		cin >> u >> v;
		Graph[u][v] = Graph[v][u] = 1;
	}

	//print_graph();

	dfs_recursive(V);
	//dfs1(V);
	//dfs2(V);
	cout << endl;

	bfs(V);

	return 0;
}

