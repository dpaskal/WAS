/*
Weighted activity selection problem:
implement an algorithm using dynamic programming
*/
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include<cmath>
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

// linear search through vector S
// to find latest job that does not conflict 
int slowLastNonConflict(vector<activity> S, int i) {
    for(int j = i-1; j >= 0; j--) {
        if(S.at(j).finish_time <= S.at(i).finish_time) {
            return j;
        }
    }
    return -1; // there is no non-conflicting activity
}

int weightedActivitySelection(vector<activity> S) {
    int size = static_cast<int>(S.size());
    if(size == 0) {
        cerr << "Zero activities available." << endl;
        exit(1);
    }
    sort(S.begin(), S.end(), comparator);       // first sort by finish time
    
    int *table = new int[size];                  // array for storing solutions of subproblems
    table[0] = S.at(0).weight;

    for(int i=1; i < size; i++) {
        int currentWeight = S.at(i).weight;
        // int l = slowLastNonConflict(S, i);
        int l = lastNonConflict(S, 0, i, S.at(i).start_time);
        if(l != -1)
            currentWeight += table[l];

        table[i] = max(currentWeight, table[i-1]);     // dynamic programming part
    }

    int result = table[size-1];
    return result;
}

int main() {
    auto start = high_resolution_clock::now();  // start timer

    vector<activity> S;                         // generate activities somehow
    S.push_back(activity{0, 5, 10});
    S.push_back(activity{2, 6, 20});
    S.push_back(activity{5, 9, 11});

    int maxWeight = weightedActivitySelection(S);
    cout << "Maximum weight possible is " << maxWeight << endl;

    auto end = high_resolution_clock::now();    // end timer
    double duration = duration_cast<nanoseconds>(end - start).count();
    duration *= 1e-9;
    cout << "running time: " << fixed << duration << setprecision(9) << endl;

    S.clear();

    //Random dataset of increasing size
    std::srand(std::time(nullptr));

	for(int i = 1; i < 5; i++){

	    for(int j = 0; j < pow(10, i); j++){
	    	int start_time = std::rand() % 100 + 1;
	    	int end_time = std::rand() % 100 + start_time;
	    	int weight = std::rand() % 100 + 1;
	    	S.push_back(activity{start_time, end_time, weight});

	   	    
	   	 }
	   	start = high_resolution_clock::now();
	   	weightedActivitySelection(S);
	   	end = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(end - start).count();
    	duration *= 1e-9;
    	cout << "input size " << (pow(10, i)) << " running time: " << fixed << duration << setprecision(9) << endl;

	    S.clear();
	}


    return 0;
}
