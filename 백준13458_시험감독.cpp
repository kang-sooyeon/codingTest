#include <iostream>
#include <queue>

using namespace std;

int N;
int A[1000000]; // 시험장
int B, C;
long int ret = 0;

// A[i] : 응시자 수
// 총감동관 : 한 시험장에서 감독할 수 있는 응시자 수 B명(각 시험장 오직 1명)
// 부감독관 : 한 시험장에서 감독할 수 있는 응시자 수 C명(각 시험장 여러명 가능)
// 필요한 감독관 수의 최솟값

// solution
// 총감독관 우선 배치, 나머지를 부감독관이 맡기
int main()
{
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	cin >> B >> C;

	for (int i = 0; i < N; ++i) {

		int cur = A[i];

		cur = cur - B;
		ret++;
		if (cur <= 0)
			continue;

		ret += cur / C;
		if (cur % C > 0)
			ret++;
	}

	cout << ret << endl;
	return 0;
}