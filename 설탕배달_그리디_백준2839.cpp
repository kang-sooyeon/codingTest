#include <iostream>

using namespace std;

int N; // N kg

int main()
{
	cin >> N;

	int bongji5 = N / 5;
	int ret = -1;

	int min = 987654321;

	for (int i = bongji5; i >= 0; i--)
	{
		int left = N - i * 5;

		int bongji3 = left / 3;
		if (bongji3 * 3 != left) continue;

		int bongji_total = i + bongji3;

		if (min > bongji_total) {
			min = bongji_total;
		}
	}

	if( min == 987654321 ) cout << -1 << endl;
	else cout << min << endl;

	return 0;
}

