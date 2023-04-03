#include <iostream>

using namespace std;

#define MAX_N 5000000
int N, L;
int A[MAX_N];
int D[MAX_N];

#define MAX 10000000001

int main()
{

	cin >> N >> L;

	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	for (int i = 0; i < N; i++) {
		int h = i - L + 1;
		int min = MAX;
		for (; h <= i; h++) {
			if (h < 0) continue;

			if (A[h] < min) {
				min = A[h];
			}
		}
		cout << min << " ";
	}
	return 0;
}

