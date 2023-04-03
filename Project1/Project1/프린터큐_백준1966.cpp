#include <iostream>
#include <queue>

using namespace std;

int testcase;

struct INFO {
	int no;
	int priority;
};

void print_job_list(vector<INFO> &job_list)
{
	for (int i = 0; i < job_list.size(); i++)
	{
		cout << job_list[i].no << ", " << job_list[i].priority << endl;
	}
}

int main()
{
	cin >> testcase;
	int N, K;

	vector<vector<INFO>> testcase_list;
	vector<int> key_list;

	for (int i = 0; i < testcase; i++)
	{
		vector<INFO> job_list;

		int n_print = 0;

		cin >> N >> K;
		key_list.push_back(K);

		for (int n = 0; n < N; n++)
		{
			int p;
			cin >> p;
			INFO info({ n, p });
			job_list.push_back(info);
		}

		testcase_list.push_back(job_list);
	}

	for (int i = 0; i < testcase; i++)
	{
		int n_print = 0;

		for (int n = 0; n < N; n++)
		{
			//print_job_list(job_list);
			// ������ť���� �ϳ��� ������
			INFO cur = testcase_list[i][0];

			testcase_list[i].erase(testcase_list[i].begin());

			//print_job_list(job_list);

			bool is_exist = false;
			// �����ִ� ������ �� 
			for (int j = 0; j < testcase_list[i].size(); j++)
			{
				// �켱���� �� ū�� ������ �ڷ� �ٽ� �ֱ�
				if (testcase_list[i][j].priority > cur.priority)
				{
					testcase_list[i].push_back({ cur });
					is_exist = true;
					break;
				}
			}

			//  ������ ��µȰ� 
			if (!is_exist) {
				n_print++;

				// ã�� ������
				if (cur.no == key_list[i]) {
					cout << n_print << endl;
					break;
				}
			}
		}
	}

	return 0;
}

