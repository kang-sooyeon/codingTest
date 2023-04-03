

//단계 L 반복
// 토네이도 시전(격자들 90도 회전)
// 현재칸이 인접해 있는 칸중 얼음 있는 칸이 2개 이하 이면,, 얼음양 1 감소


// 남아있는 얼음의 합
// 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수 :  bfs


#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <deque>
#include <queue>

using namespace std;

#define MAX_Q 1000

int A[64][64];
int B[64][64]; // 인접 얼음 갯수 
int temp[64][64]; // 회전 격자 임시 저장
int _L[MAX_Q]; // 토네이도 2의 L

int N, two_pow_N; // 맵크기 2의 N 
int Q; // Q번 시전
int L, two_pow_L, two_pow_Lplus1, two_pow_Lminus1; // 토네이도 2의 L, 2의 L+1
int max_size = 1; // 가장 큰 덩어리가 차지하는 칸의 개수
int ice_cnt = 0;

int D[4][2] = {
	{-1, 0},
	{1, 0},
	{0, 1},
	{0, -1}
};

template <typename T>
void print(T array)
{
	cout << "=================" << endl;
	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "=================" << endl;
}

struct Point {
	int r;
	int c;
};

struct Part {
	vector<int> values; // 1, 2, 3, 4, 5... (2의 L-1승 파트부분에 있는 값들)
};

struct State {
	int r;
	int c;
};

bool Visited[64][64];


void rotate(int sr, int sc)
{

	for (int i = 0; i < two_pow_L; i++) {
		for (int j = 0; j < two_pow_L; j++) {
			temp[i][j] = A[sr + two_pow_L - 1 - j][sc + i];
		}
	}

	for (int i = 0; i < two_pow_L; i++) {
		for (int j = 0; j < two_pow_L; j++) {
			A[sr + i][sc + j] = temp[i][j];
		}
	}

}

void reset_visited()
{
	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {
			// 얼음 없으면 방문처리
			if (A[i][j] > 0)
				Visited[i][j] = false;
			else
				Visited[i][j] = true;
		}
	}
}

Point get_seed()
{
	Point seed{ -1, -1 };
	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {
			if (!Visited[i][j]) {
				seed.r = i;
				seed.c = j;
				return seed;
			}
		}
	}
	return seed;
}

bool is_valid(int r, int c)
{
	if (r >= 0 && r < two_pow_N && c >= 0 && c < two_pow_N)
		return true;
	return false;
}

void calc_ice() {

	//*** 주변 얼음 갯수 체크를 전체 적용한 후에, 2개 이하면 감소 시켜야함. 
	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {

			int adj_cnt = 0;
			for (int d = 0; d < 4; d++) {
				int r = i + D[d][0];
				int c = j + D[d][1];

				if (!is_valid(r, c)) continue;

				// 얼음 남아있으면
				if (A[r][c] > 0) adj_cnt++;
			}

			B[i][j] = adj_cnt;

		}
	}

	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {
			// 주변 얼음 2개 이하면
			if (B[i][j] <= 2) {
				if (A[i][j] > 0)
					A[i][j]--;
			}
		}
	}
}

int sum()
{
	int sum = 0;
	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {
			sum += A[i][j];
		}
	}
	return sum;
}

void bfs(State s)
{
	queue<State> myqueue;
	int size = 0;

	myqueue.push(s);
	Visited[s.r][s.c] = true;
	size++;

	while (!myqueue.empty()) {
		State cur = myqueue.front();
		myqueue.pop();

		// 새로운 탐색 시작
		for (int d = 0; d < 4; d++) {
			State next = cur;
			next.r += D[d][0];
			next.c += D[d][1];

			if (!is_valid(next.r, next.c)) continue;

			if (!Visited[next.r][next.c]) {
				myqueue.push(next);
				Visited[next.r][next.c] = true;
				size++;
			}
		}
	}
	if (size > max_size) max_size = size;
}


int main()
{

	cin >> N >> Q;
	two_pow_N = pow(2, N);

	for (int i = 0; i < two_pow_N; i++) {
		for (int j = 0; j < two_pow_N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> _L[i];
	}
	//////

	for (int q = 0; q < Q; q++)
	{
		L = _L[q];
		//격자 크기 2의 L승
		two_pow_L = pow(2, L);

		// 각 격자 내부에서 회전시킬거임
		for (int i = 0; i < two_pow_N; i += two_pow_L) {
			for (int j = 0; j < two_pow_N; j += two_pow_L) {
				rotate(i, j); // 토네이도 시전
			}
		}

		// 격자적용후
		//cout << "격자 적용후";
		//print(A);

		// 얼음 재계산
		calc_ice();
		//cout << "얼음 융해후";
		//print(A);

	}

	// 얼음 없는 값 방문 처리
	reset_visited();

	// 얼음이 있는 한, 계속 다시 bfs 탐색
	while (1) {

		Point seed = get_seed();
		if (seed.r == -1 && seed.c == -1)
			break;

		bfs({ seed.r, seed.c }); // 시작위치, 칸크기
	}

	cout << sum() << endl;
	cout << max_size << endl;

	return 0;
}
