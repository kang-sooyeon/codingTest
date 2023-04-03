#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define MAX_N 16

int N;


struct State {
	int day;
	int totalP;
};

struct INFO {
	int T;
	int P;
};

INFO info[MAX_N];


int bfs(State s)
{
	queue<State> queue;
	//bool visited[MAX_N] = { false };
	int max_totalP = 0;

	queue.push(s);
	//visited[s.day] = true;

	while (!queue.empty())
	{
		State cur = queue.front();
		queue.pop();
		
		if (cur.day > N + 1) continue;

		if (max_totalP < cur.totalP)
			max_totalP = cur.totalP;


		// 가능한 다음 탐색 상태들 
		for (int i = cur.day; i <= N; i++) {

			if( i + info[i].T > N+1 ) continue;

			State next = cur;
			next.day = i + info[i].T;
			next.totalP += info[i].P;

			queue.push(next);
		}

	}

	return max_totalP;
}

int main()
{
	queue<State> myqueue;
	vector<int> v_max;

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> info[i].T >> info[i].P;
	}

	for (int i = 1; i <= N; i++) {
		// 날짜가 초과되는 않는 업무
		if (i + info[i].T <= N+1) {
			int totalP = bfs({i+(info[i].T), info[i].P});
			v_max.push_back(totalP);
		}
	}

	// v의 최대값 반환
	int len = v_max.size();
	int max = 0;
	for (int i = 0; i < len; i++)
	{
		if (max < v_max[i]) max = v_max[i];
	}
	cout << max << endl;

	return 0;
}


