#include <iostream>
#include <stack>

using namespace std;

#define MAX_N 10
int N, E;
int Graph[MAX_N][MAX_N];
bool visited[MAX_N];

//dfs 재귀 방법
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
		// 제일 위 원소 꺼내기
		int cur = mystack.top();
		mystack.pop();

		// 이미 방문한 노드면 pass
		// *pop할때 visited가 체크되기 때문에 stack에 중복으로 들어가있을수 있음.
		if (visited[cur]) continue;

		// 방문 체크
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
	// N : 노드개수, E : 간선개수
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