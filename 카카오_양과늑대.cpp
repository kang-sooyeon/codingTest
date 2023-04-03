#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

#define MAX_N 17


struct State {
    int state_no = 1;   // **** 방문한 노드들의 집합을 bitmasking으로 보유
    int nsheep = 1;
    int nwolf = 0;
};

/////// 트리 정보 저장
// 왼쪽 자식 존재하는지(간선)
struct Node {
    int val = -1; // 양:0, 늑대:1
    int left = -1;
    int right = -1;
};

Node nodes[MAX_N];

// 노드 개수
int N;

// 상태x를 방문했는가(bit-masking), 맨뒤가 0번노드 방문여부
// 상태 번호를 index로 사용
// 총 상태 2의 17승
bool visited[1 << 17] = { false, };
int max_nsheep = 1;

void dfs(State s)
{
    // 이미 방문한 상태노드면 
    if (visited[s.state_no]) return;
    // 현재 상태노드 방문 체크
    visited[s.state_no] = true;

    // 새로운 상태 탐색 : 방문했었던 노드들과 연결된 노드들 방문
    for (int i = 0; i < N; i++) {

        // 방문 노드에 있는 노드들에서 부터 탐색
        // i번째 노드가 방문 노드에 없는 노드면 pass
        if ((s.state_no & (1 << i)) == 0) continue;

        // 왼쪽 자식이 있으면 왼쪽 노드 방문 상태 세팅해서 dfs부르기
        int left_node = nodes[i].left;
        if (left_node != -1) {
            int new_state_no = s.state_no | (1 << left_node);   // i번째 bit 켜기            
            int new_nsheep = s.nsheep + (nodes[left_node].val ^ 1); // 양은 0이기에..1로 뒤집음
            int new_nwolf = s.nwolf + nodes[left_node].val;

            // 이미 방문한 상태노드 아니고, 양의수가 늑대수보다 적은 경우만 dfs
            if (!visited[new_state_no] && (new_nwolf < new_nsheep)) {
                // 새로운 양의 수가 max보다 크면 max갱신
                if (new_nsheep > max_nsheep) max_nsheep = new_nsheep;
                // 탐색
                dfs({ new_state_no, new_nsheep, new_nwolf });
            }
        }

        int right_node = nodes[i].right;
        if (right_node != -1) {
            int new_state_no = s.state_no | (1 << right_node);   // i번째 bit 켜기
            int new_nsheep = s.nsheep + (nodes[right_node].val ^ 1); // 양은 0이기에..1로 뒤집음
            int new_nwolf = s.nwolf + nodes[right_node].val;

            // 이미 방문한 상태노드 아니고, 양의수가 늑대수보다 적은 경우만 dfs
            if (!visited[new_state_no] && (new_nwolf < new_nsheep)) {
                // 새로운 양의 수가 max보다 크면 max갱신
                if (new_nsheep > max_nsheep) max_nsheep = new_nsheep;
                dfs({ new_state_no, new_nsheep, new_nwolf });
            }
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;

    // 총 노드 개수
    N = info.size();

    // 노드들의 늑대와 양 수 세팅
    for (int i = 0; i < N; i++) {
        nodes[i].val = info[i];
    }

    // 노드들의 간선 세팅, 없으면 -1
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