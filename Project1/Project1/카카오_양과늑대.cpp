#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

#define MAX_N 17


struct State {
    int state_no = 1;   // **** �湮�� ������ ������ bitmasking���� ����
    int nsheep = 1;
    int nwolf = 0;
};

/////// Ʈ�� ���� ����
// ���� �ڽ� �����ϴ���(����)
struct Node {
    int val = -1; // ��:0, ����:1
    int left = -1;
    int right = -1;
};

Node nodes[MAX_N];

// ��� ����
int N;

// ����x�� �湮�ߴ°�(bit-masking), �ǵڰ� 0����� �湮����
// ���� ��ȣ�� index�� ���
// �� ���� 2�� 17��
bool visited[1 << 17] = { false, };
int max_nsheep = 1;

void dfs(State s)
{
    // �̹� �湮�� ���³��� 
    if (visited[s.state_no]) return;
    // ���� ���³�� �湮 üũ
    visited[s.state_no] = true;

    // ���ο� ���� Ž�� : �湮�߾��� ����� ����� ���� �湮
    for (int i = 0; i < N; i++) {

        // �湮 ��忡 �ִ� ���鿡�� ���� Ž��
        // i��° ��尡 �湮 ��忡 ���� ���� pass
        if ((s.state_no & (1 << i)) == 0) continue;

        // ���� �ڽ��� ������ ���� ��� �湮 ���� �����ؼ� dfs�θ���
        int left_node = nodes[i].left;
        if (left_node != -1) {
            int new_state_no = s.state_no | (1 << left_node);   // i��° bit �ѱ�            
            int new_nsheep = s.nsheep + (nodes[left_node].val ^ 1); // ���� 0�̱⿡..1�� ������
            int new_nwolf = s.nwolf + nodes[left_node].val;

            // �̹� �湮�� ���³�� �ƴϰ�, ���Ǽ��� ��������� ���� ��츸 dfs
            if (!visited[new_state_no] && (new_nwolf < new_nsheep)) {
                // ���ο� ���� ���� max���� ũ�� max����
                if (new_nsheep > max_nsheep) max_nsheep = new_nsheep;
                // Ž��
                dfs({ new_state_no, new_nsheep, new_nwolf });
            }
        }

        int right_node = nodes[i].right;
        if (right_node != -1) {
            int new_state_no = s.state_no | (1 << right_node);   // i��° bit �ѱ�
            int new_nsheep = s.nsheep + (nodes[right_node].val ^ 1); // ���� 0�̱⿡..1�� ������
            int new_nwolf = s.nwolf + nodes[right_node].val;

            // �̹� �湮�� ���³�� �ƴϰ�, ���Ǽ��� ��������� ���� ��츸 dfs
            if (!visited[new_state_no] && (new_nwolf < new_nsheep)) {
                // ���ο� ���� ���� max���� ũ�� max����
                if (new_nsheep > max_nsheep) max_nsheep = new_nsheep;
                dfs({ new_state_no, new_nsheep, new_nwolf });
            }
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;

    // �� ��� ����
    N = info.size();

    // ������ ����� �� �� ����
    for (int i = 0; i < N; i++) {
        nodes[i].val = info[i];
    }

    // ������ ���� ����, ������ -1
    for (int i = 0; i < N - 1; i++) {
        int p = edges[i][0];
        int c = edges[i][1];
        if (nodes[p].left == -1) {
            nodes[p].left = c;
        }
        else {
            nodes[p].right = c;
        }
    }

    // state : 1, nsheep : 1, nwolf : 0
    State s({ 1, 1, 0 });

    dfs(s);
    answer = max_nsheep;

    return answer;
}