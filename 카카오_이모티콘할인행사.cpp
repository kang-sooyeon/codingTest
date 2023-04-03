#include <string>
#include <vector>

using namespace std;

int max = 0;
int N = 0;
int discount_percent[4] = { 10, 20, 30, 40 };
vector<vector<int>> users_;
vector<int> emoticons_;
vector<int> emoticons_discount;
int answer_subscriber = 0, answer_price = 0;
void dfs(int emo_index) {

    if (emo_index == N) {

        int subscriber = 0;
        int total_price = 0;
        for (int i = 0; i < users_.size(); i++) {

            int price = 0;
            // 모든 이모티콘 돌면서
            for (int j = 0; j < N; j++) {

                // 할인율이 더 크면 구매
                if (users_[i][0] <= emoticons_discount[j]) {
                    price += emoticons_[j] * (100 - emoticons_discount[j]) * 0.01;
                }
            }
            if (price >= users_[i][1])
                subscriber++;
            else
                total_price += price;

            // 최대 subscriber, total_price 갱신
            if (answer_subscriber < subscriber) {
                answer_subscriber = subscriber;
                answer_price = total_price;
            }
            else if (answer_subscriber == subscriber) {
                if (answer_price < total_price) {
                    answer_price = total_price;
                }
            }
        }

        return;
    }

    for (int i = 0; i < 4; i++) {
        // discount update
        emoticons_discount[emo_index] = discount_percent[i];
        dfs(emo_index + 1);
    }

}


vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer;

    N = emoticons.size();

    users_ = users;
    emoticons_ = emoticons;
    emoticons_discount = emoticons;

    dfs(0);

    answer.push_back(answer_subscriber);
    answer.push_back(answer_price);

    return answer;
}