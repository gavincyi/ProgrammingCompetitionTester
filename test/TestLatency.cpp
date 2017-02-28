#include <cmath>
#include "TestMachine.hpp"
#include <bits/stdc++.h>

using namespace std;

// Find the minimum time of merging sorted lists, where A[i]
// is the number of elements at file i

class TestLatency : public TestMachine<long, long> {
    public:
        TestLatency() :
            TestMachine("TestLatency", 1, 10, 1, 1000)
        {}    
        
    protected:
        virtual bool IsEqual(long& v1, long& v2) const {
            return v1 <= v2;
        }
};

long SlowRunningSolution(vector<long> A) {
    if (A.size() < 2) {
        return 0;
    }
    
    auto sum = A[0];
    auto N = A.size();
    
    for (size_t i = 1; i < N; i++) {
        sum += sum + A[i];
    }
    
    return sum;
};

long FastRunningSolution(vector<long> A) {
    // Algorithm:
    // 1. Sort the arrary
    // 2. Add from the least element to the most element list
    auto N = A.size();
    
    if (N < 2) {
        return 0;
    }
    else {
        sort(A.begin(), A.end());
        auto total_time = A[0] * (N-1);
        for (size_t i = 1; i < N; i++) {
            total_time += A[i] * (N-i);
        }
        
        return total_time;
    }
};


int main() {
    TestLatency test;
    // test.InsertTestCase({100, 250, 1000}, 3);
    test.InsertAlgorithm(FastRunningSolution);
    test.InsertAlgorithm(SlowRunningSolution);
    test.Run(1000);
    return 0;
}