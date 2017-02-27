#include <cmath>
#include "TestMachine.hpp"
#include <bits/stdc++.h>

using namespace std;

// Given an array A, where A[i] indicates the power of 2. The array is
// an non-decreasing array and forms a sum of a binaries (K). The algorithm 
// is to calculate the number of bits of 3 * K.
// Example:
// A[0] = 1
// A[1] = 4
// A[2] = 5
// K = 110010
// 3 * K = 10010110
// The answer is 4 (4 bits set to 1).

class TestCountBits : public TestMachine<int, int> {
    public:
        TestCountBits() :
            TestMachine(1, 14, 0, 14)
        {}    
        
    protected:
        
        virtual vector<int> GenerateRandomArray(long N=0) const override;
};

vector<int> TestCountBits::GenerateRandomArray(long N) const {
    auto ret = TestMachine<int, int>::GenerateRandomArray(N);
    sort( ret.begin(), ret.end() );
    ret.erase( unique( ret.begin(), ret.end() ), ret.end() );    
    return ret;
}

int SlowRunningSolution(vector<int> A) {
    
    int sum = 0;
    int count = 0;
    
    for (auto i : A) {
        sum += pow(2, i);
    }
    
    sum *= 3;
    
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
    auto count = 1;                 // First A[0]
    auto last_bit = A[0] + 1;       // The last bit is A[0] + 1
    auto N = A.size();
    
    for (size_t i = 1; i < N; i++) {
        if (A[i] == last_bit) {
            // If the previous last bit is same as A[i], it will then increment
            // to A[i] + 1 and finally to A[i] + 2. No bits is set at this stage.          
            last_bit = A[i] + 2;
        }
        else if (A[i] + 1 == last_bit) {
            // If the previous last bit is same as A[i] + 1, it will then
            // increment to A[i] + 2 as well. The A[i] bit is set.
            last_bit = A[i] + 2;
            count++;
        }
        else if (A[i] > last_bit) {
            // If the previous bit is less than A[i], the previous bit and A[i]
            // bit is set.
            last_bit = A[i] + 1;
            count += 2;
        }
    }
    
    count++;
    
    return count;
};


int main() {
    TestCountBits test;
    test.InsertTestCase({1,4,5}, 4);
    test.InsertAlgorithm(SlowRunningSolution);
    test.InsertAlgorithm(FastRunningSolution);
    test.Run(1000);
    return 0;
}