#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

constexpr int maxNumberSize = 200;

int main() {
    ios_base::sync_with_stdio(false);

    uint32_t lastN = 0;
    uint32_t n;
    vector<string> numbers{};

    while (cin >> n && n > 0) {
        if (n > lastN)
            numbers.reserve(n);

        for (uint32_t i = 0; i < n; ++i) {
            string number;
            number.reserve(maxNumberSize);

            while (number.empty())
                getline(cin, number);

            numbers.emplace_back(std::move(number));
        }

        sort(numbers.begin(), numbers.end());

        uint32_t economy = 0;
        for (uint32_t i = 1; i < n; ++i) {
            for (uint32_t j = 0; j < maxNumberSize; ++j) {
                if (numbers[i][j] == numbers[i - 1][j]) {
                    ++economy;
                } else {
                    break;
                }
            }
        }

        cout << economy << '\n';
        lastN = n;
        numbers.clear();
    }

    return 0;
}
