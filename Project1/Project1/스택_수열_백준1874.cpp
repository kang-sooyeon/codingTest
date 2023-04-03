#include <iostream>
#include <stack>

using namespace std;

#define MAX_N 100000
int N;
int A[MAX_N];


//// 책의 방법 >> pop하는 숫자가 key가 아니면 계속 pop할꺼 없이, 숫자 낭비하는 것이기 때문에 바로 NO출력해도됨
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	stack<int> mystack;
	string ans = "";

	int n = 1; // 넣어야 하는 숫자
	for (int i = 0; i < N; i++)
	{
		bool flag = false;
		int key = A[i];
		// 스택에는 n까지 들어가있음. 상위가 가장 큰 숫자
		// 스택에서 k을 찾아야함

		// n <= key : 찾는 숫자가 아직 스택에 없으면 n~key까지 push
		if (n <= key) {
			while(n <= key) {
				mystack.push(n);
				ans += "+\n";
				n++;
			}
			mystack.pop();	// 마지막 넣은 key숫자는 출력
			ans += "-\n";

		// n > key : 찾는 숫자가 이미 스택에 있으면,
		} else {
			int top = mystack.top();
			mystack.pop();

			if (top == key) {
				ans += "-\n";
			}
			else {	// top이 key가 아님.. 허투루 숫자 날려야하는 상황 --> 수열 표현 불가
				cout << "NO" << endl;
				return 0;
			}

		}
	}

	cout << ans << endl;

	return 0;
}


//key나올때까지 pop계속 하고, stack이 empty이면 "NO"출력후 종료해도됨
/*
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	stack<int> mystack;
	string ans = "";

	int n = 1; // 넣어야 하는 숫자
	for (int i = 0; i < N; i++)
	{
		bool flag = false;
		int key = A[i];
		// 스택에는 n까지 들어가있음. 상위가 가장 큰 숫자
		// 스택에서 k을 찾아야함

		// n <= key : 찾는 숫자가 아직 스택에 없으면 n~key까지 push
		while (n <= key) {
			while (n <= key) {
				mystack.push(n);
				ans += "+\n";
				n++;
			}
		}

		if (mystack.empty()) {
			cout << "NO" << endl;
			return 0;
		}

		while (1) {
			int top = mystack.top();
			mystack.pop();
			ans += "-\n";
			if (top == key)
				break;

			if (mystack.empty()) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
*/