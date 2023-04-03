#include <iostream>

using namespace std;

int in[3];
int out[3];
int fee[3];
int total_fee=0;

int main(void)
{
	for (int i = 0; i < 3; i++)
		cin >> fee[i];

	int end = 0;
	for (int i = 0; i < 3; i++) {
		cin >> in[i] >> out[i];

		if (out[i] > end)
			end = out[i];
	}

	for (int t = 2; t <= end; t++)
	{

		int count = 0;
		for (int i = 0; i < 3; i++) {
			if (in[i] < t || t < out[i])
			{
				count++;
			}

			total_fee += fee[count - 1] * count;
		}
	}

	cout << total_fee << endl;

	return 0;
}
