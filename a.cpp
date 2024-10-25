#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cmath>
#include <vector>
#include <string>

using json = nlohmann::json;
using namespace std;

// Function to decode a value from a given base to base 10
long long decodeValue(const std::string& value, int base) {
    return std::stoll(value, nullptr, base);
}

// Function to parse roots from JSON
void parseRoots(const json& jsonData, vector<pair<int, long long>>& roots) {
    for (const auto& item : jsonData.items()) {
        if (item.key() == "keys") continue;
        int x = stoi(item.key());
        int base = item.value()["base"];
        string value = item.value()["value"];
        long long y = decodeValue(value, base);
        roots.emplace_back(x, y);
    }
}

// Function to calculate Lagrange Interpolation at x=0 (gives constant term)
long long lagrangeInterpolation(const vector<pair<int, long long>>& roots) {
    int k = roots.size();
    long long constantTerm = 0;

    for (int i = 0; i < k; i++) {
        long long term = roots[i].second;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= -roots[j].first;
                term /= (roots[i].first - roots[j].first);
            }
        }
        constantTerm += term;
    }
    return constantTerm;
}

int main() {
    // Read JSON file
    std::ifstream file("input.json");
    json jsonData;
    file >> jsonData;

    // Parse keys for each test case
    vector<pair<int, long long>> roots;
    parseRoots(jsonData, roots);

    // Compute constant term using Lagrange interpolation
    long long constantTerm = lagrangeInterpolation(roots);

    // Print the constant term
    cout << "Constant term (secret): " << constantTerm << endl;

    return 0;
}