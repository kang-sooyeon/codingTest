#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_N 100000

int A[MAX_N];
int N;


struct cmp {
	bool operator()(int& a, int& b) {
		// 절대값 오름차순
		if (abs(a) > abs(b)) {
			return true;
		}
		else if (abs(a) == abs(b)) {
			//  크기 오름차순
			if (a > b) return true;
			else return false;
		}
		return false;
	}
};

int main()
{

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	priority_queue<int, vector<int>, cmp> myqueue;

	for (int i = 0; i < N; i++)
	{
		int val = A[i];

		if (val != 0) {
			myqueue.push(val);
		}
		else {
			if (myqueue.empty()) {
				cout << "0" << endl;
				continue;
			}
			int val = myqueue.top();
			myqueue.pop();
			cout << val << endl;
		}
	}

	return 0;
}

