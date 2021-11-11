#include "unit_a.hpp"

using std::cout;
using std::queue;
using std::string;

bool run_unit_a()
{
    queue<TestResult> TestReport;
    static Test<void> test_master;

    TestHeader(test_master, -2, "PRINT A TEST STRING");
    test_master.isPassed = [&]() {
        cout << "This test prints its own name: " << test_master.Name;
        return true;
    }();
    recordTestResult(test_master, TestReport);

    TestHeader(test_master, -1, "PRINT THE TEST SERIAL");
    test_master.isPassed = [&]() {
        cout << "This test prints its own serial: " << test_master.Serial;
        return true;
    }();
    recordTestResult(test_master, TestReport);

    return true;
}