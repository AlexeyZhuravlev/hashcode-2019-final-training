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
    std::vector<std::set<int>> serverToTasks;
    std::vector<int> timeOnServer;
    std::vector<char> usedTargets;

    int GetCost(int file, std::vector<int>& required, int server) {
        int result = timeOnServer[server];
        std::queue<int> elements;
        elements.push(file);
        while (!elements.empty()) {
            int file = elements.front();
            elements.pop();
            if (serverToTasks[server].count(file) == 0) {
                result += CT[file];
                required.push_back(file);
            }
            for (int dep : Deps[file]) {
                elements.push(dep);
            }
        }
        std::reverse(required.begin(), required.end());
        return result;
    }

    void Solve() {
        serverToTasks.resize(S);
        timeOnServer.assign(S, 0);
        usedTargets.assign(T, 0);
        
        while (true) {
            int server = 0;
            for (int i = 0; i < S; ++i) {
                if (timeOnServer[i] < timeOnServer[server]) {
                    server = i;
                }
            }
            int bestReward = -10000000;
            int correspondingTime = 0;
            int bestTarget = 0;
            std::vector<int> bestElements;
            
            for (int i = 0; i < T; ++i) {
                int target = Target[i];
                if (usedTargets[i]) {
                    continue;
                }
                std::vector<int> targetElements;
                int time = GetCost(target, targetElements, server);
                int deadline = Deadline[i];
                int points = Points[i];
                int reward = points + deadline - time;
                if (reward > bestReward) {
                    bestReward = reward;
                    bestElements = targetElements;
                    correspondingTime = time;
                    bestTarget = i;
                }
            }
            //std::cerr << bestReward << std::endl;
            //std::cerr << bestElements.size() << std::endl;
            if (bestElements.empty()) {
                break;
            }
            for (int task: bestElements) {
                if (serverToTasks[server].count(task) == 0) {
                    serverToTasks[server].insert(task);
                    Solution.push_back(std::make_pair(task, server));
                }
                //std::cerr << task << " " << server << std::endl;
            }
            timeOnServer[server] = correspondingTime;
            usedTargets[bestTarget] = 1;
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
