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

		// �������� �����ִ� ���� �߰�
		for (int i = 0; i< N; i++) {
			State next = cur;

			bool is_exist = false;
			for (int j = 0; j < cur.node.size(); j++) {

				// �̹� ���濡 ����ִ� ��ǰ(cur.node)�̸� pass
				if (i == cur.node[j]) {
					is_exist = true;
					break;
				}
			}

			if (is_exist) continue;

			// ���� ��ǰ�̸� ���濡 �ֱ�
			next.node.push_back(i);
			next.total_value += Value[i];
			next.total_weight += Weight[i];

			// ���԰� �ȳ��� �����̸� ť�� ���� �߰�
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
		// ���� ����. (���ǹ�ȣ, �ѹ���, �� ����ġ)
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

