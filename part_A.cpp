#include <iostream>
#include <random>

using namespace std;

// Function to simulate rolling two dice
pair<int, int> rollDice() {
    random_device rd; // Use random_device for better randomness
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 6); // Inclusive range for 1-6

    int dieA = dist(gen);
    int dieB = dist(gen);
    return {dieA, dieB};
}

// Function to calculate possible combinations
int calculateCombinations() {
    return 6 * 6; // 6 possible outcomes for each die
}

// Function to calculate distribution of sums
void calculateSumDistribution(int* distributionArr) {
    for (int i = 0; i < 11; ++i) { // Iterate through possible sums (2-12)
        distributionArr[i] = 0; // Initialize count for each sum
    }

    for (int i = 0; i < 10000; ++i) { // Perform multiple dice rolls for accuracy
        pair<int, int> diceVals = rollDice();
        int sum = diceVals.first + diceVals.second;
        distributionArr[sum - 2]++; // Adjust index for 2-12 range
    }
}

// Function to calculate probability of each sum
void calculateSumProbabilities(int* distributionArr) {
    int totalCombinations = calculateCombinations();

    for (int i = 0; i < 11; ++i) { // Iterate through possible sums (2-12)
        double probability = static_cast<double>(distributionArr[i]) / totalCombinations;
        cout << "P(Sum = " << i + 2 << ") = " << probability << endl;
    }
}

int main() {
    int distributionArr[11]; // Array to store sum distribution

    // Calculate and display combinations
    int combinations = calculateCombinations();
    cout << "Total possible combinations: " << combinations << endl;

    // Calculate and display sum distribution
    calculateSumDistribution(distributionArr);
    cout << "Distribution of sums:" << endl;
    for (int i = 0; i < 11; ++i) {
        cout << "Sum " << i + 2 << ": " << distributionArr[i] << endl;
    }

    // Calculate and display probabilities
    calculateSumProbabilities(distributionArr);

    return 0;
}
