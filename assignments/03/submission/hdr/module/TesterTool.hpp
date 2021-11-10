#ifndef TESTERTOOL_HPP
#define TESTERTOOL_HPP

#include <iostream>
#include <queue>
#include <tuple>

using std::cerr;
using std::clog;
using std::cout;
using std::string;

typedef std::tuple<int, string, bool> TestResult;

// dummy template
template<typename X>
struct Test : std::false_type {};

// specialization template
template<>
struct Test<void> : std::true_type {
    int    Serial;
    string Name;
    bool   isPassed;
    Test() : Serial{0}, Name{""} {}
};

// Print the info of the test unit
template<typename X>
void TestHeader(Test<X> &test, int id, const string &name)
{
    test.Serial = id;
    test.Name   = name;
    cout << "\n-----------------------------------------------------------------------";
    cout << "\nSERIAL#" << test.Serial << ": " << test.Name;
    cout << "\n-----------------------------------------------------------------------"
         << std::endl;
}

// finalize the test result into a queue of tuples
template<typename X>
void recordTestResult(Test<X> &test_master, std::queue<TestResult> &Results)
{
    Results.push({test_master.Serial, test_master.Name,
                  [&]() { return (test_master.isPassed) ? true : false; }()});
}

// Check if the test passes or fails.
template<typename X>
void errCheck(bool isFailed, Test<X> &test)
{

    clog << "\n-----------------------------------------------------------------------";
    if (isFailed) {
        string err_msg = "\n-ERROR--> FAILED ON TEST #"
                         + std::to_string(test.Serial)
                         + "<"
                         + test.Name
                         + ">\n";
        throw err_msg;
    }
    else {
        clog << "\n--OK!--> PASSED\n"
             << std::endl;
    }
}
// Exception handling wrapper for each test.
template<typename X>
void errCatch(bool isFailed, Test<X> &test)
{
    try {
        errCheck(isFailed, test);
    } catch (string err_msg) {
        cerr << err_msg;
    }
}

#endif