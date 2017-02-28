#include <cmath>
#include "TestMachine.hpp"
#include <bits/stdc++.h>

using namespace std;

// Given an array A, where A[i] indicates the index of power 2.
// Calculate the number of bits of the sum of A.

class TestBinarian : public TestMachine<int, int> {
    public:
        TestBinarian() :
            TestMachine("TestBinarian", 1, 1000, 0, 10)
        {}    
};

int SlowRunningSolution(vector<int> A) {
    int sum = 0;
    int count = 0;
    
    for (auto i : A) {
        sum += pow(2, i);
    }
    
    while (sum) {
        if (sum & 1) {
            count++;
        }
        
        sum = sum >> 1;
    }
    
    return count;
};

int FastRunningSolution(vector<int> A) {
    // Algorithm
    // 1.   Index the array A to a map (countA), where key is A[i] and
    //      value is number of A[i]
    // 2.   For each key, value in countA, do the following while loop
    //      if value > 0, and initialize "shift" as 0 and countA[key] = 0
    //      i. if value & 1, countA[key+shift] += 1
    //      ii. value = value >> 1
    //      iii. shift++
    // 3.   Remove all zero-valued key and return the number of pairs
    //
    // Example:
    // 1. Array A is mapped to countA { 0:3, 1:1, 2:2 }
    // 2. a. In the first step, countA is updated as { 0:1, 1:2, 2:2 }
    //    b. Then, updated as { 0:1, 1:0, 2:3 }
    //    c. Then, updated as { 0:1, 1:0, 2:1, 3:1 }
    // 3. Remove zero-valued and return 3
    
    auto countA = map<int, int>();
    auto binarian = 0;
    
    // Prepare countA
    for (auto k : A) {
        auto ret = countA.emplace(k, 1);
        if (!ret.second) {
            ret.first->second += 1;
        }
    }
    
    // Loop over countA
    for (auto p : countA) {
        // cout << p.first << ": " << p.second << endl;
        auto key = p.first;
        auto value = p.second;
        auto shift = 0;
        
        countA[key] = 0; // Reset count
        
        while (value) {
            if (value & 1) {
                countA[key + shift] += 1;
            }
            
            value >>= 1;
            shift++;
        }
        
        if (countA[key] != 0) {
            binarian++;
        }
    }
    
    return binarian;
};


int main() {
    TestBinarian test;
    test.InsertTestCase({1,0,2,0,0,2}, 3);
    test.InsertAlgorithm(SlowRunningSolution);
    test.InsertAlgorithm(FastRunningSolution);
    test.Run(1000);
    return 0;
}