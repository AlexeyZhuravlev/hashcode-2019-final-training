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
    priority_queue<pair<int, int>> Events;
    set<int> Dependants[MAX_N], GlobalDependants[MAX_N];

    int Everywhere[MAX_N];
    int OnServer[MAX_S][MAX_N];

    double CalculateScore(int task, int time, int minStartTime, int server) {
        int targetsScore = 0;
        for (int i = 0; i < T; ++i) {
            int tid = Target[i];
            if (minStartTime + CT[task] + (task == tid ? 0 : CT[tid]) <= Deadline[i]) {

                if (GlobalDependants[task].count(tid) || task == tid) {
                    targetsScore += Points[i];
                }

            }
        }
        if (!targetsScore) {
            return -1e9;
        } else {
            return targetsScore + (time - minStartTime);
        }
    }

    void Solve() {
        for (int i = C - 1; i >= 0; --i) {
            for (auto dep : Deps[i]) {
                Dependants[dep].emplace(i);
                GlobalDependants[dep].emplace(i);
                GlobalDependants[dep].insert(GlobalDependants[i].begin(), GlobalDependants[i].end());
            }
        }


        for (int i = 0; i < S; ++i) {
            Events.emplace(0, i);
        }
        memset(Everywhere, 0, sizeof(Everywhere));
        memset(OnServer, 0, sizeof(OnServer));

        int maxDeadline = 0;
        for (int i = 0; i < C; ++i) {
            maxDeadline = max(maxDeadline, Deadline[i]);
        }

        while (!Events.empty()) {
            auto e = Events.top();
            int time = -e.first;
            int server = e.second;
            Events.pop();
//            cerr << time << " " << server << " ";
            if (time > maxDeadline) {
                break;
            }

            int chosenTask = -1;
            int startTime = time;
            double maxScore = -1e9;
            for (int i = 0; i < C; ++i) {
                if (OnServer[server][i] != 0 || Everywhere[i]) {
                    continue;
                }
                bool hasAllDep = true;
                int minStartTime = time;
                for (auto dep : Deps[i]) {
                    auto tDep = OnServer[server][dep] ? OnServer[server][dep] : Everywhere[dep];
                    if (!tDep) {
                        hasAllDep = false;
                        break;
                    }
                    minStartTime = max(minStartTime, tDep);
                }
                if (!hasAllDep || (Everywhere[i] && Everywhere[i] <= minStartTime + CT[i])) {
                    continue;
                }

                double s = CalculateScore(i, time, minStartTime, server);
                if (s > maxScore) {
                    maxScore = s;
                    chosenTask = i;
                    startTime = minStartTime;
                }
            }
//            cerr << chosenTask << " " << maxScore << endl;
            if (chosenTask != -1) {
                Solution.emplace_back(chosenTask, server);

                Events.emplace(-(startTime + CT[chosenTask]), server);
                if (!Everywhere[chosenTask]) {
                    Everywhere[chosenTask] = startTime + CT[chosenTask] + RT[chosenTask];
                } else {
                    Everywhere[chosenTask] = min(Everywhere[chosenTask], startTime + CT[chosenTask] + RT[chosenTask]);
                }

                OnServer[server][chosenTask] = startTime + CT[chosenTask];
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
