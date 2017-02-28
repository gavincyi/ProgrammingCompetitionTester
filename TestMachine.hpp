#ifndef TESTMACHINE_HPP
#define TESTMACHINE_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <functional>
#include <iomanip>

using namespace std;
using RunningTimePairType = pair<long,long>;

/**
 * Test machine
 * 
 * An abstract class providing all programming competition testing utilities.
 * 
 * How to use:
 * 1. Inherit from the class and implement the following abstract methods:
 *      a. SlowRunningSolution
 *      b. FastRunningSolution
 *      c. Name
 **/
template<typename T, typename R>
class TestMachine {
    public:
    
        /**
         * Constructor
         * 
         * :param name              Name
         * :param minSize           Minimum size of the array
         * :param maxSize           Maximum size of the array
         * :param minRange          Minimum range of each element
         * :param maxRange          Maximum range of each element
         */
        TestMachine(string name, long minSize, long maxSize, T minRange, T maxRange) :
            _name(name),
            _minSize(minSize), 
            _maxSize(maxSize), 
            _minRange(minRange), 
            _maxRange(maxRange),
            _numAlgorithms(0)
        {
            srand ( time(NULL) );
        }
        
        /**
         * Insert algorithm
         * 
         * :param func              The function delegate of the algorithm
         */
        void InsertAlgorithm(function<R(vector<T>)> func)
        {
            _numAlgorithms++;
            _allAlgorithms.emplace_back(func);
            _allRunningTimes.emplace_back(vector<RunningTimePairType>());
        }
    
        /**
         * Insert test case
         * 
         * :param testArray         The test array
         * :param expectValue       The expected value of the test case
         */
        void InsertTestCase(vector<T> testArray, R expectValue)
        {
            _allTestCases.emplace_back(testArray, expectValue);
        }
        
        /**
         * Run
         * 
         * :param numTests          The number of tests
         */
        virtual void Run(int numTests=1000) {
            cout << "Start running " << _name << "..." << endl;
            vector<R> solutions(_numAlgorithms, 0);
            
            // Run the test cases first
            for (auto&& testCase : _allTestCases) {
                auto testArray = get<0>(testCase);
                auto expectValue = get<1>(testCase);
                
                for (auto index = 0; index < _numAlgorithms; index++) {
                    solutions[index] = _allAlgorithms[index](testArray);
                    if (!IsEqual(solutions[index], expectValue)) {
                        cout << "Incorrect solution: " << ToStr(testArray) << endl
                             << "Expect: " << expectValue << endl
                             << "Index " << index << ": " << solutions[index] << endl;
                        abort();
                    }
                }
            }
            
            // Run the generated array cases
            for (auto i = 0; i < numTests; i++) {
                auto randArray = GenerateRandomArray();
                auto randArraySize = randArray.size();
                
                for (auto index = 0; index < _numAlgorithms; index++) {
                    timespec runningStart, runningEnd;
                    clock_gettime(CLOCK_REALTIME, &runningStart);
                    solutions[index] = _allAlgorithms[index](randArray);
                    clock_gettime(CLOCK_REALTIME, &runningEnd);
                    if (index > 0 && !IsEqual(solutions[0], solutions[index])) {
                        cout << "Incorrect solution: " << ToStr(randArray) << endl
                             << "Index 0: " << solutions[0] << endl
                             << "Index " << index << ": " << solutions[index] << endl;
                        abort();
                    }
                    
                    _allRunningTimes[index].emplace_back(randArraySize, 
                                (runningEnd.tv_sec - runningStart.tv_sec) * 1e9 + 
                                (runningEnd.tv_nsec - runningStart.tv_nsec));
                }

            }
            
            // Print the summary
            PrintSummary();
            cout << "Finished running " << _name << "..." << endl;
        }
    
    protected:
    
        /**
         * Generate random array
         * 
         * :param N             Size of the array
         **/
        virtual vector<T> GenerateRandomArray(long N=0) const {
            vector<T> ret;
            if (!N) {
                N = rand() % _maxSize + _minSize;
            }
            
            for (auto i = 0; i < N; i++) {
                auto value = rand() % _maxRange + _minRange;
                ret.emplace_back(value);
            }
            
            return ret;
        }
    
        /**
         * Check if the two return values are the same
         * 
         * Normally the first value is the static one.
         */
        virtual bool IsEqual(R& v1, R& v2) const {
            return v1 == v2;
        }
        
    private:
    
        string _name;
        long _minSize;
        long _maxSize;
        T _minRange;
        T _maxRange;
        long _numAlgorithms;
        vector<pair<vector<T>, R>> _allTestCases;
        vector<function<R(vector<T>)>> _allAlgorithms;
        vector<vector<RunningTimePairType>> _allRunningTimes;
    
        template<typename V>
        string ToStr(V& v) {
            stringstream ss;
            ss << v;
            return ss.str();
        }
        
        template<typename V>
        string ToStr(vector<V>& v) {
            stringstream ss;
            ss << "[";
            for (auto i = 0; i < v.size(); i++) {
                ss << v[i];
                
                if (i != v.size() - 1) {
                    ss << ", ";
                }
            }
            
            ss << "]";
            return ss.str();
        }
        
        /**
         * Average of the data
         * 
         * :param stat          Data
         * :param op            Function operator implemented on each data point
         * :return Average of the data with the operator
         */
        double Average(const vector<pair<long, long>>& stat, function<double(long, long)> op) const
        {
            long count = stat.size();
            double sum = 0.0;
            
            for (auto&& p : stat) 
            {
                sum += op(get<0>(p), get<1>(p));
            }
            
            return sum/count;
        }
        
        /**
         * R square
         * 
         * :param stat          Data
         * :param opOnX         Function operator on x only
         * :return R sqaure of the data based on the operator
         */
        double RSqaure(const vector<RunningTimePairType>& stat, function<double(double)> opOnX) const 
        {
            auto meanX = Average(stat, [&](long x, long y) { return opOnX(x); });
            auto meanY = Average(stat, [&](long x, long y) { return y; });
            auto meanXsq = Average(stat, [&](long x, long y) { return opOnX(x) * opOnX(x); });
            auto meanYsq = Average(stat, [&](long x, long y) { return double(y) * double(y); });
            auto meanXY = Average(stat, [&](long x, long y) { return opOnX(x) * y; });
            auto r = (meanXY - meanX * meanY)/sqrt((meanXsq - meanX * meanX) * (meanYsq - meanY * meanY));            
            return r * r * 100.0;
        }
        
        void PrintSummary() const
        {
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << setw(2) << " " << "|"
                 << setw(6) << "logN" << "|"
                 << setw(6) << "N" << "|"
                 << setw(6) << "NlogN" << "|"
                 << setw(6) << "N*N" << "|"
                 << endl;
                 
            for (auto i = 0; i < _numAlgorithms; i++) {
                cout << setw(2) << i << "|"
                     << setprecision(4) << RSqaure(_allRunningTimes[i], [&](double x) { return log(x); }) << "%|"
                     << setprecision(4) << RSqaure(_allRunningTimes[i], [&](double x) { return x; }) << "%|"
                     << setprecision(4) << RSqaure(_allRunningTimes[i], [&](double x) { return x * log(x); }) << "%|"
                     << setprecision(4) << RSqaure(_allRunningTimes[i], [&](double x) { return x * x; }) << "%|"
                     << endl;
                
                // for (auto&& p : _allRunningTimes[i]) {
                //     cout << get<0>(p) << "," << get<1>(p) << endl;
                // }
            }
            
        }
};

#endif