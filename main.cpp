/*
Weighted activity selection problem:
implement an algorithm using dynamic programming
*/
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;                    // for timing algorithm

struct activity {                               // create activities
    int start_time;
    int finish_time;
    int weight;
};
activity act1{1, 2, 3};
activity act2{1, 2, 3};
activity act3{1, 2, 3};
activity act4{1, 2, 3};



int weightedActivitySelection(vector<activity> S) {
    return 0;
}

int main() {
    auto start = high_resolution_clock::now();  // start timer

    vector<activity> S{act1, act2, act3, act4};

    weightedActivitySelection(S);

    auto end = high_resolution_clock::now();    // end timer
    double duration = duration_cast<nanoseconds>(end - start).count();
    duration *= 1e-9;
    cout << "running time: " << fixed << duration << setprecision(9) << endl;
    return 0;
}