#include <iostream>
#include <queue>

using namespace std;

#define MAX_N 15

int N;
int T[MAX_N], P[MAX_N];
int cache[MAX_N];


int solve(int day)
{
	if (day > N) return -9876543;
	if (day == N ) return 0;

	int& ret = cache[day];
	if (ret != -1)
		return ret;

	ret = max(solve(day + 1), solve(day + T[day]) + P[day]);
	
	return ret;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> T[i] >> P[i];
		cache[i] = -1;
	}

	cout << solve(0);

	return 0;
}
