#include <common.h>

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>
#include <chrono>

using namespace std;

struct MySolver : public Context {

    int GetCost(int file, std::vector<int>& required) {
        int result = 0;
        std::queue<int> elements;
        elements.push(file);
        while (!elements.empty()) {
            int file = elements.front();
            required.push_back(file);
            elements.pop();
            result += CT[file];
            for (int dep : Deps[file]) {
                elements.push(dep);
            }
        }
        std::reverse(required.begin(), required.end());
        return result;
    }

    void Solve() {
        std::vector<std::pair<int, std::vector<int>>> results;
        for (int i = 0; i < T; ++i) {
            int target = Target[i];
            std::vector<int> targetElements;
            int time = GetCost(target, targetElements);
            int deadline = Deadline[i];
            int points = Points[i];
            if (time <= deadline) {
                int reward = points + deadline - time;
                results.push_back(std::make_pair(reward, targetElements));
            }
        }
        std::sort(results.rbegin(), results.rend());
        for (int i = 0; i < results.size(); ++i) {
            int serverNumber = i % S;
            for (int task : results[i].second) {
                Solution.push_back(std::make_pair(serverNumber, task));
            }
        }
    }
};

int main() {
    MySolver solver;

    solver.Input();

    auto start = std::chrono::system_clock::now();
    cerr << "Started solving..." << endl;
    solver.Solve();
    cerr << "Done!" << endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cerr << "Test time: " << elapsed_seconds.count() << endl;

    cerr << "Outputting" << endl;
    solver.Output();

    cerr << solver.GetScore() << endl;
    return 0;
}
