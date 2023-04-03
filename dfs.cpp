#include <iostream>
#include <stack>

using namespace std;

#define MAX_N 10
int N, E;
int Graph[MAX_N][MAX_N];
bool visited[MAX_N];

//dfs ��� ���
void dfs_recursive(int node)
{
	visited[node] = true;
	cout << node << ' ';

	for (int next = 0; next < N; next++) {
		if (!visited[next] && Graph[node][next])
			dfs_recursive(next);
	}
}

void dfs_stack(int node)
{
	stack<int> mystack;
	mystack.push(node);

	while ( !mystack.empty() )
	{
		// ���� �� ���� ������
		int cur = mystack.top();
		mystack.pop();

		// �̹� �湮�� ���� pass
		// *pop�Ҷ� visited�� üũ�Ǳ� ������ stack�� �ߺ����� �������� ����.
		if (visited[cur]) continue;

		// �湮 üũ
		visited[cur] = true;
		cout << cur << ' ';

		for (int next = 0; next < N; next++) {
			if (!visited[next] && Graph[cur][next])
				mystack.push(next);
		}
	}
}

int main()
{
	// N : ��尳��, E : ��������
	cin >> N >> E;
	memset(Graph, 0, sizeof(Graph));
	memset(visited, 0, sizeof(visited));
	
	for (int i = 0; i < E; ++i)
	{
		int u, v;
		cin >> u >> v;
		Graph[u][v] = Graph[v][u] = 1;
	}

	//dfs_recursive(0);
	dfs_stack(0);

	return 0;
}