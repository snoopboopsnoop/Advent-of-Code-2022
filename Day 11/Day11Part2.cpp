#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Monkey2.h"

using namespace std;

// https://www.youtube.com/watch?v=sAAqV1Jcfgs me after writing this code


// ASSUMPTIONS:
// operations are either multiplication or addition
// tests are always "divisible by"
// first value in operation is always "old"
// input format is the same always

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    long long result = 0;
    const int rounds = 10000;
    long long mostActive = 0;
    long long secondMostActive = 0;

    while(getline(in, line)) {
        // starting items
        getline(in, line);
        istringstream sin(line);
        string trash;
        int item;
        vector<int> items;
        sin >> trash >> trash;
        while(sin) {
            sin >> item >> trash;
            items.push_back(item);
        }

        // operation
        getline(in, line);
        sin = istringstream(line);
        vector<string> operationVals;
        string operation;
        sin >> trash >> trash >> trash >> trash;
        sin >> operation;
        operationVals.push_back(operation);
        sin >> operation;
        operationVals.push_back(operation);  
        
        // test
        getline(in, line);
        sin = istringstream(line);
        int testVal;
        sin >> trash >> trash >> trash >> testVal;
        Monkey::getEEAAO() *= testVal;

        // true/false monkeys
        getline(in, line);
        int testTrue;
        sin = istringstream(line);
        // >> if >> true: >> throw >> to >> monkey >> num
        sin >> trash >> trash >> trash >> trash >> trash >> testTrue;

        getline(in, line);
        int testFalse;
        sin = istringstream(line);
        // >> if >> true: >> throw >> to >> monkey >> num
        sin >> trash >> trash >> trash >> trash >> trash >> testFalse;

        Monkey(items, operationVals, testVal, testTrue, testFalse);

        getline(in, line);
    }

    cout << Monkey::getEEAAO() << endl;

    // for(int i = 0; i < rounds; i++) {
    // for(size_t i = 0; i < Monkey::getMonkeys().size(); ++i) {
    //     cout << "monkey " << i << endl;
    //     Monkey::getMonkeys()[i].print();
    //     cout << endl;
    // }
    // for(Monkey& monkey : Monkey::getMonkeys()) {
    //     monkey.inspect();
    // }
    for(int i = 0; i < rounds; i++) {
        for(size_t i = 0; i < Monkey::getMonkeys().size(); ++i) {
            //cout << "Monkey " << i << ": " << endl;
            Monkey::getMonkeys()[i].inspect();
            //cout << endl;
        }
    }
    for(size_t i = 0; i < Monkey::getMonkeys().size(); ++i) {
        int inspectionCount = Monkey::getMonkeys()[i].getInspectionCount();
        cout << "monkey " << i  << " inspected items "
            << inspectionCount << " times" << endl;
        if(inspectionCount > mostActive)  {
            secondMostActive = mostActive;
            mostActive = inspectionCount;
            
        }
        else if(inspectionCount > secondMostActive) secondMostActive = inspectionCount;
    }

    result = mostActive * secondMostActive;

    cout << "result: " << result << endl;

    return 0;
}