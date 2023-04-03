#include <string>
#include <vector>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;

    int d_cur = deliveries.size() - 1;
    int p_cur = pickups.size() - 1;

    while (1) {

        // 1. 배달/수거 남아있는 맨 끝 집 알아내기
        while (d_cur >= 0) {
            if (deliveries[d_cur] != 0)
                break;
            d_cur--;
        }

        while (p_cur >= 0) {
            if (pickups[p_cur] != 0)
                break;
            p_cur--;
        }

        if (d_cur == -1 && p_cur == -1)
            break;

        int cur = max(d_cur, p_cur);
        answer += (cur + 1) * 2;

        // 배달 차감
        int c = cap;
        while (d_cur >= 0 && c > 0) {
            deliveries[d_cur]--;
            if (deliveries[d_cur] < 0) {
                deliveries[d_cur]++;
                d_cur--;
                continue;
            }
            c--;
        }

        // 수거 차감
        c = cap;
        while (p_cur >= 0 && c > 0) {
            pickups[p_cur]--;
            if (pickups[p_cur] < 0) {
                pickups[p_cur]++;
                p_cur--;
                continue;
            }
            c--;
        }
    }

    return answer;
}