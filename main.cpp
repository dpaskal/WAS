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

int weightedActivitySelection(vector<activity> S){
	int sum = 0;
	sort(S.begin(), S.end(), comparator); //Sort the array by finish time
	activity lastChosen = S[0];
	sum += lastChosen.weight;
	for(auto i = S.begin()+1; i < S.end(); i++){
		if(i->start_time >= lastChosen.finish_time){
			sum += i->weight;
			lastChosen = *i;
		}
	}
	return sum;
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
	for(int i = 1; i < 7; i++){

	    for(int j = 0; j < pow(10, i); j++){
	    	int start_time = std::rand() % 100 + 1;
	    	int end_time = std::rand() % 100 + 1;
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
