#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// don't worry i took a C++1 course so this time it'll go better

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int greatest = 0;
    
    // process each elf and check if biggest
    while(in) {
        int currElf = 0;
        while(getline(in, line)) {
            if(line == "") break;
            currElf += stoi(line);
        }
        if(currElf > greatest) greatest = currElf;
    }

    cout << "Best Elf is carrying " << greatest << " Calories of food" << endl;

    return 0;
}
