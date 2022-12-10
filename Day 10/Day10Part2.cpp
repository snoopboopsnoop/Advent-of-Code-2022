#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// congratulations we have made it to double digits

// Define bounds of screen, 
const int screenWidth = 40;
const int screenHeight = 6;

// increments cycle and x row
void pulse(vector<char>& screen, int& cycle, int& x, int& check) {
    if(cycle-1 >= x-1 && cycle-1 <= x+1) {
        screen[cycle-1] = '#';
    }
    if(cycle == check) {
        x += screenWidth;
        check += screenWidth;
    }
    cycle++;
}   

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    // need all this shit for some reason
    string line;
    string command;
    int result = 0;
    int x = 1;
    int cycle = 1;
    int val = 0;
    int check = screenWidth;
    
    vector<char> screen = vector<char> (screenWidth*screenHeight, '.');

    while(getline(in, line)) {
        istringstream sin(line);
        sin >> command;
        // pulse, nothing else changes
        if(command == "noop") {
            pulse(screen, cycle, x, check);
        }
        // pulse and also change x by val
        else if(command == "addx") {
            sin >> val;
            pulse(screen, cycle, x, check);
            pulse(screen, cycle, x, check);
            x += val;
        }
    }

    // print screen
    for(size_t i = 0; i < screen.size(); ++i) {
        if(i % screenWidth == 0 && i != 0) cout << endl;
        cout << screen[i];
    }
    cout << endl;

    return 0;
}