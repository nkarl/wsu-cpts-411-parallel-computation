#include "game_of_life.hpp"

using std::cout;
using std::queue;
using std::string;

bool game_of_life()
{
    queue<TestResult> TestReport;
    static Test<void> test_master;

    TestHeader(test_master, -2, "PRINT A TEST STRING");
    test_master.isPassed = [&]() {
        cout << "This test prints its own name: " << test_master.Name << "\n";
        return true;
    }();
    recordTestResult(test_master, TestReport);

    TestHeader(test_master, -1, "PRINT THE TEST SERIAL");
    test_master.isPassed = [&]() {
        cout << "This test prints its own serial: " << test_master.Serial << "\n";
        return true;
    }();
    recordTestResult(test_master, TestReport);

    return true;
}
