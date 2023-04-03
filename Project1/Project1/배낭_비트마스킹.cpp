#include <iostream>

using namespace std;

int N, K;

int Value[100];
int Weight[100];

bool On[100];

int main()
{
	//int n = 5;
	////n = n >> 1;
	//int mask = n & 0x1;
	//cout << mask << endl;
	
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> Weight[i] >> Value[i];
	}

	int index = pow(2, N);
	
	for (int i = 1; i < index; i++)
	{
		i & 0x1;

	}


	return 0;
}

