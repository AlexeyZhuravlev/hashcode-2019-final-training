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
    using TSolution = int;
    TSolution solution;

    vector<string> _deps[MAX_N];

    size_t C, T, S;
    vector<int> Deps[MAX_N];
    unordered_map<string, int> NameToID;
    string Name[MAX_N];
    int CT[MAX_N], RT[MAX_N];

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
    }

    void Output() {
    
    }

    void Verify() {
        
    }

    int GetScore() {
        return 0;
    }

    void Better(const int iterations = 1000, const int generation = 100) {

    }

};
