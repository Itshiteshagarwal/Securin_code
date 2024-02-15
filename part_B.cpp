#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

pair<vector<int>, vector<int>> undoom_dice(const vector<int>& die_a, const vector<int>& die_b) {
    vector<int> new_die_a(die_a.size(), 0), new_die_b(die_b.size(), 0);
    unordered_map<int, int> die_a_counts, die_b_counts;

    // Count occurrences of each sum in the original dice
    for (int i = 0; i < die_a.size(); ++i) {
        for (int j = 0; j < die_b.size(); ++j) {
            int sum = die_a[i] + die_b[j];
            die_a_counts[sum]++;
            die_b_counts[sum]++;
        }
    }

    // Randomly distribute dots on Die A within constraints
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 4);
    for (int i = 0; i < die_a.size(); ++i) {
        int remaining_dots = 4;
        for (int sum = die_a[i] + 1; sum <= 6; ++sum) {
            int count_needed_on_b = die_b_counts[sum] - die_a_counts[sum];
            if (count_needed_on_b > 0) {
                int dots_to_add = min(remaining_dots, count_needed_on_b);
                remaining_dots -= dots_to_add;
                new_die_b[die_b.size() - 1] += dots_to_add; // Distribute remaining dots on the last face of Die B
            }
        }
        new_die_a[i] = dist(gen);
        remaining_dots -= new_die_a[i];
        if (remaining_dots > 0) {
            new_die_b[die_b.size() - 1] += remaining_dots; // Distribute remaining dots on the last face of Die B
        }
    }

    // Ensure both dice follow sum probability constraints
    for (int sum = 2; sum <= 6; ++sum) {
        int count_needed_on_b = die_b_counts[sum] - die_a_counts[sum];
        new_die_b[die_b.size() - 1] += count_needed_on_b;
    }

    return {new_die_a, new_die_b};
}

int main() {
    vector<int> die_a = {1, 2, 3, 4, 5, 6}, die_b = {1, 2, 3, 4, 5, 6};
    pair<vector<int>, vector<int>> new_dice = undoom_dice(die_a, die_b);

    cout << "New Die A: ";
    for (int dot : new_dice.first) {
        cout << dot << " ";
    }
    cout << endl;

    cout << "New Die B: ";
    for (int dot : new_dice.second) {
        cout << dot << " ";
    }
    cout << endl;

    return 0;
}
