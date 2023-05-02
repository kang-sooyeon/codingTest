#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
map<string, int> my_map;


void dfs(int index, int count, string& order, int& n, string& pick)
{
    if (count == n) {
        // cout << pick << endl;
        my_map[pick]++;
    }

    for (int i = index; i < order.size(); i++) {
        pick[count] = order[i];
        dfs(i + 1, count + 1, order, n, pick);
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;


    for (int i = 0; i < course.size(); i++) {
        int n = course[i];
        string pick = "";
        pick.assign(n, '.');

        for (int j = 0; j < orders.size(); j++) {
            string order = orders[j];
            sort(order.begin(), order.end());   // 메뉴가 정렬안되어 들어옴.

            // order string에서 n개 뽑기
            dfs(0, 0, order, n, pick);
        }
    }


    map<int, int> my_max;
    for (auto iter = my_map.begin(); iter != my_map.end(); iter++) {
        if (my_max[iter->first.size()] < iter->second) {
            my_max[iter->first.size()] = iter->second;
        }
    }

    for (auto iter = my_map.begin(); iter != my_map.end(); iter++) {

        if (my_max[iter->first.size()] <= 1)
            continue;

        if (my_max[iter->first.size()] == iter->second) {
            answer.push_back(iter->first);
        }
    }

    sort(answer.begin(), answer.end());

    return answer;
}