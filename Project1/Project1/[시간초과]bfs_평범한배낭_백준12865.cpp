#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, K;

int Value[100];
int Weight[100];

struct State {
	int visited[100][100];
	int total_weight;
	int total_value;
};

int bfs(State state)
{
	queue<State> myqueue;
	int max_value = 0;

	myqueue.push(state);

	while( !myqueue.empty() )
	{
		State cur = myqueue.front();
		myqueue.pop();

		// max update
		if (max_value < cur.total_value)
			max_value = cur.total_value;

		// 다음으로 갈수있는 상태 추가
		for (int i = 0; i< N; i++) {
			State next = cur;

			bool is_exist = false;
			for (int j = 0; j < cur.node.size(); j++) {

				// 이미 가방에 들어있는 물품(cur.node)이면 pass
				if (i == cur.node[j]) {
					is_exist = true;
					break;
				}
			}

			if (is_exist) continue;

			// 없는 물품이면 가방에 넣기
			next.node.push_back(i);
			next.total_value += Value[i];
			next.total_weight += Weight[i];

			// 무게가 안넘은 상태이면 큐에 상태 추가
			if (next.total_weight <= K) {
				myqueue.push(next);
			}
		}

	}

	return max_value;

}

int main()
{
	vector<int> max_list;

	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> Weight[i] >> Value[i];
	}

	for (int i = 0; i < N; i++)
	{
		// 시작 상태. (물건번호, 총무게, 총 값어치)
		vector<int> node;
		node.push_back(i);
		State state{node, Weight[i], Value[i]};

		int value = bfs(state);

		max_list.push_back(value);
	}
	
	int max = 0;
	for (int i = 0; i < N; i++)
	{
		if( max < max_list[i] )
			max = max_list[i];
	}
	cout << max << endl;

	return 0;
}

