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
        if(S.at(j).finish_time <= S.at(i).start_time) {
            return j;
        }
    }
    return -1; // there is no non-conflicting activity
}

int optimalChoiceBrute(vector<activity> * S, int pos){
	if(pos == -1){
		return 0;
	}
	int nextJobPos = -1;
	for(uint i = pos; i < S->size(); i--){
		if(S->at(pos).start_time >= S->at(i).finish_time){
			nextJobPos = i;
			break;
		}
	}
	return max(S->at(pos).weight + optimalChoiceBrute(S, nextJobPos), optimalChoiceBrute(S, pos-1)); 
}

int bruteForce(vector<activity> S){
    sort(S.begin(), S.end(), comparator);       // first sort by finish time
    int max = optimalChoiceBrute(&S, S.size()-1); //Start at the end of the possible jobs
    return max;
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
        int l = slowLastNonConflict(S, i);
        // int l = lastNonConflict(S, 0, i, S.at(i).start_time);
        if(l != -1){
            currentWeight += table[l];
        }

        table[i] = max(currentWeight, table[i-1]);     // dynamic programming part
    }

    int result = table[size-1];
    return result;
}

int main() {
    vector<activity> S;                         // generate activities somehow
    S.push_back(activity{0, 3, 3});
    S.push_back(activity{3, 4, 1});
    S.push_back(activity{0, 5, 2});
    S.push_back(activity{2, 4, 5});
    S.push_back(activity{4, 5, 3});
    S.push_back(activity{5, 7, 1});
    S.push_back(activity{8, 10, 7});
    S.push_back(activity{3, 9, 4});


    auto start = high_resolution_clock::now();  // start timer
	int maxWeight = weightedActivitySelection(S);
    auto end = high_resolution_clock::now();    // end timer

    cout << "Maximum weight possible is " << maxWeight << endl;

    double duration = duration_cast<nanoseconds>(end - start).count();
    duration *= 1e-9;
    cout << "running time: " << fixed << duration << setprecision(9) << endl;


    //Running Brute Force
    start = high_resolution_clock::now();  // start timer
	maxWeight = bruteForce(S);
    end = high_resolution_clock::now();    // end timer

	cout << "Brute Force: Maximum weight possible is " << maxWeight << endl;

    duration = duration_cast<nanoseconds>(end - start).count();
    duration *= 1e-9;
    cout << "running time: " << fixed << duration << setprecision(9) << endl;


    S.clear();

    //Random dataset of increasing size
    std::srand(std::time(nullptr));

	for(int i = 1; i < 300; i++){

	    for(int j = 0; j < i; j++){
	    	int start_time = (std::rand() % 100) + 1;
	    	int end_time = (std::rand() % 100 + 1) + start_time;
	    	assert(end_time > start_time);
	    	int weight = std::rand() % 100 + 1;
	    	S.push_back(activity{start_time, end_time, weight});

	   	    
	   	 }
	   	start = high_resolution_clock::now();
	   	weightedActivitySelection(S);
	   	end = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(end - start).count();
    	duration *= 1e-9;
    	//cout << "input size " << (i) << " running time: " << fixed << duration << setprecision(9) << endl;

	    S.clear();
	}


    return 0;
}
