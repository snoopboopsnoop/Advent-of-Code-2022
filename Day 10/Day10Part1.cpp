#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// congratulations we have made it to double digits

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    string command;
    int result = 0;
    int x = 1;
    int cycle = 1;
    int val = 0;

    const int firstCheck = 20;
    int check = firstCheck;
    const int nextCheck = 40;

    while(getline(in, line)) {
        istringstream sin(line);
        sin >> command;
        if(command == "noop") {
            // check if cycle is interesting
            if(cycle == check) {
                cout << "value at cycle " << check << " = " << x << endl;
                result += check * x;
                check += nextCheck;
            }
            cycle++;
        }
        else if(command == "addx") {
            sin >> val;
            // check if this or next cycle is interesting, doesn't matter since x won't change between cycles
            if(cycle <= check && cycle+2 > check) {
                cout << "value at cycle " << check << " = " << x << endl;
                result += check * x;
                check += nextCheck;
            }
            cycle += 2;
            x += val;
        }
    }
    cout << "Sum of signal strengths: " << result << endl;

    return 0;
}