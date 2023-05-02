
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <iostream>

using namespace std;

void printSubsets(char arr[], int n) {
    for (int i = 0; i < (1 << n); ++i) {
        cout << "{ ";
        for (int j = 0; j < n; ++j)
            if (i & (1 << j))
                cout << arr[j] << ",";
        cout << " }" << endl;
    }
}

int main() {
    char data[] = { 'A', 'B', 'C', 'D' };
    printSubsets(data, 4);
}


//https://ansohxxn.github.io/algorithm/bitset/