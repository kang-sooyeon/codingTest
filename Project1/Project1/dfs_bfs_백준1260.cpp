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
	//if (Visited[v] == true) return; --> �ص� ��������� �� �ʿ䰡 ����. ������ ó�� ������ ���״ϱ�..

	cout << v << ' ';
	Visited[v] = true;			// fiboó�� ���� ������ �ʿ䰡 ����. ��¸� �ϸ��

	// ���� ����ؾ��ϴ� �Լ�(��) �θ�.
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

		// ������ ���߿� �־ �����ͺ��� ���˰�...
		for (int next = N; next >= 1; next--)
		{
			if (!visited[next] && Graph[cur][next] == 1) {
				mystack.push(next);
			}
		}
	}
}

// dfs2 �̷��� �ϸ� �ȵ�.. 
// �ʺ�켱 Ž������ ��带 �ֱ� ������(���� ���� ����� ���� ��� ����)
// �������� dfs�� ������ ������, 
// *** 1) ��带 pop�� �� visited�� true���־����. 
// *** 2) �̷��� �Ǹ� ���ÿ� �ߺ��� ������ �� ���� �� �ֱ� ������ pop�ϰ� �ٷ� ����ϸ� �ȵ� -->  ����ϱ� ���� visited�� true�̸�, ���� pop�� �ؾ���.
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

		// ������ ���߿� �־ �����ͺ��� ���˰�...
		for (int next = N; next >= 1; next--)
		{
			if (!visited[next] && Graph[cur][next] == 1) {
				mystack.push(next);
				visited[next] = true;
			}
		}
	}
}


// bfs�� �ʺ�켱 Ž���̱� ������, push�Ҷ� visited true����.
// pop�ϰ� �ٷ� ���

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

