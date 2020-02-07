#pragma once

#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>
#include <unordered_map>

using namespace std;

const int MAX_N = 100005;

struct Context {
    using TSolution = vector<pair<string, int>>;
    TSolution Solution;

    vector<string> _deps[MAX_N];

    size_t C, T, S;
    vector<int> Deps[MAX_N];
    unordered_map<string, int> NameToID;
    string Name[MAX_N];
    int CT[MAX_N];
    int RT[MAX_N];

    string TargetName[MAX_N];
    int Target[MAX_N];
    int Deadline[MAX_N];
    int Points[MAX_N];

    void Input() {
        cin >> C >> T >> S;
        for (size_t i = 0; i < C; ++i) {
            cin >> Name[i] >> CT[i] >> RT[i];
            NameToID[Name[i]] = i;

            size_t n_deps;
            cin >> n_deps;
            for (size_t i = 0; i < n_deps; ++i) {
                string dep_name;
                cin >> dep_name;
                _deps[i].emplace_back(std::move(dep_name));
            }
        }
        for (size_t i = 0; i < C; ++i) {
            for (auto j : _deps[i]) {
                Deps[i].push_back(NameToID[j]);
            }
        }

        for (size_t i = 0; i < T; ++i) {
            cin >> TargetName[i] >> Deadline[i] >> Points[i];
            Target[i] = NameToID[TargetName[i]];
        }
    }

    void Output() {
        cout << Solution.size() << endl;
        for (auto& p : Solution) {
            cout << p.first << " " << p.second << endl;
        }
    }

    void Verify() {
        assert(Solution.size() <= C * S && "Too many steps.");

        for (auto& p : Solution) {

        }
    }

    int GetScore() {
        return 0;
    }

    void Better(const int iterations = 1000, const int generation = 100) {

    }

};
