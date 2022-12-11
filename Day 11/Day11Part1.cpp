#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Monkey.h"

using namespace std;

// congratulations we have made it to double digits


// ASSUMPTIONS:
// operations are either multiplication or addition
// tests are always "divisible by"
// first value in operation is always "old"

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int result = 0;



    cout << "result: " << result << endl;

    return 0;
}