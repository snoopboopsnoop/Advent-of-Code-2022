#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Monkey.h"

using namespace std;

// https://www.youtube.com/watch?v=sAAqV1Jcfgs me after writing this code
// i'm monkey beedubs is oogway

// ASSUMPTIONS:
// operations are either multiplication or addition
// tests are always "divisible by"
// first value in operation is always "old"
// input format is always the same

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    const int kRounds = 20;
    int mostActive = 0;
    int secondMostActive = 0;

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

        // monkey
        Monkey(items, operationVals, testVal, testTrue, testFalse);

        getline(in, line);
    }

    // run monkey inspection for kRounds
    for(int i = 0; i < kRounds; i++) {
        for(size_t i = 0; i < Monkey::getMonkeys().size(); ++i) {
            Monkey::getMonkeys()[i].inspect();
        }
    }
    // check inspection counts of each monkey, get the 2 most active ones
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
    cout << "Level of monkey business after "
        << kRounds << " rounds of stuff-slinging simian shenanigans: "
        << mostActive * secondMostActive << endl;

    return 0;
}