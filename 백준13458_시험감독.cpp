#include <iostream>
#include <queue>

using namespace std;

int N;
int A[1000000]; // ������
int B, C;
long int ret = 0;

// A[i] : ������ ��
// �Ѱ����� : �� �����忡�� ������ �� �ִ� ������ �� B��(�� ������ ���� 1��)
// �ΰ����� : �� �����忡�� ������ �� �ִ� ������ �� C��(�� ������ ������ ����)
// �ʿ��� ������ ���� �ּڰ�

// solution
// �Ѱ����� �켱 ��ġ, �������� �ΰ������� �ñ�
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