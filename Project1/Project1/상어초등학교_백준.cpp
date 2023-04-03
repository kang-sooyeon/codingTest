#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;
#define MAX_N 20

struct Point {
	int r;
	int c;
};

struct INFO {
	int id;
	int favorite_ids[4];
};

int D[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};


vector<INFO> info_list;

int Map[MAX_N][MAX_N];
int Score[MAX_N][MAX_N];
int N;

Point Positions[MAX_N * MAX_N];

Point get_position(int idx)
{
	Point p;
	p.r = idx / N;
	p.c = idx % N;
	return p;
}

int get_idx(Point  p)
{
	int idx = p.r * N + p.c;
	return idx;
}

void print_array(int array[MAX_N][MAX_N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << array[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


bool is_valid(int r, int c)
{
	if (r >= 0 && r < N && c >= 0 && c < N) return true;
	return false;
}


//������ ĭ�� ����ִ� ĭ�� ���
int get_empty_adj_n(Point p)
{
	int cnt = 0;
	for (int d = 0; d < 4; d++)
	{
		int r_ = p.r + D[d][0];
		int c_ = p.c + D[d][1];

		if (!is_valid(r_, c_)) continue;

		if (Map[r_][c_] == -1)
			cnt++;
	}
	return cnt;
}


void reset_score()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] != -1)
				Score[i][j] = -1;
			else
				Score[i][j] = 0;
		}
	}
}

void scoring(int favorite_id)
{
	// �� ���鼭, ���� �ڸ��� �����ϴ� ���� ������� üũ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			// Map[i]j]�� �����Ǿ� ������
			if (Map[i][j] != -1) continue;

			int r, c;
			for (int d = 0; d < 4; d++) {
				r = i + D[d][0];
				c = j + D[d][1];

				if (!is_valid(r, c)) continue;

				if (Map[r][c] == favorite_id) (Score[i][j])++;
			}
		}
	}
}

bool is_adj(Point p1, Point p2)
{
	int dist = abs(p1.r - p2.r) + abs(p1.c - p2.c);

	if (dist == 1) return true;
	return false;
}

int calc_satisfactory_score()
{
	// �� ��ǥ ����(index:�л�id, value: ��ǥ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int id_idx = Map[i][j];
			Positions[id_idx] = { i, j };
		}
	}

	int score = 0;
	// �� �л��� ������ ���
	for (auto iter = info_list.begin(); iter < info_list.end(); iter++) {
		// �������� ����� �л�id
		int id = iter->id;
		int good_cnt = 0;
		// �����ϴ� id�� �����Ÿ��� �ִ� ��������
		for (int i = 0; i < 4; i++) {
			int favorite_id = iter->favorite_ids[i];
			if (is_adj(Positions[id], Positions[favorite_id]))
				good_cnt++;
		}

		switch (good_cnt) {
		case 0:
			score += 0;
			break;
		case 1:
			score += 1;
			break;
		case 2:
			score += 10;
			break;
		case 3:
			score += 100;
			break;
		case 4:
			score += 1000;
			break;
		default:
			break;
		}
	}

	return score;
}

// max ���ھ� ��ǥ ���ϱ�, max ���ھ� ���ٸ� �������ڸ� ���� ��ǥ, �������� ��ǥidx ���� ��ǥ
Point get_my_position()
{
	// max ���ھ� ���ϱ�
	int max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (max < Score[i][j]) max = Score[i][j];
		}
	}

	// max ���ھ� �������ϼ� ������ vector�� ����
	vector<Point> max_point_list;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (max == Score[i][j]) {
				max_point_list.push_back({ i, j });
			}
		}
	}

	// max ���ھ� �ϳ��� ���ڸ� ��ǥreturn
	int size = max_point_list.size();
	if (size == 1)
		return max_point_list[0];
	if (size == 0) {
		cout << "error" << endl;
		exit(-1);
	}

	// ���� ���ڸ� ����� Ȯ��, 	
	// ���ڸ� ������ map�� ����(key: ���� ���ڸ�, valu: ��ǥ)
	map<int, Point> map;
	for (int i = 0; i < size; i++) {
		int empty_adj_n = get_empty_adj_n(max_point_list[i]);

		// �̹� �ִ� ��
		auto iter = map.find(empty_adj_n);
		if (iter != map.end()) {
			Point& find_pos = iter->second;
			int cur_idx = get_idx(find_pos);
			int new_idx = get_idx(max_point_list[i]);
			if (cur_idx > new_idx) {
				find_pos = max_point_list[i];
			}
		}
		else {
			map.insert({ empty_adj_n ,max_point_list[i] });
		}
	}
	auto iter = map.end();
	iter--;
	return iter->second;
}


int main()
{

	cin >> N;
	int N2 = N * N;

	for (int i = 0; i < N2; i++)
	{
		INFO info;
		cin >> info.id;
		for (int j = 0; j < 4; j++)
		{
			cin >> info.favorite_ids[j];
		}
		info_list.push_back(info);
	}
	///////////

	memset(Map, -1, sizeof(Map));

	for (int i = 0; i < info_list.size(); i++) {

		int id = info_list[i].id;

		// ���ھ� �迭 �ʱ�ȭ
		reset_score();

		// ���ھ� �迭�� ���ھ �ű�� (�ֺ��� �����ϴ� �� �������)
		for (int j = 0; j < 4; j++)
		{
			int favorite_id = info_list[i].favorite_ids[j];

			// ���� �ű��
			scoring(favorite_id);
		}

		// max ���ھ� ��ǥ ���ϱ�, max ���ھ� ���ٸ� �������ڸ� ���� ��ǥ, �������� ��ǥidx ���� ��ǥ
		Point p = get_my_position();

		// map�� id ǥ��
		Map[p.r][p.c] = id;

		// Positions[id] = { p.r, p.c }; // �����ϸ� �� �̰� ��Ÿ�� ��������..???
	}

	//////////
	//cout << "map" << endl;
	//print_array(Map);
	//cout << "reset score" << endl;
	//print_array(Score);
	cout << calc_satisfactory_score();


	return 0;
}

