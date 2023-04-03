#include <iostream>
#include <stack>

using namespace std;

#define MAX_N 100000
int N;
int A[MAX_N];


//// å�� ��� >> pop�ϴ� ���ڰ� key�� �ƴϸ� ��� pop�Ҳ� ����, ���� �����ϴ� ���̱� ������ �ٷ� NO����ص���
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	stack<int> mystack;
	string ans = "";

	int n = 1; // �־�� �ϴ� ����
	for (int i = 0; i < N; i++)
	{
		bool flag = false;
		int key = A[i];
		// ���ÿ��� n���� ������. ������ ���� ū ����
		// ���ÿ��� k�� ã�ƾ���

		// n <= key : ã�� ���ڰ� ���� ���ÿ� ������ n~key���� push
		if (n <= key) {
			while(n <= key) {
				mystack.push(n);
				ans += "+\n";
				n++;
			}
			mystack.pop();	// ������ ���� key���ڴ� ���
			ans += "-\n";

		// n > key : ã�� ���ڰ� �̹� ���ÿ� ������,
		} else {
			int top = mystack.top();
			mystack.pop();

			if (top == key) {
				ans += "-\n";
			}
			else {	// top�� key�� �ƴ�.. ������ ���� �������ϴ� ��Ȳ --> ���� ǥ�� �Ұ�
				cout << "NO" << endl;
				return 0;
			}

		}
	}

	cout << ans << endl;

	return 0;
}


//key���ö����� pop��� �ϰ�, stack�� empty�̸� "NO"����� �����ص���
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

	int n = 1; // �־�� �ϴ� ����
	for (int i = 0; i < N; i++)
	{
		bool flag = false;
		int key = A[i];
		// ���ÿ��� n���� ������. ������ ���� ū ����
		// ���ÿ��� k�� ã�ƾ���

		// n <= key : ã�� ���ڰ� ���� ���ÿ� ������ n~key���� push
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