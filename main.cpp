/*
Weighted activity selection problem:
implement an algorithm using dynamic programming
*/
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;                    // for timing algorithm

struct activity {                               // define activity
    int start_time;
    int finish_time;
    int weight;
};

// function for sorting activities by finish time
bool comparator(activity a1, activity a2) {
    return a1.finish_time < a2.finish_time;
}


// binary search through vector S
// to find latest job that does not conflict
int lastNonConflict(vector<activity> S, int lo, int hi, int target) {
    int mid;
    while(lo < hi) {
        mid = lo + (hi - lo + 1) / 2;           // integer division takes floor of solution
        if(S.at(mid).finish_time <= target)
            lo = mid;
        else 
            hi = mid - 1;
    }
    if(S.at(lo).finish_time > target)           // there is no non-conflicting activity
        return -1;
    return lo;
}

int weightedActivitySelection(vector<activity> S) {
    if(S.size() == 0) {
        cerr << "Zero activities available." << endl;
        exit(1);
    }
    int size = static_cast<int>(S.size());
    sort(S.begin(), S.end(), comparator);       // first sort by finish time
    
    int *table = new int[size];             // array for storing solutions of subproblems
    table[0] = S.at(0).weight;

    for(int i=1; i < size; i++) {
        int weight = S.at(i).weight;
        
        int l = lastNonConflict(S, 0, i, S.at(i).start_time);
        if(l != -1)
            weight += table[l];

        table[i] = max(weight, table[i-1]);
    }

    int result = table[size-1];
    return result;
}

int main() {
    auto start = high_resolution_clock::now();  // start timer

    vector<activity> S;                         // generate activities somehow

    weightedActivitySelection(S);

    auto end = high_resolution_clock::now();    // end timer
    double duration = duration_cast<nanoseconds>(end - start).count();
    duration *= 1e-9;
    cout << "running time: " << fixed << duration << setprecision(9) << endl;
    return 0;
}
